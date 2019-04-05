//
// Created by tursh on 4/2/19.
//

#include <GUI/GUIManager.h>
#include <State/StateManager.h>
#include <States/PlayingState.h>
#include "States/LosingState.h"

LosingState::LosingState(float finalTime, unsigned int finalScore, unsigned int linesCleared)
        : finalTime_(finalTime), finalScore_(finalScore), linesCleared_(linesCleared)
{
    CGE::GUI::Panel *panel = new CGE::GUI::Panel({0, 0}, {0.5f, 0.75f}, 20000,
                                                 [](int key, int action)
                                                 {});
    panel->addComponent(new CGE::GUI::Button(10000, {0.75f, 0}, {0.75f, 0.25f}, "RESTART", []()
    { CGE::State::stateManager::setCurrentState(new PlayingState); }));
    CGE::GUI::GUIManager::addComponent(panel);
}

void LosingState::tick()
{
    CGE::GUI::GUIManager::checkEvents();
}

void LosingState::draw()
{
    CGE::GUI::GUIManager::renderGUI();
}

