#include "unsupervised_models.h"
#include <iostream>
#include <stdexcept>

UnsupervisedModel UnsupervisedModel::create(const std::string& modelType) {
    if (modelType.empty()) {
        throw std::invalid_argument("Error: El tipo de modelo no puede estar vacío.");
    }

    UnsupervisedModel model;
    model.modelType = modelType;
    model.trained = false;

    std::cout << "Modelo no supervisado de tipo '" << modelType << "' creado exitosamente." << std::endl;
    return model;
}

bool UnsupervisedModel::train(const std::list<std::map<std::string, float>>& data) {
    if (data.empty()) {
        throw std::invalid_argument("Error: Los datos de entrenamiento no pueden estar vacíos.");
    }

    trained = true;

    std::cout << "Modelo no supervisado entrenado con " << data.size() << " muestras." << std::endl;
    return trained;
}

void UnsupervisedModel::save() const {
    if (!trained) {
        throw std::runtime_error("Error: No se puede guardar un modelo no entrenado.");
    }
    std::cout << "Modelo no supervisado guardado exitosamente." << std::endl;
}

std::string UnsupervisedModel::getId() const {
    return "unsupervised_model_" + modelType;
}
