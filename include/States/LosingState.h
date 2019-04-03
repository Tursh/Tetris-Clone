//
// Created by tursh on 4/2/19.
//

#pragma once


#include <State/State.h>

class LosingState : public CGE::State::State
{
public:
    LosingState

    void tick() override;
    void draw() override;
};


