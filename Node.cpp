#include "Node.h"
#include "RootNode.h"
#include <Protocol/AbstractSerialInterface.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Node::Node(const char* name, const char* description): name(name), description(description) {
    firstChild = nextSibling = NULL;
    properties = NULL;
    propertiesCount = 0;
    parent = NULL;
    propertyChangeMask = 0;
}

Node::~Node() {}

void Node::addChild(Node* child) {
    if (firstChild == NULL)
        firstChild = child;
    else {
        Node *np = firstChild;
        while (np->nextSibling != NULL) {
            np = np->nextSibling;
        }
        np->nextSibling = child;
    }
    child->parent = this;
}

Node* Node::getChildByName(const char* name) {
    if (firstChild != NULL) {
        Node* n = firstChild;
        while (n != NULL) {
            if (strcmp(n->name, name) == 0) {
                return n;
            }
            n = n->nextSibling;
        }
    }
    return NULL;
}

const Property_t* Node::getPropertyByName(const char* name) const {
    for (unsigned i = 0; i < propertiesCount; i++) {
        if (strcmp(properties[i]->name, name) == 0) {
            return properties[i];
        }
    }
    return NULL;
}

void Node::getPathRecursively(char *dest) const {
    if (parent != NULL) {
        parent->getPathRecursively(dest);
    }
    // find end of string
    while (*dest != '\0') {
        dest++;
    }
    dest[0] = '/';

    if (this->name != NULL) {
        strcpy(dest + 1, this->name);
    }
}

void Node::printPathRecursively(AbstractSerialInterface *interface) const {
	if (parent != NULL) {
		parent->printPathRecursively(interface);
		if (parent != RootNode::getInstance()) {
			*interface << '/';
		}
	}

	if (this->name != NULL) {
		*interface << this->name;
	}
}

/**
 * call this with one of the Node's properties to mark the property as changed
 * @note if the node is subscribed to, this will trigger an async change message
 */
void Node::invalidateProperty(const Property_t *prop) {
	for (uint8_t i = 0; i < propertiesCount; i++) {
		if (properties[i] == prop) {
			propertyChangeMask |= 1 << i;
			break;
		}
	}
}

/**
 * this function returns the change mask and clears it, so that each change is reported only once
 */
uint32_t Node::getAndClearPropChangeMask() {
	uint32_t mask = this->propertyChangeMask;
	this->propertyChangeMask = 0;
	return mask;
}
