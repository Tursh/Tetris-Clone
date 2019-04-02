//
// Created by tursh on 3/28/19.
//

#pragma once


#include <State/State.h>
#include <Grid/Grid.h>
#include <GLFW/glfw3.h>

class PlayingState : public CGE::State::State
{
    Grid grid_;
public:
    PlayingState();
    void tick() override;
    void draw() override;

    void keyCallBack(GLFWwindow *window, int key, int action);
};


