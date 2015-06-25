#ifndef PROPERTIES_H_
#define PROPERTIES_H_

#include <functional>

class Node;

typedef enum {
    PropertyType_Uint32,
    PropertyType_Int32,
    PropertyType_Bool,
    PropertyType_String,
    PropertyType_Method,
} PropertyType_t;

typedef enum {
    PropAccessLevel_ReadOnly,
    PropAccessLevel_ReadWrite,
    /// method only
    PropAccessLevel_Executable,
} PropAccessLevel_t;

typedef struct {
    PropertyType_t type;
    PropAccessLevel_t accessLevel;
    const char* name;
    const char* description;
    std::function<bool(Node*,char*)> getter;
    std::function<bool(Node*,char*)> setter;
} Property_t;

#endif /* PROPERTIES_H_ */
