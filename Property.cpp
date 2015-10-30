#include "Property.h"
#include <Log/Log.h>

LOG_TAG(PROPERTY);

const char* Property_TypeToStr(PropertyType_t type) {
    switch (type) {
    case PropertyType_Bool: return "BOOL";
    case PropertyType_Int32: return "INT32";
    case PropertyType_Uint32: return "UINT32";
    case PropertyType_Float32: return "FLOAT32";
    case PropertyType_String: return "STRING";
    case PropertyType_Binary: return "BINARY";
    case PropertyType_Method: return "METHOD";
    }
    Log::Error(PROPERTY, "propertyType", type);
    return "INVALID";
}
