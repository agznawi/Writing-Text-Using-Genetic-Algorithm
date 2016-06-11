#include "individual.h"
#include "population.h"
#include "evolution.h"
#include "randengine.h"

#include <fstream>
using std::ifstream;
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <iomanip>
using std::setw;
using std::left;
#include <random>
using std::random_device;
using std::default_random_engine;
using std::uniform_int_distribution;
using std::uniform_real_distribution;
#include <cassert>


random_device r;
default_random_engine e1(r());

string readFile(string fileName);
void printPopulation(Population pop, int count, bool enableNewLine);

const string FILE_NAME = "excerpt from hamlet ACT III SCENE I";
string Evolution::targetChromosome = readFile(FILE_NAME);
int Evolution::chromosomeLength = Evolution::targetChromosome.size();

// Set the perfect solution fitness
// Since the fitness is the number of characters at the right place
// the perfect fitness is equivelent to the length of the target chromosome
const int perfectFit = Evolution::targetChromosome.size();


int main()
{
    // Evolution parameters
    const int POP_SIZE = 1000; // Population size
    const float MUTATION_THRESHOLD = 0.3f; // Mutation rate of individuals, only one mutation is possible per individual
    const float SURVIVAL_RATE = 0.5f; // Survival rate, ratio of best individuals that will possibily breed

    // Algorithm parameters
    const unsigned survived = SURVIVAL_RATE * POP_SIZE; // Number of survived individuals

    // Display parameters
    const int dispIndivs = 1; // Number of individuals to be displayed
    const bool newLine = true; // Writing new line
    const bool skip = false; // Using 'return' key to evolve to next generation
    const int skipGenerations = 1; // Number of generations to be skipped before displaying

    // Make sure values are valid
    assert(survived < POP_SIZE && survived > 0);
    assert(dispIndivs <= POP_SIZE);

    // Output target solution info
    cout << "Target chromosome is:\n" << Evolution::targetChromosome << endl;
    cout << "\nPerfect fitness = " << perfectFit << endl;
    getchar();

    // Set text and background color (for Linux)
    system("setterm -term linux -back white -fore blue");

    // Initialize generation 0
    Population pop(POP_SIZE); // Create random population
    for(int i = 0; i < POP_SIZE; i++) // Calculate population fitness
        Evolution::calculateFitness(pop.individuals.at(i));
    pop.sortByFitness(); // Sort population by fitness

    system("clear"); // Yeah whatever
    cout << "Writing an " << FILE_NAME << " using genetic algorithm\n"
         <<"Generation: 0 | ";
    printPopulation(pop, dispIndivs, newLine); // Print current generation information
    if(skip) getchar();

    // Produce and evolve generations forever or until the perfect solution appears
    for(int generation = 1;; generation++)
    {
        vector<Individual> newPopulation; // Temp population

        // Create new child individuals, mutate and calculate their fitnesses
        for(int i = 0; i < POP_SIZE; i++)
        {
            // Select two random parents indecies of the best individuals
            uniform_int_distribution<int> rSelect(0, survived);
            int indivIndex1 = rSelect(e1);
            int indivIndex2 = rSelect(e1);

            // Crossover
            string parent1Chr = // Parent 1 chromosome
                    pop.getIndividual(indivIndex1).chromosome;
            string parent2Chr = // Parent 2 chromosome
                    pop.getIndividual(indivIndex2).chromosome;

            string offsprChr = // New chromosome
                    Evolution::crossover(parent1Chr, parent2Chr);

            // Create new Individual
            Individual indiv(offsprChr);

            // Expose Individual to mutation
            uniform_real_distribution<float> rMut(0, 1);
            if(rMut(e1) < MUTATION_THRESHOLD) // If rMut() is below mutation threshold:
                Evolution::mutate(indiv); // Individual will mutate

            // Calculate Individual fitness
            Evolution::calculateFitness(indiv);

            // Add Individual to the new population
            newPopulation.push_back(indiv);
        }

        pop.individuals = newPopulation; // Replace population
        pop.sortByFitness(); // Sort population by fitness

        // Print current generation information
        if(!(generation % skipGenerations))
        {
            system("clear");
            cout << "Writing an " << FILE_NAME << " using genetic algorithm\n"
                 << "Generation: " << generation << " | ";
            printPopulation(pop, dispIndivs, newLine);
            cout.flush();
            if(skip) getchar();
        }

        // Check for perfect solution
        if(pop.getFittest().getFitness() == perfectFit)
        {
            cout << "\nFound the perfect solution!\n";

            break;
        }
    }

    return 0;
}


// Reading string from file
string readFile(string fileName)
{
    ifstream file(fileName);
    string text;
    char c;
    while(file.get(c))
        text += c;
    file.close();
    return text;
}


// Print population information
void printPopulation(Population pop, int count, bool enableNewLine)
// pop = Population instance
// count = number of top individuals to be displayed
// enableNewLine = enable/disable display of \n character
{
    int popSize = pop.getPopulationCount();
    float avg = 0.0f;
    float accuracy = 100.0f * pop.getFittest().getFitness() / perfectFit;
    // Calculate average fitness
    for(int i = 0; i < popSize; i++)
        avg += pop.getIndividual(i).getFitness();
    avg /= popSize;

    // Print best and worst individual fitnesses, and overall average fitness
    cout << "Accuracy of solution = " << accuracy << "\%"
         << "\nBest fit = " << pop.getIndividual(0).getFitness()
         << " | Worst fit = " << pop.getIndividual(popSize-1).getFitness()
         << " | Avg fit = " << avg
         << endl;

    int textLength = Evolution::chromosomeLength;
    for(int i = 0; i < count; i++)
    {
        string displayText;
        displayText.back() = 0;
        for(int j = 0; j < textLength; j++)
        {

            char rt = pop.getIndividual(i).chromosome[j];
            // Display all whitespaces and invisible characters as 'space'
            if((rt == 0 && j != textLength) || // If 'Null' and still in the middle of the text
               (rt == 10 && !enableNewLine) || // If 'Newline' and displaying new line is disabled
               (rt >= 1 && rt <= 9) || // If from 'SOH' to 'TAB'
               (rt >= 11 && rt <= 31) || // If from 'VT' to 'US'
               (rt == 127)) // If 'DEL'
                displayText += ' '; // write 'space'
            else
                displayText += rt; // else copy character
        }
        // Uncomment to display a "count" number of individuals
//        cout << "Indiv" << left << setw(2) << i << " fitness = " << pop.getIndividual(i).getFitness() <<
//                " for chromosome: " << ((enableNewLine)? "\n\n" : "" ) << displayText << endl;

        cout << "Best solution so far:\n\n" << displayText << endl;
    }
}
