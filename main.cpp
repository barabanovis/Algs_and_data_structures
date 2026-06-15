#include "libs/Graph.h"
#include <string>

using namespace std;

int main() {
  	Graph<string, double> graph; 
	graph.add_vertex("mother");
	graph.add_vertex("father");
	graph.add_vertex("son");

	graph.add_edge("mother", "son", 3);
	graph.add_edge("son", "father", 5);
	graph.add_edge("father", "mother", 5);
	
	
	

	graph.print(cout);

	vector<Graph<string, double>::Edge> path = graph.shortest_path("mother", "father");
	for (auto u : path) {
		cout << u.from << " " << u.to << '\n';
	}
}