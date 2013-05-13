#include <unistd.h>
#include <signal.h>

#include <fstream>
#include <sstream>

#include "env.h"
#include "gene.h"
#include "population.h"

using namespace std;

Population *population;
ofstream output;

void signal_handler(int sig) {
	// output file printing ..
#if SHOW_LOG
	cout << "Time Over !" << endl;
	cout << "Best Solution : " << endl;
	cout << *(population->best()) << endl;
#else
#if RELEASE
#else
	cout << *(population->best());
#endif
#endif
	population->best()->print(output);
	exit(EXIT_SUCCESS);
}

int main(int argc, char **argv) {
	signal(SIGALRM, signal_handler);
	alarm(TIME_LIMIT);

#if EXPERIMENT
	if(argc != 8) {
		cout << "Usage : " << argv[0] << " [input file path] [output file path] [pool size] [crossover] [mutation_rate] [replace_policy] [convergence_threshold]" << endl;
		return -1;
	}
#else
	if(argc != 3) {
		cout << "Usage : " << argv[0] << " [input file path]" << " [output file path]" << endl;
		return -1;
	}
#endif

	ifstream input(argv[1]);
	output.open(argv[2]);
	string line;
	int i = 0;
	int gene_order = 0;
	int edge_number = 0;
	vector<pair<pair<int, int>, int> > edges;
	multimap<int, pair<int, int> > links;


	// input file tokenizing ..
	if (input.is_open()) {
		while(getline(input, line)) {
			stringstream stream(line);
			string token;

			if(i == 0) {
				stream >> token;
				gene_order = atoi(token.c_str());
				stream >> token;
				edge_number = atoi(token.c_str());

				edges.resize(edge_number);
			} else {
				stream >> token;
				int i = atoi(token.c_str());
				stream >> token;
				int j = atoi(token.c_str());
				stream >> token;
				int weight = atoi(token.c_str());

				pair <int, int> p1(i-1, j-1);
				pair <pair<int, int>, int> p2(p1, weight);
				pair <int, int> p3(j-1, weight);
				pair <int, pair<int, int> > p4(i-1, p3);
				pair <int, int> p5(i-1, weight);
				pair <int, pair<int, int> > p6(j-1, p5);
				edges.push_back(p2);
				links.insert(p4);
				links.insert(p6);
			}
			i++;
		}
		input.close();
	}
	
	Gene::initEdges(&edges);
	Gene::initLinks(&links);

#if EXPERIMENT
	int population_size = atoi(argv[3]);
	Crossover xover = (Crossover)atoi(argv[4]);
	double mutation_rate = atof(argv[5]);
	double uniform_threshold = UNIFORM_THRESHOLD;
	Replace replace = (Replace)atoi(argv[6]);
	double convergence_threshold = atof(argv[7]);
#else
	int population_size = POPULATION_SIZE;
	Crossover xover = (Crossover)CROSSOVER;
	double mutation_rate = MUTATION_RATE;
	double uniform_threshold = UNIFORM_THRESHOLD;
	Replace replace = (Replace)REPLACE;
	double convergence_threshold = CONVERGENCE_THRESHOLD;
#endif

	srand(time(NULL));
	population = new Population(gene_order, population_size);
	i = 0;

#if SHOW_LOG
	cout << "Generation " << i+1 << endl;
	cout << "Farm : " << *population << endl;
	cout << "Average : " << population->average() << endl;
	cout << endl;
#endif

	while(!population->isTerminationCondition(convergence_threshold)) {
		population->nextGeneration(xover, replace, uniform_threshold, mutation_rate);
		i++;

#if SHOW_LOG
		cout << "Generation " << i+1 << endl;
		cout << "Farm : " << *population << endl;
		cout << "Average : " << population->average() << endl;
		cout << endl;
#endif
	}

#if SHOW_LOG
	cout << "Pass termination condition!" << endl;
	cout << "Best Solution : " << endl;
	cout << *(population->best());
#else
#if RELEASE
#else
	cout << *(population->best());
#endif
#endif

	population->best()->print(output);

	return 0;
}
