#pragma once
#include "Draw_Field.h"
#include <ctime>
#define MARGIN 20.0

namespace cz
{

	class Game
	{
	public:
		virtual void draw(sf::RenderWindow& window) = 0;
		virtual void update(const float& dt, sf::RenderWindow& window) = 0;

		virtual bool ended() = 0;

		virtual void restart() = 0;

		virtual void pause() = 0;
		virtual void stop() = 0;
		virtual void start() = 0;

	private:


		virtual void end() = 0;
	};

}