#include "performance_analysis_advanced.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>

// Captura un punto de datos de rendimiento del sistema
bool PerformanceAnalysis::capturePerformanceData() {
    PerformanceDataPoint data_point = {
        .timestamp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()),
        .cpu_usage = getCPUUsage(),
        .memory_usage = getMemoryUsage(),
        .disk_io = getDiskIO(),
        .network_io = getNetworkIO(),
        .response_time = measureResponseTime()
    };

    performance_data.push_back(data_point);
    logOperation("CAPTURE_PERFORMANCE_DATA", data_point);
    enforceRetentionPolicy();
    return true;
}

// Aplica la política de retención para eliminar datos antiguos
int PerformanceAnalysis::enforceRetentionPolicy() {
    auto current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    int initial_size = performance_data.size();

    performance_data.remove_if([&](const PerformanceDataPoint& data_point) {
        return (current_time - data_point.timestamp) > current_config.retention_period;
    });

    int removed_count = initial_size - performance_data.size();
    logOperation("ENFORCE_RETENTION_POLICY", removed_count);
    return removed_count;
}

// Genera un informe resumido de rendimiento
std::map<std::string, float> PerformanceAnalysis::generatePerformanceReport() {
    std::map<std::string, float> report = {
        {"average_cpu_usage", calculateAverage([](const auto& dp) { return dp.cpu_usage; })},
        {"peak_cpu_usage", calculatePeak([](const auto& dp) { return dp.cpu_usage; })},
        {"average_memory_usage", calculateAverage([](const auto& dp) { return dp.memory_usage; })},
        {"peak_memory_usage", calculatePeak([](const auto& dp) { return dp.memory_usage; })}
    };

    logOperation("GENERATE_PERFORMANCE_REPORT", report);
    return report;
}

// Identifica cuellos de botella en el sistema
std::list<std::string> PerformanceAnalysis::identifyBottlenecks() {
    std::list<std::string> bottlenecks;
    for (const auto& dp : performance_data) {
        if (dp.cpu_usage > current_config.alert_thresholds.at("cpu")) bottlenecks.push_back("High CPU Usage");
        if (dp.memory_usage > current_config.alert_thresholds.at("memory")) bottlenecks.push_back("High Memory Usage");
        if (dp.disk_io > current_config.alert_thresholds.at("disk_io")) bottlenecks.push_back("High Disk I/O");
        if (dp.network_io > current_config.alert_thresholds.at("network_io")) bottlenecks.push_back("High Network I/O");
        if (dp.response_time > current_config.alert_thresholds.at("response_time")) bottlenecks.push_back("High Response Time");
    }
    logOperation("IDENTIFY_BOTTLENECKS", bottlenecks);
    return bottlenecks;
}

// Genera alertas en caso de superar umbrales
std::list<std::string> PerformanceAnalysis::generateAlerts() {
    std::list<std::string> alerts;
    for (const auto& dp : performance_data) {
        if (dp.cpu_usage > current_config.alert_thresholds.at("cpu")) alerts.push_back("CPU usage exceeded threshold");
        if (dp.memory_usage > current_config.alert_thresholds.at("memory")) alerts.push_back("Memory usage exceeded threshold");
        if (dp.disk_io > current_config.alert_thresholds.at("disk_io")) alerts.push_back("Disk I/O exceeded threshold");
        if (dp.network_io > current_config.alert_thresholds.at("network_io")) alerts.push_back("Network I/O exceeded threshold");
        if (dp.response_time > current_config.alert_thresholds.at("response_time")) alerts.push_back("Response time exceeded threshold");
    }
    if (!alerts.empty()) sendAlert("Performance Alerts", alerts);
    logOperation("GENERATE_ALERTS", alerts);
    return alerts;
}

// Realiza análisis de tendencias
std::map<std::string, float> PerformanceAnalysis::trendAnalysis(int duration) {
    auto current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto relevant_data = filterPerformanceData([&](const auto& dp) {
        return (current_time - dp.timestamp) <= duration;
    });

    std::map<std::string, float> trends = {
        {"cpu_trend", calculateTrend(relevant_data, [](const auto& dp) { return dp.cpu_usage; })},
        {"memory_trend", calculateTrend(relevant_data, [](const auto& dp) { return dp.memory_usage; })}
    };

    logOperation("TREND_ANALYSIS", duration, trends);
    return trends;
}

// Ajusta la configuración del análisis
bool PerformanceAnalysis::adjustAnalysisConfig(const AnalysisConfig& new_config) {
    current_config = new_config;
    logOperation("ADJUST_ANALYSIS_CONFIG", new_config);
    return true;
}

// Optimización automática basada en el análisis
void PerformanceAnalysis::autoOptimize() {
    auto report = generatePerformanceReport();
    auto bottlenecks = identifyBottlenecks();

    if (std::find(bottlenecks.begin(), bottlenecks.end(), "High CPU Usage") != bottlenecks.end()) applyCPUOptimization();
    if (std::find(bottlenecks.begin(), bottlenecks.end(), "High Memory Usage") != bottlenecks.end()) applyMemoryOptimization();

    logOperation("AUTO_OPTIMIZE", bottlenecks);
}

// Métodos privados de utilidad
float PerformanceAnalysis::calculateAverage(const std::function<float(const PerformanceDataPoint&)>& metric) const {
    if (performance_data.empty()) return 0.0f;
    float total = std::accumulate(performance_data.begin(), performance_data.end(), 0.0f,
        [&](float sum, const auto& dp) { return sum + metric(dp); });
    return total / performance_data.size();
}

float PerformanceAnalysis::calculatePeak(const std::function<float(const PerformanceDataPoint&)>& metric) const {
    if (performance_data.empty()) return 0.0f;
    return std::max_element(performance_data.begin(), performance_data.end(),
        [&](const auto& a, const auto& b) { return metric(a) < metric(b); })->cpu_usage;
}

std::list<PerformanceDataPoint> PerformanceAnalysis::filterPerformanceData(const std::function<bool(const PerformanceDataPoint&)>& filter) const {
    std::list<PerformanceDataPoint> filtered_data;
    std::copy_if(performance_data.begin(), performance_data.end(), std::back_inserter(filtered_data), filter);
    return filtered_data;
}
