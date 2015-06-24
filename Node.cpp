#include "Node.h"
#include <stdlib.h>
#include <string.h>

Node::Node(const char* name): name(name) {
    firstChild = nextSibling = NULL;
    properties = NULL;
    propertiesCount = 0;
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
