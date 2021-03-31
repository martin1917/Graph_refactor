#include "Classes.h"
/*
	20ВП1 Лёвин Максим
	Ориентированный граф
*/
V::V(){
	init();
}
V::V(string data) {
	init();
	this->data = data;
}
V::V(V*& v) {
	this->num = v->num;
	this->data = v->data;
	this->inGraph = false;
}

void V::init() {
	num = 0;
	next = nullptr;
	inGraph = false;
}

void V::setNum(int num) {
	this->num = num;
}
int V::getNum() {
	return num;
}

void V::setData(string data) {
	this->data = data;
}
string V::getData() {
	return data;
}

void V::setNext(V* v) {
	this->next = v;
}
V* V::getNext() {
	return next;
}

void V::setInGraph(bool inGraph) {
	this->inGraph = inGraph;
}
bool V::getInGraph() {
	return this->inGraph;
}

V::~V() {
	cout << "\nVertex is deleted\n" << endl;
}

void V::writeData(){
	if (this != nullptr && this->getInGraph()) {
		string name = "test" + to_string(this->getNum());
		writeData(name);
	}
}

void V::writeData(string fileName){
	if (this->getInGraph()) {
		ofstream fout;
		string path = PATH + "\\" + fileName + ".txt";
		fout.open(path);
		if (!fout.is_open()) {
			cout << "file can`t be opened" << endl;
		}
		else {
			V* curr = this;
			while (curr != nullptr) {
				if (curr->getData() != "")
					fout << curr->getNum() << ": " << curr->getData() << endl;
				curr = curr->next;
			}
		}
		fout.close();
	}
}

void V::readData(string fileName) {
	ifstream ifs;
	string path = PATH + "\\" + fileName + ".txt";
	string line;
	ifs.open(path);
	if (!ifs.is_open())
	{
		cout << "file can`t be opened" << endl;
	}
	else {
		while (getline(ifs, line)) {
			string old_data = this->getData();
			this->setData(old_data + line + "\n");
		}
	}
	ifs.close();
}