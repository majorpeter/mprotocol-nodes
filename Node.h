#ifndef NODE_H_
#define NODE_H_

#include "Property.h"
#include <stdint.h>

class Node {
    const char *name;
    Node* nextSibling;
    Node* firstChild;
protected:
    const Property_t** properties;
    unsigned propertiesCount;
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
    unsigned getPropertiesCount() const {
        return propertiesCount;
    }
    Node* getNextSibling() {
        return nextSibling;
    }
};

/**
 * sets node's properties pointer & properties count
 * @note call from constructor with a const array of the node's static properties
 * @note the array has to be a static var in the current module for size calculation
 */
#define NODE_SET_PROPS(_PROPERTIES_ARRAY_) { \
        this->properties = _PROPERTIES_ARRAY_; \
        this->propertiesCount = sizeof(_PROPERTIES_ARRAY_)/sizeof(_PROPERTIES_ARRAY_[0]); \
    }
/**
 * sets node's properties pointer & properties count
 * @note call from constructor with a const array of the node's static properties
 */
#define NODE_SET_PROPS_WITH_COUNT(_PROPERTIES_ARRAY_, _PROPERTIES_COUNT_) \
        this->properties = _PROPERTIES_ARRAY_; \
        this->propertiesCount = _PROPERTIES_COUNT_

#endif /* NODE_H_ */
