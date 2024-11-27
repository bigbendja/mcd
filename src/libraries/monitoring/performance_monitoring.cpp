#include "performance_monitoring.h"
#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>
#include <atomic>

PerformanceMonitoring::PerformanceMonitoring() {
    // Inicialización de umbrales de alerta por tipo de métrica
    alertThresholds = {{"cpu", 0.9}, {"memory", 0.85}, {"disk", 0.8}, {"network", 0.75}};
    stopMonitoringFlag = false; // Inicialización de la bandera de interrupción
}

bool PerformanceMonitoring::addPerformanceMetric(const std::string& id, const std::string& type) {
    if (alertThresholds.find(type) == alertThresholds.end()) {
        logOperation("ADD_PERFORMANCE_METRIC_FAILED", {{"id", id}, {"reason", "invalid type"}});
        return false;
    }
    PerformanceMetric newMetric = {id, type, 0.0, 0.0, 1.0, 0.0, std::time(nullptr)};
    performanceMetrics.push_back(newMetric);
    logOperation("ADD_PERFORMANCE_METRIC", {{"id", id}, {"type", type}});
    return true;
}

bool PerformanceMonitoring::updateMetricUsage(const std::string& id, float usage) {
    for (auto& metric : performanceMetrics) {
        if (metric.id == id) {
            metric.usage = usage;
            metric.peak_usage = std::max(metric.peak_usage, usage);
            metric.min_usage = std::min(metric.min_usage, usage);
            metric.average_usage = (metric.average_usage * 0.9) + (usage * 0.1); // Promedio ponderado
            metric.timestamp = std::time(nullptr);
            logOperation("UPDATE_METRIC_USAGE", {{"id", id}, {"usage", std::to_string(usage)}});
            return true;
        }
    }
    logOperation("UPDATE_METRIC_USAGE_FAILED", {{"id", id}});
    return false;
}

std::vector<std::map<std::string, std::string>> PerformanceMonitoring::checkAlertThresholds() {
    std::vector<std::map<std::string, std::string>> alerts;
    for (const auto& metric : performanceMetrics) {
        if (metric.usage > alertThresholds[metric.type]) {
            alerts.push_back({{"id", metric.id}, {"type", metric.type}, {"usage", std::to_string(metric.usage)}});
            logOperation("ALERT_THRESHOLD_EXCEEDED", {{"id", metric.id}, {"type", metric.type}, {"usage", std::to_string(metric.usage)}});
        }
    }
    return alerts;
}

void PerformanceMonitoring::startMonitoring(int interval) {
    stopMonitoringFlag = false;
    std::thread monitoringThread([this, interval]() {
        while (!stopMonitoringFlag) {
            std::this_thread::sleep_for(std::chrono::seconds(interval));
            auto alerts = checkAlertThresholds();
            if (!alerts.empty()) {
                logOperation("PERFORMANCE_ALERTS", {{"alert_count", std::to_string(alerts.size())}});
            }
            logOperation("MONITORING_CYCLE_COMPLETE", {{"interval", std::to_string(interval)}});
        }
    });
    monitoringThread.detach(); // Permitir que el hilo corra independientemente
}

void PerformanceMonitoring::stopMonitoring() {
    stopMonitoringFlag = true; // Señal para detener el monitoreo
    logOperation("STOP_MONITORING", {});
}

std::map<std::string, std::map<std::string, float>> PerformanceMonitoring::generatePerformanceReport() {
    std::map<std::string, std::map<std::string, float>> report;
    for (const auto& metric : performanceMetrics) {
        report[metric.id] = {
            {"average_usage", metric.average_usage},
            {"peak_usage", metric.peak_usage},
            {"min_usage", metric.min_usage},
            {"last_usage", metric.usage},
            {"last_timestamp", static_cast<float>(metric.timestamp)}
        };
    }
    logOperation("GENERATE_PERFORMANCE_REPORT", {});
    return report;
}

void PerformanceMonitoring::logOperation(const std::string& operation, const std::map<std::string, std::string>& details) {
    std::cout << "Operation: " << operation;
    for (const auto& [key, value] : details) {
        std::cout << " | " << key << ": " << value;
    }
    std::cout << std::endl;
}
