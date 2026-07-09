#ifndef ALGORITHM_STATE_H
#define ALGORITHM_STATE_H

#include <vector>
#include <climits>

struct Individual{
    int delay=0;
    std::vector <int> order;
};

struct AlgorithmState{
    int generation = 0;

    int bestFitness = INT_MAX;
    double averageFitness = 0;

    std::vector <Individual> population;
};

#endif
