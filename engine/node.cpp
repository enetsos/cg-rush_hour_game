#include "node.h"

// default constructor
Node::Node() {
	// Initialization code
}


// Destructor
Node::~Node() {
    // Cleanup code
}

// Set position
void Node::setPosition(const glm::vec3& pos) {
    position = pos;
}

// Get position
glm::vec3 Node::getPosition() const {
    return position;
}

void Node::printData() const{
    cout << "node]" << endl;
    cout << "   Name  . . . . :  " << name << endl;
    cout << "   Nr. children  :  " << numberOfChildren << endl;
    cout << "   Target node . :  " << targetName << endl;

}

string Node::getName() const {
    return name;
}

string Node::getTargetName() const {
    return targetName;
}

glm::mat4 Node::getMatrix() const {
    return matrix;
}

unsigned int Node::getNumberOfChildren() const {
    return numberOfChildren;
}

// Add child
void Node::addChild(Node* child) {
    children.push_back(child);
}

// Remove child
void Node::removeChild(Node* child) {
    // Implementation depends on how you manage the list of children
}

// Other implementation details...
