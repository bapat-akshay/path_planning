#include "node.cpp"
#include <vector>
#include <iostream>
#include <queue>
#include <unordered_map>

using namespace std;


// Initialize map of nodes with obstacles, start and goal
void initMap(vector<vector<node*> >& map, int mapWidth, int mapHeight, vector<int> obstaclesX, vector<int> obstaclesY, int* start, int* goal) {

	for (int x = 0; x < mapWidth; ++x) {

		for (int y = 0; y < mapHeight; ++y) {
			map[y][x] = new node(x, y);
		}
	}

	for (int x = 0; x < mapWidth; ++x) {

		for (int y = 0; y < mapHeight; ++y) {

			if (y < mapHeight - 1) {
				map[y][x]->neighbors.push_back(map[y + 1][x]);
			}
			if (x < mapWidth - 1) {
				map[y][x]->neighbors.push_back(map[y][x + 1]);
			}
			if (y > 0) {
				map[y][x]->neighbors.push_back(map[y - 1][x]);
			}
			if (x > 0) {
				map[y][x]->neighbors.push_back(map[y][x - 1]);
			}
			
		}
	}

	for (int i = 0; i < obstaclesX.size(); ++i) {
		map[obstaclesY[i]][obstaclesX[i]]->obstacle = 1;
	}

	map[start[1]][start[0]]->start = 1;
	map[start[1]][start[0]]->cost = 0;
	map[goal[1]][goal[0]]->goal = 1;
}


// Return cost from node one to node two
int getCost(node* one, node* two) {
	int dist = abs(one->x - two->x) + abs(one->y - two->y);

	return ((one->obstacle || two->obstacle) ? INF : dist);
}


// Visit all nodes exhaustively using Dijkstra's algorithm, while keeping
// track of shortest distance from the start node
void updateNodes(vector<vector<node*> >& map, node* startNode) {
	queue<node*> nodeQ;
	unordered_map<node*, int> visited, unvisited;
	node* current;
	nodeQ.push(startNode);

	// nodeQ contains nodes that are to be visited. Visiting a node means 
	// iterating through all its neighbors and updating their costs
	while (nodeQ.size()) {
		current = nodeQ.front();
		nodeQ.pop();

		// Iterate through all neighbors
		for (node* n : current->neighbors) {

			// if neighbor is not an obstacle and if it hasn't been visited yet,
			// check if the current path yields a smaller cost. If yes, update
			// the cost.
			if (!(n->obstacle) && !(visited[n])) {

				if (current->cost + getCost(current, n) < n->cost) {
					n->cost = current->cost + getCost(current, n);
					n->parent = current;
				}

				if (!unvisited[n]) {
					// Add each unvisited neighbor to the queue
					nodeQ.push(n);
					++unvisited[n];
				}
			}
		}

		if (visited[current] == 0) {
			++visited[current];
		}
	}
}


// Print shortest path in reverse order, from goal to start
void printPath(vector<vector<node*> >& map, node* start, node* goal) {
	node* current = goal;

	while (current != start) {

		if (current == nullptr) {
			cout << "NULL encountered" << endl;
			return;
		}

		cout << "(" << current->x << "," << current->y << ")" << endl;
		current = current->parent;
	}
	cout << "(" << current->x << "," << current->y << ")" << endl << "Done" << endl;
}


int main() {
	int mapWidth = 100, mapHeight = 100;
	int start[] = {5, 5};
	int goal[] = {90, 90};
	vector<int> obstaclesX, obstaclesY;

	obstaclesX = {10,11,12,13,14,15,15,15,15,15,15,80,80,80,80,80,80,81,82,83,84,85};
	obstaclesY = {15,15,15,15,15,15,14,13,12,11,10,85,84,83,82,81,80,80,80,80,80,80};

	//obstaclesX = {5,6,6,5,6};
	//obstaclesY = {6,6,5,4,4};

	vector<vector<node*> > map (mapHeight, vector<node*> (mapWidth));
	initMap(map, mapWidth, mapHeight, obstaclesX, obstaclesY , start, goal);

	node* startNode = map[start[1]][start[0]];
	node* goalNode = map[goal[1]][goal[0]];

	updateNodes(map, startNode);

	printPath(map, startNode, goalNode);

	return 0;
}