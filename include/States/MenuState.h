//
// Created by tursh on 4/12/19.
//

#pragma once


#include <State/State.h>

class MenuState : public CGE::State::State
{
public:
    MenuState();
    ~MenuState();

    void tick() override ;
    void draw() override ;
};


