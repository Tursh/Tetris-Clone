//
// Created by tursh on 4/2/19.
//

#pragma once


#include <State/State.h>

class LosingState : public CGE::State::State
{
    float finalTime_;
    unsigned int finalScore_, linesCleared_;
public:
    LosingState(float finalTime, unsigned int finalScore, unsigned int linesCleared);
    ~LosingState();

    void tick() override;
    void draw() override;
};


