#pragma once
#include "motor.h"

struct PhysProps
{
    // Pay attention to 16 byte alignement (use padding):      
    unsigned char type;
    unsigned char contCollisionDetection;
    unsigned char collideWithRBodies;
    unsigned char hullType;

    // Vector data:
    glm::vec3 massCenter;

    // Mesh properties:
    float mass;
    float staticFriction;
    float dynamicFriction;
    float bounciness;
    float linearDamping;
    float angularDamping;
    unsigned int nrOfHulls;
    unsigned int _pad;

    // Pointers:
    void* physObj;
    void* hull;
};