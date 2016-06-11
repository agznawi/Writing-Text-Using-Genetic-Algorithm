#include "population.h"
#include "individual.h"
#include "evolution.h"

#include <algorithm>
using std::sort;


// Initialize population instance with random chromosomes
Population::Population(int populationSize)
{
    this->populationSize = populationSize;
    for(int i = 0; i < populationSize; i++)
        individuals.push_back(Individual(Evolution::chromosomeLength));
}

int Population::getPopulationCount()
{
    return populationSize;
}

// Compare function to be passed to sort() function
inline bool Population::compFitness(Individual indiv1, Individual indiv2)
{
    return indiv1.getFitness() > indiv2.getFitness();
}

// Call sort() function with parameters
void Population::sortByFitness()
{
    sort(individuals.begin(), individuals.end(), compFitness);
}

Individual& Population::getFittest()
{
    return individuals.front();
}

Individual& Population::getIndividual(int pos)
{
    return individuals.at(pos);
}
