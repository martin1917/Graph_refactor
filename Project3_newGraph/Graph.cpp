#include "Classes.h"

Graph::Graph() {
	matrix_created = false;
	lengthMatrix = 0;
	lastNum = 0;
}

vector<V*> Graph::getVertexes() {
	return vertexes;
}

string** Graph::getMatrix() {
	return matrix;
}

int Graph::get_abs_index(int i1) {
	int index = 0;
	for (int i = 0; i < vertexes.size() + 1; i++) {
		if (to_string(i1) == matrix[0][i]) {
			index = i;
			break;
		}
	}
	return index;
}

void Graph::create_matrix() {
	if(!matrix_created){
		matrix_created = true;
		int size = vertexes.size();
		lengthMatrix = size + 1;
		matrix = new string* [lengthMatrix];
		for (int i = 0; i < lengthMatrix; i++) {
			matrix[i] = new string[lengthMatrix];
			for (int j = 0; j < lengthMatrix; j++) {
				if (i == 0 && j == 0) matrix[i][j] = "";
				else if (i == 0) matrix[i][j] = to_string(vertexes[j - 1]->getNum());
				else if (j == 0) matrix[i][j] = to_string(vertexes[i - 1]->getNum());
				else matrix[i][j] = to_string(0);
			}
		}
	}
}

void Graph::add_v(V* v) {
	v = v->getInGraph() ? new V(v) : v; //хз работает или нет
	v->setNum(lastNum++);
	vertexes.push_back(v);
	setDataInVertex(v, v->getData());
	if (matrix_created) {
		refresh(v);
	}
	if(!v->getInGraph())
		v->setInGraph(true);
}

void Graph::delete_v(V* v) {
	vector<V*>::iterator it;
	it = find(vertexes.begin(), vertexes.end(), v);
	if(it != vertexes.end()) {
		for (auto vertex : vertexes){
			if (vertex != nullptr && vertex->getNum() == v->getNum()) continue;
			V* end = vertex;
			V* curr = vertex->getNext();
			while (curr != nullptr && curr->getNum() != v->getNum()) {
				end = curr;
				curr = curr->getNext();
			}
			if (curr != nullptr){
				end->setNext(curr->getNext());
				delete curr;
			}
		}

		vertexes.erase(it);
		refresh(v);

		V* tmp = v;
		V* prev = nullptr;
		while (tmp != nullptr) {
			prev = tmp;
			tmp = tmp->getNext();
			delete prev;
		}
		
	}
}

void Graph::make_edge(V* v1, V* v2) {
	make_edge(v1, v2, 1);
}

void Graph::make_edge(V* v1, V* v2, int weight){
	vector<V*>::iterator it1 = find(vertexes.begin(), vertexes.end(), v1);
	vector<V*>::iterator it2 = find(vertexes.begin(), vertexes.end(), v2);
	if (it1 != vertexes.end() && it2 != vertexes.end()){
		V* v = new V(v2);
		v->setInGraph(true);
		if (v1->getNext() == nullptr) {
			v1->setNext(v);
		}
		else {
			V* curr = v1->getNext();
			while (curr->getNext() != nullptr) {
				curr = curr->getNext();
			}
			if (!has_edge(v1, v)) {
				curr->setNext(v);
			}
		}

		if (matrix_created && v1 != nullptr && v != nullptr) {
			int i = get_abs_index(v1->getNum());
			int j = get_abs_index(v->getNum());
			matrix[i][j] = to_string(weight);
		}
	}
}

void Graph::delete_e(V* v1, V* v2){
	vector<V*>::iterator it1 = find(vertexes.begin(), vertexes.end(), v1);
	vector<V*>::iterator it2 = find(vertexes.begin(), vertexes.end(), v2);
	if (it1 != vertexes.end() && it2 != vertexes.end()){
		V* curr = v1;
		V* prev = nullptr;
		while(curr != nullptr && curr->getNum() != v2->getNum()){
			prev = curr;
			curr = curr->getNext();
		}
		if (curr != nullptr){
			prev->setNext(curr->getNext());
			int i = get_abs_index(v1->getNum());
			int j = get_abs_index(v2->getNum());
			matrix[i][j] = to_string(0);
		}
	}
}

bool Graph::has_edge(V* v1, V* v2){
	bool has_edge = false;
	vector<V*>::iterator it1 = find(vertexes.begin(), vertexes.end(), v1);
	vector<V*>::iterator it2 = find(vertexes.begin(), vertexes.end(), v2);
	if (it1 != vertexes.end() && it2 != vertexes.end()) {
		if (v1->getNext() == nullptr) {
			has_edge = false;
		}
		else {
			V* curr = v1->getNext();
			while (curr != nullptr) {
				if (curr->getNum() == v2->getNum()) {
					has_edge = true;
					break;
				}
				curr = curr->getNext();
			}
		}
		return has_edge;
	}
	return false;
}

void Graph::refresh(V* v) {
	int size = vertexes.size(); //текущее кол-во вершин
	int lengthMatrix_new = size + 1;
	string** matrix_new = new string* [lengthMatrix_new];
	for (int i = 0; i < lengthMatrix_new; i++) {
		matrix_new[i] = new string[lengthMatrix_new];
	}

	if (lengthMatrix_new > lengthMatrix) { //добавление вершины
		for (int i = 0; i < lengthMatrix_new - 1; i++) {
			for (int j = 0; j < lengthMatrix_new - 1; j++) {
				matrix_new[i][j] = matrix[i][j];
			}
		}

		matrix_new[0][lengthMatrix_new - 1] = to_string(v->getNum());
		matrix_new[lengthMatrix_new - 1][0] = to_string(v->getNum());

		for (int i = 1; i < lengthMatrix_new; i++) {
			matrix_new[i][lengthMatrix_new - 1] = to_string(0);
			matrix_new[lengthMatrix_new - 1][i] = to_string(0);
		}
	}
	else if (lengthMatrix_new < lengthMatrix) { //удаление вершины
		int index = get_abs_index(v->getNum());
		int r = 0;
		int c = 0;
		for (int i = 0; i < lengthMatrix_new + 1; i++) {
			if (i == index) continue;
			for (int j = 0; j < lengthMatrix_new + 1; j++) {
				if (j == index) continue;
				matrix_new[r][c++] = matrix[i][j];
			}
			r++;
			c = 0;
		}
	}

	for (int i = 0; i < lengthMatrix; i++) {
		delete[] matrix[i];
	}
	delete matrix;

	matrix = matrix_new;
	lengthMatrix = lengthMatrix_new;
}

void Graph::setDataInVertex(V* v, string data){
	vector<V*>::iterator it;
	it = find(vertexes.begin(), vertexes.end(), v);
	if (it != vertexes.end()) {
		for (auto vertex : vertexes) {
			V* end = vertex;
			V* curr = vertex == nullptr ? nullptr : vertex->getNext();

			if (end != nullptr && end->getNum() == v->getNum()) {
				vertex->setData(data);
			}
			else {
				while (curr != nullptr && curr->getNum() != v->getNum()) {
					end = curr;
					curr = curr->getNext();
				}
				if (curr != nullptr) {
					curr->setData(data);
				}
			}
		}
	}
}

ostream& operator<<(ostream& out, Graph*& graph) {
	for (int i = 0; i < graph->lengthMatrix; i++) {
		for (int j = 0; j < graph->lengthMatrix; j++) {
			out << graph->matrix[i][j] << "\t";
		}
		out << "\n";
	}
	return out;
}