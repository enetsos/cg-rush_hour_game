#pragma once
#include "motor.h"

struct Bone {

    string boneName;
    glm::mat4 boneMatrix;
    unsigned int boneIndex[4];
    unsigned short boneWeightData[4];


};

