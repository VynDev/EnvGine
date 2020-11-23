#pragma once
#include <vector>
#include <chrono>
#include <mutex>

#include <SFML/Graphics.hpp>

#include "Environment.h"
#include "Exception.h"

class Engine {

    public:

    //typedef sf::Keyboard Keyboard;

    int Execute(Environment *environment);

    static Engine *Init(int width, int height);
    void SetWindow(sf::RenderWindow *window);
    sf::RenderWindow &GetWindow();
    int GetWindowWidth() const;
    int GetWindowHeight() const;

    void AddThread();
    int GetThreadCount() const {return threadCount;}

    void SetTickEnabled(bool value) {bTickEnabled = value;}
    void Tick(int threadIndex);
    void RenderLoop();

    void ProcessInputs();
    void ProcessMouse();
    bool IsKeyPressed(int keyCode);

    template<class T>
    T* CreateEnvironment() {
        T *environment = new T(this);
        environmentsMutex.lock();
        environments.push_back(environment);
        environmentsMutex.unlock();
        return environment;
    }

    void RemoveEnvironment(Environment *environment);
    Environment* StartEnvironment(Environment *environment);

    private:    

    std::mutex environmentsMutex;
    bool quit = false;
    bool bTickEnabled = true;
    int threadCount = 0;
    sf::RenderWindow *window = nullptr;
    std::vector<Environment*> environments;
    std::chrono::_V2::system_clock::time_point lastTick = std::chrono::high_resolution_clock::now();

    int keys[4];
};