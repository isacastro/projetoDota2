#pragma once
#include "Objeto.h"
#include <SFML\Audio.hpp>
#include <SFML\Graphics\RectangleShape.hpp>

class Ancient : public Objeto
{
private:
	bool isRadiant;
	sf::RectangleShape bgShape;
	sf::RectangleShape vidaShape;
	float vidaMaxima;
	sf::SoundBuffer victoryBuffer;
	sf::Sound sound;
	bool morreu;

public:
	Ancient(GerenteObjeto* manager, bool Radiante, const std::string &nomeImagem, float x, float y);
	void update();
	void Desenha(sf::RenderWindow* window);
	~Ancient();
};

