//
// Created by tursh on 4/2/19.
//

#pragma once


#include <State/State.h>

class LosingState : public CGE::State::State
{
    unsigned int finalTime_, finalScore_, linesCleared_;
public:
    LosingState(float finalTime, unsigned int finalScore, unsigned int linesCleared);

    void tick() override;
    void draw() override;
};


