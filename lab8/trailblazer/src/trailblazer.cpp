// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

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
// TODO: include any other headers you need; remove this comment
using namespace std;

vector<Vertex*> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    vector<Vertex*> path;
    stack<Vertex*> stack;

    graph.resetData();

    stack.push(start);
    start->visited = true;

    //dfs
    while (!stack.empty()) {
        Vertex* current = stack.top();

        if (current == end) {
            break;
        }

        bool pushed = false;
        for (auto i = current->arcs.begin(); i != current->arcs.end(); ++i) {
            if ((*i)->finish != nullptr && !(*i)->finish->visited) {
                stack.push((*i)->finish);
                (*i)->finish->visited = true;
                pushed = true;
                break;
            }
        }

        //deadend
        if (!pushed) {
            stack.pop();
            current->setColor(GRAY);
        }
    }

    // copy elements to path
    while (!stack.empty()) {
        path.push_back(stack.top());
        stack.top()->setColor(GREEN);
        stack.pop();
    }

    reverse(path.begin(), path.end());

    return path;
}

vector<Vertex*> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    vector<Vertex*> path;
    queue<Vertex*> q;

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
            // copy t path
            while (current != nullptr) {
                path.push_back(current);
                current = parent[current];
            }
            reverse(path.begin(), path.end());
            break;
        }

        //samma som dfs ingen break
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


vector<Node*> dijkstrasAlgorithm(BasicGraph& graph, Node* start, Node* end) {
    vector<Node*> path;
    PriorityQueue<Node*> pq;
    graph.resetData();

    for (Node* node : graph.getNodeSet()) {
        node->cost = numeric_limits<double>::infinity();
    }

    start->cost = 0;
    pq.enqueue(start, start->cost);
    start->setColor(YELLOW);

    while (!pq.isEmpty()) {
        Node* current = pq.dequeue();

        //Markera finalized
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

        for (auto i = current->arcs.begin(); i != current->arcs.end(); ++i) {
            Node* neighbor = (*i)->finish;
            double newCost = current->cost + (*i)->cost;  //Calculate newcost

            if (!neighbor->visited || newCost < neighbor->cost) {
                // om en billagre path hitaas t neigbour
                if (newCost < neighbor->cost) {
                    neighbor->cost = newCost;
                    neighbor->previous = current;
                    pq.enqueue(neighbor, newCost);
                    neighbor->setColor(YELLOW);
                }
                else {
                    // om kostnad redan updaterad måste prioritetskö ändras accrodinly
                    pq.changePriority(neighbor, newCost);
                }
            }
        }
    }
    return path;
}

vector<Node*> aStar(BasicGraph& graph, Node* start, Node* end) {
    vector<Node*> path;
    PriorityQueue<Node*> pq;
    graph.resetData();

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

        // Markera hanterad
        if (current->visited) continue;
        current->visited = true;
        current->setColor(GREEN);

        if (current == end) {
            //copy to paht
            while (current != nullptr) {
                path.push_back(current);
                current = current->previous;
            }
            reverse(path.begin(), path.end());
            break;
        }

        for (auto i = current->arcs.begin(); i != current->arcs.end(); ++i) {
            Node* neighbor = (*i)->finish;
            double newCost = current->cost + (*i)->cost;  //g(n) kosntad att komma t nod

            if (!neighbor->visited || newCost < neighbor->cost) {
                // Updatera cost o previous
                neighbor->cost = newCost;
                neighbor->previous = current;

                pq.enqueue(neighbor, neighbor->cost + neighbor->heuristic(end));
                neighbor->setColor(YELLOW);
            }
        }
    }

    return path;
}
