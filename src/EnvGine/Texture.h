#pragma once
#include <SFML/Graphics.hpp>

class Texture {

    public:

    Texture(int width, int height);

    sf::Drawable &GetSFMLDrawable();
    sf::RenderTexture &GetSFMLRenderTexture();

    void SetPosition(int x, int y);
    
    void SetWidth(int value);
    void SetHeight(int value);

    private:

    sf::RenderTexture texture;
    sf::Sprite sprite;

};