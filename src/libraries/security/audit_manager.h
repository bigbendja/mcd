#ifndef AUDIT_MANAGER_H
#define AUDIT_MANAGER_H

#include <string>
#include <vector>
#include <mutex>

namespace mc_security {

    // Enumeración para los niveles de criticidad de los eventos
    enum class EventLevel {
        INFO,       // Informativo
        WARNING,    // Alerta
        CRITICAL    // Crítico, requiere atención inmediata
    };

    // Clase para gestionar el sistema de auditoría y eventos de seguridad
    class AuditManager {
    public:
        /**
         * Registra un evento de auditoría con un nivel de criticidad específico.
         * @param event Descripción del evento.
         * @param level Nivel del evento (INFO, WARNING, CRITICAL).
         */
        static void logEvent(const std::string& event, EventLevel level);

        /**
         * Analiza los eventos registrados para identificar patrones anómalos.
         */
        static void analyzePatterns();

        /**
         * Recupera una lista de eventos críticos para revisión.
         * @return Vector de eventos marcados como CRITICAL.
         */
        static std::vector<std::string> getCriticalEvents();

    private:
        // Contenedor seguro para almacenar los eventos de auditoría
        static std::vector<std::string> eventLog;

        // Mutex para proteger el acceso concurrente a eventLog
        static std::mutex logMutex;
    };

} // namespace mc_security

#endif // AUDIT_MANAGER_H
