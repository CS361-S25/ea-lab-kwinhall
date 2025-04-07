#include <iostream>
#include "Empirical/include/emp/math/Random.hpp"

class Organism {
    public:
        double behavior;
        Organism(double x=0) {
            behavior = x;
        }
        void mutate(emp::Random random) {
            double randomNum = random.GetRandNormal(0.0, 0.02);
            behavior += randomNum;
        }
        Organism* reproduce(emp::Random random) {
            Organism* child = new Organism(behavior);
            child->mutate(random);
            return child;
        }
    };

int main() {
    emp::Random random(1);
    emp::vector<Organism> population;

    // create population and mutate initial organisms
    for (int i = 0; i < 100; i++) {
        population.push_back(*new Organism(0.5));
        population[i].mutate(random);
    }

    int numUpdates = 10000;
    for (int update = 0; update < numUpdates; update++) { 
        // find organism with max behavior value
        Organism& bestOrganism = population[0];
        for(Organism j : population) {
            if (j.behavior > bestOrganism.behavior) {
                bestOrganism = j;
            }
        }

        // replace a random organism in the population with the best organism's child
        Organism* newOrganism = bestOrganism.reproduce(random);
        int overwrite = random.GetUInt(0,100);
        population[overwrite] = *newOrganism;

        if (update == numUpdates - 1) {
            std::cout << bestOrganism.behavior << std::endl;
        }
    }
}