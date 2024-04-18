#pragma once

#include<SFML\\Graphics.hpp>
#include "InterfaceBase.hpp"

namespace sfForm
{
    class CheckBoxForm : public FormBase
    {
    public:
        CheckBoxForm()
        {
            rect.setSize(sf::Vector2f(15.f, 15.f));
            rect.setFillColor(sf::Color::Transparent);
            rect.setOutlineColor(sf::Color::Black);
            rect.setOutlineThickness(3);

            text.setPosition(rect.getPosition() + sf::Vector2f{ rect.getSize().x + 10.f, 0.f });
            text.setFillColor(sf::Color::Black);
        }

        #pragma region Rect set get

        void setRectFillColor(const sf::Color& color)
        {
            fillColor = color;
            UpdateColor();
        }
        void setRectOutlineColor(const sf::Color& color)
        {
            rect.setOutlineColor(color);
        }
        void setRectOutlineThickness(const float v)
        {
            rect.setOutlineThickness(v);
        }
        void setWidth(const float& v)
        {
            if (v <= 0)
                return;
            rect.setSize(sf::Vector2f(v, v));
            text.setPosition(rect.getPosition() + sf::Vector2f{ rect.getSize().x + 10.f, 0.f });
        }

        const sf::Color& getRectFillColor() const
        {
            return fillColor;
        }
        const sf::Color& getRectOutlineColor() const
        {
            return rect.getOutlineColor();
        }
        const float getRectOutlineThikness() const
        {
            return rect.getOutlineThickness();
        }
        const float& getWidth() const
        {
            return rect.getSize().x;
        }

        #pragma endregion

        #pragma region Text get set

        void setString(const sf::String& str)
        {
            text.setString(str);
        }
        void setFont(const sf::Font& font)
        {
            text.setFont(font);
        }
        void setCharacterSize(const unsigned int c)
        {
            text.setCharacterSize(c);
        }
        void setTextOutlineColor(const sf::Color& color)
        {
            text.setOutlineColor(color);
        }
        void setTextOutlineThikness(const float c)
        {
            text.setOutlineThickness(c);
        }
        void setTextFillColor(const sf::Color& color)
        {
            text.setFillColor(color);
        }
        void setText(const sf::Text& t)
        {
            text = t;
            UpdateColor();
            text.setPosition(rect.getPosition() + sf::Vector2f{rect.getSize().x + 10.f, 0.f});
        }

        const sf::String& getSting() const
        {
            return text.getString();
        }
        const sf::Font* getFont() const
        {
            return text.getFont();
        }
        const unsigned int getCharacterSize() const
        {
            return text.getCharacterSize();
        }
        const sf::Color& getTextOutlineColor() const
        {
            return text.getOutlineColor();
        }
        const float getTextOutlineThikness() const
        {
            return text.getOutlineThickness();
        }
        const sf::Color& getTextFillColor() const
        {
            return text.getFillColor();
        }
        const sf::Text& getText() const
        {
            return text;
        }

        #pragma endregion

        #pragma region Position Bounds get set

        const sf::Vector2f& getPosition() const
        {
            return rect.getPosition();
        }
        const sf::FloatRect getGlobalBounds() const
        {
            sf::FloatRect res;
            res.top = text.getPosition().y;
            res.left = rect.getPosition().x;
            auto pr = text.getGlobalBounds();
            res.height = pr.height;
            res.width = pr.left + pr.width - rect.getPosition().x;
            return res;
        }

        void setPosition(const sf::Vector2f& pos)
        {
            rect.setPosition(pos);
            text.setPosition(pos + sf::Vector2f{ rect.getSize().x + 10.f, 0.f });
        }
        void setPosition(const float x, const float y)
        {
            setPosition({x, y});
        }

        #pragma endregion

        //@result true if check value is changed 
        bool update(const sf::RenderWindow& window, const sf::Event& event) override
        {
            if (event.type != sf::Event::MouseButtonPressed)
                return false;
            sf::Vector2i pos = sf::Mouse::getPosition(window);
            if (rect.getGlobalBounds().contains((float)pos.x, (float)pos.y) || text.getGlobalBounds().contains((float)pos.x, (float)pos.y))
            {
                cheked = !cheked;
                UpdateColor();
                return true;
            }
            return false;
        }

        const bool& isCheked() const
        {
            return cheked;
        }
        void setCheked(const bool v)
        {
            cheked = v;
            UpdateColor();
        }

    private:
        sf::RectangleShape rect;
        sf::Text text;
        sf::Color fillColor = sf::Color::Blue;

        bool cheked = false;

        void UpdateColor()
        {
            if (cheked)
                rect.setFillColor(fillColor);
            else
                rect.setFillColor(sf::Color::Transparent);
        }

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override
        {
            states.transform *= getTransform();
            target.draw(rect, states);
            target.draw(text, states);
        }
    };

    using CheckBox = std::shared_ptr<CheckBoxForm>;

}