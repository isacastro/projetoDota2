#include "Ancient.h"
#include "GerenteObjeto.h"


Ancient::Ancient(GerenteObjeto* manager, bool Radiante, const std::string &nomeImagem, float x, float y) : Objeto(manager, nomeImagem)
{
	gerente = manager;
	isRadiant = Radiante;
	vida = 800;
	vidaMaxima = vida;
	morreu = false;

	//bg
	bgShape.setSize(sf::Vector2f(80, 10));
	bgShape.setPosition(posX, posY);
	bgShape.setFillColor(sf::Color(0, 0, 0, 255));
	//vida
	vidaShape.setSize(sf::Vector2f(80, 10));
	vidaShape.setPosition(posX, posY);
	vidaShape.setFillColor(sf::Color(255, 0, 0, 255));

	if (isRadiant == true)
	{
		//audio
		victoryBuffer.loadFromFile("dire_victory.wav");
		tipo = ancient_radiant;
		posX = x;
		posY = y;
		vidaShape.setFillColor(sf::Color(0, 255, 0, 255));
	}

	else
	{
		victoryBuffer.loadFromFile("radiant_victory.wav");
		tipo = ancient_dire;
		posX = x;
		posY = y;
	}
}

void Ancient::update()
{
	Sprite.setPosition(posX, posY);

	if (!morreu)
	{
		if (vida <= 0)
		{
			morreu = true;
			sound.setBuffer(victoryBuffer);
			sound.play();
		}
	}

	float escala = 80 / vidaMaxima;
	float larguraAtual = vida * escala;

	vidaShape.setSize(sf::Vector2f(larguraAtual, 10));

	bgShape.setPosition(posX, posY);
	vidaShape.setPosition(posX, posY);
}

void Ancient::Desenha(sf::RenderWindow* window)
{
	window->draw(Sprite);

	if (vida > 0)
	{
		window->draw(bgShape);
		window->draw(vidaShape);
	}
}

Ancient::~Ancient()
{
}
