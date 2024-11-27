#include "ai_ml.h"
#include <iostream>
#include <vector>
#include <chrono>

// Función auxiliar para medir el tiempo de ejecución
double measureExecutionTime(std::function<void()> func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    return elapsed.count();
}

// Prueba de carga para entrenamiento supervisado
void performanceTestSupervisedTraining() {
    std::cout << "Prueba de carga: Entrenamiento supervisado" << std::endl;
    
    // Crear un conjunto de datos simulado de gran tamaño
    std::list<std::map<std::string, float>> training_data;
    std::list<float> labels;
    for (int i = 0; i < 100000; ++i) {
        training_data.push_back({{"feature1", static_cast<float>(i % 100)}, {"feature2", static_cast<float>((i + 1) % 100)}});
        labels.push_back(i % 2);
    }

    // Ejecutar entrenamiento y medir tiempo
    double time_taken = measureExecutionTime([&]() {
        auto result = AIML::trainSupervisedModel(training_data, labels, "neural_network");
        std::cout << "Precisión obtenida: " << result.at("accuracy") << std::endl;
    });

    std::cout << "Tiempo de entrenamiento: " << time_taken << " segundos" << std::endl;
}

// Prueba de carga para detección de anomalías
void performanceTestAnomalyDetection() {
    std::cout << "Prueba de carga: Detección de anomalías" << std::endl;

    // Crear un conjunto de datos simulado de gran tamaño
    std::list<std::map<std::string, float>> anomaly_data;
    for (int i = 0; i < 50000; ++i) {
        anomaly_data.push_back({{"sensor1", static_cast<float>(i % 50)}, {"sensor2", static_cast<float>((i + 1) % 50)}});
    }

    // Ejecutar detección y medir tiempo
    double time_taken = measureExecutionTime([&]() {
        auto result = AIML::anomalyDetection(anomaly_data, "isolation_forest");
        std::cout << "Modelo ID: " << result.at("model_id") << std::endl;
    });

    std::cout << "Tiempo de detección: " << time_taken << " segundos" << std::endl;
}

// Prueba de carga para decisiones por refuerzo
void performanceTestReinforcementLearning() {
    std::cout << "Prueba de carga: Aprendizaje por refuerzo" << std::endl;

    ReinforcementAgent agent = ReinforcementAgent::create("RL_Agent_1", "Q-learning", {{"learning_rate", 0.005}});
    std::map<std::string, float> environment = {{"state1", 0.7}, {"state2", 0.3}};

    // Ejecutar múltiples decisiones para simular carga
    double time_taken = measureExecutionTime([&]() {
        for (int i = 0; i < 10000; ++i) {
            auto result = AIML::reinforcementLearningDecision(environment, agent);
        }
    });

    std::cout << "Tiempo de toma de decisiones (10k iteraciones): " << time_taken << " segundos" << std::endl;
}

// Función principal para ejecutar las pruebas
int main() {
    std::cout << "Iniciando pruebas de rendimiento para 'ai_ml'" << std::endl;

    performanceTestSupervisedTraining();
    performanceTestAnomalyDetection();
    performanceTestReinforcementLearning();

    std::cout << "Pruebas de rendimiento completadas." << std::endl;
    return 0;
}
