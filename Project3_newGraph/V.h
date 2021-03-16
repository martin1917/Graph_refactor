#pragma once

class Graph;

class V {
private:
	int num;  //vertex number
	string data;  //data into vertex
	V* next;  //next vertex into graph
	bool inGraph;  //vertex into the graph?
	void init();  //initial method

public:
	V();  //constructor
	V(string data);  //constructor with data
	V(V*& v);  //copy constructor

	void setNum(int num);
	int getNum();

	void setData(string data);
	string getData();

	void setNext(V* v);
	V* getNext();

	void setInGraph(bool inGraph);
	bool getInGraph();

	void writeData();  //write data into the txt file
	void writeData(string fileName);  //write data into the txt file where name = fileName
	void readData(string fileName);  //read data from txt file where name = fileName
};