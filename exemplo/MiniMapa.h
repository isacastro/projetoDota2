#pragma once
#include "Heroi.h"

class HUD
{
	sf::Texture ursaTexture;
	sf::Sprite ursa;
	sf::Texture MiniMapTexture;
	sf::Sprite MiniMap;
	sf::View MiniMapView;
	Heroi* heroi;

	/*sf::Texture portraitTexture;
	sf::Sprite portrait;
	sf::View portraitView;*/

	sf::RectangleShape bgBarra;
	sf::RectangleShape vidaBarra;
	sf::View vidaView;

	sf::RectangleShape bgShape;
	sf::RectangleShape vidaShape;

public:
	HUD(Heroi* hero);
	void DrawMiniMap(sf::RenderWindow *window);
	~HUD();
};

