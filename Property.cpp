#include "Property.h"

const char* Property_TypeToStr(PropertyType_t type) {
    switch (type) {
    case PropertyType_Bool: return "BOOL";
    case PropertyType_Int32: return "INT32";
    case PropertyType_Uint32: return "UINT32";
    case PropertyType_Float32: return "FLOAT32";
    case PropertyType_String: return "STRING";
    case PropertyType_Binary:
    case PropertyType_BinarySegmented:
        return "BINARY";
    case PropertyType_Method: return "METHOD";
    }
    //TODO Log::Error(PROPERTY, "propertyType", type);
    return "INVALID";
}
