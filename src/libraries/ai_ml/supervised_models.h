#ifndef SUPERVISED_MODELS_H
#define SUPERVISED_MODELS_H

#include <string>
#include <map>
#include <list>
#include <stdexcept>

/**
 * Clase SupervisedModel en MC++: Proporciona una estructura avanzada para modelos de aprendizaje supervisado.
 */
class SupervisedModel {
public:
    /**
     * Crea un modelo supervisado con un tipo específico y parámetros de hiperparámetros.
     * @param modelType Tipo de modelo, como "regresión", "clasificación", etc.
     * @param hyperparams Mapa de hiperparámetros para ajustar el modelo.
     * @return Una instancia de SupervisedModel configurada.
     */
    static SupervisedModel create(const std::string& modelType, const std::map<std::string, float>& hyperparams);

    /**
     * Entrena el modelo con un conjunto de datos y etiquetas.
     * @param data Conjunto de datos de entrada, donde cada mapa representa una muestra.
     * @param labels Lista de etiquetas correspondientes a cada muestra de datos.
     * @return Verdadero si el entrenamiento fue exitoso.
     * @throws std::invalid_argument si el tamaño de `data` y `labels` no coincide.
     */
    bool train(const std::list<std::map<std::string, float>>& data, const std::list<float>& labels);

    /**
     * Realiza una predicción basada en los datos de entrada.
     * @param inputData Lista de valores de características para hacer una predicción.
     * @return Valor predicho.
     * @throws std::runtime_error si el modelo no ha sido entrenado.
     */
    float predict(const std::list<float>& inputData) const;

    /**
     * Obtiene el puntaje de confianza para una predicción.
     * @param inputData Lista de valores de características para evaluar la confianza.
     * @return Puntaje de confianza en el rango de [0,1].
     * @throws std::runtime_error si el modelo no ha sido entrenado.
     */
    float getConfidenceScore(const std::list<float>& inputData) const;

    /**
     * Valida la precisión del modelo.
     * @return Precisión del modelo basada en el conjunto de entrenamiento.
     * @throws std::runtime_error si el modelo no ha sido entrenado.
     */
    float validateAccuracy() const;

    /**
     * Evalúa la precisión del modelo en un conjunto de datos de prueba.
     * @param testData Conjunto de datos de prueba.
     * @param testLabels Etiquetas correspondientes al conjunto de datos de prueba.
     * @return Precisión del modelo en el conjunto de prueba.
     * @throws std::invalid_argument si el tamaño de `testData` y `testLabels` no coincide.
     */
    float evaluateAccuracy(const std::list<std::map<std::string, float>>& testData, const std::list<float>& testLabels) const;

    /**
     * Ajusta los hiperparámetros del modelo para mejorar el rendimiento.
     * @throws std::runtime_error si el modelo no ha sido entrenado.
     */
    void tuneHyperparameters();

    /**
     * Guarda el modelo entrenado en un almacenamiento persistente.
     * @throws std::runtime_error si el modelo no ha sido entrenado.
     */
    void save() const;

    /**
     * Obtiene el identificador único del modelo.
     * @return ID del modelo.
     */
    std::string getId() const;

private:
    std::string modelType;
    std::map<std::string, float> hyperparams;
    bool trained = false;
    float accuracy = 0.0f;
};

#endif // SUPERVISED_MODELS_H
