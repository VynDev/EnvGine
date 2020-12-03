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
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(width, height), "Snake");
    Engine *engine = new Engine(window);
    return engine;
}

Engine::Engine(sf::RenderWindow *window) : window(window) {
    SelectMonitor<Monitor>();
}

void Engine::ThreadLoop(int threadIndex) {
    std::cout << "Thread started (" << threadIndex << ")" << std::endl;
    while (true)
        Tick(threadIndex);
    std::cout << "Thread Ended (" << threadIndex << ")" << std::endl;
}

void Engine::AddThread() {
    ++threadCount;
    std::thread *thread = new std::thread(&Engine::ThreadLoop, this, threadCount);
}

int Engine::Execute(Environment *environment) {
    StartEnvironment(environment);
    AddThread();
    RenderLoop();
    return 0;
}

void Engine::Tick(int threadIndex) {
    if (!bTickEnabled)
        return ;
    auto currentTick = high_resolution_clock::now();
    float delta = static_cast<float>(duration_cast<nanoseconds>(currentTick - lastTick).count()) / static_cast<float>(1000000000);
    lastTick = currentTick;

    environmentsMutex.lock();
    for (auto *environment : environments) {
        if (!environment->IsRunning())
            continue;
        for (auto *entity : environment->GetEntities()) {
            entity->Tick(delta);
        }
        environment->Tick(delta);
    }
    environmentsMutex.unlock();
    monitor->Tick(delta);
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
    bool bShouldContinue = true;
    while (bShouldContinue) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                exit(1);
                /*for (int i = 0; i < environments.size(); ++i) {
                    environments[i]->SetRunning(false);
                }*/
            }
            keys[0] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z);
            keys[1] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q);
            keys[2] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);
            keys[3] = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
        }
        ProcessMouse();

        window->clear(sf::Color::Black);
        //bShouldContinue = false;
        for (auto *environment : environments) {
            if (!environment->IsRunning() || !environment->IsRenderingEnabled())
                continue;
            //bShouldContinue = true;
            environment->Render(1/*delta*/);
        }
        window->display();
    }
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

    for (auto *environment : environments) {
        if (!environment->IsRunning())
            continue;
        std::vector<Entity*> &entities = environment->GetEntities();
        
        for (auto *entity : environment->GetEntities()) {
            if (!entity->IsRenderable())
                continue;
            RenderableEntity *renderableEntity = dynamic_cast<RenderableEntity *>(entity);
            if (mouseX >= renderableEntity->GetPosition().x
                && mouseX <= renderableEntity->GetPosition().x + renderableEntity->GetWidth()
                && mouseY >= renderableEntity->GetPosition().y
                && mouseY <= renderableEntity->GetPosition().y + renderableEntity->GetHeight())
            {
                if (renderableEntity->IsClickable())
                    renderableEntity->OnClick();
                return ;
            }
        }
    }
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