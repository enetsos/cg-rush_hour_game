#pragma once
#ifndef NODE_H
#define NODE_H

#include "motor.h"
#include "object.h"

class LIB_API Node : public Object {
public:

    Node ();
    // Constructors and Destructor
    Node(const std::string& name, const glm::mat4& matrix, unsigned int children, const std::string& targetName)
        : name(name), matrix(matrix), numberOfChildren(children), targetName(targetName){}
    virtual ~Node();

    // Spatial transformation methods
    void setPosition(const glm::vec3& pos);
    glm::vec3 getPosition() const;

    virtual void printData() const;

    string getName() const;
    string getTargetName() const;
    glm::mat4 getMatrix() const;
    unsigned int getNumberOfChildren() const;
    

    // Hierarchy methods
    void addChild(Node* child);
    void removeChild(Node* child);


private:
    string name;
    string targetName;
    unsigned int numberOfChildren;
    glm::mat4 matrix;
    glm::vec3 position;
    std::vector<Node*> children; // List of child nodes
};
#endif // NODE_H
