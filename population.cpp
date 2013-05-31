#include "population.h"

bool compare(Gene *g1, Gene *g2) { return g1->fitness() < g2->fitness(); }

Population::Population(int gene_order, int population_size) : _v(), _sumOfFitness(0) {
	int f = 0;
	_generation = 0;

	_minFitness = INT_MAX;
	for (int i=0; i<population_size; i++) {
		Gene *g = new Gene();
		g->generate(gene_order);
		_v.push_back(g);
		f = g->fitness();
		_sumOfFitness += f;
		if(_minFitness > f) _minFitness = f;
	}
	sort(_v.begin(), _v.end(), compare);
	_best = new Gene(_v.back());
}


void Population::nextGeneration(Crossover xover, Replace replace, double uniform_threshold, double mutation_rate, Optimize opt) {
	vector<Gene *>::iterator it;

	int k = 0;
	switch(replace) {
		case STATIC:
			k = 1;
			break;
		case HALF:
			k = _v.size() / 2;
			break;
		case GENERATION:
			k = _v.size();
			break;
	}

	int mutation_count = 0;

	for(int i=0; i<k; i++) {
		int g1_p = _select();
		int g2_p = _select();
		Gene *g1 = _v[g1_p];
		Gene *g2 = _v[g2_p];
		int replace_position = 0;
	
		// crossover
		Gene *n = Gene::crossover(g1, g2, xover, uniform_threshold);

		// mutation
		if(n->mutation(mutation_rate)){
			mutation_count++;
		}

		// local optimization
		if(opt == ORIGIN) n->optimize();
		else n->optimize_new(opt);

		_v.push_back(n);
		
		if(n->fitness() > g1->fitness() && n->fitness() > g2->fitness()){
			if(Gene::numberSameBits(g1, n) > Gene::numberSameBits(g2, n)) replace_position = g1_p;
			else replace_position = g2_p;
		} else {
			replace_position = 0;
		}

		_sumOfFitness += n->fitness();
		_sumOfFitness -= _v[replace_position]->fitness();
		delete _v[replace_position];
		_v.erase(_v.begin() + replace_position);
	}

#if SHOW_LOG
	cout << "mutation count : " << mutation_count << endl;
#endif

	sort(_v.begin(), _v.end(), compare);

	if(_best) delete _best;
	_best = new Gene( _v.back());
	_minFitness = _v.front()->fitness();
	_generation++;
}

int Population::_select() {
	// Define your selection algorithm here ..

	int size = _v.size();
	int total = _sumOfFitness;
	if(_minFitness < 0) {
		total += -1 * ( _minFitness * size );
	}
	int point = rand() % total;
	int sum = 0;
	for(int i=0; i<size; i++) {
		sum += _v[i]->fitness() - ( _minFitness < 0 ? _minFitness : 0 );
		if(point < sum) return i;
	}
	cerr << "_sumOfFitness : " << _sumOfFitness << ", _minFitness : " << _minFitness << ", sum : " << sum << ", point : " << point << endl;

	exit(-1);
}

Gene *Population::best() {
	return _best;
}

ostream &operator<<(ostream &os, const Population &population) {
	vector<Gene *>::const_iterator it;
#if SHOW_LOG
	for(it = population._v.begin(); it != population._v.end(); it++) {
		os << (*it)->fitness() << " ";
	}
#endif
	return os;
}

double Population::average() {
	vector<Gene *>::iterator it;
	double averageFitness = 0.0;
	for(it = _v.begin(); it != _v.end(); it++) {
		averageFitness += (*it)->fitness();
	}
	averageFitness /= (double)_v.size();
	return averageFitness;
}

bool Population::isTerminationCondition(double convergence_threshold) {
	double averageFitness = average();
	double bestFitness = _best->fitness();

	return (bestFitness - averageFitness) / bestFitness < convergence_threshold;
}

void Population::restart(void) {
	int size = _v.size();
	int gene_order = _v[0]->size();
	

	// remain only best solution
	for(int i=0; i<size-1; i++){
		int f = _v[i]->fitness();
		delete _v[i];
		_sumOfFitness -= f;

		Gene *g = new Gene();
		g->generate(gene_order);
		_v[i] = g;
		f = _v[i]->fitness();
		_sumOfFitness += f;
	}
	sort(_v.begin(), _v.end(), compare);
	_minFitness = _v.front()->fitness();
}
