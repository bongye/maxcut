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
#define SHOW_LOG 0
#define RELEASE 0
#define EXPERIMENT 1
#define POPULATION_SIZE 50
#define CROSSOVER 0
#define MUTATION_RATE 0.01
#define REPLACE 2
#define CONVERGENCE_THRESHOLD 0.001
#define UNIFORM_THRESHOLD 0.5
#define OPTIMIZE 3

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
