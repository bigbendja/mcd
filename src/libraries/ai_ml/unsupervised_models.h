#ifndef UNSUPERVISED_MODELS_H
#define UNSUPERVISED_MODELS_H

#include <string>
#include <map>
#include <list>

/**
 * Clase UnsupervisedModel: Implementa un modelo de aprendizaje no supervisado con funciones 
 * de entrenamiento y gestión. Proporciona un marco general para varios tipos de modelos 
 * no supervisados con manejo de hiperparámetros y control de entrenamiento.
 */
class UnsupervisedModel {
public:
    /**
     * Crea una instancia de un modelo no supervisado del tipo especificado.
     * 
     * @param modelType Tipo del modelo (ej., "clustering", "reducción de dimensionalidad").
     * @return Un objeto UnsupervisedModel configurado con el tipo de modelo especificado.
     * @throws std::invalid_argument Si el tipo de modelo está vacío.
     */
    static UnsupervisedModel create(const std::string& modelType);
    
    /**
     * Entrena el modelo con los datos proporcionados.
     * 
     * @param data Datos de entrada para el entrenamiento, donde cada mapa representa una muestra.
     * @return true si el entrenamiento fue exitoso, false en caso contrario.
     * @throws std::invalid_argument Si los datos están vacíos.
     */
    bool train(const std::list<std::map<std::string, float>>& data);

    /**
     * Guarda el modelo entrenado. 
     * 
     * @throws std::runtime_error Si el modelo no ha sido entrenado antes de llamar a esta función.
     */
    void save() const;

    /**
     * Obtiene el identificador único del modelo.
     * 
     * @return Un identificador único del modelo, basado en su tipo.
     */
    std::string getId() const;

private:
    std::string modelType;                   // Tipo del modelo no supervisado.
    std::map<std::string, float> hyperparams; // Hiperparámetros del modelo (si aplican).
    bool trained = false;                    // Estado de entrenamiento del modelo.
};

#endif // UNSUPERVISED_MODELS_H
