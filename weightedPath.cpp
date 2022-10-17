#include "weightedPath.h"

weightedPath::weightedPath(float w, locationNode *f) {
    this->weight = w;
    this->finish = f;
}

float weightedPath::getWeight() {
    return this->weight;
}

locationNode *weightedPath::getFinish() {
    return this->finish;
}