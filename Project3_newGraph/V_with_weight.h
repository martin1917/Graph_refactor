#pragma once

class V;

class V_with_weight : public V{
private:
	int weight;
public:
	V_with_weight(V* v, int weight);
	void setWeight(int weight);
	int getWeight();
};