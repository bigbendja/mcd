#include "resource_release_advanced.h"
#include <iostream>
#include <algorithm>
#include <chrono>
#include <future> // Para paralelización
#include <cmath>  // Para cálculos estadísticos

ResourceReleaseAdvanced::ResourceReleaseAdvanced() {}

ResourceReleaseAdvanced::~ResourceReleaseAdvanced() {}

bool ResourceReleaseAdvanced::addResource(const std::string& id, const std::string& type, float threshold) {
    Resource new_resource = {id, type, 0.0, threshold, getCurrentTimestamp(), {}};
    system_resources.push_back(new_resource);
    logOperation("ADD_RESOURCE", {{"id", id}, {"type", type}, {"threshold", std::to_string(threshold)}});
    return true;
}

bool ResourceReleaseAdvanced::removeResource(const std::string& id) {
    auto it = std::remove_if(system_resources.begin(), system_resources.end(), [&id](const Resource& resource) {
        return resource.id == id;
    });
    bool removed = (it != system_resources.end());
    system_resources.erase(it, system_resources.end());
    logOperation("REMOVE_RESOURCE", {{"id", id}});
    return removed;
}

bool ResourceReleaseAdvanced::updateResourceUsage(const std::string& id, float usage) {
    Resource* resource = findResourceById(id);
    if (resource) {
        resource->usage = usage;
        resource->last_used_timestamp = getCurrentTimestamp();
        resource->usage_history.push_back(usage); // Almacena métricas de uso para análisis
        logOperation("UPDATE_RESOURCE_USAGE", {{"id", id}, {"usage", std::to_string(usage)}});
        return true;
    }
    return false;
}

int ResourceReleaseAdvanced::releaseUnusedResources(long threshold_time) {
    int released_count = 0;
    std::vector<std::future<void>> tasks; // Para paralelización
    for (auto& resource : system_resources) {
        tasks.push_back(std::async(std::launch::async, [&]() {
            if (resource.usage < resource.threshold &&
                (getCurrentTimestamp() - resource.last_used_timestamp > threshold_time)) {
                resource.usage = 0.0;
                logOperation("RELEASE_UNUSED_RESOURCE", {{"id", resource.id}, {"type", resource.type}});
                released_count++;
            }
        }));
    }
    for (auto& task : tasks) {
        task.get(); // Espera la finalización de cada tarea
    }
    return released_count;
}

bool ResourceReleaseAdvanced::releaseMemoryIfOverloaded(float critical_threshold) {
    float total_memory_usage = calculateTotalUsage("memory");
    if (total_memory_usage > critical_threshold) {
        for (auto& resource : system_resources) {
            if (resource.type == "memory") {
                resource.usage = 0.0;
                logOperation("RELEASE_MEMORY", {{"id", resource.id}});
            }
        }
        return true;
    }
    return false;
}

int ResourceReleaseAdvanced::releaseResourcesByType(const std::string& resource_type, float priority_threshold) {
    int released_count = 0;
    for (auto& resource : system_resources) {
        if (resource.type == resource_type && resource.usage > priority_threshold) {
            resource.usage = 0.0;
            released_count++;
            logOperation("RELEASE_RESOURCES_BY_TYPE", {{"id", resource.id}, {"type", resource.type}});
        }
    }
    return released_count;
}

bool ResourceReleaseAdvanced::releaseDiskSpace(float usage_limit) {
    float disk_usage = calculateTotalUsage("disk");
    if (disk_usage > usage_limit) {
        logOperation("RELEASE_DISK_SPACE", {{"usage_limit", std::to_string(usage_limit)}});
        cleanTemporaryStorage(); // Limpieza específica de disco
        return true;
    }
    return false;
}

void ResourceReleaseAdvanced::adjustResourceThresholds(float factor) {
    for (auto& resource : system_resources) {
        if (resource.usage > resource.threshold) {
            resource.threshold *= factor;
            resource.threshold = std::min(resource.threshold, 1.0f); // Limita al 100%
            logOperation("ADJUST_RESOURCE_THRESHOLDS", {{"id", resource.id}, {"new_threshold", std::to_string(resource.threshold)}});
        }
    }
}

void ResourceReleaseAdvanced::analyzeUsagePatterns() {
    for (auto& resource : system_resources) {
        if (!resource.usage_history.empty()) {
            float average_usage = std::accumulate(resource.usage_history.begin(), resource.usage_history.end(), 0.0f) /
                                  resource.usage_history.size();
            logOperation("ANALYZE_USAGE_PATTERNS", {{"id", resource.id}, {"average_usage", std::to_string(average_usage)}});
        }
    }
}

void ResourceReleaseAdvanced::monitorAndAutoRelease(int interval) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(interval));
        releaseUnusedResources(300);
        releaseMemoryIfOverloaded();
        releaseDiskSpace();
        analyzeUsagePatterns(); // Integra análisis de patrones
        logOperation("MONITOR_AND_AUTO_RELEASE", {{"interval", std::to_string(interval)}});
    }
}

// Función auxiliar para calcular el uso total de un tipo de recurso
float ResourceReleaseAdvanced::calculateTotalUsage(const std::string& type) const {
    float total = 0.0;
    for (const auto& resource : system_resources) {
        if (resource.type == type) {
            total += resource.usage;
        }
    }
    return total;
}

// Función auxiliar para encontrar un recurso por su ID
Resource* ResourceReleaseAdvanced::findResourceById(const std::string& id) {
    for (auto& resource : system_resources) {
        if (resource.id == id) return &resource;
    }
    return nullptr;
}

// Función auxiliar para registrar operaciones de log
void ResourceReleaseAdvanced::logOperation(const std::string& operation, const std::map<std::string, std::string>& details) const {
    std::cout << "Operation: " << operation << "\n";
    for (const auto& [key, value] : details) {
        std::cout << " - " << key << ": " << value << "\n";
    }
}

// Función auxiliar para obtener el timestamp actual
long ResourceReleaseAdvanced::getCurrentTimestamp() const {
    return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
}

// Limpieza de almacenamiento temporal
void ResourceReleaseAdvanced::cleanTemporaryStorage() const {
    logOperation("CLEAN_TEMPORARY_STORAGE", {});
    std::cout << "Temporary storage cleaned.\n";
}
