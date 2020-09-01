#include "node.h"
#include <climits>
#include <cstdio>

#define INF INT_MAX

node::node() {
	this->obstacle = 0;
	this->start = 0;
	this->goal = 0;
	this->parent = nullptr;
	this->cost = INF;
}

node::node(int x, int y) {
	this->x = x;
	this->y = y;
	this->obstacle = 0;
	this->start = 0;
	this->goal = 0;
	this->parent = nullptr;
	this->cost = INF;
}