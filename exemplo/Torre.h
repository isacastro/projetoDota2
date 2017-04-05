#pragma once
#include "Objeto.h"
#include "GerenteObjeto.h"
#include <SFML\Audio.hpp>
#include <SFML\Graphics\RectangleShape.hpp>

enum EstadosTorres
{
	torre_procurando,
	torre_atacando
};

class Torre : public Objeto
{
private:
	int ataque;
	bool isRadiant;
	Objeto* AlvoPentelho;
	EstadosTorres estado;
	void Atacar();
	void Procurar();
	sf::RectangleShape bgShape;
	sf::RectangleShape vidaShape;
	float vidaMaxima;
	sf::SoundBuffer shootBuffer;
	sf::SoundBuffer deathBuffer;
	sf::Sound sound;
	bool morreu;
	int contadorAtaque;

public:
	Torre(GerenteObjeto* manager, bool Radiante, const std::string &nomeImagem, float x, float y);

	void update();
	void Desenha(sf::RenderWindow* window);

	~Torre();
};

