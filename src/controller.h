#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QCoreApplication>
#include <vector>

#include "algorithm/geneticAlgorithm.h"
#include "algorithm/task.h"
#include "algorithm/parameters.h"
#include "algorithm/algorithmState.h"
#include "gui/executionPage.h"

class ExecutionPage;

class Controller : public QObject{
    Q_OBJECT

    public:
        explicit Controller(QObject *parent = nullptr);

    public slots:
        void run(const std::vector<Task> &tasks, Parameters &parameters);

        void step();
        void fullExecute();

        void showIndividual(int row);

    signals:
        void stateChange(const AlgorithmState& state);
        void individualReady(const Individual& individ);

    private:
        Parameters params;
        GeneticAlgorithm gen_algorithm;
};

#endif
