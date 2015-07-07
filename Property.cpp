#include "Property.h"

const char* Property_TypeToStr(PropertyType_t type) {
    switch (type) {
    case PropertyType_Uint32: return "UINT32";
    case PropertyType_Int32: return "INT32";
    case PropertyType_Bool: return "BOOL";
    case PropertyType_String: return "STRING";
    case PropertyType_Method: return "METHOD";
    }
    //TODO log!
    return "INVALID";
}