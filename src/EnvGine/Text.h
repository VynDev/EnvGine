#pragma once

#include <iostream>
#include <functional>

#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "Engine.h"

class Text : public Entity {

    public:

    Text(Environment *environment);

    virtual void Render(Surface &surface);

    virtual void OnClick();
    void SetOnClickFunction(std::function<void()> f);

    void SetText(std::string value);

    void SetPosition(int x, int y);
    const Position &GetPosition() const;

    void SetCharacterSize(int value) {text.setCharacterSize(value);}
    int GetWidth() const {return text.getGlobalBounds().width;}
    int GetHeight() const {return text.getGlobalBounds().height;}

    protected:

    sf::Font font;
    sf::Text text;

    std::function<void()> onClickFunction = nullptr;

};