#pragma once
#ifndef NODE_H
#define NODE_H
#include <vector>
#include "object.h"
#include "motor.h"

class LIB_API Node : public Object {
private:
    Node* parent;
    vector<Node*> childs;
    glm::vec3 position;

public:
    // default Constructor
    Node();

    Node(string _name) : Object(_name) {
        this->parent = nullptr;
    }
    virtual ~Node() {
        delete parent;
    }
    bool addChild(Node* _child);
    Node* getChild(int _id);
    Node* getChild(Node* _child);
    bool setParent(Node* _parent);
    Node* getParent();
    void set_position(glm::vec3 pos);
    void set_rotation(float degree, glm::vec3 rot);
    void get_final_matrix();
protected:
    glm::mat4 matrix = glm::mat4(1.0f);
};

#endif // NODE_H

