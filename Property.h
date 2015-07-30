#ifndef PROPERTIES_H_
#define PROPERTIES_H_

#include <stdint.h>
#include <stddef.h>

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
    PropAccessLevel_Invokable,
} PropAccessLevel_t;

typedef struct {
    const char* name;
    const char* description;

    PropertyType_t type;
    PropAccessLevel_t accessLevel;
    union {
        void *addressGetter;
        void (*boolGet)(Node*, bool* dest);
        void (*intGet)(Node*, int32_t* dest);
        void (*uintGet)(Node*, uint32_t* dest);
        void (*stringGet)(Node*, char* dest);
    };
    union {
        void *addressSetter;
        void (*boolSet)(Node*, bool);
        void (*intSet)(Node*, int32_t);
        void (*uintSet)(Node*, uint32_t);
        void (*stringSet)(Node*, const char* from);
        void (*methodInvoke)(Node*, const char* params);
    };
    size_t nodeOffset;
} Property_t;

const char* Property_TypeToStr(PropertyType_t type);

// Property creation macros!
#define DECLARE_PROP_RW(_NAME_, _CTYPE_) \
    public: \
        static const Property_t prop_ ## _NAME_; \
        void get ## _NAME_(_CTYPE_*); \
        void set ## _NAME_(const _CTYPE_)
#define DECLARE_PROP_RO(_NAME_, _CTYPE_) \
    public: \
        static const Property_t prop_ ## _NAME_; \
        void get ## _NAME_(_CTYPE_*)
#define DECLARE_PROP_METHOD(_NAME_) \
    public: \
        static const Property_t prop_ ## _NAME_; \
        void invoke ## _NAME_(const char* params)

#define MK_PROP_RW(_CLASS_, _NAME_, _TYPE_, _DESC_) \
    const Property_t _CLASS_::prop_ ## _NAME_ = {   \
        #_NAME_, _DESC_,    \
        _TYPE_, PropAccessLevel_ReadWrite, \
        (void*)&_CLASS_::get ## _NAME_, \
        (void*)&_CLASS_::set ## _NAME_, \
        ((size_t)(Node*)(_CLASS_*) 1) - 1 \
    }
#define MK_PROP_RO(_CLASS_, _NAME_, _TYPE_, _DESC_) \
    const Property_t _CLASS_::prop_ ## _NAME_ = {   \
        #_NAME_, _DESC_,    \
        _TYPE_, PropAccessLevel_ReadOnly, \
        (void*)&_CLASS_::get ## _NAME_, \
        NULL, \
        ((size_t)(Node*)(_CLASS_*) 1) - 1 \
    }
#define MK_PROP_METHOD(_CLASS_, _NAME_, _DESC_) \
    const Property_t _CLASS_::prop_ ## _NAME_ = {   \
        #_NAME_, _DESC_,    \
        PropertyType_Method, PropAccessLevel_Invokable, \
        NULL, \
        (void*)&_CLASS_::invoke ## _NAME_, \
        ((size_t)(Node*)(_CLASS_*)1) - 1 \
    }


// shortcuts
#define DECLARE_PROP_UINT32_RW(_NAME_) DECLARE_PROP_RW(_NAME_, uint32_t)
#define DECLARE_PROP_INT32_RW(_NAME_) DECLARE_PROP_RW(_NAME_, int32_t)
#define DECLARE_PROP_BOOL_RW(_NAME_) DECLARE_PROP_RW(_NAME_, bool)
//TODO #define DECLARE_PROP_STRING_RW(_NAME_) DECLARE_PROP_RW(_NAME_, char*)

#define DECLARE_PROP_UINT32_RO(_NAME_) DECLARE_PROP_RO(_NAME_, uint32_t)
#define DECLARE_PROP_INT32_RO(_NAME_) DECLARE_PROP_RO(_NAME_, int32_t)
#define DECLARE_PROP_BOOL_RO(_NAME_) DECLARE_PROP_RO(_NAME_, bool)
//TODO #define DECLARE_PROP_STRING_RO(_NAME_) DECLARE_PROP_RO(_NAME_, char*)

#define MK_PROP_UINT32_RW(_CLASS_, _NAME_, _DESC_) MK_PROP_RW(_CLASS_, _NAME_, PropertyType_Uint32, _DESC_)
#define MK_PROP_INT32_RW(_CLASS_, _NAME_, _DESC_)  MK_PROP_RW(_CLASS_, _NAME_, PropertyType_Int32, _DESC_)
#define MK_PROP_BOOL_RW(_CLASS_, _NAME_, _DESC_)   MK_PROP_RW(_CLASS_, _NAME_, PropertyType_Bool, _DESC_)
#define MK_PROP_STRING_RW(_CLASS_, _NAME_, _DESC_) MK_PROP_RW(_CLASS_, _NAME_, PropertyType_String, _DESC_)

#define MK_PROP_UINT32_RO(_CLASS_, _NAME_, _DESC_) MK_PROP_RO(_CLASS_, _NAME_, PropertyType_Uint32, _DESC_)
#define MK_PROP_INT32_RO(_CLASS_, _NAME_, _DESC_)  MK_PROP_RO(_CLASS_, _NAME_, PropertyType_Int32, _DESC_)
#define MK_PROP_BOOL_RO(_CLASS_, _NAME_, _DESC_)   MK_PROP_RO(_CLASS_, _NAME_, PropertyType_Bool, _DESC_)
#define MK_PROP_STRING_RO(_CLASS_, _NAME_, _DESC_) MK_PROP_RO(_CLASS_, _NAME_, PropertyType_String, _DESC_)

#endif /* PROPERTIES_H_ */
