#include "Creep.h"
#include "GerenteObjeto.h"

Creep::Creep(GerenteObjeto* manager, bool Radiante, const std::string &nomeImagem, float speed) : Objeto(manager, nomeImagem)
{
	vida = 50;
	vidaMaxima = 50;
	atacou = false;
	gerente = manager;
	velocidade = speed;
	isRadiant = Radiante;
	//bg
	bgShape.setSize(sf::Vector2f(80, 10));
	bgShape.setPosition(posX, posY);
	bgShape.setFillColor(sf::Color(0, 0, 0, 255));
	//vida
	vidaShape.setSize(sf::Vector2f(80, 10));
	vidaShape.setPosition(posX, posY);
	vidaShape.setFillColor(sf::Color(255, 0, 0, 255));

	estado = creep_procurando;

	if (isRadiant == true)
	{
		tipo = creep_radiant;
		posX = rand() % 100;
		posY = rand() % 100 + 1948;
		alvoX = rand() % 100 + 1948;
		alvoY = rand() % 100;
		vidaShape.setFillColor(sf::Color(0, 255, 0, 255));
	}

	else
	{
		tipo = creep_dire;
		posX = rand() % 100 + 1948;
		posY = rand() % 100;
		alvoX = rand() % 100;
		alvoY = rand() % 100 + 1948;
	}
}

void Creep::update()
{
	if (contadorFury > 0)
	{
		contadorFury--;

		if (contadorFury == 0)
		{
			multiplicadorFury = 0;
		}
	}

	if (contadorReduzVelocidade > 0)
	{
		contadorReduzVelocidade--;
	}

	if (vida < 0)
	{
		vida = 0;
	}

	float escala = 80 / vidaMaxima;
	float larguraAtual = vida * escala;

	vidaShape.setSize(sf::Vector2f(larguraAtual, 10));

	bgShape.setPosition(posX, posY);
	vidaShape.setPosition(posX, posY);

	if (vida <= 0)
	{
		return;
	}

	Sprite.setPosition(posX, posY);

	switch (estado)
	{
	case creep_procurando:
		Procurar();
		break;
	case creep_perseguindo:
		Perseguir();
		break;
	case creep_atacando:
		Atacar();
		break;
	}
}

void Creep::Procurar()
{
	float catX = alvoX - posX;
	float catY = alvoY - posY;

	float dis = sqrt((catY * catY) + (catX * catX));

	if (dis > velocidade)
	{
		if (contadorReduzVelocidade > 0)
		{
			float PassoY = (catY * velocidade * 0.4) / dis;
			float PassoX = (catX * velocidade * 0.4) / dis;

			posX += PassoX;
			posY += PassoY;
		}
		else
		{
			float PassoY = (catY * velocidade) / dis;
			float PassoX = (catX * velocidade) / dis;

			posX += PassoX;
			posY += PassoY;
		}
	}

	for (Objeto* obj : gerente->objetos)
	{
		if (isRadiant == true)
		{
			if (obj->GetTipo() == creep_dire || obj->GetTipo() == torre_dire)
			{

				float catX = obj->GetPosX() - posX;
				float catY = obj->GetPosY() - posY;

				float dis = sqrt((catY * catY) + (catX * catX));

				if (dis < 150)
				{
					AlvoPentelho = obj;
					estado = creep_perseguindo;
				}
			}
		}
		else
		{
			if (obj->GetTipo() == creep_radiant || obj->GetTipo() == heroi || obj->GetTipo() == torre_radiant)
			{
				float catX = obj->GetPosX() - posX;
				float catY = obj->GetPosY() - posY;

				float dis = sqrt((catY * catY) + (catX * catX));

				if (dis < 150)
				{
					AlvoPentelho = obj;
					estado = creep_perseguindo;
				}
			}
		}
	}
}

void Creep::Perseguir()
{
	if (AlvoPentelho->GetVida() <= 0)
	{
		if (isRadiant == true)
		{
			alvoX = rand() % 100 + 1948;
			alvoY = rand() % 100;
		}

		else
		{
			alvoX = rand() % 100;
			alvoY = rand() % 100 + 1948;
		}

		estado = creep_procurando;
		return;
	}

	float catX = AlvoPentelho->GetPosX() - posX;
	float catY = AlvoPentelho->GetPosY() - posY;

	float dis = sqrt((catY * catY) + (catX * catX));

	if (dis < 40)
	{
		estado = creep_atacando;
		contadorAtaque = 50;
	}
	else
	{
		float PassoY = (catY * velocidade) / dis;
		float PassoX = (catX * velocidade) / dis;

		posX += PassoX;
		posY += PassoY;
	}
}

void Creep::Atacar()
{
	if (AlvoPentelho->GetVida() <= 0)
	{
		if (isRadiant == true)
		{
			alvoX = rand() % 100 + 1948;
			alvoY = rand() % 100;
		}

		else
		{
			alvoX = rand() % 100;
			alvoY = rand() % 100 + 1948;
		}

		estado = creep_procurando;
		return;
	}

	float catX = AlvoPentelho->GetPosX() - posX;
	float catY = AlvoPentelho->GetPosY() - posY;

	float dis = sqrt((catY * catY) + (catX * catX));

	if (dis > 50)
	{
		estado = creep_perseguindo;
		return;
	}

	contadorAtaque--;

	if (contadorAtaque == 0)
	{
		AlvoPentelho->tomaDano(15);
		contadorAtaque = 600 + rand() % 2000;
	}
}

void Creep::Desenha(sf::RenderWindow* window)
{
	window->draw(Sprite);

	if (vida > 0)
	{
		window->draw(bgShape);
		window->draw(vidaShape);
	}
}

Creep::~Creep()
{
}
