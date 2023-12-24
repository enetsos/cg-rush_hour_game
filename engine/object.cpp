#include "object.h"

// Initialize static member
unsigned int Object::globalIdCounter = 0;

// Constructor
Object::Object() {
  id = ++globalIdCounter; // Assign a unique ID to the object
}

// Destructor
Object::~Object() {
  // Destructor code (if any)
}

// Get object ID
unsigned int Object::getId() const { return id; }

// Other implementation details...
