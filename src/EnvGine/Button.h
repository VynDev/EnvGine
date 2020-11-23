#pragma once

#include <iostream>
#include <functional>

#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "Engine.h"

class Button : public Entity {

    public:

    Button(Environment *environment);

    virtual void Render(Surface &surface);

    virtual void OnClick() {
        if (!onClickFunction)
            return;
        onClickFunction();
    }
    void SetOnClickFunction(std::function<void()> f) {
        this->onClickFunction = f;
    }

    void SetText(std::string value);

    void SetPosition(int x, int y) {
        text.setPosition(x, y);
        position.x = text.getGlobalBounds().left;
        position.y = text.getGlobalBounds().top;
    }
    const Position &GetPosition() const {return position;}

    void SetCharacterSize(int value);
    int GetWidth() const {return text.getGlobalBounds().width;}
    int GetHeight() const {return text.getGlobalBounds().height;}

    void CenterHorizontaly();
    void CenterVerticaly();

    protected:

    sf::Font font;
    sf::Text text;

    std::function<void()> onClickFunction = nullptr;

};