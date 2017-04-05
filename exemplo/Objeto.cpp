#include "Objeto.h"
#include <iostream>

Objeto::Objeto(GerenteObjeto* manager, const std::string &nomeImagem)
{
	gerente = manager;
	tipo = default;
	Textura.loadFromFile(nomeImagem);
	Sprite = sf::Sprite(Textura);
}

Objeto::Objeto(GerenteObjeto* manager, const std::string &nomeImagem, float x, float y)
{
	gerente = manager;
	tipo = default;
	Textura.loadFromFile(nomeImagem);
	Sprite = sf::Sprite(Textura);
	posX = x;
	posY = y;
}

//sf::Sprite Objeto::RetornaSprite()
//{
//	return Sprite;
//}

void Objeto::Desenha(sf::RenderWindow* window)
{
	window->draw(Sprite);
}

Tipo Objeto::GetTipo()
{
	return tipo;
}
float Objeto::GetPosX()
{
	return posX;
}

float Objeto::GetPosY()
{
	return posY;
}

int Objeto::GetVida()
{
	return vida;
}

void Objeto::SetPosition(float x, float y)
{
	Sprite.setPosition(x, y);
}

void Objeto::tomaDano(int dano)
{
	vida -= dano * (1 + multiplicadorFury);
}

bool Objeto::isClicked(sf::Vector2f mousePosition)
{
	return (mousePosition.x > posX && mousePosition.x < posX + Textura.getSize().x &&
			mousePosition.y > posY && mousePosition.y < posY + Textura.getSize().y);
}

void Objeto::reduzirVelocidade(int tempo)
{
	contadorReduzVelocidade = tempo;
}

//void Objeto::update()
//{
//	std::cout << "KATIAU" << std::endl;
//}
void Objeto::Sangra()
{
	contadorFury = 8000;
	multiplicadorFury += 0.2;
}

void Objeto::Morrer()
{
	SetPosition(-10000, -10000);
	posX = -10000;
	posY = -10000;
}

Objeto::~Objeto()
{
}
