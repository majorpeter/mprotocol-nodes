#include "RootNode.h"
#include <stdlib.h>

RootNode::RootNode(): Node("/") {}

RootNode::~RootNode() {}

RootNode* RootNode::getInstance() {
    static RootNode* instance = NULL;
    if (instance == NULL) {
        instance = new RootNode();
    }
    return instance;
}
