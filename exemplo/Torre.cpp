#include "Torre.h"
#include "Objeto.h"
#include "GerenteObjeto.h"

Torre::Torre(GerenteObjeto* manager, bool Radiante, const std::string &nomeImagem, float x, float y) : Objeto(manager, nomeImagem)
{
	gerente = manager;
	isRadiant = Radiante;
	estado = torre_procurando;
	vida = 150;
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
		shootBuffer.loadFromFile("radiant_shoot.wav");
		deathBuffer.loadFromFile("rtower_fall.wav");
		tipo = torre_radiant;
		posX = x;
		posY = y;
		vidaShape.setFillColor(sf::Color(0, 255, 0, 255));
	}

	else
	{
		shootBuffer.loadFromFile("dire_shoot.wav");
		deathBuffer.loadFromFile("dtower_fall.wav");
		tipo = torre_dire;
		posX = x;
		posY = y;
	}
}

void Torre::update()
{
	Sprite.setPosition(posX, posY);

	if (!morreu)
	{
		if (vida <= 0)
		{
			morreu = true;
			sound.setBuffer(deathBuffer);
			sound.play();
		}
	}

	float escala = 80 / vidaMaxima;
	float larguraAtual = vida * escala;

	vidaShape.setSize(sf::Vector2f(larguraAtual, 10));

	bgShape.setPosition(posX, posY);
	vidaShape.setPosition(posX, posY);

	switch (estado)
	{
	case torre_procurando:
		Procurar();
		break;
	case torre_atacando:
		Atacar();
		break;
	}
}

void Torre::Procurar()
{
	for (Objeto* obj : gerente->objetos)
	{
		if (isRadiant == true)
		{
			if (obj->GetTipo() == creep_dire)
			{

				float catX = obj->GetPosX() - posX;
				float catY = obj->GetPosY() - posY;

				float dis = sqrt((catY * catY) + (catX * catX));

				if (dis < 180)
				{
					AlvoPentelho = obj;
					estado = torre_atacando;
					contadorAtaque = 50;
				}
			}
		}
		else
		{
			if (obj->GetTipo() == creep_radiant || obj->GetTipo() == heroi)
			{
				float catX = obj->GetPosX() - posX;
				float catY = obj->GetPosY() - posY;

				float dis = sqrt((catY * catY) + (catX * catX));

				if (dis < 180)
				{
					AlvoPentelho = obj;
					estado = torre_atacando;
					contadorAtaque = 50;
				}
			}
		}
	}
}

void Torre::Atacar()
{
	if (AlvoPentelho->GetVida() <= 0)
	{
		estado = torre_procurando;
		return;
	}

	float catX = AlvoPentelho->GetPosX() - posX;
	float catY = AlvoPentelho->GetPosY() - posY;

	float dis = sqrt((catY * catY) + (catX * catX));

	if (dis > 180)
	{
		estado = torre_procurando;
	}

	contadorAtaque--;

	if (contadorAtaque == 0)
	{
		AlvoPentelho->tomaDano(20);
		sound.setBuffer(shootBuffer);
		sound.play();
		contadorAtaque = 600 + rand() % 2000;
	}
}

void Torre::Desenha(sf::RenderWindow* window)
{
	window->draw(Sprite);

	if (vida > 0)
	{
		window->draw(bgShape);
		window->draw(vidaShape);
	}
}

Torre::~Torre()
{
}
