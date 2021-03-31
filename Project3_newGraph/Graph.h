#pragma once
/*
	20ВП1 Лёвин Максим
	Ориентированный граф
*/
class V;

class Graph{
private:
	vector<V*> vertexes; // vector of vertexes (this graph)
	string** matrix;  //adjacency matrix
	int lastNum; //Last number added vertex 
	int lengthMatrix;  // Length of matrix
	bool matrix_created; // matrix was created?
	void refresh(V* v);  //update matrix
	int get_abs_index(int i);  //abs index in array
	bool has_edge(V* v1, V* v2); //v1 has edge with v2?

public:
	Graph();
	~Graph();
	vector<V*> getVertexes();
	string** getMatrix();
	void add_v(V* v);  //add vertex
	void make_edge(V* v1, V* v2);  //connect v1 with v2 where edge = 1
	void make_edge(V* v1, V* v2, int weight); //connect v1 with v2 where edge = weight
	void delete_v(V* v);  //delete vertex
	void delete_e(V* v1, V* v2); //delete edge between v1 and v2
	void create_matrix();  //create matrix
	void setDataInVertex(V* v, string data);  //set data into graph

	Graph& operator =(Graph& graph);
	friend ostream& operator<<(ostream& out, Graph& graph);  //output graph in console
};