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
#include <Text/TextRenderer.h>

PlayingState::PlayingState()
        : grid_(1, -0.975f, 0.25f, -0.975f, 10)
{
    CGE::GUI::GUIManager::addComponent(
            new CGE::GUI::Panel(glm::vec2(0, -1), glm::vec2(1.1f, 0.025), 20000,
                                [](int key, int action)
                                {}, true));
    CGE::GUI::GUIManager::addComponent(
            new CGE::GUI::Panel(glm::vec2(0.75f, 0), glm::vec2(0.5f, 1.1f), 20000,
                                [](int key, int action)
                                {}, true));
    CGE::GUI::GUIManager::addComponent(
            new CGE::GUI::Panel(glm::vec2(-1, 0), glm::vec2(0.025f, 1.1f), 20000,
                                [](int key, int action)
                                {}, true));

    CGE::Utils::setTPS(1.0f);

    CGE::IO::input::setYourOwnKeyCallBack(
            std::bind(&PlayingState::keyCallBack, this, std::placeholders::_1, std::placeholders::_2,
                      std::placeholders::_3));

    CGE::GUI::GUIManager::addComponent(new CGE::GUI::Panel({0.735f, 0.73f}, {0.25f, 0.25f}, 20001,
                                                           [](int key, int action){}, true));

    grid_.setFuturPieceLocation({0.735f, 0.73f, 0.8f});
}

PlayingState::~PlayingState()
{
    CGE::GUI::GUIManager::clear();
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
    //Render Tetris grid
    grid_.render();
    //Render game info
    auto gameInfo = grid_.getInfo();
    //TIME
    CGE::Text::textRenderer::renderText("TIME", 0.73, 0.3f, 0.4f, {0, 0, 0});
    std::string time = CGE::Utils::timeToString(CGE::Utils::getChronoTime(0), 4, false);
    CGE::Text::textRenderer::renderText(time.substr(0, 5), 0.73, 0.15f, 0.4f, {0, 0, 0});
    CGE::Text::textRenderer::renderText(time.substr(5, time.size() - 1), 0.73, 0.0f, 0.4f, {0, 0, 0});
    //SCORE
    CGE::Text::textRenderer::renderText("SCORE", 0.73, -0.2f, 0.4f, {0, 0, 0});
    CGE::Text::textRenderer::renderText(std::to_string(std::get<1>(gameInfo)), 0.73, -0.35f, 0.4f, {0, 0, 0});

    //Level
    CGE::Text::textRenderer::renderText("LEVEL", 0.73, -0.5f, 0.4f, {0, 0, 0});
    CGE::Text::textRenderer::renderText(std::to_string(std::get<0>(gameInfo)), 0.73, -0.65f, 0.4f, {0, 0, 0});

    //Line
    CGE::Text::textRenderer::renderText("LINES", 0.73, -0.8f, 0.4f, {0, 0, 0});
    CGE::Text::textRenderer::renderText(std::to_string(std::get<2>(gameInfo)), 0.73, -0.95f, 0.4f, {0, 0, 0});
}

void PlayingState::keyCallBack(GLFWwindow *window, int key, int action)
{
    if (action == GLFW_PRESS)
    {
        if (key == GLFW_KEY_LEFT)
            grid_.movePiece(LEFT);
        else if (key == GLFW_KEY_RIGHT)
            grid_.movePiece(RIGHT);
        else if (key == GLFW_KEY_DOWN)
            grid_.movePiece(DOWN);
        else if (key == GLFW_KEY_Z)
            grid_.movePiece(COUNTER_CLOCKWISE);
        else if (key == GLFW_KEY_X)
            grid_.movePiece(CLOCKWISE);
        else if (key == GLFW_KEY_SPACE)
            grid_.movePiece(DROP);
    }
}