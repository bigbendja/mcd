#ifndef AI_ML_H
#define AI_ML_H

#include <string>
#include <map>
#include <list>
#include "supervised_models.h"
#include "unsupervised_models.h"
#include "reinforcement_learning.h"

using std::string;
using std::map;
using std::list;

class AIML {
public:
    /**
     * Entrenamiento supervisado de modelo
     * @param data: Datos de entrenamiento en forma de lista de mapas de características.
     * @param labels: Etiquetas correspondientes para los datos de entrenamiento.
     * @param modelType: Tipo de modelo supervisado a entrenar.
     * @param hyperparams: Parámetros de hiperajuste del modelo.
     * @return Mapa con métricas clave como exactitud y tiempo de entrenamiento.
     */
    static map<string, float> trainSupervisedModel(const list<map<string, float>>& data, const list<float>& labels, const string& modelType, const map<string, float>& hyperparams = {});

    /**
     * Predicción y monitoreo de confianza
     * @param model: Modelo supervisado entrenado.
     * @param inputData: Datos de entrada para realizar la predicción.
     * @return Mapa con la predicción y el puntaje de confianza.
     */
    static map<string, float> predictAndMonitor(const SupervisedModel& model, const list<float>& inputData);

    /**
     * Predicción en batch
     * @param model: Modelo supervisado entrenado.
     * @param batchInput: Lista de entradas para realizar predicciones.
     * @return Lista de mapas con predicciones y puntajes de confianza.
     */
    static list<map<string, float>> predictBatch(const SupervisedModel& model, const list<list<float>>& batchInput);

    /**
     * Detección de anomalías
     * @param data: Datos para la detección de anomalías.
     * @param modelType: Tipo de modelo no supervisado a utilizar.
     * @return Mapa con estado de entrenamiento y ID del modelo.
     */
    static map<string, string> anomalyDetection(const list<map<string, float>>& data, const string& modelType);

    /**
     * Toma de decisiones en aprendizaje por refuerzo
     * @param environment: Representación del entorno para la toma de decisiones.
     * @param agent: Agente de aprendizaje por refuerzo.
     * @return Mapa con la acción tomada y la recompensa obtenida.
     */
    static map<string, float> reinforcementLearningDecision(const map<string, float>& environment, ReinforcementAgent& agent);

    /**
     * Optimización híbrida de modelos supervisados y no supervisados
     * @param data: Datos de entrada para la optimización híbrida.
     * @param supervisedModelType: Tipo de modelo supervisado a utilizar.
     * @param unsupervisedModelType: Tipo de modelo no supervisado a utilizar.
     * @param hyperparams: Hiperparámetros para el modelo supervisado.
     * @return Mapa con los IDs de los modelos generados.
     */
    static map<string, string> hybridOptimization(const list<map<string, float>>& data, const string& supervisedModelType, const string& unsupervisedModelType, const map<string, float>& hyperparams = {});

    /**
     * Evaluación y reentrenamiento de modelos
     * @param model: Modelo supervisado a evaluar y reentrenar si es necesario.
     * @param testData: Datos de prueba para evaluar el modelo.
     * @param testLabels: Etiquetas de prueba para los datos de prueba.
     * @return Mapa con la precisión obtenida y el estado de evaluación.
     */
    static map<string, string> autoEvaluateAndRetuneModel(SupervisedModel& model, const list<map<string, float>>& testData, const list<float>& testLabels);

    /**
     * Evaluación distribuida de modelos
     * @param model: Modelo supervisado a evaluar.
     * @param testData: Datos de prueba.
     * @param testLabels: Etiquetas correspondientes.
     * @param numThreads: Número de hilos a utilizar para la evaluación distribuida.
     * @return Mapa con precisión promedio y estado de evaluación.
     */
    static map<string, string> distributedAutoEvaluate(SupervisedModel& model, const list<map<string, float>>& testData, const list<float>& testLabels, int numThreads = 4);
};

#endif // AI_ML_H
