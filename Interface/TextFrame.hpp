#pragma once

#include <SFML\\Graphics.hpp>

#include "InterfaceHelpFunctions.hpp"
#include "InterfaceBase.hpp"

namespace sfForm
{
    class TextFrameForm : public FormBase
    {
    public:
        TextFrameForm()
        {
            rect.setFillColor(sf::Color::Transparent);
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
            updateText();
        }
        void setStyle(const TextStyle s)
        {
            style = s;
            updateText();
        }
        void setText(const sf::Text& t)
        {
            text = t;
            updateText();
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
        const sf::String& getString() const
        {
            return text.getString();
        }
        const TextStyle getStyle() const
        {
            return style;
        }
        const sf::Text& getText() const
        {
            return text;
        }

        #pragma endregion

        #pragma region Rectangle get set

        void setHeight(const float h)
        {
            if (h < 0.f)
                return;
            rect.setSize({ rect.getSize().x, h });
            updateText();
        }
        void setWidth(const float w)
        {
            if (w < 0.f)
                return;
            rect.setSize({ w, rect.getSize().y });
            updateText();
        }
        void setBackgrounColor(const sf::Color& color)
        {
            rect.setFillColor(color);
        }
        void setBorderOutlineColor(const sf::Color& color)
        {
            rect.setOutlineColor(color);
        }

        const float getHeight() const
        {
            return rect.getSize().y;
        }
        const float getWidth() const
        {
            return rect.getSize().x;
        }
        const sf::Color& getBackgoundColor() const
        {
            return rect.getFillColor();
        }
        const sf::Color& getBorderOutlineColor() const
        {
            return rect.getOutlineColor();
        }

        #pragma endregion

        #pragma region Position Bounds get set

        void setPosition(const float x, const float y)
        {
            setPosition(sf::Vector2f(x, y));
        }
        void setPosition(const sf::Vector2f& pos)
        {
            rect.setPosition(pos);
            updateText();
        }

        const sf::Vector2f& getPosition() const
        {
            return rect.getPosition();
        }
        const sf::FloatRect getGlobalBounds() const
        {
            sf::FloatRect res;
            res.left = rect.getPosition().x;
            res.top = rect.getPosition().y;
            res.width = rect.getSize().x;
            res.height = rect.getSize().y;
            return res;
        }

        #pragma endregion

        bool update(const sf::RenderWindow& window, const sf::Event& event) override
        {
            return false;
        }

    private:
        sf::Text text;
        sf::RectangleShape rect;
        TextStyle style = TextStyle::center;

        void updateText()
        {
            centreteText(style, rect, text);
        }

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override
        {
            states.transform *= getTransform();
            sf::RectangleShape r;

            target.draw(rect, states);
            target.draw(text, states);
        }
    };

    using TextFrame = std::shared_ptr<TextFrameForm>;

}