#pragma once

#include <vector>
#include <initializer_list>

#include <SFML/Graphics.hpp>
#include "InterfaceBase.hpp"

#include "TextFrame.hpp"

namespace sfForm
{
    class ListBoxForm : public FormBase
    {
    public:
        ListBoxForm()
        {
            frameName.setTextFillColor(sf::Color::Black);
        }
        ListBoxForm(const std::initializer_list<sf::String> values)
        {
            frameName.setTextFillColor(sf::Color::Black);
            for (const auto& i : values)
            {
                items.push_back(frameName);
                items.back().setString(i);
            }
            updatePosition();
        }

        #pragma region Text set get

        void setFont(const sf::Font& font)
        {
            frameName.setFont(font);
            for (auto& i : items)
                i.setFont(font);
            updatePosition();
        }
        void setTextFillColor(const sf::Color& color)
        {
            frameName.setTextFillColor(color);
            for (auto& i : items)
                i.setTextFillColor(color);
        }
        void setCharacterSize(const unsigned int size)
        {
            frameName.setCharacterSize(size);
            for (auto& i : items)
                i.setCharacterSize(size);
        }
        void setTextOutLineColor(const sf::Color& color)
        {
            frameName.setTextOutLineColor(color);
            for (auto& i : items)
                i.setTextOutLineColor(color);
        }
        void setTextOutlineThickness(const float s)
        {
            frameName.setTextOutlineThickness(s);
            for (auto& i : items)
                i.setTextOutlineThickness(s);
        }
        void setStyle(const TextStyle s)
        {
            frameName.setStyle(s);
            for (auto& i : items)
                i.setStyle(s);
        }

        const sf::Font* getFont() const
        {
            return frameName.getFont();
        }
        const sf::Color& getTextFillColor() const
        {
            return frameName.getTextFillColor();
        }
        const size_t getCharacterSize() const
        {
            return frameName.getCharacterSize();
        }
        const sf::Color& getTextOutlineColor() const
        {
            return frameName.getTextOutlineColor();
        }
        const unsigned int getTextOutlineThickness() const
        {
            frameName.getTextOutlineThickness();
        }
        const TextStyle getStyle() const
        {
            return frameName.getStyle();
        }

        #pragma endregion

        #pragma region Rect get set

        void setWidth(const float w)
        {
            frameName.setWidth(w);
            for (auto& i : items)
                i.setWidth(w);
        }
        void setHeight(const float h)
        {
            frameName.setHeight(h);
            for (auto& i : items)
                i.setHeight(h);
            updatePosition();
        }
        void setDefaultBackgourndColor(const sf::Color& color)
        {
            defaultColor = color;
            updateColor();
        }
        void setActiveBackgroundColor(const sf::Color& color)
        {
            activeColor = color;
            updateColor();
        }

        const float getWidth() const
        {
            return frameName.getWidth();
        }
        const float getHeight() const
        {
            return frameName.getHeight();
        }
        const sf::Color& getDefaultBackgourndColor() const
        {
            return defaultColor;
        }
        const sf::Color& getActiveBackgroundColor() const
        {
            return activeColor;
        }

        #pragma endregion

        #pragma region Position Bounds get set

        void setPosition(const sf::Vector2f& pos)
        {
            frameName.setPosition(pos);
            updatePosition();
        }
        void setPosition(const float x, const float y)
        {
            setPosition({ x, y });
        }

        const sf::Vector2f& getPosition() const
        {
            return frameName.getPosition();
        }
        const sf::FloatRect getGlobalBounds() const
        {
            if (items.empty() || !isOpen)
                return frameName.getGlobalBounds();
            sf::FloatRect res;
            auto gb = frameName.getGlobalBounds();
            res.left = gb.left;
            res.top = gb.top;
            res.width = gb.width;
            res.height = (items.back().getPosition().y + items.back().getHeight()) - gb.top;
            return res;
        }

        #pragma endregion

