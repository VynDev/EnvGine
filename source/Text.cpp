#include "Text.h"
#include "Surface.h"

Text::Text(Environment *environment) : RenderableEntity(environment) {

    if (!font.loadFromFile("Resources/arial.ttf"))
    {
        std::cout << "Cannot load arial.ttf" << std::endl;
        return ;
    }

    text.setFont(font);
    text.setString("Hello world");
    text.setCharacterSize(64);
    text.setFillColor(sf::Color::Red);
    text.setPosition(400, 400);
}

void Text::Render(Surface &surface) {
    surface.Draw(&text, GetX(), GetY());
}

void Text::OnClick() {
    if (!onClickFunction)
        return;
    onClickFunction();
}

void Text::SetOnClickFunction(std::function<void()> f) {
    this->onClickFunction = f;
    SetClickable(true);
}

void Text::SetText(std::string value) {
    text.setString(value);
}

void Text::CenterHorizontaly() {
    SetPosition(GetEnvironment().GetSurface().GetWidth() / 2 - GetWidth() / 2, GetY());
}

void Text::CenterVerticaly() {
    SetPosition(GetX(), GetEnvironment().GetSurface().GetHeight() / 2 - GetHeight() / 2);
}