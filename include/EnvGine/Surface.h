#pragma once
#include <SFML/Graphics.hpp>
#include "Utils.h"

class Engine;
class Texture;

class Surface {

    public:

    Surface(Engine *engine) : engine(engine) {};

    void FullScreen();

    void SetX(int x);
    void SetY(int y);
    int GetX() const;
    int GetY() const;
    void SetPosition(int x, int y);
    const Position &GetPosition() const;

    void SetWidth(int width);
    void SetHeight(int height);
    int GetWidth() const;
    int GetHeight() const;

    void Draw(Texture *texture, int x, int y, int width, int height);
    void Draw(sf::Text *drawable, int x, int y);

    private:

    Engine *engine = nullptr;
    Position position;
    int width;
    int height;
};