#include "evolution.h"
#include "individual.h"
#include "randengine.h"

#include <random>
using std::uniform_int_distribution;

string Evolution::crossover(string chromosome1, string chromosome2)
{
    uniform_int_distribution<int> rCut(0, chromosomeLength-1);
    int cut = rCut(e1); // Select random crossover point

    // Return the new chromosome as a combination of both chromosome as follow ...
    return chromosome1.substr(0, cut) + // Take first genes until cut point from chromosome1
           chromosome2.substr(cut); // Take rest of genes from chromosome2
}

void Evolution::mutate(Individual &indiv)
{
    uniform_int_distribution<int> rGene(0, chromosomeLength-1);
    uniform_int_distribution<int> rValue(0, 127);
    int gene = rGene(e1); // Select random location
    int value = rValue(e1); // Select random ASCII
    indiv.chromosome.at(gene) = value; // Apply mutation
}

void Evolution::calculateFitness(Individual &indiv)
{
    /* The fitness represents only the number of characters that are  *
     * in the right place. It achieves this by comparing the          *
     * characters of the individual with its corresponding characters *
     * of the target solution and counting the matching occurrences.  */

    int fitness = 0;
    for(int j = 0; j < chromosomeLength; j++) // For every character in the chromosome
        if(indiv.chromosome[j] == targetChromosome[j]) // if it matches the corresponding target chromosome character
            fitness++; // increase fitness by 1
    indiv.setFitness(fitness);
}
