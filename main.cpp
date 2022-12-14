#include <iostream>
#include <string>
#include <unordered_map>

#include "locationNode.h"
#include "weightedPath.h"

using std::string;
using std::unordered_map;

// TODO: fix errors on lines 18 and 37 (pair function spits an error)

void update(unordered_map<string, float> *distances, float newDistance,
            string s) {
    // https://stackoverflow.com/questions/15815649/stdunordered-map-pass-by-reference
    if (newDistance == -1.0) {
        return;
    } // nothing is bigger than infinity, so reject.

    float oldDistance = distances->at(s); // Get the current distance.
    if (oldDistance == -1.0) { // Anything smaller than infinity is allowed.
        distances->erase(s);
        distances->insert(std::pair<string, float>(s, newDistance));
        return;
    }
    if (oldDistance > newDistance) {// if both finite, but the new path quicker, replace.
        distances->erase(s);
        distances->insert(std::pair<string, float>(s, newDistance));
    }
    return; // if all else fails, return
}

bool shortestPathSequence(unordered_map<string, locationNode *> *visited,
                          unordered_map<string, locationNode *> *unVisited,
                          const string &current, const string &end,
                          unordered_map<string, float> *distances) {
    if (current == end) {return true;} // No need to go further, we found it
    vector<weightedPath> paths =unVisited->at(current)->retrieveCopiedPaths();//get every path from current

    for (auto p : paths) {
        // Check every connected node and update its distance;
        // each path check its weight, update by passing index + weight
        float newDistance = distances->at(current) + p.getWeight();
        update(distances, newDistance, p.getFinish()->getName());
    }

    // Now that every node has been checked, this is a VISITED node.
    visited->insert(std::pair<string, locationNode *>(current, unVisited->at(current)));
    unVisited->erase(current);
    // Now go again from the unvisited node with the shortest tentative distance
    float d = 16.0;
    bool found = false;
    while (d != -1.0 && !found) { // run until all tentative distances left are infinite
        float d = -1.0;
        float c = -1.0;
        string s = "";
        for (auto &u : *(unVisited)) {
            c = distances->at(u.first);
            if (d == -1.0 && c != -1.0) { // shorter than infinity
                d = c;
                s = u.first;
            } else if (c != -1.0 && c < d) { // shorter than finite
                d = c;
                s = u.first;
            } else {
                // do nothing!!!
            }
        } // loop for
        if (d != -1.0) { // Run again for the next node, if we found a non-infinite path
            found = shortestPathSequence(visited, unVisited, s, end, distances);
        }
    } // loop while
    return found; // If there are no non-infinite tentative distances left, give up
}

void shortestPathSetup(unordered_map<string, locationNode *> *uMap,
                       string start, string end) {
    unordered_map<string, locationNode *> visited;   // Where have we been?
    unordered_map<string, locationNode *> unVisited; // Where have we not been?

    // At the start, we haven't been ANYWHERE. Copy uMap into unVisited
    for (auto kv : *uMap) { // kv == Key-Value
        unVisited[kv.first] = kv.second;
    }

    string current; // Where are we right now?

    // To represent distance, we will take -1.0 as representing infinity.
    unordered_map<string, float>
            distances; // to start with, treat all nodes as infinitely far away.
    for (auto kv : unVisited) { // kv == Key-Value
        distances[kv.first] = -1.0;
    }
    current = start; // start at the beginning
    distances[current] = 0.0;

    // now we start the iterations recursively. pass params in by reference
    if (shortestPathSequence(&visited, &unVisited, start, end, &distances)) {
        std::cout << "The shortest path is: " << std::to_string(distances[end])<< "\n";
    } else {
        std::cout << "There is no path.\n";
    }
}

int main() {
    std::cout << "Hello World! - Hal9000\n";

    unordered_map<string, locationNode *> uMap;

    uMap["London Canary Wharf"] = new locationNode("London Canary Wharf");
    uMap["San Fransisco"] = new locationNode("San Fransisco");
    uMap["Zurich"] = new locationNode("Zurich");
    uMap["Rome"] = new locationNode("Rome");
    uMap["Perth"] = new locationNode("Perth");
    uMap["Manchester"] = new locationNode("Manchester");
    uMap["Byzantium"] = new locationNode("Byzantium");
    uMap["Cape Town"] = new locationNode("Cape Town");
    uMap["New York"] = new locationNode("New York");
    uMap["Beijing"] = new locationNode("Beijing");
    uMap["Ontario"] = new locationNode("Ontario");
    uMap["Juba City"] = new locationNode("Juba City");
    uMap["Abuja"] = new locationNode("Abuja");
    uMap["Sydney"] = new locationNode("Sydney");

    // How far from London to Zurich, and vice versa?
    uMap["London Canary Wharf"]->linkNode(uMap["Zurich"], 777.0, 777.0);
    uMap["Zurich"]->linkNode(uMap["Manchester"], 1336.5, 1336.5);
    uMap["Zurich"]->linkNode(uMap["Perth"], 13789.0, 13789.0);
    uMap["Perth"]->linkNode(uMap["Rome"], 13331.0, 13331.0);
    uMap["Rome"]->linkNode(uMap["San Fransisco"], 10041.0, 10041.0);
    uMap["San Fransisco"]->linkNode(uMap["Byzantium"], 10778.0, 10778.0);
    uMap["Byzantium"]->linkNode(uMap["Beijing"], 7051.0, 7051.0);
    uMap["Beijing"]->linkNode(uMap["Cape Town"], 12948.0, 12948.0);
    uMap["Perth"]->linkNode(uMap["Ontario"], 17249.0, 17249.0);
    uMap["Ontario"]->linkNode(uMap["Juba City"], 11388.0, 11388.0);
    uMap["Ontario"]->linkNode(uMap["New York"], 1458.0, 13789.0);
    uMap["New York"]->linkNode(uMap["Abuja"], 70.0, 70.0);
    uMap["Abuja"]->linkNode(uMap["Sydney"], 15397.0, 15397.0);
    uMap["Juba City"]->linkNode(uMap["London Canary Wharf"], 9469.0, 9469.0);

    // see about making a network of nodes to test the path finding algorithm
    shortestPathSetup(&uMap, "London Canary Wharf", "Beijing");

    // see about making a network of nodes to test the path finding algorithm
}