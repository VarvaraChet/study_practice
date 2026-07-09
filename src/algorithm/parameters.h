#ifndef PARAMETERS_H
#define PARAMETERS_H

struct Parameters{
    int populationSize = 100;
    int generations = 500;
    int tournamentSize = 3;
    int eliteSize = 3;

    double Pc = 0.8;
    double Pm = 0.2;

    int stepDelayMs = 50;
};

#endif
