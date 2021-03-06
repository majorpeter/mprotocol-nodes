#ifndef PROPERTIES_H_
#define PROPERTIES_H_

#include "AbstractSerialInterface.h"
#include "AbstractPacketInterface.h"

#include <stddef.h>

#define float32_t float

class Node;

typedef enum {
    ProtocolResult_Ok,
    ProtocolResult_Failed,
    ProtocolResult_UnknownFunc,
    ProtocolResult_NodeNotFound,
    ProtocolResult_PropertyNotFound,
    ProtocolResult_SyntaxError,
    ProtocolResult_InvalidFunc,
    ProtocolResult_InvalidValue,
    ProtocolResult_InternalError,
} ProtocolResult_t;

typedef enum {
    PropertyType_Bool,
    PropertyType_Int32,
    PropertyType_Uint32,
    PropertyType_Float32,
    PropertyType_String,
    PropertyType_Binary,
    PropertyType_BinarySegmented,
    PropertyType_Method
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
        void* addressGetter;
        ProtocolResult_t (Node::*boolGet)(bool*) const;
        ProtocolResult_t (Node::*intGet)(int32_t*) const;
        ProtocolResult_t (Node::*uintGet)(uint32_t*) const;
        ProtocolResult_t (Node::*floatGet)(float*) const;
        ProtocolResult_t (Node::*stringGet)(char*) const;
        ProtocolResult_t (Node::*binaryGet)(void**, uint16_t*) const;
        ProtocolResult_t (Node::*binarySegmentedGet)(AbstractSerialInterface*) const;
    };
    union {
        void* addressSetter;
        ProtocolResult_t (Node::*boolSet)(bool);
        ProtocolResult_t (Node::*intSet)(int32_t);
        ProtocolResult_t (Node::*uintSet)(uint32_t);
        ProtocolResult_t (Node::*floatSet)(float32_t);
        ProtocolResult_t (Node::*stringSet)(const char*);
        ProtocolResult_t (Node::*binarySet)(const void*, uint16_t);
        AbstractPacketInterface* binarySegmentedSet;
        ProtocolResult_t (Node::*methodInvoke)(const char*);
    };
    size_t nodeOffset;
} Property_t;

const char* Property_TypeToStr(PropertyType_t type);

static inline AbstractPacketInterface* getBinarySegmentedSetter(Node* node, const Property_t* property) {
    AbstractPacketInterface* packetInterface = (AbstractPacketInterface*) ((uintptr_t) node + (uintptr_t) property->binarySegmentedSet);
    return packetInterface;
}

// Property creation macros!
#define DECLARE_PROP_RO(_NAME_, _CTYPE_) \
    public: \
        static const Property_t prop_ ## _NAME_; \
        ProtocolResult_t get ## _NAME_(_CTYPE_*) const
#define DECLARE_PROP_RW(_NAME_, _CTYPE_) \
        DECLARE_PROP_RO(_NAME_, _CTYPE_); \
        ProtocolResult_t set ## _NAME_(const _CTYPE_)
#define DECLARE_PROP_METHOD(_NAME_) \
    public: \
        static const Property_t prop_ ## _NAME_; \
        ProtocolResult_t invoke ## _NAME_(const char* params)

#define MK_PROP_RO(_CLASS_, _NAME_, _TYPE_, _DESC_) \
    const Property_t _CLASS_::prop_ ## _NAME_ = {   \
        #_NAME_, _DESC_,    \
        _TYPE_, PropAccessLevel_ReadOnly, \
        (void*)&_CLASS_::get ## _NAME_, \
        NULL, \
        ((size_t)(Node*)(_CLASS_*) 1) - 1 \
    }
#define MK_PROP_RW(_CLASS_, _NAME_, _TYPE_, _DESC_) \
    const Property_t _CLASS_::prop_ ## _NAME_ = {   \
        #_NAME_, _DESC_,    \
        _TYPE_, PropAccessLevel_ReadWrite, \
        (void*)&_CLASS_::get ## _NAME_, \
        (void*)&_CLASS_::set ## _NAME_, \
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
#define DECLARE_PROP_BOOL_RO(_NAME_) DECLARE_PROP_RO(_NAME_, bool)
#define DECLARE_PROP_INT32_RO(_NAME_) DECLARE_PROP_RO(_NAME_, int32_t)
#define DECLARE_PROP_UINT32_RO(_NAME_) DECLARE_PROP_RO(_NAME_, uint32_t)
#define DECLARE_PROP_FLOAT32_RO(_NAME_) DECLARE_PROP_RO(_NAME_, float32_t)
#define DECLARE_PROP_STRING_RO(_NAME_) \
    public: \
        static const Property_t prop_ ## _NAME_; \
        ProtocolResult_t get ## _NAME_(char*) const
#define DECLARE_PROP_BINARY_RO(_NAME_) \
    public: \
        static const Property_t prop_ ## _NAME_; \
        ProtocolResult_t get ## _NAME_(const void**, uint16_t *) const
#define DECLARE_PROP_BINARY_SEGMENTED_RO(_NAME_) \
    ProtocolResult_t get ## _NAME_ (AbstractSerialInterface* serialInterface); \
    static const Property_t prop_ ## _NAME_;

