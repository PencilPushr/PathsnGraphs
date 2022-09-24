#include <iostream>
#include <unordered_map>
#include <string>

#include "locationNode.h"
#include "weightedPath.h"

using std::unordered_map;
using std::string;

//TODO: fix errors on lines 18 and 37 (pair function spits an error)

void update(unordered_map<string, float> *distances, float newDistance, string s){
    //https://stackoverflow.com/questions/15815649/stdunordered-map-pass-by-reference
    if (newDistance == -1.0){
        return;
    }//nothing is bigger than infinity, so reject.

    float oldDistance = distances->at(s);// Get the current distance.
    if (oldDistance == -1.0){// Anything smaller than infinity is allowed.
        distances->insert(std::pair<string,float>(s,newDistance));
        return;
    }
    if (oldDistance > newDistance){//if they are both finite, but the new path is quicker, replace.
        distances->insert(std::pair<string,float>(s,newDistance));
    }
    return;//if all else fails, return
}

void shortestPathSequence(unordered_map<string, locationNode *> *visited, unordered_map<string, locationNode *> *unVisited,  const string& current, const string& end, unordered_map<string, float> *distances){
    if (current == end){return;}//No need to go further, we found it
    vector<weightedPath> paths = unVisited->at(current)->retrieveCopiedPaths(); // get every path from this node.

    for (auto p : paths){
        // Check every connected node and update its distance;
        // each path check its weight, update by passing our index + weight we are at
        float newDistance = distances->at(current) + p.getWeight();
        update(distances,newDistance,p.getFinish()->getName());
    }

    //Now that every node has been checked, this is a VISITED node.
    visited->insert(std::pair<string,locationNode *>(current,unVisited->at(current)));
    unVisited->erase(current);
    // Now go again from the unvisited node with the shortest tentative distance
    float d = 16.0;
    while (d != -1.0){//run until all tentative distances left are infinite
        d = -1.0;
        float c = -1.0;
        string s = "";
        for (auto &u : *(unVisited)){
            c = distances->at(u.first);
            if (d == -1.0 && c != -1.0){//shorter than infinity
                d = c;
                s = u.first;
            } else if (c != -1.0 && c < d){//shorter than finite
                d = c;
                s = u.first;
            } else {
                //do nothing!!!
            }
        }//loop while
        if (d != -1.0){// Run again for the next node, if we found a non-infinite path
            shortestPathSequence(visited,unVisited,s,end,distances);
        }
    }
    return;// If there are no non-infinite tentative distances to unvisited nodes, we give up.

}

void shortestPathSetup(unordered_map<string, locationNode *> *uMap, string start, string end) {
    unordered_map<string, locationNode *> visited;// Where have we been?
    unordered_map<string, locationNode *> unVisited;// Where have we not been?

    // At the start, we haven't been ANYWHERE. Copy uMap into unVisited
    for(auto kv : *uMap) {// kv == Key-Value
        unVisited[kv.first] = kv.second;
    }

    string current;// Where are we right now?

    // To represent distance, we will take -1.0 as representing infinity.
    unordered_map<string, float> distances;// to start with, treat all nodes as infinitely far away.
    for(auto kv : unVisited) {// kv == Key-Value
        distances[kv.first] = -1.0;
    }
    current = start;//start at the beginning
    distances[current] = 0.0;

    //now we start the iterations recursively.
    shortestPathSequence(&visited, &unVisited, start, end, &distances);// pass them in by reference
    if (distances[end] == -1.0){
        std::cout << "There is no path.";
    } else {
        std::cout << "The shortest path is: " << std::to_string(distances[end]);
    }
}


int main() {
  std::cout << "Hello World! - Hal9000\n";

  unordered_map<string, locationNode *> uMap;
  uMap["London Canary Wharf"] = new locationNode("London Canary Wharf");
  uMap["San Fransico"] = new locationNode("San Fransico");
  uMap["Zurich"] = new locationNode("Zurich");

  // How far from London to Zurich, and vice versa?
  uMap["London Canary Wharf"]->linkNode(uMap["Zurich"], 777.0, 777.0);

    //see about making a network of nodes to test the path finding algorithm
}