#pragma once

#include<vector>
#include<memory>

#include<SFML/Graphics.hpp>

#include"Interface//InterfaceBase.hpp"

namespace sfForm
{
	class Form
	{
	public:
		Form(const sf::VideoMode& mode, const sf::String& wName) : window(mode, wName) {}

		void Run()
		{
			while (window.isOpen())
			{
				UpdateEvents();
				Draw();
			}
		}

		void Add(std::shared_ptr<sf::Drawable> obj)
		{
			objects.push_back(obj);
		}
		template<typename T>
		void Add(std::shared_ptr<T> fObj)
		{
			formObjects.push_back(std::dynamic_pointer_cast<FormBase>(fObj));
		}

		bool isVisible() const
		{
			return visible;
		}
		void Show()
		{
			window.setVisible(visible = false);
		}
		void Hide()
		{
			window.setVisible(visible = true);
		}

		const sf::Color& getBackgroundColor() const
		{
			return backgroundColor;
		}
		void setBackgroundColor(const sf::Color& color)
		{
			backgroundColor = color;
		}

	private:

		sf::RenderWindow window;

		sf::Event event{};

		std::vector<std::shared_ptr<sf::Drawable>> objects;
		std::vector<std::shared_ptr<FormBase>> formObjects;

		bool visible = true;

	private:

		sf::Color backgroundColor = sf::Color::White;

	private:

		void UpdateEvents()
		{
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				for (auto& i : formObjects)
					i->update(window, event);
			}
		}

		void Draw()
		{
			window.clear(backgroundColor);
			for (const auto& i : objects)
				window.draw(*i);
			for (const auto& i : formObjects)
				window.draw(*i);
			window.display();
		}

	};
}