#ifndef ENV_H
#define ENV_H

#include <stdio.h>
#include <stdlib.h>

#include <utility>
#include <vector>
#include <map>

#include <ostream>
#include <iostream>
#include <climits>

#define TIME_LIMIT 175
#define SHOW_LOG 1
#define RELEASE 0
#define EXPERIMENT 0
#define POPULATION_SIZE 100
#define CROSSOVER 0
#define MUTATION_RATE 0.01
#define REPLACE 0
#define CONVERGENCE_THRESHOLD 0.01
#define UNIFORM_THRESHOLD 0.5
#define OPTIMIZE 1

enum Crossover {
	UNIFORM,
	ONE_POINT,
	FIVE_POINT
};

enum Replace {
	STATIC,
	HALF,
	GENERATION
};

enum Optimize {
	ORIGIN,
	FM,
	LG,
	RG
};

#endif
