#ifndef EVOLUTION_H
#define EVOLUTION_H

#include "individual.h"
#include "population.h"

class Evolution
{
public:
    static string targetChromosome;
    static int chromosomeLength;

    static string crossover(std::string chromosome1, std::string chromosome2);
    static void mutate(Individual &indiv);
    static void calculateFitness(Individual &indiv);
};

#endif // EVOLUTION_H
