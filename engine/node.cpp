#include "node.h"

bool Node::addChild(Node *_child) {
  if (_child == nullptr) {
    return false;
  }

  // Check if the child already has a parent
  if (_child->getParent() != nullptr) {
    return false;
  }

  // Set this node as the parent of the child
  _child->parent = this;

  // Add the child to the vector of children
  childs.push_back(_child);

  return true;
}

Node *Node::getChild(int _id) {
  for (Node *child : childs) {
    if (child->get_id() == _id) {
      return child;
    }
  }

  return nullptr;
}

Node *Node::getChild(Node *_child) {
  for (Node *child : childs) {
    if (child == _child) {
      return child;
    }
  }

  return nullptr;
}

bool Node::setParent(Node *_parent) {
  if (_parent == nullptr) {
    return false;
  }

  // Remove this node from its current parent's child list
  if (parent != nullptr) {
    auto it = std::find(parent->childs.begin(), parent->childs.end(), this);
    if (it != parent->childs.end()) {
      parent->childs.erase(it);
    }
  }

  // Set the new parent
  _parent->addChild(this);

  return true;
}

Node *Node::getParent() { return parent; }

void Node::set_position(glm::vec3 pos) {
  matrix = glm::translate(glm::mat4(1.0f), pos);
}

void Node::set_rotation(float degree, glm::vec3 rot) {
  matrix = glm::rotate(matrix, glm::radians(degree), rot);
}

/*
void Node::get_final_matrix() {
    // Calculate the final transformation matrix based on the hierarchy
    if (parent != nullptr) {
        matrix = parent->get_final_matrix() * matrix;
    }

    // Print or use the final matrix as needed
    // For example, you might use it in rendering
    std::cout << "Final Matrix for Node " << get_id() << ":\n";
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}
*/