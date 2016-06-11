#include "individual.h"
#include "randengine.h"

#include <random>
using std::uniform_int_distribution;

// Constructor to initialize Individual by number of genes
Individual::Individual(int chromosomeLength)
    : fitness(0)
{
    uniform_int_distribution<int> rGene(0, 127);
    for(int i = 0; i < chromosomeLength; i++)
    {
        chromosome += rGene(e1);
    }
}

// Constructor to initialize Individual by set of genes
Individual::Individual(std::string chromosome)
    : fitness(0)
{
    this->chromosome = chromosome;
}

int Individual::getFitness()
{
    return fitness;
}

void Individual::setFitness(int f)
{
    fitness = f;
}
