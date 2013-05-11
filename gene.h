#ifndef GENE_H
#define GENE_H

#include "env.h"

using namespace std;

class Gene {
	public:
		static void initEdges(vector<pair<pair<int, int>, int> > * edges) { _edges = edges; };
		static Gene *crossover(Gene*, Gene*, Crossover, double);

		void generate(int);
		int fitness() const;
		int size();
		bool mutation(double);

		void print(ostream&);
		friend ostream& operator<<(ostream&, const Gene&);

	private:
		vector<bool> _v;
		int _fitness;
		static vector<pair<pair<int, int>, int> > * _edges;

		void _calculateFitness();
		void _normalize();
};

#endif
