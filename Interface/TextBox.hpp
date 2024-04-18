#pragma once

#include<SFML\\Graphics.hpp>

#include "InterfaceBase.hpp"

namespace sfForm
{
    class TextBoxForm : public FormBase
    {
    public:
        TextBoxForm()
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
            UpdateText();
            if (intOnly)
                UpdateInt();
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
        void setBackgrounColor(const sf::Color& color)
        {
            rect.setFillColor(color);
        }
        void setDefaultOutlineColor(const sf::Color& color)
        {
            outBack = color;
            UpdateColor();
        }
        void setActiveOutlineColor(const sf::Color& color)
        {
            outActive = color;
            UpdateColor();
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
            return rect.getFillColor();
        }
        const sf::Color& getDefaultOutlineColor() const
        {
            return outBack;
        }
        const sf::Color& getActiveOutlineColor() const
        {
            return outActive;
        }

        #pragma endregion

        #pragma region Position Bounds get set

        void setPosition(const sf::Vector2f& pos)
        {
            text.setPosition(pos);
            rect.setPosition(pos);
        }
        void setPosition(const float x, const float y)
        {
            setPosition(sf::Vector2f(x, y));
        }

        const sf::Vector2f& getPosition() const
        {
            return text.getPosition();
        }
        const sf::FloatRect getGlobalBounds() const
        {
            return rect.getGlobalBounds();
        }

        #pragma endregion
        
        const bool& getReadOnly() const
        {
            return readOnly;
        }
        const bool& getIntOnlyt() const
        {
            return intOnly;
        }

        void setReadOnly(const bool v)
        {
            readOnly = v;
        }
        void setIntOnly(const bool v)
        {
            intOnly = v;
            if (intOnly)
                UpdateInt();
        }

        //@result true if letter was added
        bool update(const sf::RenderWindow& window, const sf::Event& event) override
        {
            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i pos = sf::Mouse::getPosition(window);
                isActive = rect.getGlobalBounds().contains((float)pos.x, (float)pos.y);
                UpdateColor();
                return false;
            }
            if (event.type == sf::Event::TextEntered)
            {
                if (!isActive || readOnly || event.text.unicode == 0)
                    return false;
                return UpdateText(event.text.unicode);
            }
            return false;
        }

    private:
        sf::Text text;
        sf::RectangleShape rect;
        bool isActive = false;
        bool readOnly = false;
        bool intOnly = false;

        sf::Color outBack = sf::Color::Black;
        sf::Color outActive = sf::Color::Blue;

        //@result true if update is sucsess
        bool UpdateText(const sf::Uint32& c = 0)
        {
            if (c == 0 || readOnly)
                return false;
            sf::String s = text.getString();
            if (c == '\b')
            {
                if (s.getSize() == 0)
                    return false;
                s.erase(s.getSize() - 1, 1);
            }
            else if (c == 127)
            {
                size_t pos = 0;
                for (size_t i = s.getSize(); i > 0; --i)
                    if (s[i - 1] == ' ' || s[i - 1] == '\t' || s[i - 1] == '\n')
                    {
                        pos = i - 1;
                        break;
                    }
                s.erase(pos, s.getSize() - pos);
            }
            else if (c == 13)
                s += '\n';
            else
            {
                if (intOnly)
                {
                    if (c >= '0' && c <= '9')
                        s += c;
                }
                else
                    s += c;
            }
            text.setString(s);
            const size_t cs = s.getSize();
            for (sf::FloatRect a = text.getGlobalBounds(), b = rect.getGlobalBounds();
                a.width >= b.width || a.height > b.height;
                a = text.getGlobalBounds(), b = rect.getGlobalBounds())
            {
                s.erase(s.getSize() - 1, 1);
                text.setString(s);
            }
            return s.getSize() == cs;
        }

        void UpdateColor()
        {
            if (isActive)
                rect.setOutlineColor(outActive);
            else
                rect.setOutlineColor(outBack);
        }

        void UpdateInt()
        {
            sf::String s = text.getString();
            for (size_t i = s.getSize(); i > 0; --i)
            {
                if (s[i - 1] < '0' || s[i - 1] > '9')
                    s.erase(i - 1, 1);
            }
            text.setString(s);
        }

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override
        {
            states.transform *= getTransform();
            target.draw(rect, states);
            target.draw(text, states);
        }
    };

    using TextBox = std::shared_ptr<TextBoxForm>;

}