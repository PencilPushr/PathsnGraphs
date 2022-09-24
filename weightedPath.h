//
// Created by averagejoe on 9/24/22.
//

#ifndef PATHSNGRAPHS_WEIGHTEDPATH_H
#define PATHSNGRAPHS_WEIGHTEDPATH_H

#include "locationNode.h"

//two classes that refer to each other require forward declarations
class locationNode;

class weightedPath {
private:
    float weight; // Always in kilometres
    locationNode *finish;

public:
    //constructor
    weightedPath(float w, locationNode *pNode);
    float getWeight();
    locationNode *getFinish();
};


#endif //PATHSNGRAPHS_WEIGHTEDPATH_H
