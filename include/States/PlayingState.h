//
// Created by tursh on 3/28/19.
//

#pragma once


#include <State/State.h>
#include <Grid/Grid.h>
#include <GLFW/glfw3.h>
#include <thread>

class PlayingState : public CGE::State::State
{
    std::thread *keyCheckThread;
    Grid grid_;
    void checkKeys();
public:
    PlayingState();
    ~PlayingState() override;
    void tick() override;
    void draw() override;

    void keyCallBack(GLFWwindow *window, int key, int action);
};


