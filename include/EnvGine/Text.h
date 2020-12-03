#pragma once

#include <iostream>
#include <functional>

#include <SFML/Graphics.hpp>

#include "RenderableEntity.h"
#include "Engine.h"

class Text : public RenderableEntity {

    public:

    Text(Environment *environment);

    virtual void Render(Surface &surface) override;
    virtual void OnClick() override;
    virtual int GetWidth() const override {return text.getGlobalBounds().width;}
    virtual int GetHeight() const override {return text.getGlobalBounds().height;}

    void SetOnClickFunction(std::function<void()> f);
    void SetText(std::string value);
    void SetCharacterSize(int value) {text.setCharacterSize(value);}

    void CenterHorizontaly();
    void CenterVerticaly();

    protected:

    sf::Font font;
    sf::Text text;

    std::function<void()> onClickFunction = nullptr;

};