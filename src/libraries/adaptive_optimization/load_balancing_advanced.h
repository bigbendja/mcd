#ifndef LOAD_BALANCING_ADVANCED_H
#define LOAD_BALANCING_ADVANCED_H

#include <string>
#include <vector>
#include <map>

// Estructura para representar un nodo de servidor con métricas extendidas
struct ServerNode {
    std::string id;
    std::string ip;
    float cpu_load;
    float memory_load;
    int active_connections;
    int max_connections;
    float latency;       // Latencia promedio en ms
    std::string health_status; // "healthy", "degraded", "offline", "warm-up"
    float weight;        // Peso para balanceo basado en prioridades

    ServerNode(const std::string& id, const std::string& ip, int max_connections, float weight = 1.0)
        : id(id), ip(ip), cpu_load(0.0), memory_load(0.0), active_connections(0),
          max_connections(max_connections), latency(0.0), health_status("healthy"), weight(weight) {}
};

// Clase principal que encapsula la lógica de balanceo avanzado
class LoadBalancingAdvanced {
private:
    std::vector<ServerNode> server_nodes;
    size_t round_robin_index;
    
    ServerNode* findNodeById(const std::string& id);
    void logOperation(const std::string& operation, const std::map<std::string, std::string>& details) const;

public:
    LoadBalancingAdvanced();
    ~LoadBalancingAdvanced();

    bool addServerNode(const std::string& id, const std::string& ip, int max_connections, float weight = 1.0);
    bool removeServerNode(const std::string& id);
    bool updateServerMetrics(const std::string& id, float cpu_load, float memory_load, int active_connections, float latency);

    ServerNode balanceByWeightedLeastConnections();
    ServerNode balanceByDynamicRoundRobin();
    ServerNode balanceByLeastLatency();

    void healthMonitor();
    ServerNode smartBalance();
};

#endif // LOAD_BALANCING_ADVANCED_H
