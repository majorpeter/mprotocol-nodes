#ifndef PROPERTIES_H_
#define PROPERTIES_H_

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

// TODO fix for node methods
typedef void* SetterFunc_t;

typedef struct {
    PropertyType_t type;
    PropAccessLevel_t accessLevel;
    const char* name;
    const char* description;
    SetterFunc_t setter;
} Property_t;

#endif /* PROPERTIES_H_ */
