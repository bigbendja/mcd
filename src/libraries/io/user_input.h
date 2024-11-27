#ifndef USER_INPUT_H
#define USER_INPUT_H

#include <string>
#include <vector>

/**
 * @brief Módulo de entrada de usuario para MC++.
 * 
 * Este módulo proporciona funciones avanzadas para recopilar datos del usuario con validaciones 
 * integradas para tipos específicos como números, fechas, contraseñas, etc.
 */

/**
 * @brief Solicita al usuario ingresar un texto libre.
 * 
 * @param prompt Mensaje para mostrar al usuario.
 * @param required Indica si la entrada es obligatoria.
 * @param max_length Longitud máxima permitida (-1 para sin límite).
 * @return Cadena ingresada por el usuario.
 * @throws std::runtime_error si se viola una regla de validación.
 */
std::string GET_INPUT(const std::string& prompt, bool required = true, int max_length = -1);

/**
 * @brief Solicita al usuario ingresar un número entero.
 * 
 * @param prompt Mensaje para mostrar al usuario.
 * @param min_value Valor mínimo permitido.
 * @param max_value Valor máximo permitido.
 * @return Número entero ingresado por el usuario.
 * @throws std::runtime_error si se viola una regla de validación.
 */
int GET_INT(const std::string& prompt, int min_value = -2147483648, int max_value = 2147483647);

/**
 * @brief Solicita al usuario ingresar un número de punto flotante.
 * 
 * @param prompt Mensaje para mostrar al usuario.
 * @param min_value Valor mínimo permitido.
 * @param max_value Valor máximo permitido.
 * @return Número de punto flotante ingresado por el usuario.
 * @throws std::runtime_error si se viola una regla de validación.
 */
float GET_FLOAT(const std::string& prompt, float min_value = -1e38, float max_value = 1e38);

/**
 * @brief Solicita al usuario seleccionar una opción de una lista.
 * 
 * @param prompt Mensaje para mostrar al usuario.
 * @param options Vector de opciones válidas.
 * @return Opción seleccionada por el usuario.
 * @throws std::runtime_error si la opción ingresada no es válida.
 */
std::string GET_OPTION(const std::string& prompt, const std::vector<std::string>& options);

/**
 * @brief Solicita al usuario confirmar una acción.
 * 
 * @param prompt Mensaje para mostrar al usuario.
 * @param default_yes Valor predeterminado si el usuario no ingresa respuesta.
 * @return `true` si el usuario confirma, `false` en caso contrario.
 */
bool GET_CONFIRMATION(const std::string& prompt, bool default_yes = true);

/**
 * @brief Solicita al usuario ingresar una contraseña.
 * 
 * @param prompt Mensaje para mostrar al usuario.
 * @param min_length Longitud mínima requerida.
 * @param max_length Longitud máxima permitida.
 * @param require_special Indica si se requieren caracteres especiales.
 * @return Contraseña ingresada por el usuario.
 * @throws std::runtime_error si se viola una regla de validación.
 */
std::string GET_PASSWORD(const std::string& prompt, int min_length = 8, int max_length = 128, bool require_special = true);

/**
 * @brief Solicita al usuario ingresar una dirección de correo electrónico.
 * 
 * @param prompt Mensaje para mostrar al usuario.
 * @return Correo electrónico ingresado por el usuario.
 * @throws std::runtime_error si el formato no es válido.
 */
std::string GET_EMAIL(const std::string& prompt);

/**
 * @brief Solicita al usuario ingresar una fecha.
 * 
 * @param prompt Mensaje para mostrar al usuario.
 * @param format Formato esperado de la fecha (por defecto: "YYYY-MM-DD").
 * @return Fecha ingresada por el usuario.
 * @throws std::runtime_error si el formato no es válido.
 */
std::string GET_DATE(const std::string& prompt, const std::string& format = "YYYY-MM-DD");

/**
 * @brief Solicita al usuario ingresar un número de teléfono.
 * 
 * @param prompt Mensaje para mostrar al usuario.
 * @param country_code Código de país esperado (por defecto: "+1").
 * @return Número de teléfono ingresado por el usuario.
 * @throws std::runtime_error si el formato no es válido.
 */
std::string GET_PHONE_NUMBER(const std::string& prompt, const std::string& country_code = "+1");

#endif // USER_INPUT_H
