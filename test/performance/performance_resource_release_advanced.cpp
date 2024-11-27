#include "resource_release_advanced.h"
#include <chrono>
#include <iostream>

void performanceTestResourceRelease() {
    ResourceReleaseAdvanced rr;

    // Añadir 500 recursos
    for (int i = 0; i < 500; ++i) {
        rr.addResource("res" + std::to_string(i), "memory", 0.8);
    }

    // Simular uso de recursos
    for (int i = 0; i < 500; ++i) {
        rr.updateResourceUsage("res" + std::to_string(i), 0.7);
    }

    auto start = std::chrono::high_resolution_clock::now();
    int released = rr.releaseUnusedResources(300);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Released " << released << " resources in " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;
}

int main() {
    performanceTestResourceRelease();
    return 0;
}
