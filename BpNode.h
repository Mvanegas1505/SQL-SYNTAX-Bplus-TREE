#ifndef NODE_H
#define NODE_H 

#include <vector>
#include "Dato.h"

class BpNode{

public:
 
    bool isLeaf;
    std::vector<Dato*> key;
    std::vector<BpNode*> child_ptrs;
    BpNode* next;
    BpNode* nextLeaf;

    BpNode(bool isNodeleaf) : isLeaf(isNodeleaf), next(nullptr){}
};



#endif
