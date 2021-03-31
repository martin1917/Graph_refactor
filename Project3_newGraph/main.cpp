#include "Classes.h"
/*
	20ВП1 Лёвин Максим
	Ориентированный граф
*/
int main() {
	Graph graph;
	vector<V*> vertexes;

	for (int i = 0; i < 5; i++) {
		vertexes.push_back(new V());
	}
	for (int i = 0; i < 5; i++) {
		graph.add_v(vertexes[i]);
	}
	graph.create_matrix();

	graph.make_edge(vertexes[1], vertexes[2], 20);

	graph.make_edge(vertexes[0], vertexes[1], 10);
	graph.make_edge(vertexes[0], vertexes[2]);
	graph.make_edge(vertexes[0], vertexes[3], 30);
	graph.make_edge(vertexes[0], vertexes[4], 3);

	cout << graph;
	cout << "================================================================================" << endl;

	V* v = new V();
	graph.add_v(v);
	cout << graph;
	cout << "================================================================================" << endl;

	graph.make_edge(vertexes[4], vertexes[3], 24);
	graph.delete_e(vertexes[1], vertexes[2]);

	graph.setDataInVertex(vertexes[0], "hello ");
	graph.setDataInVertex(vertexes[1], "world");
	graph.setDataInVertex(vertexes[2], "Maksim");
	graph.setDataInVertex(vertexes[3], "Levin");
	cout << graph;
	cout << "================================================================================\n" << endl;

	Graph graph2;
	graph2 = graph;
	
	cout << endl;
	cout << endl;
	cout << endl;
	
	auto vers = graph2.getVertexes();
	graph2.delete_v(vers[3]);

	cout << graph2;
	return 0;
}