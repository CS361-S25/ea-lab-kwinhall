#include <iostream>
#include "Empirical/include/emp/math/Random.hpp"

/*
Kendra Winhall 
Evolutionary Algorithm Lab, CS 361
Adapted from starter code from Anya Vostinar

This program simulates the evolution of organisms that are more likely to survive and reproduce if their behavior value is similar to pi.
*/

// Defines organisms that have a behavior value, can mutate, and can reproduce
class Organism {
    public:
        // an organism's ability to survive and reproduce is based on its behavior value (and pseudorandom "luck")
        double behavior;
        Organism(double x=0) {
            behavior = x;
        }

        // modifies behavior value by a small, pseudorandom amount
        void mutate(emp::Random random) {
            double randomNum = random.GetRandNormal(0.0, 0.02);
            behavior += randomNum;
        }

        // creates child that has a similar (but likely not identical) behavior value 
        Organism* reproduce(emp::Random random) {
            Organism* child = new Organism(behavior);
            child->mutate(random);
            return child;
        }
};

// Creates a population of organisms, runs updates to allow population to evolve, and prints the best organism's behavior value
int main() {
    emp::Random random(1);

    // creates population and mutates initial organisms
    emp::vector<Organism> population;
    for (int i = 0; i < 100; i++) {
        population.push_back(*new Organism(0.5));
        population[i].mutate(random);
    }

    // runs updates, enabling the population to evolve
    int numUpdates = 1000;
    for (int update = 0; update < numUpdates; update++) { 

        // finds organism with behavior value closest to pi
        Organism& bestOrganism = population[0];
        for(Organism j : population) {
            if (abs(M_PI - j.behavior) < abs(M_PI - bestOrganism.behavior)) {
                bestOrganism = j;
            }
        }

        // replaces a random organism in the population with the best organism's child
        Organism* newOrganism = bestOrganism.reproduce(random);
        int overwrite = random.GetUInt(0,100);
        population[overwrite] = *newOrganism;

        // after the last update, prints the behavior value of the best organism
        if (update == numUpdates - 1) {
            std::cout << "After " << numUpdates << " updates, the best organism's behavior value is " << bestOrganism.behavior << std::endl;
        }
    }
}