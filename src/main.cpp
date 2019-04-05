#include <Engine.h>
#include <Utils/TimeUtils.h>
#include <States/PlayingState.h>
#include <State/StateManager.h>
#include <Text/TextRenderer.h>

void init()
{
    CGE::initEngine("Tretris", CGE::IO::DEFAULT_HEIGHT, CGE::IO::DEFAULT_HEIGHT, false);
    CGE::Text::textRenderer::init("res/graphics/fonts/Archivo-Regular.ttf");
    CGE::State::stateManager::setCurrentState(new PlayingState);
}

void loop()
{
    CGE::IO::Display *display = CGE::IO::getDisplay();
    while(!glfwWindowShouldClose(display->window))
    {
        CGE::State::State *currentState = CGE::State::stateManager::getCurrentState();
        while(CGE::Utils::shouldTick())
        {
            currentState->tick();
        }
        currentState->draw();
        display->update();
    }
}

void close()
{
    CGE::stopEngine();
}

int main()
{
    init();
    loop();
    close();
    return 0;
}