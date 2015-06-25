#ifndef NODE_H_
#define NODE_H_

#include "Properties.h"
#include <stdint.h>

class Node {
    const char *name;
    Node* nextSibling;
    Node* firstChild;
protected:
    const Property_t** properties;
    uint16_t propertiesCount;
public:
    static Property_t prop_setName;

    Node(const char *name);
    virtual ~Node();

    const char* getName() const {
        return name;
    }

    void addChild(Node* child);

    Node* getFirstChild() {
        return firstChild;
    }

    Node* getChildByName(const char* name);
    const Property_t* getPropertyByName(const char* name) const;
    const Property_t** getProperties() const {
        return properties;
    }
    uint16_t getPropertiesCount() const {
        return propertiesCount;
    }
    Node* getNextSibling() {
        return nextSibling;
    }
};

#endif /* NODE_H_ */
