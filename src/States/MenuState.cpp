//
// Created by tursh on 4/12/19.
//

#include <GUI/GUIManager.h>
#include <States/PlayingState.h>
#include <State/StateManager.h>
#include <IO/Display.h>
#include "States/MenuState.h"



MenuState::MenuState()
{
    CGE::GUI::Panel *panel = new CGE::GUI::Panel({0, 0}, {0.7f, 0.9f}, 20000,
                                                 [](int key, int action)
                                                 {});

    panel->createChildComponent<CGE::GUI::Button>(10000, glm::vec2{0, 0.5f}, glm::vec2{0.75f, 0.2f}, "PLAY", [&]()
    { CGE::State::stateManager::createCurrentState<PlayingState>(); });

    panel->createChildComponent<CGE::GUI::Button>(10000, glm::vec2{0, 0}, glm::vec2{0.75f, 0.2f}, "OPTIONS", [&]()
    { logInfo("No options yet"); });

    panel->createChildComponent<CGE::GUI::Button>(10000, glm::vec2{0, -0.5f}, glm::vec2{0.75f, 0.2f}, "QUIT", [&]()
    { glfwSetWindowShouldClose(CGE::IO::getDisplay()->window, true);});
}

MenuState::~MenuState()
{
    CGE::GUI::GUIManager::clear();
}

void MenuState::tick()
{
    CGE::GUI::GUIManager::checkEvents();
}

void MenuState::draw()
{
    CGE::GUI::GUIManager::renderGUI();
}
