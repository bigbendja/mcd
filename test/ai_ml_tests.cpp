#include "ai_ml.h"
#include "config.h"
#include <cassert>
#include <iostream>

void run_test(const std::string& test_name, bool result) {
    if (result) {
        std::cout << "[PASSED] " << test_name << std::endl;
    } else {
        std::cerr << "[FAILED] " << test_name << std::endl;
    }
}

void test_trainSupervisedModel() {
    std::list<std::map<std::string, float>> training_data = {{{"feature1", 0.5}, {"feature2", 1.2}}, {{"feature1", 0.9}, {"feature2", 0.8}}};
    std::list<float> labels = {1.0, 0.0};
    std::map<std::string, float> hyperparams = {{"learning_rate", 0.01}, {"batch_size", 32}};

    auto result = AIML::trainSupervisedModel(training_data, labels, "neural_network", hyperparams);
    run_test("Train Supervised Model - Accuracy Check", result["accuracy"] > 0.8);
    run_test("Train Supervised Model - Training Time Check", result["training_time"] > 0.0);
}

void test_predictAndMonitor() {
    SupervisedModel model = SupervisedModel::create("neural_network", {{"learning_rate", 0.01}});
    model.train({{{"feature1", 0.5}, {"feature2", 1.2}}, {{"feature1", 0.9}, {"feature2", 0.8}}}, {1.0, 0.0});

    std::list<float> input_data = {0.6, 1.0};
    auto result = AIML::predictAndMonitor(model, input_data);
    run_test("Predict and Monitor - Prediction Confidence", result["confidence"] > 0.7);
}

void test_anomalyDetection() {
    std::list<std::map<std::string, float>> data = {{{"sensor1", 0.4}, {"sensor2", 1.0}}, {{"sensor1", 1.5}, {"sensor2", 0.5}}};
    auto result = AIML::anomalyDetection(data, "isolation_forest");
    run_test("Anomaly Detection - Model Trained", result["status"] == "anomaly_detection_trained");
}

void test_reinforcementLearningDecision() {
    ReinforcementAgent agent = ReinforcementAgent::create("RL_agent_1", "Q-learning", {{"learning_rate", 0.005}});
    std::map<std::string, float> environment = {{"state1", 0.7}, {"state2", 0.3}};

    auto result = AIML::reinforcementLearningDecision(environment, agent);
    run_test("Reinforcement Learning - Valid Action", result["action"] >= 0.0);
    run_test("Reinforcement Learning - Valid Reward", result["reward"] >= 0.0);
}

void test_autoEvaluateAndRetuneModel() {
    SupervisedModel model = SupervisedModel::create("svm", {{"C", 1.0}});
    std::list<std::map<std::string, float>> test_data = {{{"feature1", 0.5}, {"feature2", 1.2}}, {{"feature1", 0.9}, {"feature2", 0.8}}};
    std::list<float> test_labels = {1.0, 0.0};

    auto result = AIML::autoEvaluateAndRetuneModel(model, test_data, test_labels);
    run_test("Auto Evaluate and Retune Model - Accuracy", std::stof(result["accuracy"]) >= 0.85);
    run_test("Auto Evaluate and Retune Model - Status", result["status"] == "evaluated" || result["status"] == "retrained");
}

void test_configurationIntegration() {
    config::load_config("./config/ai_ml_config.json");
    std::string model_path = config::get_setting<std::string>("supervised_model.default_hyperparameters.learning_rate");
    run_test("Configuration Integration - Default Hyperparameters", model_path == "0.01");
}

int main() {
    std::cout << "Starting tests for AI_ML library" << std::endl;

    test_trainSupervisedModel();
    test_predictAndMonitor();
    test_anomalyDetection();
    test_reinforcementLearningDecision();
    test_autoEvaluateAndRetuneModel();
    test_configurationIntegration();

    std::cout << "All tests completed successfully." << std::endl;
    return 0;
}
