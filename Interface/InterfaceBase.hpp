#pragma once

#include<memory>

#include <SFML/Graphics.hpp>

namespace sfForm
{
	class FormBase : public sf::Drawable, public sf::Transformable
	{
	public:

		virtual bool update(const sf::RenderWindow& window, const sf::Event& event) = 0;

		bool isVisible() const
		{
			return visible;
		}
		void show()
		{
			visible = true;
		}
		void hide()
		{
			visible = false;
		}

	protected:

		bool visible = true;

	};
}