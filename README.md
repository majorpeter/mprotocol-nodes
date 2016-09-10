# mprotocol-nodes

The `MProtocol Node library` contains a very simple `Node` object that could be accessed via any protocol. The Node itself does not depend on any other library (or platform).

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
