#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent){}

void Controller::run(const std::vector<Task>& tasks, Parameters& parameters){
    params = parameters;

    gen_algorithm.run(tasks, params);

    emit stateChange(gen_algorithm.getState());
}

void Controller::step(){
    gen_algorithm.step();

    emit stateChange(gen_algorithm.getState());
}

void Controller::fullExecute(){
    AlgorithmState cur=gen_algorithm.getState();

    while (cur.generation <= params.generations && cur.bestFitness != 0){
        step();
        cur = gen_algorithm.getState();

        QCoreApplication::processEvents();
    }
}

void Controller::showIndividual(int row){
    if (row < 0 || row >= gen_algorithm.getState().population.size())
        return;

    emit individualReady(gen_algorithm.getState().population[row]);
}
