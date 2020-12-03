#pragma once
#include <vector>
#include <chrono>
#include "Base.h"
#include "Entity.h"
#include "RenderableEntity.h"
#include "Utils.h"

class Engine;
class Surface;

class Environment : public Base {
    public:

    Environment(Engine *engine);
    virtual ~Environment() {};

    virtual void Tick(float delta) {};
    virtual void Render(float delta);
    virtual void OnSurfaceResized(int newWidth, int newHeight) {};

    void Start();
    void Remove();

    void SetRenderingEnabled(bool value) {bRenderingEnabled = value;}
    bool IsRenderingEnabled() const {return bRenderingEnabled;}

    void SetWidth(int value);
    void SetHeight(int value);
    void FullScreen();
    int GetWidth() const;
    int GetHeight() const;
    Surface &GetSurface();

    void Stop();

    bool IsRunning() const;
    void SetRunning(bool state);

    std::vector<Entity*> &GetEntities();
    void RemoveEntities();

    template<class T>
    T* CreateEntity();

    int GetFpsCount() const {return fpsCount;}

    void SetPosition(int x, int y);
    const Position &GetPosition() const;

    private:    

    Surface *surface = nullptr;
    bool bRenderingEnabled = true;

    bool isRunning = false;
    std::vector<Entity *> entities;

    int _fpsCount = 0;
    int fpsCount = 0;
    std::chrono::_V2::system_clock::time_point lastRenderTime;
    
};

#include "Environment.tpp"