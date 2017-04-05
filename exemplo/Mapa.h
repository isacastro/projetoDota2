#pragma once
#include "Objeto.h"
#include "GerenteObjeto.h"

class Mapa : public Objeto
{
private:
	sf::Texture seaTexture;
	sf::Texture groundTexture;
	sf::Sprite sea1;
	sf::Sprite sea2;
	sf::Sprite sea3;
	sf::Sprite sea4;
	sf::Sprite ground;
	//sf::Texture treesTexture;
	//sf::Sprite trees;
	float sea1_PosX;
	float sea2_PosX;
	float sea1_PosY;
	float sea2_PosY;
	float velocidade;

public:
	Mapa(GerenteObjeto* manager);
	void update();
	void Desenha(sf::RenderWindow* window);
	~Mapa();
};

