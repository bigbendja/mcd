#include "autonomous_scaling_adjustment_advanced.h"
#include <chrono>
#include <iostream>

void performanceTestScalingAdjustment() {
    ScalingPolicy policy = {0.8, 0.4, 300};
    AutonomousScalingAdjustment asa(policy);

    // Añadir 200 nodos
    for (int i = 0; i < 200; ++i) {
        asa.addNode("node" + std::to_string(i), "192.168.1." + std::to_string(i), 100);
    }

    // Simular carga en los nodos
    for (int i = 0; i < 200; ++i) {
        asa.updateNodeLoad("node" + std::to_string(i), 0.85, 0.75, 80);
    }

    auto start = std::chrono::high_resolution_clock::now();
    asa.scaleUpIfNeeded();
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Scale-up operation time: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;
}

int main() {
    performanceTestScalingAdjustment();
    return 0;
}
