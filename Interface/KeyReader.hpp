#pragma once

#include <SFML/Graphics.hpp>

#include "InterfaceHelpFunctions.hpp"
#include "InterfaceBase.hpp"

namespace sfForm
{
    class KeyReaderForm : public FormBase
    {
    public:
        KeyReaderForm()
        {
            text.setFillColor(sf::Color::Black);
            text.setString("Unknown");
            text.setOutlineColor(sf::Color::Blue);
        }

        #pragma region Text get set

        void setFont(const sf::Font& font)
        {
            text.setFont(font);
        }
        void setTextFillColor(const sf::Color& color)
        {
            text.setFillColor(color);
        }
        void setTextOutLineColor(const sf::Color& color)
        {
            text.setOutlineColor(color);
        }
        void setTextOutlineThickness(const float s)
        {
            text.setOutlineThickness(s);
        }
        void setCharacterSize(const unsigned int size)
        {
            text.setCharacterSize(size);
        }

        const sf::Font* getFont() const
        {
            return text.getFont();
        }
        const sf::Color& getTextFillColor() const
        {
            return text.getFillColor();
        }
        const sf::Color& getTextOutlineColor() const
        {
            return text.getOutlineColor();
        }
        const unsigned int getTextOutlineThickness() const
        {
            text.getOutlineThickness();
        }
        const unsigned int getCharacterSize() const
        {
            return text.getCharacterSize();
        }

        #pragma endregion

        #pragma region Position Bounds get set

        void setPosition(const sf::Vector2f& pos)
        {
            text.setPosition(pos);
        }
        void setPosition(const float x, const float y)
        {
            setPosition({ x, y });
        }

        const sf::FloatRect getGlobalBounds() const
        {
            return text.getGlobalBounds();
        }
        const sf::Vector2f& getPosition() const
        {
            return text.getPosition();
        }

        #pragma endregion

        void setKey(const sf::Keyboard::Key& k)
        {
            key = k;
            text.setString(sfKeyToString(key));
        }

        const sf::Keyboard::Key& getKey() const
        {
            return key;
        }

        //@param true if key is entered, else false
        bool update(const sf::RenderWindow& window, const sf::Event& event) override
        {
            if (event.type == sf::Event::MouseButtonPressed)
            {
                auto pos = sf::Mouse::getPosition(window);
                active = text.getGlobalBounds().contains((float)pos.x, (float)pos.y);
                UpdateColor();
            }
            else if ((event.type == sf::Event::KeyPressed) && active)
            {
                key = event.key.code;
                text.setString(sfKeyToString(key));
                active = false;
                UpdateColor();
                return true;
            }
            return false;
        }

    private:
        sf::Text text;
        sf::Keyboard::Key key = sf::Keyboard::Unknown;

        bool active = false;

        void UpdateColor()
        {
            if (active)
                text.setOutlineThickness(3);
            else
                text.setOutlineThickness(0);
        }

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override
        {
            states.transform *= getTransform();
            target.draw(text, states);
        }
    };

    using KeyReader = std::shared_ptr<KeyReaderForm>;

}