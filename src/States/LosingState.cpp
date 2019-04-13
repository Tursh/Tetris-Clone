//
// Created by tursh on 4/2/19.
//

#include <GUI/GUIManager.h>
#include <State/StateManager.h>
#include <States/PlayingState.h>
#include <Utils/TimeUtils.h>
#include <Text/TextRenderer.h>
#include <States/MenuState.h>
#include "States/LosingState.h"

static const float INFO_X_POSITION = 0, INFO_TEXT_SIZE = 0.35f;

LosingState::LosingState(float finalTime, unsigned int finalScore, unsigned int linesCleared)
        : finalTime_(finalTime), finalScore_(finalScore), linesCleared_(linesCleared)
{
    CGE::GUI::Panel *panel = new CGE::GUI::Panel({0, 0}, {0.7f, 0.9f}, 20000,
                                                 [](int key, int action)
                                                 {});
    panel->createChildComponent<CGE::GUI::Button>(10000, glm::vec2{0, 0.7f}, glm::vec2{0.75f, 0.2f}, "RESTART", [&]()
    { CGE::State::stateManager::createCurrentState<PlayingState>(); });
    panel->createChildComponent<CGE::GUI::Button>(10000, glm::vec2{0, -0.7f}, glm::vec2{0.75f, 0.2f}, "RETURN TO MENU",
                                                  []()
                                                  { CGE::State::stateManager::createCurrentState<MenuState>() ;});
    CGE::Utils::setTPS(60);
}

LosingState::~LosingState()
{
    CGE::GUI::GUIManager::clear();
}

void LosingState::tick()
{
    CGE::GUI::GUIManager::checkEvents();
}

void LosingState::draw()
{
    CGE::GUI::GUIManager::renderGUI();

    CGE::Text::textRenderer::renderText("TIME", INFO_X_POSITION, 0.35f, INFO_TEXT_SIZE, {0, 0, 0});
    CGE::Text::textRenderer::renderText(CGE::Utils::timeToString(finalTime_, 4, false), INFO_X_POSITION, 0.25,
                                        INFO_TEXT_SIZE, {0, 0, 0});
    //SCORE
    CGE::Text::textRenderer::renderText("SCORE", INFO_X_POSITION, 0, INFO_TEXT_SIZE, {0, 0, 0});
    CGE::Text::textRenderer::renderText(std::to_string(finalScore_), INFO_X_POSITION, -0.1f, INFO_TEXT_SIZE,
                                        {0, 0, 0});

    //Level
    CGE::Text::textRenderer::renderText("LINES CLEARED", INFO_X_POSITION, -0.3f, INFO_TEXT_SIZE, {0, 0, 0});
    CGE::Text::textRenderer::renderText(std::to_string(linesCleared_), INFO_X_POSITION, -0.4f, INFO_TEXT_SIZE,
                                        {0, 0, 0});
}

