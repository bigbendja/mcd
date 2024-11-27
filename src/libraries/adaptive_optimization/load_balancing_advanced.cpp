#include "load_balancing_advanced.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>

LoadBalancingAdvanced::LoadBalancingAdvanced() : round_robin_index(0) {}

LoadBalancingAdvanced::~LoadBalancingAdvanced() {}

ServerNode* LoadBalancingAdvanced::findNodeById(const std::string& id) {
    for (auto& node : server_nodes) {
        if (node.id == id) return &node;
    }
    return nullptr;
}

void LoadBalancingAdvanced::logOperation(const std::string& operation, const std::map<std::string, std::string>& details) const {
    std::cout << "Operation: " << operation << "\n";
    for (const auto& [key, value] : details) {
        std::cout << " - " << key << ": " << value << "\n";
    }
}

bool LoadBalancingAdvanced::addServerNode(const std::string& id, const std::string& ip, int max_connections, float weight) {
    ServerNode new_node(id, ip, max_connections, weight);
    server_nodes.push_back(new_node);
    logOperation("ADD_SERVER_NODE", {{"id", id}, {"ip", ip}, {"max_connections", std::to_string(max_connections)}, {"weight", std::to_string(weight)}});
    return true;
}

bool LoadBalancingAdvanced::removeServerNode(const std::string& id) {
    auto it = std::remove_if(server_nodes.begin(), server_nodes.end(), [&id](const ServerNode& node) {
        return node.id == id;
    });
    bool removed = (it != server_nodes.end());
    server_nodes.erase(it, server_nodes.end());
    logOperation("REMOVE_SERVER_NODE", {{"id", id}});
    return removed;
}

bool LoadBalancingAdvanced::updateServerMetrics(const std::string& id, float cpu_load, float memory_load, int active_connections, float latency) {
    ServerNode* node = findNodeById(id);
    if (node) {
        node->cpu_load = cpu_load;
        node->memory_load = memory_load;
        node->active_connections = active_connections;
        node->latency = latency;
        node->health_status = (cpu_load > 0.9 || memory_load > 0.9 || active_connections >= node->max_connections) ? "degraded" : "healthy";
        logOperation("UPDATE_SERVER_METRICS", {{"id", id}, {"cpu_load", std::to_string(cpu_load)}, {"memory_load", std::to_string(memory_load)}, {"latency", std::to_string(latency)}});
        return true;
    }
    return false;
}

ServerNode LoadBalancingAdvanced::balanceByWeightedLeastConnections() {
    auto it = std::min_element(server_nodes.begin(), server_nodes.end(), [](const ServerNode& a, const ServerNode& b) {
        return a.health_status == "healthy" && (a.active_connections / a.weight) < (b.active_connections / b.weight);
    });
    if (it == server_nodes.end() || it->health_status != "healthy") {
        throw std::runtime_error("No available servers for load balancing.");
    }
    logOperation("BALANCE_BY_WEIGHTED_LEAST_CONNECTIONS", {{"selected_node", it->id}});
    return *it;
}

ServerNode LoadBalancingAdvanced::balanceByDynamicRoundRobin() {
    auto available_nodes = server_nodes.size();
    if (available_nodes == 0) throw std::runtime_error("No available servers for load balancing.");
    ServerNode& selected_node = server_nodes[round_robin_index % available_nodes];
    round_robin_index = (round_robin_index + 1) % available_nodes;
    logOperation("BALANCE_BY_DYNAMIC_ROUND_ROBIN", {{"selected_node", selected_node.id}});
    return selected_node;
}

ServerNode LoadBalancingAdvanced::balanceByLeastLatency() {
    auto it = std::min_element(server_nodes.begin(), server_nodes.end(), [](const ServerNode& a, const ServerNode& b) {
        return a.health_status == "healthy" && a.latency < b.latency;
    });
    if (it == server_nodes.end() || it->health_status != "healthy") {
        throw std::runtime_error("No available servers for load balancing.");
    }
    logOperation("BALANCE_BY_LEAST_LATENCY", {{"selected_node", it->id}});
    return *it;
}

void LoadBalancingAdvanced::healthMonitor() {
    for (auto& node : server_nodes) {
        if (node.cpu_load > 0.95 || node.memory_load > 0.95 || node.latency > 500.0) {
            node.health_status = "degraded";
        } else if (node.active_connections < node.max_connections * 0.1) {
            node.health_status = "warm-up";
        } else {
            node.health_status = "healthy";
        }
        logOperation("HEALTH_MONITOR", {{"id", node.id}, {"health_status", node.health_status}});
    }
}

ServerNode LoadBalancingAdvanced::smartBalance() {
    healthMonitor();
    return balanceByWeightedLeastConnections();
}
