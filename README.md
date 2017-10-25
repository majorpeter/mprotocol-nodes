# mprotocol-nodes

The `MProtocol Node library` contains a very simple `Node` object that could be accessed via *any* protocol. The Node itself does not depend on any other library (or platform).

## RootNode

The Nodes comprise a tree graph. Each tree has one root, that is the `RootNode` *singleton*.

## Properties

Each Node has a set of properties that can be accessed using a higher layer protocol. These are the defined property types:

* `PropertyType_Bool`: boolean value
* `PropertyType_Int32`: 32-bit signed integer
* `PropertyType_Uint32`: 32-bit unsigned integer
* `PropertyType_Float32`: 32-bit floating-point number
* `PropertyType_String`: ASCII string
* `PropertyType_Binary`: arbitrary binary data
* `PropertyType_Method`: callable routine

## Manual

Each Node and Property may have a *manual entry*, which is a short text about its purpose.

## Usage

The project's nodes are classes derived from the `Node` class. Each property has to be declared in the **class declaration**, e.g.:
```cpp
class LedNode: public Node {
public:
    enum LedType {
        LedType_Green,
        LedType_Orange,
        LedType_Red,
        LedType_Blue
    };

    LedNode(LedType type, PwmInterface* pwm);
    virtual ~LedNode();

    static void globalInit();
    void init(uint32_t alternateFunction);

    DECLARE_PROP_BOOL_RW(Enabled);
    DECLARE_PROP_UINT32_RW(Pwm);
private:
    GPIO_TypeDef* gpio_port;
    uint16_t gpio_pin;
    PwmInterface* pwm;
};
```

The `DECLARE_PROP_xx_Ry` macros generate the descriptor object and the setter & getter method declaration for the property. `xx` stands for the property type, `y` can be `O` or `W` (as in *read-only* or *read/write*).

The **source file** (*.cpp*) contains the definition for the descriptor. Use the `MK_PROP_xx_Ry` macros to fill the structure, e.g.:
```cpp
MK_PROP_BOOL_RW(LedNode, Enabled, "LED is On or Off.");
```

It also contains the property array that is assigned to the node's property array pointer:
```cpp
PROP_ARRAY(props) = {
        PROP_ADDRESS(LedNode, Enabled),
        PROP_ADDRESS(LedNode, Pwm)
};

LedNode::LedNode(LedType type, PwmInterface* pwm): Node(ledNames[type]) {
    this->gpio_port = ledPorts[type];
    this->gpio_pin = ledPins[type];
    this->pwm = pwm;
    
    // assign properties array
    NODE_SET_PROPS(props);
}
```

The source of course also contains the method implementations that the node/protocol exports for remote access (RPC). The getters have a `const` qualifier and return via pointer, while setters' parameters are take by value. Both setters and getters return the common `ProtocolResult_t` type to report errors to the protocol (or caller).

See also [the STM32 demo project](https://github.com/majorpeter/stm32-mprotocol-demo).
