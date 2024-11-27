#include "supervised_models.h"
#include <iostream>
#include <stdexcept>

SupervisedModel SupervisedModel::create(const std::string& modelType, const std::map<std::string, float>& hyperparams) {
    if (modelType.empty()) {
        throw std::invalid_argument("Error: El tipo de modelo no puede estar vacío.");
    }
    
    SupervisedModel model;
    model.modelType = modelType;
    model.hyperparams = hyperparams;
    model.trained = false;
    return model;
}

bool SupervisedModel::train(const std::list<std::map<std::string, float>>& data, const std::list<float>& labels) {
    if (data.size() != labels.size()) {
        throw std::invalid_argument("Error: La cantidad de datos y etiquetas debe ser igual.");
    }
    
    trained = true;
    accuracy = 0.9f;  // Placeholder para precisión tras entrenamiento
    return trained;
}

float SupervisedModel::predict(const std::list<float>& inputData) const {
    if (!trained) {
        throw std::runtime_error("Error: El modelo no está entrenado.");
    }
    return 0.7f;  // Predicción simulada
}

float SupervisedModel::getConfidenceScore(const std::list<float>& inputData) const {
    if (!trained) {
        throw std::runtime_error("Error: El modelo no está entrenado.");
    }
    return 0.85f;  // Puntaje de confianza simulado
}

float SupervisedModel::validateAccuracy() const {
    if (!trained) {
        throw std::runtime_error("Error: El modelo no está entrenado.");
    }
    return accuracy;
}

float SupervisedModel::evaluateAccuracy(const std::list<std::map<std::string, float>>& testData, const std::list<float>& testLabels) const {
    if (testData.size() != testLabels.size()) {
        throw std::invalid_argument("Error: La cantidad de datos de prueba y etiquetas debe ser igual.");
    }
    return accuracy;  // Precisión simulada basada en el conjunto de prueba
}

void SupervisedModel::tuneHyperparameters() {
    if (!trained) {
        throw std::runtime_error("Error: El modelo debe estar entrenado antes de ajustar hiperparámetros.");
    }
    
    // Ejemplo de ajuste de hiperparámetros: reducción de tasa de aprendizaje
    if (hyperparams.find("learning_rate") != hyperparams.end()) {
        hyperparams["learning_rate"] *= 0.9f;
    }
}

void SupervisedModel::save() const {
    if (!trained) {
        throw std::runtime_error("Error: No se puede guardar un modelo no entrenado.");
    }
    std::cout << "Modelo supervisado guardado correctamente." << std::endl;
}

std::string SupervisedModel::getId() const {
    return "model_id";  // Identificador de modelo simulado
}
