#include "JsonBuffer.h"
#include "JsonObject.h"
#include "JsonValue.h"
#include "JsonNode.h"
#include <string.h> // for strcmp

//JsonValue& JsonObject::operator[](char const* key)
//{
//    addNodeAt(key, innerObject._node);
//    return innerObject;
//}
//
//void JsonObject::addNodeAt(const char* key, JsonNode& node)
//{
//    JsonNode& keyNode = _buffer.createNode();
//    keyNode.becomeKey(key, node);
//    appendChild(keyNode);
//}
//
//void JsonObject::appendChild(JsonNode& newChild)
//{
//    JsonNode* lastChild = _node.asObjectNode.child;
//    while (lastChild->next)
//    {
//        lastChild = lastChild->next;
//    }
//
//    if (lastChild)
//        lastChild->next = &newChild;
//    else
//        _node.asObjectNode.child = &newChild;
//}

size_t JsonObject::size()
{
    JsonNode* firstChild = _node->content.asObject.child;

    int size = 0;

    for (JsonNode* child = firstChild; child; child = child->next)
    {
        size++;
    }

    return size;
}

JsonValue JsonObject::operator[](char const* key)
{
    JsonNode* node = getOrCreateNodeAt(key);
    return JsonValue(node);
}

bool JsonObject::operator==(JsonObject const& other) const
{
    return _node == other._node;
}

JsonNode* JsonObject::getOrCreateNodeAt(char const* key)
{
    if (!_node || _node->type != JSON_OBJECT) return 0;

    JsonNode* firstChild = _node->content.asObject.child;
    JsonNode* lastChild = 0;

    for (JsonNode* child = firstChild; child; child = child->next)
    {
        const char* childKey = child->content.asKey.key;

        if (!strcmp(childKey, key))
            return child->content.asKey.value;

        lastChild = child;
    }

    JsonBuffer* buffer = _node->content.asObject.buffer;

    JsonNode* newValueNode = buffer->createNode(JSON_UNDEFINED);
    
    JsonNode* newKeyNode = buffer->createNode(JSON_KEY);
    newKeyNode->content.asKey.key = key;
    newKeyNode->content.asKey.value = newValueNode;

    if (lastChild)
        lastChild->next = newKeyNode;
    else
        _node->content.asObject.child = newKeyNode;

    return newValueNode;
}