#pragma once
#include "Objeto.h"
#include <SFML\Audio.hpp>

enum EstadosUrsa
{
	ursa_default,
	ursa_perseguindo,
	ursa_atacando
};


class Heroi : public Objeto
{
private:
	sf::RenderWindow *window;
	float alvoX;
	float alvoY;
	float velocidade;
	EstadosUrsa estado;
	Objeto* AlvoPentelho;
	int contadorAtaque;
	//skills
	int contadorOverpower;
	int coolDownOverpower;
	int contadorEnrage;
	int coolDownEnrage;
	int coolDownEarthshock;
	sf::RectangleShape bgShape;
	sf::RectangleShape vidaShape;
	float vidaMaxima;
	sf::SoundBuffer *move_buffer[5];
	sf::SoundBuffer *ataque_buffer[4];
	sf::SoundBuffer *not_buffer[3];
	sf::Sound moveSound;
	sf::Sound skillSound;
	sf::Sound notSound;
	sf::SoundBuffer skillQ_Buffer;
	sf::SoundBuffer skillW_Buffer;
	sf::SoundBuffer skillR_Buffer;
public:
	Heroi(GerenteObjeto* manager, sf::RenderWindow *janela);
	Heroi(GerenteObjeto* manager, sf::RenderWindow *janela, float x, float y, float speed);
	void Default();
	void Perseguir();
	void Atacar();
	void tomaDano(int dano);
	void Desenha(sf::RenderWindow* window);

	~Heroi();

	void update();
};

