#include "gene.h"

vector<pair<pair<int, int>, int> > * Gene::_edges = NULL;

void Gene::generate(int size) {
	_v.resize(size);
	for (int i=0; i<size; i++) {
		_v[i] = rand() % 2 == 0;
	}
	
	_normalize();
	_calculateFitness();
}

int Gene::fitness() const {
	return _fitness;
}

int Gene::size() {
	return _v.size();
}

void Gene::_normalize() {
	// vertex number 1 should be in group 1.
	int size = _v.size();
	if(!_v[0]) {
		for(int i=0; i<size; i++){
			_v[i] = !_v[i];
		}
	}
}

void Gene::_calculateFitness() {
	vector<pair<pair<int, int>, int> > edges = *(_edges);
	int s = edges.size();
	int f = 0;
	for (int i=0; i<s; i++) {
		pair<pair<int, int>, int> p = edges[i];
		f += (_v[p.first.first] ^ _v[p.first.second]) * p.second;
	}
	_fitness = f;
}

Gene *Gene::crossover(Gene *g1, Gene *g2, Crossover xover, double uniform_threshold) {
	// Define your crossover algorithm here ..
	
	Gene *result = new Gene();
	int size;
	int mid;
	switch (xover) {
		case UNIFORM:
			size = g1->_v.size();
			result->_v.resize(size);
			for (int i=0; i<size; i++) {
				double random = ((double)rand()/(double)RAND_MAX);
				result->_v[i] = (random > uniform_threshold) ? g1->_v[i] : g2->_v[i];		
			}
			break;
		case ONE_POINT:
			size = g1->_v.size();
			mid = rand() % size;
			result->_v.insert(result->_v.end(), g1->_v.begin(), g1->_v.begin() + mid);
			result->_v.insert(result->_v.end(), g2->_v.begin() + mid, g2->_v.end());
			break;
	}
	result->_normalize();
	result->_calculateFitness();
	return result;
}

bool Gene::mutation(double mutation_rate) {
	// Define your mutation algorithm here ..
	int size = _v.size();
	bool change = false;
	double random = ((double)rand()/(double)RAND_MAX);
	
	if(random < mutation_rate) {
		int l = rand() % size;
		_v[l] = _v[l] ^ 1;
		change = true;
	}

	if(change){
		_normalize();
	  _calculateFitness();
	}
	return change;
}

void Gene::print(ostream &os) {
	int size = _v.size();
	for(int i=0; i<size; i++) {
		if(_v[i]) {
			os << i+1 << " ";
		}
	}
	os << endl;


	for(int i=0; i<size; i++) {
		if(!_v[i]) {
			os << i+1 << " ";
		}
	}
	os << endl;
}

ostream &operator<<(ostream &os, const Gene& gene) {
	int size = gene._v.size();
#if SHOW_LOG
	os << "\tfirst : ";
	for(int i=0; i<size; i++) {
		if(gene._v[i]) {
			os << i+1 << " ";
		}
	}
	os << endl;


	os << "\tsecond : ";
	for(int i=0; i<size; i++) {
		if(!gene._v[i]) {
			os << i+1 << " ";
		}
	}
	os << endl;

	os << "\tfitness : " << gene.fitness() << endl;
#else
	os << gene.fitness() << endl;
#endif
	return os;
}
