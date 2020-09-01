#pragma once
#include <string>
#include <vector>

using namespace std;

class node
{
public:
	int obstacle, start, goal;
	int x, y;
	int cost;

	vector<node*> neighbors;
	node* parent;

	node();

	node(int x, int y);

	node(int, int, string);
};

