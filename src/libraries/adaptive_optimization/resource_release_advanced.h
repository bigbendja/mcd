#ifndef RESOURCE_RELEASE_ADVANCED_H
#define RESOURCE_RELEASE_ADVANCED_H

#include <string>
#include <vector>
#include <map>

class ResourceReleaseAdvanced {
public:
    struct Resource {
        std::string id;                   // Identificador único del recurso
        std::string type;                 // Tipo de recurso: memory, disk, etc.
        float usage;                      // Uso actual en porcentaje (0.0 a 1.0)
        float threshold;                  // Umbral máximo permitido
        long last_used_timestamp;         // Marca de tiempo del último uso
        std::vector<float> usage_history; // Historial de uso para análisis predictivo
    };

    ResourceReleaseAdvanced();
    ~ResourceReleaseAdvanced();

    // Gestión de recursos
    bool addResource(const std::string& id, const std::string& type, float threshold);
    bool removeResource(const std::string& id);
    bool updateResourceUsage(const std::string& id, float usage);

    // Liberación de recursos
    int releaseUnusedResources(long threshold_time);
    bool releaseMemoryIfOverloaded(float critical_threshold = 0.9f);
    int releaseResourcesByType(const std::string& resource_type, float priority_threshold);
    bool releaseDiskSpace(float usage_limit = 0.8f);

    // Análisis y ajuste
    void adjustResourceThresholds(float factor);
    void analyzeUsagePatterns();

    // Monitoreo y limpieza automática
    void monitorAndAutoRelease(int interval);

private:
    std::vector<Resource> system_resources;

    // Métodos auxiliares
    Resource* findResourceById(const std::string& id);
    float calculateTotalUsage(const std::string& type) const;
    void logOperation(const std::string& operation, const std::map<std::string, std::string>& details) const;
    long getCurrentTimestamp() const;
    void cleanTemporaryStorage() const;
};

#endif // RESOURCE_RELEASE_ADVANCED_H
