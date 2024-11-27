#include "logging_audit.h"
#include <algorithm>
#include <ctime>
#include <json/json.h> // Asumimos que se incluye una librería JSON

LoggingAudit::LoggingAudit() {
    // Configuración inicial de retención
    retentionPolicy = {{"max_logs", "10000"}, {"retention_period", "2592000"}}; // 30 días en segundos
}

bool LoggingAudit::addLog(const std::string& level, const std::string& source, const std::string& message,
                          const std::map<std::string, std::string>& details) {
    if (std::find(log_levels.begin(), log_levels.end(), level) == log_levels.end()) {
        return false; // Nivel no válido
    }

    LogEntry logEntry{std::to_string(logEntries.size()), std::time(nullptr), level, source, message, details};
    logEntries.push_back(logEntry);

    // Retención de logs según la política
    if (logEntries.size() > maxLogs) {
        enforceRetentionPolicy();
    }

    logOperation("ADD_LOG", {{"level", level}, {"source", source}, {"message", message}});
    return true;
}

std::vector<LogEntry> LoggingAudit::filterLogs(const std::string& level, time_t start_time, time_t end_time) const {
    std::vector<LogEntry> filteredLogs;
    for (const auto& log : logEntries) {
        if (log.level == level && log.timestamp >= start_time && log.timestamp <= end_time) {
            filteredLogs.push_back(log);
        }
    }
    logOperation("FILTER_LOGS", {{"level", level}});
    return filteredLogs;
}

std::map<std::string, std::map<std::string, int>> LoggingAudit::generateLogReport() const {
    std::map<std::string, std::map<std::string, int>> report;
    for (const auto& log : logEntries) {
        report[log.level][log.source]++;
    }
    logOperation("GENERATE_LOG_REPORT", {});
    return report;
}

bool LoggingAudit::recordAuditEvent(const std::string& action, const std::string& user,
                                    const std::map<std::string, std::string>& details) {
    auditTrail.push_back({{"action", action}, {"user", user}, {"timestamp", std::to_string(std::time(nullptr))}});
    logOperation("RECORD_AUDIT_EVENT", {{"action", action}, {"user", user}});
    return true;
}

std::vector<std::map<std::string, std::string>> LoggingAudit::generateAuditReport(const std::string& user,
                                                                                  time_t start_time, time_t end_time) const {
    std::vector<std::map<std::string, std::string>> filteredAudit;
    for (const auto& entry : auditTrail) {
        time_t timestamp = std::stoi(entry.at("timestamp"));
        if ((user.empty() || entry.at("user") == user) && timestamp >= start_time && timestamp <= end_time) {
            filteredAudit.push_back(entry);
        }
    }
    logOperation("GENERATE_AUDIT_REPORT", {{"user", user}});
    return filteredAudit;
}

int LoggingAudit::enforceRetentionPolicy() {
    time_t currentTime = std::time(nullptr);
    size_t initialLogCount = logEntries.size();
    logEntries.erase(std::remove_if(logEntries.begin(), logEntries.end(),
                                    [currentTime, this](const LogEntry& log) {
                                        return (currentTime - log.timestamp) > retentionPeriod;
                                    }),
                     logEntries.end());
    int logsRemoved = initialLogCount - logEntries.size();

    size_t initialAuditCount = auditTrail.size();
    auditTrail.erase(std::remove_if(auditTrail.begin(), auditTrail.end(),
                                    [currentTime, this](const std::map<std::string, std::string>& entry) {
                                        return (currentTime - std::stoi(entry.at("timestamp"))) > retentionPeriod;
                                    }),
                     auditTrail.end());
    int auditsRemoved = initialAuditCount - auditTrail.size();

    logOperation("ENFORCE_RETENTION_POLICY", {{"logs_removed", std::to_string(logsRemoved)}, {"audits_removed", std::to_string(auditsRemoved)}});
    return logsRemoved + auditsRemoved;
}

std::string LoggingAudit::exportLogsAndAudit() const {
    Json::Value data;
    for (const auto& log : logEntries) {
        Json::Value logJson;
        logJson["id"] = log.id;
        logJson["timestamp"] = static_cast<Json::Int64>(log.timestamp);
        logJson["level"] = log.level;
        logJson["source"] = log.source;
        logJson["message"] = log.message;
        Json::Value detailsJson;
        for (const auto& detail : log.details) {
            detailsJson[detail.first] = detail.second;
        }
        logJson["details"] = detailsJson;
        data["logs"].append(logJson);
    }

    for (const auto& entry : auditTrail) {
        Json::Value auditJson;
        for (const auto& field : entry) {
            auditJson[field.first] = field.second;
        }
        data["audit_trail"].append(auditJson);
    }

    Json::StreamWriterBuilder writer;
    logOperation("EXPORT_LOGS_AND_AUDIT", {});
    return Json::writeString(writer, data);
}

std::vector<LogEntry> LoggingAudit::searchLogs(const std::string& query) const {
    std::vector<LogEntry> results;
    for (const auto& log : logEntries) {
        if (log.message.find(query) != std::string::npos) {
            results.push_back(log);
        }
    }
    logOperation("SEARCH_LOGS", {{"query", query}});
    return results;
}

std::map<std::string, int> LoggingAudit::eventFrequencyAnalysis(int window) const {
    std::map<std::string, int> frequencyMap;
    time_t currentTime = std::time(nullptr);
    for (const auto& log : logEntries) {
        if ((currentTime - log.timestamp) <= window) {
            frequencyMap[log.level]++;
        }
    }
    logOperation("EVENT_FREQUENCY_ANALYSIS", {{"window", std::to_string(window)}});
    return frequencyMap;
}

void LoggingAudit::triggerAutomaticAlerts() {
    for (const auto& log : filterLogs("ERROR")) {
        // Aquí se puede implementar una función de envío de alertas.
        logOperation("TRIGGER_AUTOMATIC_ALERT", {{"source", log.source}, {"message", log.message}});
    }
}

void LoggingAudit::logOperation(const std::string& operation, const std::map<std::string, std::string>& details) const {
    // Esta función simula el registro de operaciones internas, proporcionando un seguimiento de auditoría.
    // Implementación de ejemplo que podría registrar en un archivo o en un sistema de monitorización.
}
