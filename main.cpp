#include <iostream>
#include "Empirical/include/emp/math/Random.hpp"

int main() {
    class Organism {
      public:
        double behavior;
        Organism(double x) {
            behavior = x;
        }
        Organism reproduce() {
            return *new Organism(behavior);
        }
    };   

    emp::vector<Organism> population;
    for (int i = 0; i < 100; i++) {
        population.push_back(*new Organism(0.5));
    }
    std::cout << population[4].behavior << std::endl;

    Organism parent = *new Organism(1);
    Organism child = parent.reproduce();
    std::cout << child.behavior << std::endl;

    for (int update = 0; update < 100; update++) {
        
    }

    Organism bestOrganism = population[0];
    for(Organism j : population) {
        if (j.behavior > bestOrganism.behavior) {
            bestOrganism = j;
        }
    }
    
    Organism newOrganism = bestOrganism.reproduce();
}