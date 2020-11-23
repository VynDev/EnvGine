#include "Texture.h"
#include <iostream>

Texture::Texture(int width, int height) {
    texture.create(width, height);
}

sf::RenderTexture &Texture::GetSFMLRenderTexture() {
    return texture;
}

sf::Drawable &Texture::GetSFMLDrawable() {
    sprite.setTexture(GetSFMLRenderTexture().getTexture());
    return sprite;
}

void Texture::SetPosition(int x, int y) {
    sprite.setPosition(x, y);
}

void Texture::SetWidth(int value) {
    sprite.setScale(value / sprite.getLocalBounds().width, sprite.getScale().y);
}

void Texture::SetHeight(int value) {
    sprite.setScale(sprite.getScale().x, value / sprite.getLocalBounds().height);
}