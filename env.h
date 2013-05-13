#ifndef ENV_H
#define ENV_H

#include <stdio.h>
#include <stdlib.h>

#include <utility>
#include <vector>
#include <map>

#include <ostream>
#include <iostream>

#define TIME_LIMIT 30
#define SHOW_LOG 0
#define RELEASE 0
#define EXPERIMENT 0
#define POPULATION_SIZE 100
#define CROSSOVER 0
#define MUTATION_RATE 0.3
#define REPLACE 1
#define CONVERGENCE_THRESHOLD 0.001
#define UNIFORM_THRESHOLD 0.5

enum Crossover {
	UNIFORM,
	ONE_POINT
};

enum Replace {
	STATIC,
	HALF,
	GENERATION
};

#endif
