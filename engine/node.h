#pragma once
#ifndef NODE_H
#define NODE_H

#include "motor.h"
#include "object.h"

class LIB_API Node : public Object {
public:
    // Constructors and Destructor
    Node();
    virtual ~Node();

    // Spatial transformation methods
    void setPosition(const glm::vec3& pos);
    glm::vec3 getPosition() const;

    // Hierarchy methods
    void addChild(Node* child);
    void removeChild(Node* child);

private:
    glm::vec3 position;
    std::vector<Node*> children; // List of child nodes
};
#endif // NODE_H
