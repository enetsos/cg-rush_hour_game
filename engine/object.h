#pragma once

#ifndef OBJECT_H
#define OBJECT_H

#include "motor.h"
#include <cstring>
#include <iostream>

class LIB_API Object {
protected:
    int id;
    static int current_id;
    string name;

public:
    Object(string _name) : id(current_id++), name(_name) {}

    const string get_name() const {
        return name;
    }

    int get_id() {
        return id;
    }

    virtual bool render(glm::mat4 m) = 0;
};
#endif//OBJECT_H