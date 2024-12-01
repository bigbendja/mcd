// autonomous_scaling_adjustment_advanced.cpp
// Implementación Mejorada del Módulo de Escalado y Ajuste Autónomo Avanzado para MC++

#include "autonomous_scaling_adjustment_advanced.h"
#include <algorithm>
#include <iostream>
#include <cmath>
#include <unordered_map>

AutonomousScalingAdjustment::AutonomousScalingAdjustment(const ScalingPolicy& policy)
    : scaling_policy(policy) {}

// Añadir un nodo escalable al sistema
bool AutonomousScalingAdjustment::addNode(const std::string& id, const std::string& ip, int max_connections) {
    ScalableNode new_node = {id, ip, 0.0f, 0.0f, 0, max_connections, "healthy", std::chrono::steady_clock::now(), 0.0};
    scalable_nodes[id] = new_node; // Uso de unordered_map para acceso eficiente
    logOperation("ADD_SCALABLE_NODE", id, {{"max_connections", static_cast<float>(max_connections)}});
    return true;
}

// Remover un nodo escalable del sistema
bool AutonomousScalingAdjustment::removeNode(const std::string& id) {
    if (scalable_nodes.erase(id)) {
        logOperation("REMOVE_SCALABLE_NODE", id, {});
        return true;
    }
    return false;
}

// Actualizar la carga de un nodo específico
bool AutonomousScalingAdjustment::updateNodeLoad(const std::string& id, float cpu_load, float memory_load, int active_connections) {
    auto it = scalable_nodes.find(id);
    if (it != scalable_nodes.end()) {
        auto& node = it->second;
        node.cpu_load = cpu_load;
        node.memory_load = memory_load;
        node.active_connections = active_connections;
        node.health_status = determineNodeHealth(node);
        logOperation("UPDATE_NODE_LOAD", id, {
            {"cpu_load", cpu_load}, 
            {"memory_load", memory_load}, 
            {"active_connections", static_cast<float>(active_connections)}
        });
        return true;
    }
    return false;
}

// Determinar el estado de salud del nodo
std::string AutonomousScalingAdjustment::determineNodeHealth(const ScalableNode& node) const {
    if (node.cpu_load > 0.95 || node.memory_load > 0.95) {
        return "degraded";
    } else if (node.active_connections < node.max_connections * 0.1) {
        return "underutilized";
    } else if (node.latency > 500.0) {
        return "overloaded";
    }
    return "healthy";
}

// Escalado hacia arriba si el nodo supera el umbral de carga
bool AutonomousScalingAdjustment::scaleUpIfNeeded() {
    bool scaled = false;
    for (auto& [id, node] : scalable_nodes) {
        if (node.health_status == "degraded" &&
            std::chrono::steady_clock::now() - node.last_scaling_action >= std::chrono::seconds(scaling_policy.cooldown_period)) {
            node.max_connections += static_cast<int>(node.max_connections * 0.5);
            node.last_scaling_action = std::chrono::steady_clock::now();
            node.health_status = "scaling_up";
            logOperation("SCALE_UP", id, {{"new_max_connections", static_cast<float>(node.max_connections)}});
            scaled = true;
        }
    }
    return scaled;
}

// Escalado hacia abajo si el nodo reduce la carga
bool AutonomousScalingAdjustment::scaleDownIfNeeded() {
    bool scaled = false;
    for (auto& [id, node] : scalable_nodes) {
        if (node.health_status == "underutilized" &&
            node.cpu_load < scaling_policy.scale_down_threshold &&
            node.memory_load < scaling_policy.scale_down_threshold) {
            node.max_connections = std::max(static_cast<int>(node.max_connections * 0.7), 10);
            node.last_scaling_action = std::chrono::steady_clock::now();
            node.health_status = "scaling_down";
            logOperation("SCALE_DOWN", id, {{"new_max_connections", static_cast<float>(node.max_connections)}});
            scaled = true;
        }
    }
    return scaled;
}

// Escalado predictivo basado en análisis de patrones históricos
void AutonomousScalingAdjustment::predictiveScaling(const std::unordered_map<std::string, float>& predicted_loads) {
    for (auto& [id, node] : scalab                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                e] : scalable_nodes) {
        status.push_back(node);
    }
    return status;
}

// Ajustar la política de escalado en tiempo real
bool AutonomousScalingAdjustment::adjustScalingPolicy(float new_scale_up_threshold, float new_scale_down_threshold, int new_cooldown_period) {
    scaling_policy.scale_up_threshold = new_scale_up_threshold;
    scaling_policy.scale_down_threshold = new_scale_down_threshold;
    scaling_policy.cooldown_period = new_cooldown_period;
    logOperation("ADJUST_SCALING_POLICY", "", {
        {"scale_up_threshold", new_scale_up_threshold},
        {"scale_down_threshold", new_scale_down_threshold},
        {"cooldown_period", static_cast<float>(new_cooldown_period)}
    });
    return true;
}

// Registro de operación para auditoría
void AutonomousScalingAdjustment::logOperation(const std::string& operation, const std::string& node_id, const std::map<std::string, float>& details) const {
    std::cout << "Operation: " << operation << ", Node ID: " << node_id << ", Details: ";
    for (const auto& [key, value] : details) {
        std::cout << key << ": " << value << " ";
    }
    std::cout << std::endl;
}
