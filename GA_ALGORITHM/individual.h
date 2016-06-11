#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <string>
using std::string;

class Individual
{
private:
    int fitness;

public:
    string chromosome;
    Individual(int chromosomeLength);
    Individual(string chromosome);

    int getFitness();
    void setFitness(int f);
};

#endif // INDIVIDUAL_H
