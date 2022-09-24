//
// Created by averagejoe on 9/24/22.
//
#include "locationNode.h"

using std::string;

locationNode::locationNode(string &n) {
    this->name = n;
}

void locationNode::addLink(locationNode *destination, float pathWeight) {
    weightedPath route = new weightedPath(pathWeight, destination);
        this->paths.push_back(route);
}

void locationNode::linkNode(locationNode *destination, float pathWeight, float backWeight) {
    // We must now make TWO new weighted paths.
    // the two weights can differ, for instance, it is harder to go uphill than
    // downhill.
    destination->addLink(this, backWeight);
    this->addLink(destination, pathWeight);
}

vector<weightedPath> locationNode::retrieveCopiedPaths() {
    vector<weightedPath> temp;
    for (int i = 0; i < this->paths.size(); ++i) {
        temp.push_back(this->paths[i]);
    }
    return temp;
}

string locationNode::getName() {
    return this->name;
}

bool locationNode::findSomeWay(locationNode *destination, float budget, vector<locationNode> pathSoFar) {
    if (this == destination) {
        // print out and return true
        for (int i = 0; i < pathSoFar.size(); i++) {
            std::cout << "";
            std::cout << "Then, to:";
        }
        std::cout << "";
        // https://stackoverflow.com/questions/2125880/convert-float-to-stdstring-in-c
        std::cout << ("With " + std::to_string(budget) + " to spare.");
        return true;
    }
}
