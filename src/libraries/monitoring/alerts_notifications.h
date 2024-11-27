#ifndef ALERTS_NOTIFICATIONS_H
#define ALERTS_NOTIFICATIONS_H

#include <string>
#include <map>
#include <vector>
#include <ctime>
#include <mutex>

/**
 * @brief Representa una alerta en el sistema de notificaciones.
 */
struct Alert {
    std::string id;                        // Identificador único de la alerta.
    time_t timestamp;                      // Marca de tiempo de creación.
    std::string type;                      // Tipo de alerta (CPU, Memory, Disk, etc.).
    std::string severity;                  // Nivel de severidad (INFO, WARNING, CRITICAL).
    std::string message;                   // Mensaje descriptivo de la alerta.
    std::map<std::string, std::string> details; // Detalles adicionales de la alerta.
    bool acknowledged;                     // Estado de reconocimiento de la alerta.
};

/**
 * @brief Clase principal para gestionar alertas y notificaciones en el sistema.
 */
class AlertsNotifications {
public:
    /**
     * @brief Constructor por defecto.
     */
    AlertsNotifications();

    /**
     * @brief Crea una nueva alerta y envía notificaciones a los canales configurados.
     * @param type Tipo de alerta.
     * @param severity Nivel de severidad de la alerta.
     * @param message Mensaje descriptivo de la alerta.
     * @param details Detalles adicionales de la alerta (opcional).
     * @return true si la alerta se creó con éxito, false en caso contrario.
     */
    bool createAlert(const std::string& type, const std::string& severity, const std::string& message,
                     const std::map<std::string, std::string>& details = {});

    /**
     * @brief Reconoce una alerta existente.
     * @param alert_id Identificador de la alerta a reconocer.
     * @return true si la alerta fue reconocida con éxito, false en caso contrario.
     */
    bool acknowledgeAlert(const std::string& alert_id);

    /**
     * @brief Reintenta enviar notificaciones para alertas no reconocidas.
     */
    void retryUnacknowledgedAlerts();

    /**
     * @brief Limpia alertas viejas o reconocidas según las políticas configuradas.
     * @return Número de alertas eliminadas.
     */
    int cleanupOldAlerts();

    /**
     * @brief Genera un reporte de alertas agrupado por tipo y severidad.
     * @return Un mapa anidado con el conteo de alertas por tipo y severidad.
     */
    std::map<std::string, std::map<std::string, int>> generateAlertReport() const;

    /**
     * @brief Configura un canal de notificación con una nueva dirección.
     * @param channel Canal a configurar (email, sms, webhook).
     * @param destination Nueva dirección para el canal.
     * @return true si la configuración fue exitosa, false en caso contrario.
     */
    bool configureNotificationChannel(const std::string& channel, const std::string& destination);

    /**
     * @brief Busca alertas según un término en el mensaje o en los detalles.
     * @param query Término de búsqueda.
     * @return Vector de alertas que coinciden con la búsqueda.
     */
    std::vector<Alert> searchAlerts(const std::string& query) const;

    /**
     * @brief Analiza la frecuencia de alertas dentro de una ventana de tiempo específica.
     * @param window Ventana de tiempo en segundos.
     * @return Mapa con el conteo de alertas por nivel de severidad dentro de la ventana.
     */
    std::map<std::string, int> alertFrequencyAnalysis(int window) const;

    /**
     * @brief Activa la escalada automática para alertas críticas no reconocidas.
     */
    void automaticEscalation();

private:
    std::vector<Alert> activeAlerts;             // Lista de alertas activas.
    std::map<std::string, std::string> notificationChannels; // Canales de notificación (email, sms, webhook).
    std::vector<std::string> severityLevels;    // Niveles de severidad permitidos.
    std::map<std::string, int> alertPolicy;     // Políticas de alertas (reintentos, intervalos, etc.).

    mutable std::mutex alertMutex;              // Mutex para sincronizar acceso a alertas.
    mutable std::mutex notificationMutex;       // Mutex para sincronizar notificaciones.

    /**
     * @brief Envía notificaciones para una alerta específica.
     * @param alert La alerta para la cual se enviarán notificaciones.
     */
    void sendNotification(const Alert& alert);

    /**
     * @brief Registra operaciones internas del sistema.
     * @param operation Nombre de la operación realizada.
     * @param details Detalles adicionales sobre la operación.
     */
    void logOperation(const std::string& operation, const std::map<std::string, std::string>& details) const;
};

#endif // ALERTS_NOTIFICATIONS_H
