#ifndef POPULATION_H
#define POPULATION_H

#include "env.h"
#include "gene.h"
#include <algorithm>
#include <limits.h>

using namespace std;

class Population {
	public:
		Population(int, int);
		void nextGeneration(Crossover, Replace, double, double, Optimize);
		double average(void);
		Gene *best(void);
		friend ostream &operator<<(ostream &, const Population &);
		bool isTerminationCondition(double);
		void restart(void);

	private:
		vector<Gene *> _v;
		Gene *_best;

		int _select();
		int _minFitness;
		int _sumOfFitness;
		int _generation;
};
#endif
