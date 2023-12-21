#ifndef OBJECT_H
#define OBJECT_H
#include "motor.h"

class LIB_API Object {
public:
    // Constructors
    Object();
    virtual ~Object();

    // Unique identifier
    unsigned int getId() const;

private:
    static unsigned int globalIdCounter;
    unsigned int id;
};

#endif // OBJECT_H