#define DECLARE_PROP_BOOL_RW(_NAME_) DECLARE_PROP_RW(_NAME_, bool)
#define DECLARE_PROP_INT32_RW(_NAME_) DECLARE_PROP_RW(_NAME_, int32_t)
#define DECLARE_PROP_UINT32_RW(_NAME_) DECLARE_PROP_RW(_NAME_, uint32_t)
#define DECLARE_PROP_FLOAT32_RW(_NAME_) DECLARE_PROP_RW(_NAME_, float32_t)
#define DECLARE_PROP_STRING_RW(_NAME_)  \
    public: \
        static const Property_t prop_ ## _NAME_; \
        ProtocolResult_t get ## _NAME_(char*) const; \
        ProtocolResult_t set ## _NAME_(const char*)
#define DECLARE_PROP_BINARY_RW(_NAME_) \
    public: \
        static const Property_t prop_ ## _NAME_; \
        ProtocolResult_t get ## _NAME_(const void**, uint16_t *) const; \
        ProtocolResult_t set ## _NAME_(const void*, uint16_t)
#define DECLARE_PROP_BINARY_SEGMENTED_RW(_NAME_, _PARENT_CLASS_) \
    DECLARE_PROP_BINARY_SEGMENTED_RO(_NAME_); \
    class Set ## _NAME_: public AbstractPacketInterface { \
    public: \
        inline Set ## _NAME_(_PARENT_CLASS_* that) : that(that) {} \
        virtual bool startTransaction(); \
        virtual bool transmitData(const uint8_t *data, uint16_t length); \
        virtual bool commitTransaction(); \
        virtual void cancelTransaction(); \
        friend class _PARENT_CLASS_; \
    private: \
        _PARENT_CLASS_* that; \
    }; \
    Set ## _NAME_ set ## _NAME_

#define MK_PROP_BOOL_RO(_CLASS_, _NAME_, _DESC_)    MK_PROP_RO(_CLASS_, _NAME_, PropertyType_Bool, _DESC_)
#define MK_PROP_INT32_RO(_CLASS_, _NAME_, _DESC_)   MK_PROP_RO(_CLASS_, _NAME_, PropertyType_Int32, _DESC_)
#define MK_PROP_UINT32_RO(_CLASS_, _NAME_, _DESC_)  MK_PROP_RO(_CLASS_, _NAME_, PropertyType_Uint32, _DESC_)
#define MK_PROP_FLOAT32_RO(_CLASS_, _NAME_, _DESC_) MK_PROP_RO(_CLASS_, _NAME_, PropertyType_Float32, _DESC_)
#define MK_PROP_STRING_RO(_CLASS_, _NAME_, _DESC_)  MK_PROP_RO(_CLASS_, _NAME_, PropertyType_String, _DESC_)
#define MK_PROP_BINARY_RO(_CLASS_, _NAME_, _DESC_)  MK_PROP_RO(_CLASS_, _NAME_, PropertyType_Binary, _DESC_)
#define MK_PROP_BINARY_SEG_RO(_CLASS_, _NAME_, _DESC_) \
        const Property_t _CLASS_::prop_ ## _NAME_ = { \
            #_NAME_, _DESC_, \
            PropertyType_BinarySegmented, PropAccessLevel_ReadWrite, \
            (void*) &_CLASS_::get ## _NAME_, \
            NULL, \
            ((size_t)(Node*)(_CLASS_*) 1) - 1 \
        }

#define MK_PROP_BOOL_RW(_CLASS_, _NAME_, _DESC_)    MK_PROP_RW(_CLASS_, _NAME_, PropertyType_Bool, _DESC_)
#define MK_PROP_INT32_RW(_CLASS_, _NAME_, _DESC_)   MK_PROP_RW(_CLASS_, _NAME_, PropertyType_Int32, _DESC_)
#define MK_PROP_UINT32_RW(_CLASS_, _NAME_, _DESC_)  MK_PROP_RW(_CLASS_, _NAME_, PropertyType_Uint32, _DESC_)
#define MK_PROP_FLOAT32_RW(_CLASS_, _NAME_, _DESC_) MK_PROP_RW(_CLASS_, _NAME_, PropertyType_Float32, _DESC_)
#define MK_PROP_STRING_RW(_CLASS_, _NAME_, _DESC_)  MK_PROP_RW(_CLASS_, _NAME_, PropertyType_String, _DESC_)
#define MK_PROP_BINARY_RW(_CLASS_, _NAME_, _DESC_)  MK_PROP_RW(_CLASS_, _NAME_, PropertyType_Binary, _DESC_)
#define MK_PROP_BINARY_SEG_RW(_CLASS_, _NAME_, _DESC_) \
        const Property_t _CLASS_::prop_ ## _NAME_ = { \
            #_NAME_, _DESC_, \
            PropertyType_BinarySegmented, PropAccessLevel_ReadWrite, \
            (void*) &_CLASS_::get ## _NAME_, \
            &((_CLASS_*)NULL)->set ## _NAME_, \
            ((size_t)(Node*)(_CLASS_*) 1) - 1 \
        }

#define PROP_ARRAY(_NAME_) static const Property_t* _NAME_[]
#define PROP_ADDRESS(_CLASS_, _NAME_) &_CLASS_::prop_ ## _NAME_

#endif /* PROPERTIES_H_ */
