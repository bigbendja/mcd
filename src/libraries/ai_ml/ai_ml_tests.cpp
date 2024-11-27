#include "ai_ml.h"
#include <cassert>
#include <iostream>

void testTrainSupervisedModel() {
    std::list<std::map<std::string, float>> training_data = {{{"feature1", 0.5}, {"feature2", 1.2}}, {{"feature1", 0.9}, {"feature2", 0.8}}};
    std::list<float> labels = {1.0, 0.0};
    std::map<std::string, float> hyperparams = {{"learning_rate", 0.01}, {"batch_size", 32}};

    auto result = AIML::trainSupervisedModel(training_data, labels, "neural_network", hyperparams);
    assert(result["accuracy"] >= 0.85);  // Threshold for production quality
    std::cout << "testTrainSupervisedModel passed\n";
}

void testPredictAndMonitor() {
    SupervisedModel model = SupervisedModel::create("neural_network", {{"learning_rate", 0.01}});
    model.train({{{"feature1", 0.5}, {"feature2", 1.2}}, {{"feature1", 0.9}, {"feature2", 0.8}}}, {1.0, 0.0});

    std::list<float> input_data = {0.6, 1.0};
    auto result = AIML::predictAndMonitor(model, input_data);
    assert(result["confidence"] >= 0.7);
    std::cout << "testPredictAndMonitor passed\n";
}

void testAnomalyDetection() {
    std::list<std::map<std::string, float>> data = {{{"sensor1", 0.4}, {"sensor2", 1.0}}, {{"sensor1", 1.5}, {"sensor2", 0.5}}};
    auto result = AIML::anomalyDetection(data, "isolation_forest");

    assert(result["status"] == "anomaly_detection_trained");
    std::cout << "testAnomalyDetection passed\n";
}

void testReinforcementLearningDecision() {
    ReinforcementAgent agent = ReinforcementAgent::create("RL_agent_1", "Q-learning", {{"learning_rate", 0.005}});
    std::map<std::string, float> environment = {{"state1", 0.7}, {"state2", 0.3}};

    auto result = AIML::reinforcementLearningDecision(environment, agent);
    assert(result["reward"] >= 0.0); // Ensuring positive feedback mechanism
    std::cout << "testReinforcementLearningDecision passed\n";
}

void testAutoEvaluateAndRetuneModel() {
    SupervisedModel model = SupervisedModel::create("svm", {{"C", 1.0}});
    std::list<std::map<std::string, float>> test_data = {{{"feature1", 0.5}, {"feature2", 1.2}}, {{"feature1", 0.9}, {"feature2", 0.8}}};
    std::list<float> test_labels = {1.0, 0.0};

    auto result = AIML::autoEvaluateAndRetuneModel(model, test_data, test_labels);
    assert(result["status"] == "evaluated" && std::stof(result["accuracy"]) >= 0.85);
    std::cout << "testAutoEvaluateAndRetuneModel passed\n";
}

int main() {
    testTrainSupervisedModel();
    testPredictAndMonitor();
    testAnomalyDetection();
    testReinforcementLearningDecision();
    testAutoEvaluateAndRetuneModel();
    std::cout << "All tests passed successfully.\n";
    return 0;
}
