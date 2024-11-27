#ifndef OUTPUT_FORMATTING_H
#define OUTPUT_FORMATTING_H

#include <string>
#include <vector>
#include <map>

/**
 * @file output_formatting.h
 * @brief Módulo para formateo y visualización de datos en MC++.
 *
 * Este módulo proporciona funciones para formatear e imprimir texto, tablas, JSON y
 * otros tipos de datos en la consola, con soporte para mensajes coloridos, progreso en tiempo real,
 * y formatos personalizados de números y fechas.
 */

/** Impresión básica */

/**
 * @brief Imprime texto simple con un final opcional.
 * @param text Texto a imprimir.
 * @param end Carácter final (por defecto: "\n").
 */
void PRINT(const std::string& text, const std::string& end = "\n");

/**
 * @brief Imprime texto formateado con placeholders reemplazados por valores.
 * @param template_text Texto con placeholders en el formato "{placeholder}".
 * @param values Mapa de placeholders y sus valores correspondientes.
 */
void PRINT_FORMATTED(const std::string& template_text, const std::map<std::string, std::string>& values);

/** Impresión de Tablas y JSON */

/**
 * @brief Imprime una tabla con encabezados opcionales.
 * @param data Datos de la tabla como vector de vectores de cadenas.
 * @param headers Encabezados opcionales de las columnas.
 * @param padding Espaciado entre columnas (por defecto: 2).
 */
void PRINT_TABLE(const std::vector<std::vector<std::string>>& data, const std::vector<std::string>& headers = {}, int padding = 2);

/**
 * @brief Imprime un mapa como JSON con indentación.
 * @param data Mapa de datos a imprimir.
 * @param indent Nivel de indentación (por defecto: 4).
 */
void PRINT_JSON(const std::map<std::string, std::string>& data, int indent = 4);

/** Mensajes de Estado */

/**
 * @brief Imprime un mensaje de error en rojo.
 * @param message Mensaje de error.
 */
void PRINT_ERROR(const std::string& message);

/**
 * @brief Imprime un mensaje de advertencia en amarillo.
 * @param message Mensaje de advertencia.
 */
void PRINT_WARNING(const std::string& message);

/**
 * @brief Imprime un mensaje de éxito en verde.
 * @param message Mensaje de éxito.
 */
void PRINT_SUCCESS(const std::string& message);

/**
 * @brief Imprime un mensaje de log con diferentes niveles de severidad.
 * @param message Mensaje a registrar.
 * @param level Nivel de severidad (por defecto: "INFO").
 */
void PRINT_LOG(const std::string& message, const std::string& level = "INFO");

/** Formateo Avanzado */

/**
 * @brief Imprime una barra de progreso en tiempo real.
 * @param current Valor actual del progreso.
 * @param total Valor total que indica el 100%.
 * @param bar_length Longitud de la barra de progreso (por defecto: 30).
 * @throws std::invalid_argument Si el total es menor o igual a 0.
 */
void PRINT_PROGRESS(int current, int total, int bar_length = 30);

/**
 * @brief Formatea un valor como moneda.
 * @param amount Cantidad a formatear.
 * @param currency_symbol Símbolo de la moneda (por defecto: "$").
 * @param decimal_places Número de decimales (por defecto: 2).
 * @return Cadena formateada como moneda.
 */
std::string FORMAT_CURRENCY(float amount, const std::string& currency_symbol = "$", int decimal_places = 2);

/**
 * @brief Formatea una fecha según un formato especificado.
 * @param date Fecha en formato "YYYY-MM-DD".
 * @param format Formato deseado (por defecto: "YYYY-MM-DD").
 * @return Fecha formateada como cadena.
 * @throws std::invalid_argument Si el formato de la fecha no es válido.
 */
std::string FORMAT_DATE(const std::string& date, const std::string& format = "YYYY-MM-DD");

/**
 * @brief Formatea un número con decimales y separadores opcionales.
 * @param number Número a formatear.
 * @param decimal_places Número de decimales (por defecto: 2).
 * @param use_commas Usar separadores de miles (por defecto: true).
 * @return Número formateado como cadena.
 */
std::string FORMAT_NUMBER(float number, int decimal_places = 2, bool use_commas = true);

#endif // OUTPUT_FORMATTING_H
