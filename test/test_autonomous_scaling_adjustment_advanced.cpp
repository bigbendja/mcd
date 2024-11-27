#include "autonomous_scaling_adjustment_advanced.h"
#include <cassert>
#include <iostream>

void testAddNode() {
    ScalingPolicy policy = {0.8, 0.4, 300};
    AutonomousScalingAdjustment asa(policy);
    assert(asa.addNode("node1", "192.168.1.1", 100));
    assert(asa.addNode("node2", "192.168.1.2", 150));
    std::cout << "testAddNode passed." << std::endl;
}

void testScaleUpIfNeeded() {
    ScalingPolicy policy = {0.8, 0.4, 300};
    AutonomousScalingAdjustment asa(policy);
    asa.addNode("node1", "192.168.1.1", 100);
    asa.updateNodeLoad("node1", 0.95, 0.8, 90);
    assert(asa.scaleUpIfNeeded());
    std::cout << "testScaleUpIfNeeded passed." << std::endl;
}

void testPredictiveScaling() {
    ScalingPolicy policy = {0.8, 0.4, 300};
    AutonomousScalingAdjustment asa(policy);
    asa.addNode("node1", "192.168.1.1", 100);
    asa.updateNodeLoad("node1", 0.9, 0.7, 90);
    asa.predictiveScaling();
    auto nodes = asa.getCurrentNodeStatus();
    assert(nodes[0].max_connections > 100);
    std::cout << "testPredictiveScaling passed." << std::endl;
}

int main() {
    testAddNode();
    testScaleUpIfNeeded();
    testPredictiveScaling();
    std::cout << "All tests for AutonomousScalingAdjustment passed." << std::endl;
    return 0;
}