        #pragma region Array methods

        void setSelectIndex(const unsigned int ind)
        {
            updateIndex(ind);
        }

        const int getSelectIndex() const
        {
            return selectIndex;
        }

        const sf::String& operator[](const size_t ind) const
        {
            return items[ind].getString();
        }
        void pushBack(const sf::String& str)
        {
            items.push_back(frameName);
            items.back().setBackgrounColor(defaultColor);
            items.back().setString(str);
            if (frameName.getFont() != nullptr)
                items.back().setFont(*frameName.getFont());
        }
        void setStringAt(const size_t ind, const sf::String& str)
        {
            if (ind >= items.size())
                return;
            items[ind].setString(str);
        }
        void erase(const size_t ind, size_t count = 1)
        {
            if (ind >= items.size())
                return;
            if (selectIndex >= ind && selectIndex <= ind + count)
                frameName.setString("");
            if (items.size() - count < ind)
                count = items.size() - ind;
            items.erase(items.begin() + ind, items.begin() + ind + count);
        }

        #pragma endregion

        bool isListOpen()
        {
            return isOpen;
        }

        bool update(const sf::RenderWindow& window, const sf::Event& event) override
        {
            auto pos = sf::Mouse::getPosition(window);
            if (isOpen)
            {
                for (size_t i = 0; i < items.size(); ++i)
                {
                    if (i == selectIndex)
                        continue;
                    if (items[i].getGlobalBounds().contains((float)pos.x, (float)pos.y))
                        items[i].setBackgrounColor(activeColor);
                    else
                        items[i].setBackgrounColor(defaultColor);
                }
            }
            else
            {
                if (frameName.getGlobalBounds().contains((float)pos.x, (float)pos.y))
                    frameName.setBackgrounColor(activeColor);
                else
                    frameName.setBackgrounColor(defaultColor);
            }
            if (event.type != sf::Event::MouseButtonPressed)
                return false;
            if (isOpen)
            {
                for (size_t i = 0; i < items.size(); ++i)
                    if (items[i].getGlobalBounds().contains((float)pos.x, (float)pos.y))
                    {
                        isOpen = false;
                        return updateIndex(i);
                    }
                isOpen = false;
                return false;
            }
            else
            {
                if (frameName.getGlobalBounds().contains((float)pos.x, (float)pos.y))
                    isOpen = true;
            }
            return false;
        }

    private:
        TextFrameForm frameName;
        std::vector<TextFrameForm> items;

        sf::Color activeColor = sf::Color::Blue;
        sf::Color defaultColor = sf::Color::White;

        int selectIndex = -1;

        bool isOpen = false;

        void updatePosition()
        {
            if (items.size() == 0)
                return;
            const sf::Vector2f& pos = frameName.getPosition();
            float pr = frameName.getCharacterSize() * 1.5f;
            for (size_t i = 0; i < items.size(); ++i)
                items[i].setPosition({ pos.x, pos.y + (pr + 3) * i });
        }

        void updateColor()
        {
            if (isOpen)
            {
                if (selectIndex == 0)
                    return;
                for (auto& i : items)
                    i.setBackgrounColor(defaultColor);
                items[selectIndex].setBackgrounColor(activeColor);
            }
            else
                frameName.setBackgrounColor(defaultColor);
        }

        bool updateIndex(const size_t ind)
        {
            if (ind >= items.size() || ind == selectIndex)
                return false;
            if (selectIndex >= 0)
                items[selectIndex].setBackgrounColor(defaultColor);
            items[ind].setBackgrounColor(activeColor);
            selectIndex = (int)ind;
            frameName.setString(items[selectIndex].getString());
            return true;
        }

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override
        {
            states.transform *= getTransform();
            if (isOpen)
                for (const auto& i : items)
                    target.draw(i, states);
            else
                target.draw(frameName, states);
        }
    };

    using ListBox = std::shared_ptr<ListBoxForm>;

}