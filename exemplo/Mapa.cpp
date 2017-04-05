#include "Mapa.h"



Mapa::Mapa(GerenteObjeto* manager) : Objeto (manager, "map.png" )
{
	groundTexture.loadFromFile("ground.png");
	seaTexture.loadFromFile("sea.png");
	//treesTexture.loadFromFile("trees.png");
	sea1.setTexture(seaTexture);
	sea2.setTexture(seaTexture);
	sea3.setTexture(seaTexture);
	sea4.setTexture(seaTexture);
	ground.setTexture(groundTexture);
	//trees.setTexture(treesTexture);
	sea1_PosX = 0;
	sea2_PosX = -2048;
	sea1_PosY = 0;
	sea2_PosY = -2048;
	velocidade = 0.2;
}
void Mapa::update()
{
	sea1_PosX += velocidade;
	sea2_PosX += velocidade;
	sea1_PosY += velocidade;
	sea2_PosY += velocidade;

	if (sea1_PosX >= 2048)
	{
		sea1_PosX -= 4096;
	}
	if (sea2_PosX >= 2048)
	{
		sea2_PosX -= 4096;
	}
	if (sea1_PosY >= 2048)
	{
		sea1_PosY -= 4096;
	}
	if (sea2_PosY >= 2048)
	{
		sea2_PosY -= 4096;
	}

	sea1.setPosition(sea1_PosX, sea1_PosY);
	sea2.setPosition(sea2_PosX, sea1_PosY);
	sea3.setPosition(sea1_PosX, sea2_PosY);
	sea4.setPosition(sea2_PosX, sea2_PosY);
}

void Mapa::Desenha(sf::RenderWindow* window)
{
	window->draw(ground);
	window->draw(sea1);
	window->draw(sea2);
	window->draw(sea3);
	window->draw(sea4);

	window->draw(Sprite);

	//window->draw(trees);
}

Mapa::~Mapa()
{
}
