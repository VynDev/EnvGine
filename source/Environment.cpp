#include "Environment.h"
#include "Engine.h"
#include "Surface.h"

using namespace std::chrono;

Environment::Environment(Engine *engine) : Base(engine) {
    surface = new Surface(engine);
}

void Environment::Start() {
    SetRunning(true);
}

void Environment::Remove() {
    SetRunning(false);
    GetEngine().RemoveEnvironment(this);
}

void Environment::RemoveEntities() {
    for (int i = 0; i < entities.size(); ++i) {
        delete entities[i];
    }
}

void Environment::Render(float delta) {

    auto currentRenderTime = high_resolution_clock::now();
    ++_fpsCount;
    if (duration_cast<milliseconds>(currentRenderTime - lastRenderTime).count() >= 1000) {
        lastRenderTime = currentRenderTime;
        fpsCount = _fpsCount;
        _fpsCount = 0;
    }

    for (int i = 0; i < entities.size(); ++i) {
        if (entities[i]->IsRenderable()) {
            dynamic_cast<RenderableEntity *>(entities[i])->Render(*surface);
        }
    }
}

void Environment::SetPosition(int x, int y) {
    surface->SetPosition(x, y);
}

const Position &Environment::GetPosition() const {
    return surface->GetPosition();
}

void Environment::SetWidth(int value) {
    surface->SetWidth(value);
    OnSurfaceResized(surface->GetWidth(), surface->GetHeight());
}

void Environment::SetHeight(int value) {
    surface->SetHeight(value);
    OnSurfaceResized(surface->GetWidth(), surface->GetHeight());
}

void Environment::FullScreen() {
    surface->FullScreen();
    OnSurfaceResized(surface->GetWidth(), surface->GetHeight());
}

int Environment::GetWidth() const {
    return surface->GetWidth();
}

int Environment::GetHeight() const {
    return surface->GetHeight();
}

Surface &Environment::GetSurface() {
    return *surface;
}

void Environment::Stop() {
    SetRunning(false);
}

bool Environment::IsRunning() const {
    return isRunning;
}

void Environment::SetRunning(bool state) {
    isRunning = state;
}

std::vector<Entity*> &Environment::GetEntities() {
    return entities;
}