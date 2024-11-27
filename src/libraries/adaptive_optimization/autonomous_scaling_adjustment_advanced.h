// autonomous_scaling_adjustment_advanced.h
// Librería MC++ 1.1 - Módulo de Escalado y Ajuste Autónomo Avanzado

#ifndef AUTONOMOUS_SCALING_ADJUSTMENT_ADVANCED_H
#define AUTONOMOUS_SCALING_ADJUSTMENT_ADVANCED_H

#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <unordered_map>

// Estructura para representar un nodo de servidor escalable
struct ScalableNode {
    std::string id;
    std::string ip;
    float cpu_load; // Carga de CPU del nodo
    float memory_load; // Carga de memoria del nodo
    int active_connections; // Conexiones activas
    int max_connections; // Máximo de conexiones permitidas
    std::string health_status; // "healthy", "degraded", "scaling_up", "scaling_down"
    std::chrono::steady_clock::time_point last_scaling_action; // Última acción de escalado
    float latency; // Latencia promedio (en ms)
};

// Políticas de escalado configurables
struct ScalingPolicy {
    float scale_up_threshold; // Umbral para escalar hacia arriba
    float scale_down_threshold; // Umbral para escalar hacia abajo
    int cooldown_period; // Tiempo mínimo entre escalados (en segundos)
};

// Clase de administración de escalado y ajuste autónomo de nodos
class AutonomousScalingAdjustment {
public:
    // Constructor con configuración de política de escalado
    AutonomousScalingAdjustment(const ScalingPolicy& policy);

    // Añadir y remover nodos escalables
    bool addNode(const std::string& id, const std::string& ip, int max_connections);
    bool removeNode(const std::string& id);

    // Actualizar carga y métricas en un nodo específico
    bool updateNodeLoad(const std::string& id, float cpu_load, float memory_load, int active_connections);

    // Escalado automático basado en condiciones de carga
    bool scaleUpIfNeeded();
    bool scaleDownIfNeeded();

    // Ajuste dinámico de política de escalado
    bool adjustScalingPolicy(float new_scale_up_threshold, float new_scale_down_threshold, int new_cooldown_period);

    // Ajuste dinámico de tamaño de nodo según la carga
    bool dynamicNodeSizeAdjustment(const std::string& node_id, float target_cpu_load, float target_memory_load);

    // Escalado predictivo basado en patrones históricos de carga
    void predictiveScaling(const std::unordered_map<std::string, float>& predicted_loads);

    // Monitoreo y ajuste continuo de nodos
    void monitorAndAdjust(int interval);

    // Obtener el estado actual de todos los nodos escalables
    std::vector<ScalableNode> getCurrentNodeStatus() const;

private:
    // Lista de nodos escalables y política de escalado actual
    std::unordered_map<std::string, ScalableNode> scalable_nodes; // Cambiado a unordered_map para acceso eficiente
    ScalingPolicy scaling_policy;

    // Métodos internos
    ScalableNode* findNode(const std::string& id);
    std::string determineNodeHealth(const ScalableNode& node) const;
    void logOperation(const std::string& operation, const std::string& node_id, const std::map<std::string, float>& details) const;
};

#endif // AUTONOMOUS_SCALING_ADJUSTMENT_ADVANCED_H
