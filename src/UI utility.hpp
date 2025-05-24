#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "game_data.hpp"


using namespace std;



namespace myUI {

	class button {
	public:

		bool const_pressed = false;


		button(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Font& font, const std::string& label) : text(font, label, 22){
			background.setSize(size);
			background.setPosition(position);
			background.setFillColor(sf::Color::Red);

			text.setFont(font);
			text.setString(label);
			text.setCharacterSize(22);
			text.setFillColor(sf::Color::White);

			// Center the text
			auto bounds = text.getLocalBounds();
			text.setOrigin(bounds.getCenter()); // SFML 3: centers origin
			text.setPosition(position + size / 2.f);
		}



		void draw(sf::RenderWindow& window) {
			window.draw(background);
			window.draw(text);
		}


		bool isMouseOver(int x, int y) {
			if (x > this->background.getPosition().x && x < this->background.getPosition().x + this->background.getSize().x &&
				y > this->background.getPosition().y && y < this->background.getPosition().y + this->background.getSize().y)
			{
				const_pressed = true;
				return true;
			}

			return false;
		}
		bool isMouseOver(sf::Vector2i pos) {
			if (pos.x > this->background.getPosition().x && pos.x < this->background.getPosition().x + this->background.getSize().x &&
				pos.y > this->background.getPosition().y && pos.y < this->background.getPosition().y + this->background.getSize().y)
			{
				const_pressed = true;
				return true;
			}

			return false;
		}
		bool isMouseOver(sf::Vector2f pos) {
			if (pos.x > this->background.getPosition().x && pos.x < this->background.getPosition().x + this->background.getSize().x &&
				pos.y > this->background.getPosition().y && pos.y < this->background.getPosition().y + this->background.getSize().y)
			{
				const_pressed = true;
				return true;
			}

			return false;
		}





	private:
		sf::RectangleShape background;
		sf::Text text;
	};
}


