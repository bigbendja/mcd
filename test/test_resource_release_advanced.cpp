#include "resource_release_advanced.h"
#include <cassert>
#include <iostream>

void testAddResource() {
    ResourceReleaseAdvanced rr;
    assert(rr.addResource("res1", "memory", 0.8));
    assert(rr.addResource("res2", "cpu", 0.9));
    std::cout << "testAddResource passed." << std::endl;
}

void testReleaseUnusedResources() {
    ResourceReleaseAdvanced rr;
    rr.addResource("res1", "memory", 0.8);
    rr.updateResourceUsage("res1", 0.5);
    int released = rr.releaseUnusedResources(300);
    assert(released == 1);
    std::cout << "testReleaseUnusedResources passed." << std::endl;
}

void testReleaseMemoryIfOverloaded() {
    ResourceReleaseAdvanced rr;
    rr.addResource("res1", "memory", 0.8);
    rr.updateResourceUsage("res1", 0.9);
    assert(rr.releaseMemoryIfOverloaded(0.85));
    std::cout << "testReleaseMemoryIfOverloaded passed." << std::endl;
}

int main() {
    testAddResource();
    testReleaseUnusedResources();
    testReleaseMemoryIfOverloaded();
    std::cout << "All tests for ResourceReleaseAdvanced passed." << std::endl;
    return 0;
}
