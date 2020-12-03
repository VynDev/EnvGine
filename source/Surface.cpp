
#include <SFML/Graphics.hpp>
#include "Surface.h"
#include "Engine.h"
#include "Texture.h"

void Surface::Draw(Texture *texture, int x, int y, int width, int height) {
    texture->SetPosition(GetX() + x, GetY() + y);
    texture->SetWidth(width);
    texture->SetHeight(height);
    engine->GetWindow().draw(texture->GetSFMLDrawable());
}

void Surface::Draw(sf::Text *drawable, int x, int y) {
    drawable->setPosition(GetX() + x, GetY() + y);
    engine->GetWindow().draw(*drawable);
}

void Surface::FullScreen() {
    SetWidth(engine->GetWindow().getSize().x);
    SetHeight(engine->GetWindow().getSize().y);
}

void Surface::SetPosition(int x, int y) {
    position.x = x; position.y = y;
}

void Surface::SetX(int x) {
    position.x = x;
}

void Surface::SetY(int y) {
    position.y = y;
}

const Position &Surface::GetPosition() const {
    return position;
}

int Surface::GetX() const {
    return position.x;
}

int Surface::GetY() const {
    return position.y;
}

void Surface::SetWidth(int width) {
    this->width = width;
}

void Surface::SetHeight(int height) {
    this->height = height;
}

int Surface::GetWidth() const {
    return width;
}

int Surface::GetHeight() const {
    return height;
}