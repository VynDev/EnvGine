#include "Text.h"
#include "Surface.h"

Text::Text(Environment *environment) : Entity(environment) {

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

    SetPosition(text.getGlobalBounds().left, text.getGlobalBounds().top);
    SetWidth(text.getGlobalBounds().width);
    SetHeight(text.getGlobalBounds().height);
    SetClickable(true);
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
}

void Text::SetText(std::string value) {
    text.setString(value);
}

void Text::SetPosition(int x, int y) {
    position.x = x;
    position.y = y;
    text.setPosition(x, y);
}

const Position &Text::GetPosition() const {
    return position;
}