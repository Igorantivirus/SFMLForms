#pragma once

#include <functional>

#include <SFML/Graphics.hpp>

#include "InterfaceHelpFunctions.hpp"
#include "InterfaceBase.hpp"

namespace sfForm
{
    class ButtonForm : public FormBase
    {
    public:
        ButtonForm()
        {
            rect.setFillColor(sf::Color::White);
            rect.setOutlineColor(sf::Color::Black);
            rect.setOutlineThickness(3);
            rect.setSize({ 150.f, (float)text.getCharacterSize() * 1.5f });
            text.setFillColor(sf::Color::Black);
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
            rect.setSize({ rect.getSize().x, (float)text.getCharacterSize() * 1.5f });
        }
        void setString(const sf::String& str)
        {
            text.setString(str);
            UpdateText();
        }
        void setStyle(const TextStyle& s)
        {
            style = s;
            UpdateText();
        }
        void setText(const sf::Text& t)
        {
            text = t;
            UpdateColor();
            UpdateText();
        }

        const sf::Font* getFont() const
        {
            return text.getFont();
        }
        const sf::Color getTextFillColor() const
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
        const sf::String& getString() const
        {
            return text.getString();
        }
        const TextStyle& getStyle() const
        {
            return style;
        }
        const sf::Text& getText() const
        {
            return text;
        }

        #pragma endregion

        #pragma region Rectangle get set

        void setHeight(const float& h)
        {
            if (h < 0.f)
                return;
            rect.setSize({ rect.getSize().x, h });
            UpdateText();
        }
        void setWidth(const float& w)
        {
            if (w < 0.f)
                return;
            rect.setSize({ w, rect.getSize().y });
            UpdateText();
        }
        void setBackgoundColor(const sf::Color& color)
        {
            backColor = color;
            UpdateColor();
        }
        void setActiveBackgoundColor(const sf::Color& color)
        {
            activeColor = color;
            UpdateColor();
        }
        void setOutlineColor(const sf::Color& color)
        {
            rect.setOutlineColor(color);
        }

        const float& getHeight() const
        {
            return rect.getSize().y;
        }
        const float& getWidth() const
        {
            return rect.getSize().x;
        }
        const sf::Color& getBackgoundColor() const
        {
            return backColor;
        }
        const sf::Color& getActiveBackgoundColor() const
        {
            return activeColor;
        }
        const sf::Color& getOutlineColor() const
        {
            return text.getOutlineColor();
        }

        #pragma endregion

        #pragma region Position Bounds get set

        const sf::Vector2f& getPosition() const
        {
            return text.getPosition();
        }
        const sf::FloatRect getGlobalBounds() const
        {
            return rect.getGlobalBounds();
        }

        void setPosition(const sf::Vector2f& pos)
        {
            rect.setPosition(pos);
            UpdateText();
        }
        void setPosition(const float x, const float y)
        {
            setPosition(sf::Vector2f(x, y));
        }

        #pragma endregion

        void setFunc(const std::function<void()>& foo)
        {
            func = foo;
        }
        const std::function<void()>& getFunc() const
        {
            return func;
        }

        bool isActive() const
        {
            return actve;
        }

        //@result true if Buttin is clicked else false
        bool update(const sf::RenderWindow& window, const sf::Event& event) override
        {
            static bool wasPressed = false;
            bool res;
            if (event.type != sf::Event::MouseButtonPressed)
            {
                actve = false;
                UpdateColor();
                res =  wasPressed ? !(wasPressed = false) : wasPressed;
            }
            else
            {
                auto pos = sf::Mouse::getPosition(window);
                if (rect.getGlobalBounds().contains((float)pos.x, (float)pos.y))
                {
                    actve = true;
                    UpdateColor();
                    res = !(wasPressed = true);
                }
                else
                {
                    actve = false;
                    UpdateColor();
                    res = wasPressed = false;
                }
            }
            if (res && func != nullptr)
                func();
            return res;
        }

    private:
        sf::Text text;
        sf::RectangleShape rect;

        TextStyle style = TextStyle::center;

        sf::Color activeColor = sf::Color::Blue;
        sf::Color backColor = sf::Color::White;

        std::function<void()> func;

        bool actve = false;

    private:

        //centrete text at style value
        void UpdateText()
        {
            centreteText(style, rect, text);
        }

        //replace back color
        void UpdateColor()
        {
            if (actve)
                rect.setFillColor(activeColor);
            else
                rect.setFillColor(backColor);
        }

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override
        {
            if (!visible)
                return;
            states.transform *= getTransform();
            target.draw(rect, states);
            target.draw(text, states);
        }
    };

    using Button = std::shared_ptr<ButtonForm>;

}