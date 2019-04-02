//
// Created by tursh on 3/28/19.
//

#include "States/PlayingState.h"
#include <GUI/GUIManager.h>
#include <GUI/Panel.h>
#include <Entities/Entity.h>
#include <Shader/ModelShader/BasicShader.h>
#include <glm/ext/matrix_transform.hpp>
#include <IO/Input.h>
#include <glm/gtx/string_cast.hpp>
#include <Utils/TimeUtils.h>

PlayingState::PlayingState()
        : grid_(1, -0.975f, 0.45f, -0.975f, 10)
{
    CGE::GUI::GUIManager::addComponent(
            new CGE::GUI::Panel(glm::vec2(0, -1), glm::vec2(1.1f, 0.025), CGE::GUI::PANEL_DEFAULT,
                                [](int key, int action)
                                {}, true));
    CGE::GUI::GUIManager::addComponent(
            new CGE::GUI::Panel(glm::vec2(0.75f, 0), glm::vec2(0.3f, 1.1f), CGE::GUI::PANEL_DEFAULT,
                                [](int key, int action)
                                {}, true));
    CGE::GUI::GUIManager::addComponent(
            new CGE::GUI::Panel(glm::vec2(-1, 0), glm::vec2(0.025f, 1.1f), CGE::GUI::PANEL_DEFAULT,
                                [](int key, int action)
                                {}, true));

    CGE::Utils::setTPS(2.0f);

    auto test = std::bind(&PlayingState::keyCallBack, this,
                                                                             std::placeholders::_1,
                                                                             std::placeholders::_2,
                                                                             std::placeholders::_3);

    CGE::IO::input::setYourOwnKeyCallBack(
            std::bind(&PlayingState::keyCallBack, this, std::placeholders::_1, std::placeholders::_2,
                      std::placeholders::_3));
}

void PlayingState::tick()
{
    CGE::GUI::GUIManager::checkEvents();
    grid_.tick();
    //testTile->move(glm::vec3(0.0001f, 0, 0));
    //glm::vec2 mousePos = CGE::IO::input::getCursorPos(0);
    //logInfo(glm::to_string(mousePos));
    //testTile->position_ = glm::vec3(mousePos.x, mousePos.y, 0);
}

void PlayingState::draw()
{
    CGE::GUI::GUIManager::renderGUI();
    grid_.render();
}

void PlayingState::keyCallBack(GLFWwindow *window, int key, int action)
{
    if(action == GLFW_PRESS)
    {
        if(key == GLFW_KEY_LEFT)
            grid_.movePiece(LEFT);
        else if(key == GLFW_KEY_RIGHT)
            grid_.movePiece(RIGHT);
        else if(key == GLFW_KEY_DOWN)
            grid_.movePiece(DOWN);
        else if(key == GLFW_KEY_Z)
            grid_.movePiece(COUNTER_CLOCKWISE);
        else if(key == GLFW_KEY_X)
            grid_.movePiece(CLOCKWISE);
    }
}
