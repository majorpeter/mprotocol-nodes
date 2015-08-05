#include "Node.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Node::Node(const char* name): name(name) {
    firstChild = nextSibling = NULL;
    properties = NULL;
    propertiesCount = 0;
    parent = NULL;
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

void Node::getPathRecursively(char *dest) {
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
