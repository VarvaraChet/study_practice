#ifndef ALGORITHM_STATE_H
#define ALGORITHM_STATE_H

#include <vector>

struct IndividualState{
    int delay;
    std::vector <int> order;
};

struct AlgorithmState{
    int generation = 0;

    double bestFitness = 0;
    double averageFitness = 0;

    std::vector <IndividualState> population;
};

#endif
