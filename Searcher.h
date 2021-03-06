#ifndef PROJ2_SEARCHER_H
#define PROJ2_SEARCHER_H

#include "Searchable.h"


template <class Solution, class T>
class Searcher{

public:
    virtual Solution search(Searchable<T>* toSearch) = 0;
    virtual int getNumberOfNodesEvaluated() = 0;
    virtual double getCost() = 0;
    virtual ~Searcher(){};

};

#endif //PROJ2_SEARCHER_H
