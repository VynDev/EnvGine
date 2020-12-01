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

    /* Basics */

    Engine(sf::RenderWindow *window) : window(window) {}

    static Engine *Init(int width, int height);
    int Execute(Environment *environment);
   
    sf::RenderWindow &GetWindow();

    int GetWindowWidth() const;
    int GetWindowHeight() const;

    int GetThreadCount() const {return threadCount;}

    void SetTickEnabled(bool value) {bTickEnabled = value;}

    /* Inputs - Keys */

    bool IsKeyPressed(int keyCode);

    /* Environments */

    template<class T>
    T* CreateEnvironment();
    void RemoveEnvironment(Environment *environment);
    Environment* StartEnvironment(Environment *environment);

    private:

    void Tick(int threadIndex);
    void AddThread();
    void ThreadLoop(int threadIndex);

    void RenderLoop(); 
    void ProcessMouse();

    bool bTickEnabled = true;

    int threadCount = 0;
    int keys[4]; // Z Q S D, because I only have this use case atm and I want to make it simple.

    std::mutex environmentsMutex;
    sf::RenderWindow *window = nullptr;
    std::vector<Environment*> environments;
    std::chrono::_V2::system_clock::time_point lastTick = std::chrono::high_resolution_clock::now();
};

#include "Engine.tpp"