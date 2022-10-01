//
// Created by averagejoe on 9/24/22.
//

#ifndef PATHSNGRAPHS_LOCATIONNODE_H
#define PATHSNGRAPHS_LOCATIONNODE_H

#include "weightedPath.h"

#include <vector>
#include <iostream>
#include <string>

using std::vector;
using std::string;
//two classes that refer to each other require forward declarations
class weightedPath;

class locationNode {
private:
    vector<weightedPath> paths;
    string name;

public:
    //constructor
    locationNode(string n);

    //utility functions
    void addLink(locationNode *destination, float pathWeight);
    void linkNode(locationNode *destination, float pathWeight, float backWeight);
    vector<weightedPath> retrieveCopiedPaths();
    // This just tried to find a path that is within a "budget".
    // It need not be the most efficient or shortest path.
    bool findSomeWay(locationNode *destination, float budget,
                     vector<locationNode> pathSoFar);

    //getter
    string getName();
};


#endif //PATHSNGRAPHS_LOCATIONNODE_H
