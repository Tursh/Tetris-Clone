#include <Engine.h>
#include <Utils/TimeUtils.h>
#include <State/StateManager.h>
#include <Text/TextRenderer.h>
#include <States/MenuState.h>

void init()
{
    CGE::initEngine("Tretris", CGE::IO::DEFAULT_HEIGHT, CGE::IO::DEFAULT_HEIGHT, false);
    CGE::Text::textRenderer::init("res/graphics/fonts/Archivo-Regular.ttf");
    CGE::State::stateManager::createCurrentState<MenuState>();
    CGE::Utils::initTPSClock();
}

void loop()
{
    CGE::IO::Display *display = CGE::IO::getDisplay();
    while(!glfwWindowShouldClose(display->window))
    {
        while(CGE::Utils::shouldTick())
        {
            CGE::State::stateManager::getCurrentState()->tick();
        }
        CGE::State::stateManager::getCurrentState()->draw();
        display->update();
    }
}

void close()
{
    CGE::Utils::terminateTPSClock();
    CGE::stopEngine();
}

int main()
{
    init();
    loop();
    close();
    return 0;
}