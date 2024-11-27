#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <string>
#include <map>
#include <vector>

/**
 * @brief Registra un nuevo usuario con credenciales seguras.
 * 
 * @param username Nombre único del usuario.
 * @param password Contraseña del usuario.
 * @param user_data Información adicional del usuario (opcional).
 * @return true si el registro es exitoso, false de lo contrario.
 * @throws std::runtime_error si el usuario ya existe.
 */
bool RegisterUser(const std::string& username, const std::string& password, const std::map<std::string, std::string>& user_data = {});

/**
 * @brief Autentica a un usuario validando su contraseña.
 * 
 * @param username Nombre único del usuario.
 * @param password Contraseña proporcionada para autenticación.
 * @return true si la autenticación es exitosa, false de lo contrario.
 */
bool AuthenticateUser(const std::string& username, const std::string& password);

/**
 * @brief Genera un token de sesión encriptado con tiempo de expiración.
 * 
 * @param username Nombre del usuario para el cual se genera el token.
 * @param expiration Tiempo de expiración del token en segundos.
 * @return Token de sesión en formato encriptado.
 */
std::string GenerateSessionToken(const std::string& username, int expiration = 3600);

/**
 * @brief Verifica la validez y expiración de un token de sesión.
 * 
 * @param token Token de sesión a verificar.
 * @return true si el token es válido, false de lo contrario.
 */
bool VerifySessionToken(const std::string& token);

/**
 * @brief Asigna un rol a un usuario.
 * 
 * @param username Nombre del usuario.
 * @param role Rol a asignar.
 * @return true si el rol se asigna correctamente, false de lo contrario.
 */
bool AssignRole(const std::string& username, const std::string& role);

/**
 * @brief Verifica si un usuario tiene un rol específico.
 * 
 * @param username Nombre del usuario.
 * @param role Rol a verificar.
 * @return true si el usuario tiene el rol, false de lo contrario.
 */
bool HasRole(const std::string& username, const std::string& role);

/**
 * @brief Revoca un rol asignado a un usuario.
 * 
 * @param username Nombre del usuario.
 * @param role Rol a revocar.
 * @return true si el rol se revoca correctamente, false de lo contrario.
 */
bool RevokeRole(const std::string& username, const std::string& role);

/**
 * @brief Registra un intento de acceso para propósitos de auditoría.
 * 
 * @param username Nombre del usuario que intenta acceder.
 * @param action Acción realizada (e.g., "LOGIN", "PASSWORD_CHANGE").
 * @param success true si la acción fue exitosa, false de lo contrario.
 * @return true si el registro se realiza correctamente.
 */
bool RecordAccess(const std::string& username, const std::string& action, bool success);

/**
 * @brief Verifica el número de intentos de inicio de sesión en un periodo de tiempo.
 * 
 * @param username Nombre del usuario.
 * @param max_attempts Máximo número de intentos permitidos.
 * @param time_window Periodo de tiempo en segundos para verificar intentos.
 * @return true si el número de intentos está dentro del límite permitido, false de lo contrario.
 */
bool CheckLoginAttempts(const std::string& username, int max_attempts = 5, int time_window = 300);

/**
 * @brief Genera un token temporal para operaciones de verificación de identidad.
 * 
 * @param username Nombre del usuario.
 * @param purpose Propósito del token (e.g., "PASSWORD_RESET").
 * @param expiration Tiempo de expiración del token en segundos.
 * @return Token temporal en formato encriptado.
 */
std::string GenerateTemporaryToken(const std::string& username, const std::string& purpose, int expiration = 900);

/**
 * @brief Verifica la validez y propósito de un token temporal.
 * 
 * @param token Token temporal a verificar.
 * @param purpose Propósito esperado del token.
 * @return true si el token es válido y coincide con el propósito, false de lo contrario.
 */
bool VerifyTemporaryToken(const std::string& token, const std::string& purpose);

#endif // AUTHENTICATION_H
