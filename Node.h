#ifndef NODE_H_
#define NODE_H_

#include "Properties.h"
#include <stdint.h>

class Node {
    const char *name;
    Node* nextSibling;
    Node* firstChild;
    const Property_t* properties;
    uint16_t propertiesCount;
public:
    Node(const char *name);
    virtual ~Node();

    void addChild(Node* child);

    Node* getFirstChild() {
        return firstChild;
    }

    Node* getChildByName(const char* name);
    /* TODO kell ez? Node* getNextSibling() {
        return nextSibling;
    }*/
};

#endif /* NODE_H_ */
