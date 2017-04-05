#pragma once
#include "Objeto.h"
#include <SFML\Graphics\RectangleShape.hpp>

enum EstadosCreeps
{
	creep_procurando,
	creep_perseguindo,
	creep_atacando
};

class Creep : public Objeto
{
private:
	int ataque;
	float alvoX;
	float alvoY;
	float velocidade;
	bool isRadiant;
	bool atacou;
	sf::RectangleShape bgShape;
	sf::RectangleShape vidaShape;
	float vidaMaxima;
	Objeto* AlvoPentelho;
	EstadosCreeps estado;
	void Procurar();
	void Perseguir();
	void Atacar();
	int contadorAtaque;



public:
	Creep(GerenteObjeto* manager, bool Radiante, const std::string &nomeImagem, float speed);

	void update();

	void Desenha(sf::RenderWindow* window);

	~Creep();
};

