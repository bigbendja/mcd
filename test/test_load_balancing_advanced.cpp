#include "load_balancing_advanced.h"
#include <cassert>
#include <iostream>

void testAddServerNode() {
    LoadBalancingAdvanced lb;
    assert(lb.addServerNode("node1", "192.168.1.1", 100));
    assert(lb.addServerNode("node2", "192.168.1.2", 150));
    std::cout << "testAddServerNode passed." << std::endl;
}

void testRemoveServerNode() {
    LoadBalancingAdvanced lb;
    lb.addServerNode("node1", "192.168.1.1", 100);
    assert(lb.removeServerNode("node1"));
    assert(!lb.removeServerNode("node2"));
    std::cout << "testRemoveServerNode passed." << std::endl;
}

void testBalanceByLeastConnections() {
    LoadBalancingAdvanced lb;
    lb.addServerNode("node1", "192.168.1.1", 100);
    lb.addServerNode("node2", "192.168.1.2", 150);
    lb.updateServerLoad("node1", 0.3, 0.2, 10);
    lb.updateServerLoad("node2", 0.3, 0.2, 5);

    auto node = lb.balanceByLeastConnections();
    assert(node.id == "node2");
    std::cout << "testBalanceByLeastConnections passed." << std::endl;
}

void testHealthCheck() {
    LoadBalancingAdvanced lb;
    lb.addServerNode("node1", "192.168.1.1", 100);
    lb.updateServerLoad("node1", 0.95, 0.9, 80);
    lb.healthCheck();
    assert(lb.getServerNodes()[0].health_status == "degraded");
    std::cout << "testHealthCheck passed." << std::endl;
}

int main() {
    testAddServerNode();
    testRemoveServerNode();
    testBalanceByLeastConnections();
    testHealthCheck();
    std::cout << "All tests for LoadBalancingAdvanced passed." << std::endl;
    return 0;
}
