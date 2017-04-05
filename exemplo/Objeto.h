#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class GerenteObjeto;

enum Tipo
{
	default,
	heroi,
	creep_radiant,
	creep_dire,
	torre_radiant,
	torre_dire,
	ancient_radiant,
	ancient_dire
};

class Objeto
{
private:
	sf::Texture Textura;

protected:
	sf::Sprite Sprite;
	float posX;
	float posY;
	int vida;
	Tipo tipo;
	GerenteObjeto* gerente;
	int contadorReduzVelocidade;
	int contadorFury;
	int multiplicadorFury;

public:
	Objeto(GerenteObjeto* manager, const std::string &nomeImagem);

	Objeto(GerenteObjeto* manager, const std::string &nomeImagem, float x, float y);

	Tipo GetTipo();
	float GetPosX();
	float GetPosY();
	int GetVida();
	//sf::Sprite RetornaSprite();

	virtual void Desenha(sf::RenderWindow* window);

	void SetPosition(float x, float y);

	virtual void update() { Sprite.setPosition(posX, posY); };

	virtual void tomaDano(int dano);

	void reduzirVelocidade(int tempo);

	void Sangra();

	void Morrer();

	bool isClicked(sf::Vector2f mousePosition);

	~Objeto();
};

