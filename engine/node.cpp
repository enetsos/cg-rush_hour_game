#include "node.h"
#include <algorithm>

bool LIB_API Node::addChild(Node* _child) {
    if (_child != nullptr) {
        _child->parent = this;
        childs.push_back(_child);
        return true;
    }
    return false;
}

LIB_API Node* Node::getChild(int _id) {
    for (Node* child : childs) {
        if (child->get_id() == _id) {
            return child;
        }
    }
    return nullptr;
}

LIB_API Node* Node::getChild(Node* _child) {

    //childs.end ==  past-the-end element (element that would follow the last element in the vector)
    auto child = find(childs.begin(), childs.end(), _child);
    if (child != childs.end()) {
        return *child;
    }
    return nullptr;
}

bool LIB_API Node::setParent(Node* _parent) {
    if (_parent != nullptr) {
        this->parent = _parent;
        return true;
    }
    return false;
}

LIB_API Node*  Node::getParent() {
	return this->parent;
}

//provvisori

void LIB_API Node::set_position(glm::vec3 pos) {
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), pos);
    matrix = parent->matrix * matrix * translation;
}

void LIB_API Node::set_rotation(float degree, glm::vec3 rot) {
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(degree),rot);
    matrix = parent->matrix * matrix * rotation;
}
