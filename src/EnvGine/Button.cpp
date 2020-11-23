#include "Button.h"
#include "Surface.h"

Button::Button(Environment *environment) : Entity(environment) {

    if (!font.loadFromFile("Resources/arial.ttf"))
    {
        std::cout << "Cannot load arial.ttf" << std::endl;
        return ;
    }

    text.setFont(font);
    text.setString("Hello world");
    text.setCharacterSize(64);
    text.setFillColor(sf::Color::Red);

    SetWidth(text.getGlobalBounds().width);
    SetHeight(text.getGlobalBounds().height);
    SetClickable(true);
}

void Button::Render(Surface &surface) {
    surface.Draw(&text, GetX(), GetY());
}

void Button::SetText(std::string value) {
    text.setString(value);
    SetWidth(text.getGlobalBounds().width);
    SetHeight(text.getGlobalBounds().height);
}

void Button::SetCharacterSize(int value) {
    text.setCharacterSize(value);
    SetWidth(text.getGlobalBounds().width);
    SetHeight(text.getGlobalBounds().height);
}

void Button::CenterHorizontaly() {
    SetPosition(GetEnvironment().GetSurface().GetWidth() / 2 - GetWidth() / 2, GetY());
}

void Button::CenterVerticaly() {
    SetPosition(GetX(), GetEnvironment().GetSurface().GetHeight() / 2 - GetHeight() / 2);
}