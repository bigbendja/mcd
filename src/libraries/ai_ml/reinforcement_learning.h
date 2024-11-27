#include "reinforcement_learning.h"
#include <iostream>
#include <stdexcept>

ReinforcementAgent ReinforcementAgent::create(const std::string& agentId, const std::string& algorithm, const std::map<std::string, float>& hyperparams) {
    ReinforcementAgent agent;
    agent.agentId = agentId;
    agent.algorithm = algorithm;
    agent.hyperparams = hyperparams;
    agent.trained = false;
    agent.episodesTrained = 0;
    return agent;
}

bool ReinforcementAgent::train(const std::string& environment, int episodes) {
    if (episodes <= 0) {
        throw std::invalid_argument("Error: Número de episodios debe ser positivo.");
    }
    
    for (int i = 0; i < episodes; ++i) {
        // Simulación lógica de entrenamiento
        episodesTrained++;
    }
    trained = true;
    return trained;
}

float ReinforcementAgent::decideAction(const std::map<std::string, float>& environment) const {
    if (!trained) {
        throw std::runtime_error("Error: El agente no está entrenado.");
    }
    return 1.0f;  // Acción simulada
}

float ReinforcementAgent::evaluateAction(float action) const {
    if (action < 0.0f || action > 1.0f) {
        throw std::invalid_argument("Error: Acción fuera del rango permitido [0, 1].");
    }
    return 0.9f;  // Recompensa simulada
}

void ReinforcementAgent::updatePolicy(float reward, float action) {
    if (!trained) {
        throw std::runtime_error("Error: El agente debe estar entrenado antes de actualizar la política.");
    }
    // Lógica de actualización de política simulada
}

void ReinforcementAgent::save() const {
    if (!trained) {
        throw std::runtime_error("Error: El agente no está entrenado; no se puede guardar.");
    }
    std::cout << "Agente de refuerzo guardado con éxito." << std::endl;
}

std::string ReinforcementAgent::getId() const {
    return agentId;
}

void ReinforcementAgent::adjustExplorationRate(float decayRate) {
    if (decayRate <= 0.0f || decayRate >= 1.0f) {
        throw std::invalid_argument("Error: Tasa de decaimiento debe estar en el rango (0, 1).");
    }
    if (hyperparams.count("exploration_rate")) {
        hyperparams["exploration_rate"] *= decayRate;
    }
}

std::map<std::string, float> ReinforcementAgent::optimizeHyperparameters(const std::map<std::string, std::pair<float, float>>& paramBounds, const std::string& environment, int iterations) {
    if (iterations <= 0) {
        throw std::invalid_argument("Error: Iteraciones debe ser un número positivo.");
    }
    
    std::map<std::string, float> bestParams = hyperparams;
    float bestReward = -1.0f;
    
    for (int i = 0; i < iterations; ++i) {
        // Simulación de optimización (Bayesian o similar)
        float currentReward = evaluatePolicy(environment);
        if (currentReward > bestReward) {
            bestReward = currentReward;
            bestParams = hyperparams;
        }
    }
    hyperparams = bestParams;
    return bestParams;
}

float ReinforcementAgent::evaluatePolicy(const std::string& environment) const {
    if (!trained) {
        throw std::runtime_error("Error: El agente debe estar entrenado para evaluar la política.");
    }
    return 0.85f;  // Evaluación de política simulada
}

std::map<std::string, std::string> ReinforcementAgent::generateReport() const {
    return {
        {"agent_id", agentId},
        {"algorithm", algorithm},
        {"episodes_trained", std::to_string(episodesTrained)},
        {"trained", trained ? "true" : "false"}
    };
}
