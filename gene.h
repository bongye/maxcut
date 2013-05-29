#ifndef GENE_H
#define GENE_H

#include "env.h"
#include <math.h>
#include <algorithm>

using namespace std;

class Gene {
	public:
		static void initEdges(vector<pair<pair<int, int>, int> > * edges) { _edges = edges; };
		static void initLinks(multimap<int, pair<int, int> > *links) { _links = links; };
		static void initDegree(double degree) { _degree = degree; };
		static Gene *crossover(Gene*, Gene*, Crossover, double);
		static int numberSameBits(Gene*, Gene*);

		Gene(void);
		Gene(const Gene *);
		void generate(int);
		int fitness(void) const;
		int size(void);
		bool mutation(double);
		void optimize(void);
		void optimize_new(Optimize);

		void print(ostream&);
		friend ostream& operator<<(ostream&, const Gene&);

	private:
		vector<bool> _v;
		int _fitness;
		static vector<pair<pair<int, int>, int> > * _edges;
		static multimap<int, pair<int, int> > *_links;
		static double _degree;

		void _calculateFitness(void);
		void _normalize(void);
};

#endif
