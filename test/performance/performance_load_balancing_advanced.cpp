#include "load_balancing_advanced.h"
#include <chrono>
#include <iostream>

void performanceTestLoadBalancing() {
    LoadBalancingAdvanced lb;

    // Añadir 100 nodos
    for (int i = 0; i < 100; ++i) {
        lb.addServerNode("node" + std::to_string(i), "192.168.1." + std::to_string(i), 100);
    }

    // Simular miles de conexiones
    for (int i = 0; i < 100; ++i) {
        lb.updateServerLoad("node" + std::to_string(i), 0.5, 0.4, i * 10);
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        lb.balanceByLeastConnections();
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time for 1000 balance operations: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;
}

int main() {
    performanceTestLoadBalancing();
    return 0;
}
