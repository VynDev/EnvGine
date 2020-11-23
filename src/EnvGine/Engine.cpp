#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <unistd.h>

#include "Engine.h"
#include "Environment.h"

using namespace std::chrono;

Engine* Engine::Init(int width, int height) {
    std::cout << "Thread count :" << std::thread::hardware_concurrency() << std::endl;
    Engine *engine = new Engine;
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(width, height), "Snake");

    engine->SetWindow(window);

    return engine;
}

void ThreadLoop(Engine *engine, int threadIndex) {
    std::cout << "Thread started (" << threadIndex << ")" << std::endl;
    while (true) {
        engine->Tick(threadIndex);
    }
    std::cout << "Thread Ended (" << threadIndex << ")" << std::endl;
}

void Engine::AddThread() {
    ++threadCount;
    std::thread *thread = new std::thread(ThreadLoop, this, threadCount);
}

int Engine::Execute(Environment *environment) {
    StartEnvironment(environment);
    AddThread();
    while (true) {
        RenderLoop();
    }
    return 0;
}

void Engine::Tick(int threadIndex) {
    if (!bTickEnabled)
        return ;
    auto currentTick = high_resolution_clock::now();
    float delta = static_cast<float>(duration_cast<nanoseconds>(currentTick - lastTick).count()) / static_cast<float>(1000000000);
    lastTick = currentTick;

    environmentsMutex.lock();
    for (int i = 0; i < environments.size(); ++i) {
        if (!environments[i]->IsRunning())
            continue;
        environments[i]->Tick(delta);
        
        std::vector<Entity*> &entities = environments[i]->GetEntities();
        for (int j = 0; j < entities.size(); ++j) {
            entities[j]->Tick(delta);
        }
    }
    environmentsMutex.unlock();
}

bool Engine::IsKeyPressed(int keyCode) {
    if (keyCode == sf::Keyboard::Key::Z && keys[0])
        return true;
    else if (keyCode == sf::Keyboard::Key::Q && keys[1])
        return true;
    else if (keyCode == sf::Keyboard::Key::S && keys[2])
        return true;
    else if (keyCode == sf::Keyboard::Key::D && keys[3])
        return true;

    return false;
}

void Engine::RenderLoop() {
    
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            for (int i = 0; i < environments.size(); ++i) {
                environments[i]->SetRunning(false);
                quit = true;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
            keys[0] = true;
        else
            keys[0] = false;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
            keys[1] = true;
        else
            keys[1] = false;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            keys[2] = true;
        else
            keys[2] = false;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            keys[3] = true;
        else
            keys[3] = false;            

    }
    ProcessInputs();

    window->clear(sf::Color::Black);
    
    for (int i = 0; i < environments.size(); ++i) {
        if (!environments[i]->IsRunning() || !environments[i]->IsRenderingEnabled())
            continue;
        Environment *environment = environments[i];
        environment->Render(/*delta*/1);
    }

    window->display();
}

void Engine::ProcessInputs() {
    ProcessMouse();
}

void Engine::ProcessMouse() {
    static bool leftButtonAlreadyPressed = false;

    int mouseX = sf::Mouse::getPosition(*window).x;
    int mouseY = sf::Mouse::getPosition(*window).y;

    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        leftButtonAlreadyPressed = false;
        return ;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && leftButtonAlreadyPressed) {
        return ;
    }

    leftButtonAlreadyPressed = true;
    
    for (int i = 0; i < environments.size(); ++i) {
        if (!environments[i]->IsRunning())
            continue;
        std::vector<Entity*> &entities = environments[i]->GetEntities();
        for (int j = 0; j < entities.size(); ++j) {
            if (mouseX >= entities[j]->GetPosition().x
            && mouseX <= entities[j]->GetPosition().x + entities[j]->GetWidth()
            && mouseY >= entities[j]->GetPosition().y
            && mouseY <= entities[j]->GetPosition().y + entities[j]->GetHeight())
            {
                if (entities[j]->IsClickable())
                    entities[j]->OnClick();
                return ;
            }
        }
    }
   
}

void Engine::SetWindow(sf::RenderWindow *window) {
    this->window = window;
}

sf::RenderWindow &Engine::GetWindow() {
    return *window;
}

int Engine::GetWindowWidth() const {
    return window->getSize().x;
}

int Engine::GetWindowHeight() const {
    return window->getSize().y;
}

void Engine::RemoveEnvironment(Environment *environment) {
    for (int i = 0; i < environments.size(); ++i) {
        if (environments[i] == environment) {
            environmentsMutex.lock();
            environments.erase(environments.begin() + i);
            environmentsMutex.unlock();
            delete environment;
            return ;
        }
    }
}

Environment* Engine::StartEnvironment(Environment *environment) {
    environment->SetRunning(true);
    return environment;
}