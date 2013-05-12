#include "gene.h"

vector<pair<pair<int, int>, int> > * Gene::_edges = NULL;
multimap<int, pair<int, int> > * Gene::_links = NULL;

Gene::Gene()
{}

Gene::Gene(const Gene *g) :
	_v(g->_v), _fitness(g->_fitness)
{}

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
	vector<bool>::iterator it = _v.begin();
	for(it = _v.begin(); it != _v.end(); it++) {
		if(*it) os << it - _v.begin() + 1 << " ";
	}
	os << endl;


	for(it = _v.begin(); it != _v.end(); it++) {
		if(!*it) os << it - _v.begin() + 1 << " ";
	}
	os << endl;
}

void Gene::optimize(){
	int size = _v.size();
	vector<int> p;
	vector<bool> v(_v.begin(), _v.end());
	p.resize(size);

	for(int i=0; i<size; i++){
		p[i] = i;
	}
	random_shuffle(p.begin(), p.end());

	bool improved = true;
	int f = _fitness;
	while(improved){
		improved = false;
		for(int i=0; i<size; i++){
			pair<multimap<int, pair<int, int> >::iterator, multimap<int, pair<int, int> >::iterator> it_pair;
			multimap<int, pair<int, int> >::iterator it;
			it_pair = _links->equal_range(p[i]);
			int delta_f = 0;
			for(it = it_pair.first; it != it_pair.second; it++){
				pair<int, int> l = it->second;
				if(v[p[i]] ^ v[l.first]) delta_f -= l.second;
				else delta_f += l.second;
			}

			if(delta_f > 0){
				improved = true;
				v[p[i]] = !v[p[i]];
				f += delta_f;
			}
		}
	}
	_v.clear();
	_v.assign(v.begin(), v.end());
	_fitness = f;
	_normalize();
}

ostream &operator<<(ostream &os, const Gene& gene) {
#if SHOW_LOG
	os << "\tfirst : ";
	vector<bool>::const_iterator it = gene._v.begin();
	for(it = gene._v.begin(); it != gene._v.end(); it++) {
		if(*it) os << it - gene._v.begin() + 1 << " ";
	}
	os << endl;


	os << "\tsecond : ";
	for(it = gene._v.begin(); it != gene._v.end(); it++) {
		if(!*it) os << it - gene._v.begin() + 1 << " ";
	}
	os << endl;

	os << "\tfitness : " << gene.fitness() << endl;
#else
	os << gene.fitness() << endl;
#endif
	return os;
}
