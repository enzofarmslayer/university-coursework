/*
 * This file defines the four (4) different algorithms that are created
 * to find the shortest path from one point to another in both the maze
 * and terrain maps.
 *
 * Developers: kevma271, enzcu445
 */

#include "costs.h"
#include "trailblazer.h"
#include <stack>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <pqueue.h>
#include <limits>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

/*
 * Searches in a path until it reaches the goal
 * or a stop, which it then backtracks and tries
 * another path.
 */
vector<Vertex*> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    vector<Vertex*> path;
    stack<Vertex*> stack;

    // Make sure that the data doesn't contain trash
    graph.resetData();

    stack.push(start);
    start->visited = true;

    while (!stack.empty()) {
        Vertex* current = stack.top();

        if (current == end) {
            break;
        }

        bool pushed = false;

        // Loop through all nieghbours of a node
        for (auto i = current->arcs.begin(); i != current->arcs.end(); ++i) {

            // If the neighbour hasn't been visited and isn't null
            if ((*i)->finish != nullptr && !(*i)->finish->visited) {

                // Push the neighbour and loop through its' neighbours
                stack.push((*i)->finish);
                (*i)->finish->visited = true;
                pushed = true;
                break;
            }
        }

        // If no neighbours are found of a node
        if (!pushed) {
            stack.pop();
            current->setColor(GRAY);
        }
    }

    // Copy all elements from stack to path
    while (!stack.empty()) {
        path.push_back(stack.top());
        stack.top()->setColor(GREEN);
        stack.pop();
    }

    reverse(path.begin(), path.end());

    return path;
}

/*
 * Instead of searching in one direction until a dead end,
 * we search in all directions. Switching between the nodes
 * so that we are going in multiple paths "simoultanesously".
 */
vector<Vertex*> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    vector<Vertex*> path;
    queue<Vertex*> q;

    // Remove garbage
    graph.resetData();

    q.push(start);
    start->visited = true;
    start->setColor(YELLOW);

    unordered_map<Vertex*, Vertex*> parent;

    while (!q.empty()) {
        Vertex* current = q.front();
        q.pop();
        current->setColor(GREEN);

        if (current == end) {

            while (current != nullptr) {
                path.push_back(current);
                current = parent[current];
            }
            reverse(path.begin(), path.end());
            break;
        }

        // Similair to DFS but we don't break once we find a valid neighbour
        for (auto i = current->arcs.begin(); i != current->arcs.end(); ++i) {
            Vertex* neighbor = (*i)->finish;
            if (neighbor != nullptr && !neighbor->visited) {
                q.push(neighbor);
                neighbor->visited = true;
                neighbor->setColor(YELLOW);
                parent[neighbor] = current;
            }
        }
    }

    return path;
}


/*
 * Djikstra utilizes cost on nodes to determine
 * which path leads to the shortest one.
 */
vector<Node*> dijkstrasAlgorithm(BasicGraph& graph, Node* start, Node* end) {
    vector<Node*> path;
    PriorityQueue<Node*> pq;
    graph.resetData();

    // Set nodes to infinity so all comparisons work first time
    for (Node* node : graph.getNodeSet()) {
        node->cost = numeric_limits<double>::infinity();
    }

    start->cost = 0;
    pq.enqueue(start, start->cost);
    start->setColor(YELLOW);

    while (!pq.isEmpty()) {
        Node* current = pq.dequeue();

        //Mark finalized
        if (current->visited) continue;
        current->visited = true;
        current->setColor(GREEN);

        if (current == end) {
            while (current != nullptr) {
                path.push_back(current);
                current = current->previous;
            }
            reverse(path.begin(), path.end());
            break;
        }

        // Same as BFS but we also take cost into consideration
        for (auto i = current->arcs.begin(); i != current->arcs.end(); ++i) {
            Node* neighbor = (*i)->finish;
            double newCost = current->cost + (*i)->cost;  //Calculate newcost


            if (newCost < neighbor->cost) {

                neighbor->cost = newCost;
                neighbor->previous = current;

                if (!neighbor->visited) {
                    pq.enqueue(neighbor, newCost);
                    neighbor->setColor(YELLOW);
                }
                else {
                    pq.changePriority(neighbor, newCost);
                }
            }
        }
    }
    return path;
}


/*
 * Similair to djikstra but in this case we also utilize
 * a heuristic to "predict" which is the cheapest path
 * to a node. Resulting in fewer nodes being visited
 * but ultimately creates the same shortest path.'
 */
vector<Node*> aStar(BasicGraph& graph, Node* start, Node* end) {
    vector<Node*> path;
    PriorityQueue<Node*> pq;
    graph.resetData();

    // Set nodes to infinity so all comparisons work first time
    for (Node* node : graph.getNodeSet()) {
        node->cost = std::numeric_limits<double>::infinity();
        node->previous = nullptr;
        node->visited = false;
    }

    //set start
    start->cost = 0;
    pq.enqueue(start, start->cost + start->heuristic(end));  //f(n)=g(n)+h(n)
    start->setColor(YELLOW);

    while (!pq.isEmpty()) {
        Node* current = pq.dequeue();

        // Mark finalized
        if (current->visited) continue;
        current->visited = true;
        current->setColor(GREEN);

        if (current == end) {
            //copy to path
            while (current != nullptr) {
                path.push_back(current);
                current = current->previous;
            }
            reverse(path.begin(), path.end());
            break;
        }

        // Same as BFS but we also take the heuristic cost into consideration
        for (auto i = current->arcs.begin(); i != current->arcs.end(); ++i) {
            Node* neighbor = (*i)->finish;
            double newCost = current->cost + (*i)->cost;

            if(newCost < neighbor->cost){

                neighbor->cost = newCost;
                neighbor->previous = current;

                if (!neighbor->visited) {
                    pq.enqueue(neighbor, neighbor->cost + neighbor->heuristic(end));
                    neighbor->setColor(YELLOW);
                }
                else {
                    pq.changePriority(neighbor, neighbor->cost + neighbor->heuristic(end));
                }
            }
        }
    }
    return path;
}
