#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>
#include <climits>

#include "task.h"
#include "parameters.h"
#include "algorithmState.h"

class GeneticAlgorithm{
    public:
        GeneticAlgorithm() = default;

        void run(const std::vector <Task>& tasks, Parameters& param);
        void step();

        AlgorithmState getState();

    private:
        Parameters params;

        int cnt_tasks;
        std::vector <Task> tasks;
        std::vector <Individual> new_population;

        AlgorithmState state;

        Individual createIndividual();

        void calcDelay(Individual& individ);
        void calcСharacteristic();

        int tournament();
        void fillOutChild(Individual& parent, Individual& child, int x);
        void crossover(Individual& parent1, Individual& parent2);
        void mutation(Individual& individ);
};

#endif
