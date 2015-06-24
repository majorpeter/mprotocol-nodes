#ifndef ROOTNODE_H_
#define ROOTNODE_H_

#include "Node.h"

class RootNode: public Node {
private:
    RootNode();
    virtual ~RootNode();
public:
    static RootNode* getInstance();

    static RootNode* create() {
        return getInstance();
    }
};

#endif /* ROOTNODE_H_ */
