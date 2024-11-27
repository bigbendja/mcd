#include "ai_ml.h"
#include <iostream>
#include <stdexcept>
#include <ctime>
#include <thread>

// Entrenamiento supervisado con monitoreo de tiempo y manejo de errores
map<string, float> AIML::trainSupervisedModel(const list<map<string, float>>& data, const list<float>& labels, const string& modelType, const map<string, float>& hyperparams) {
    if (data.empty() || labels.empty()) {
        throw std::invalid_argument("Error: Los datos de entrenamiento y etiquetas no pueden estar vacíos.");
    }

    SupervisedModel model = SupervisedModel::create(modelType, hyperparams);

    // Monitoreo del tiempo de entrenamiento
    clock_t start = clock();
    model.train(data, labels);
    model.save();
    clock_t end = clock();
    float training_time = static_cast<float>(end - start) / CLOCKS_PER_SEC;

    return {{"accuracy", model.validateAccuracy()}, {"training_time", training_time}};
}

// Predicción y monitoreo de confianza
map<string, float> AIML::predictAndMonitor(const SupervisedModel& model, const list<float>& inputData) {
    if (inputData.empty()) {
        throw std::invalid_argument("Error: Los datos de entrada no pueden estar vacíos.");
    }

    float prediction = model.predict(inputData);
    float confidence = model.getConfidenceScore(inputData);

    return {{"prediction", prediction}, {"confidence", confidence}};
}

// Predicción en lote
list<map<string, float>> AIML::predictBatch(const SupervisedModel& model, const list<list<float>>& batchInput) {
    list<map<string, float>> predictions;

    for (const auto& inputData : batchInput) {
        predictions.push_back(predictAndMonitor(model, inputData));
    }

    return predictions;
}

// Detección de anomalías con monitoreo de tiempo
map<string, string> AIML::anomalyDetection(const list<map<string, float>>& data, const string& modelType) {
    if (data.empty()) {
        throw std::invalid_argument("Error: Los datos de entrada para la detección de anomalías no pueden estar vacíos.");
    }

    UnsupervisedModel model = UnsupervisedModel::create(modelType);

    // Monitoreo del tiempo de entrenamiento
    clock_t start = clock();
    model.train(data);
    model.save();
    clock_t end = clock();
    float training_time = static_cast<float>(end - start) / CLOCKS_PER_SEC;

    return {{"status", "anomaly_detection_trained"}, {"model_id", model.getId()}, {"training_time", std::to_string(training_time)}};
}

// Decisiones basadas en aprendizaje por refuerzo
map<string, float> AIML::reinforcementLearningDecision(const map<string, float>& environment, ReinforcementAgent& agent) {
    if (environment.empty()) {
        throw std::invalid_argument("Error: El entorno para la toma de decisiones no puede estar vacío.");
    }

    float action = agent.decideAction(environment);
    float reward = agent.evaluateAction(action);

    agent.updatePolicy(reward, action);
    return {{"action", action}, {"reward", reward}};
}

// Optimización híbrida de modelos supervisados y no supervisados
map<string, string> AIML::hybridOptimization(const list<map<string, float>>& data, const string& supervisedModelType, const string& unsupervisedModelType, const map<string, float>& hyperparams) {
    if (data.empty()) {
        throw std::invalid_argument("Error: Los datos de entrada no pueden estar vacíos.");
    }

    SupervisedModel supervisedModel = SupervisedModel::create(supervisedModelType, hyperparams);
    UnsupervisedModel unsupervisedModel = UnsupervisedModel::create(unsupervisedModelType);

    supervisedModel.train(data, {});
    unsupervisedModel.train(data);

    return {{"supervised_model_id", supervisedModel.getId()}, {"unsupervised_model_id", unsupervisedModel.getId()}};
}

// Autoevaluación y ajuste dinámico de modelos supervisados
map<string, string> AIML::autoEvaluateAndRetuneModel(SupervisedModel& model, const list<map<string, float>>& testData, const list<float>& testLabels) {
    if (testData.empty() || testLabels.empty()) {
        throw std::invalid_argument("Error: Los datos de prueba y etiquetas no pueden estar vacíos.");
    }

    float accuracy = model.evaluateAccuracy(testData, testLabels);
    string status = "evaluated";

    if (accuracy < 0.85) {
        model.tuneHyperparameters();
        model.train(testData, testLabels);
        status = "retrained";
    }

    return {{"accuracy", std::to_string(accuracy)}, {"status", status}};
}

// Evaluación distribuida usando hilos
map<string, string> AIML::distributedAutoEvaluate(SupervisedModel& model, const list<map<string, float>>& testData, const list<float>& testLabels, int numThreads) {
    if (testData.empty() || testLabels.empty()) {
        throw std::invalid_argument("Error: Los datos de prueba y etiquetas no pueden estar vacíos.");
    }

    std::vector<std::thread> threads;
    size_t chunkSize = testData.size() / numThreads;
    std::atomic<float> totalAccuracy(0.0f);

    auto evaluateChunk = [&](size_t start, size_t end) {
        auto itData = std::next(testData.begin(), start);
        auto itLabels = std::next(testLabels.begin(), start);

        for (size_t i = start; i < end; ++i, ++itData, ++itLabels) {
            totalAccuracy += model.evaluateAccuracy({*itData}, {*itLabels});
        }
    };

    for (int i = 0; i < numThreads; ++i) {
        size_t start = i * chunkSize;
        size_t end = (i == numThreads - 1) ? testData.size() : start + chunkSize;

        threads.emplace_back(evaluateChunk, start, end);
    }

    for (auto& t : threads) {
        t.join();
    }

    float avgAccuracy = totalAccuracy / testData.size();
    return {{"average_accuracy", std::to_string(avgAccuracy)}, {"status", "distributed_evaluation_completed"}};
}
