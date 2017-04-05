#include "Heroi.h"
#include "Objeto.h"
#include "GerenteObjeto.h"

Heroi::Heroi(GerenteObjeto* manager, sf::RenderWindow *janela) : Objeto(manager, "ursa.png")
{
	gerente = manager;
	tipo = heroi;
	window = janela;
	estado = ursa_default;
	vida = 200;
	vidaMaxima = 200;
	//bg
	bgShape.setSize(sf::Vector2f(80, 10));
	bgShape.setPosition(posX, posY);
	bgShape.setFillColor(sf::Color(0, 0, 0, 255));
	//vida
	vidaShape.setSize(sf::Vector2f(80, 10));
	vidaShape.setPosition(posX, posY);
	vidaShape.setFillColor(sf::Color(255, 0, 0, 255));
	//audio
	//if (!move_buffer[0].loadFromFile("move_1.wav"))
	//	std::cout << "ERRO CARREGAR MOVE 1" << std::endl;
	//if(!move_buffer[1].loadFromFile("move_2.wav"))
	//	std::cout << "ERRO CARREGAR MOVE 2" << std::endl;
	//if(!move_buffer[2].loadFromFile("move_3.wav"))
	//	std::cout << "ERRO CARREGAR MOVE 3" << std::endl;
	//if(!move_buffer[3].loadFromFile("move_4.wav"))
	//	std::cout << "ERRO CARREGAR MOVE 4" << std::endl;
	//if(!move_buffer[4].loadFromFile("move_5.wav"))
	//	std::cout << "ERRO CARREGAR MOVE 5" << std::endl;
}

Heroi::Heroi(GerenteObjeto* manager, sf::RenderWindow *janela, float x, float y, float speed) : Objeto(manager, "ursa.png")
{
	gerente = manager;
	tipo = heroi;
	window = janela;
	posX = x;
	posY = y;
	alvoX = x;
	alvoY = y;
	velocidade = speed;
	estado = ursa_default;
	vida = 200;
	vidaMaxima = 200;
	//bg
	bgShape.setSize(sf::Vector2f(80, 10));
	bgShape.setPosition(posX, posY);
	bgShape.setFillColor(sf::Color(0, 0, 0, 255));
	//vida
	vidaShape.setSize(sf::Vector2f(80, 10));
	vidaShape.setPosition(posX, posY);
	vidaShape.setFillColor(sf::Color(0, 255, 0, 255));
	//audio
	move_buffer[0] = new sf::SoundBuffer();
	move_buffer[1] = new sf::SoundBuffer();
	move_buffer[2] = new sf::SoundBuffer();
	move_buffer[3] = new sf::SoundBuffer();
	move_buffer[4] = new sf::SoundBuffer();

	if (!move_buffer[0]->loadFromFile("move_1.wav"))
		std::cout << "ERRO CARREGAR MOVE 1" << std::endl;
	if (!move_buffer[1]->loadFromFile("move_2.wav"))
		std::cout << "ERRO CARREGAR MOVE 2" << std::endl;
	if (!move_buffer[2]->loadFromFile("move_3.wav"))
		std::cout << "ERRO CARREGAR MOVE 3" << std::endl;
	if (!move_buffer[3]->loadFromFile("move_4.wav"))
		std::cout << "ERRO CARREGAR MOVE 4" << std::endl;
	if (!move_buffer[4]->loadFromFile("move_5.wav"))
		std::cout << "ERRO CARREGAR MOVE 5" << std::endl;

	ataque_buffer[0] = new sf::SoundBuffer();
	ataque_buffer[1] = new sf::SoundBuffer();
	ataque_buffer[2] = new sf::SoundBuffer();
	ataque_buffer[3] = new sf::SoundBuffer();

	if (!ataque_buffer[0]->loadFromFile("ataque_1.wav"))
		std::cout << "ERRO CARREGAR ATAQUE 1" << std::endl;
	if (!ataque_buffer[1]->loadFromFile("ataque_2.wav"))
		std::cout << "ERRO CARREGAR ATAQUE 2" << std::endl;
	if (!ataque_buffer[2]->loadFromFile("ataque_3.wav"))
		std::cout << "ERRO CARREGAR ATAQUE 3" << std::endl;
	if (!ataque_buffer[3]->loadFromFile("ataque_4.wav"))
		std::cout << "ERRO CARREGAR ATAQUE 4" << std::endl;

	not_buffer[0] = new sf::SoundBuffer();
	not_buffer[1] = new sf::SoundBuffer();
	not_buffer[2] = new sf::SoundBuffer();

	if (!not_buffer[0]->loadFromFile("ataque_1.wav"))
		std::cout << "ERRO CARREGAR NOT 1" << std::endl;
	if (!not_buffer[1]->loadFromFile("ataque_2.wav"))
		std::cout << "ERRO CARREGAR NOT 2" << std::endl;
	if (!not_buffer[2]->loadFromFile("ataque_3.wav"))
		std::cout << "ERRO CARREGAR NOT 3" << std::endl;

	skillQ_Buffer.loadFromFile("skillQ.wav");
	skillW_Buffer.loadFromFile("skillW.wav");
	skillR_Buffer.loadFromFile("skillR.wav");

}

void Heroi::update()
{
	float escala = 80 / vidaMaxima;
	float larguraAtual = vida * escala;

	vidaShape.setSize(sf::Vector2f(larguraAtual, 10));

	bgShape.setPosition(posX, posY);
	vidaShape.setPosition(posX, posY);

	if (gerente->RightMouseClicked || gerente->LeftMouseClicked)
	{
		estado = ursa_default;

		bool atacou = false;

		sf::Vector2i screenPosition = sf::Mouse::getPosition(*window);
		sf::Vector2f localPosition = window->mapPixelToCoords(screenPosition);

		for (Objeto* obj : gerente->objetos)
		{
			if (obj->GetTipo() != creep_dire && obj->GetTipo() != torre_dire && obj->GetTipo() != ancient_dire)
			{
				continue;
			}

			if (obj->isClicked(localPosition))
			{
				AlvoPentelho = obj;
				atacou = true;
				estado = ursa_perseguindo;
			}
		}

		alvoX = localPosition.x - 52;
		alvoY = localPosition.y - 40;

		if (moveSound.getStatus() != sf::Sound::Playing)
		{

			if (!atacou)
			{
				moveSound.setBuffer(*move_buffer[rand() % 5]);
				moveSound.play();
			}
			else
			{
				moveSound.setBuffer(*ataque_buffer[rand() % 4]);
				moveSound.play();
			}
		}
	}

	if (coolDownEarthshock >= 0)
	{
		coolDownEarthshock--;
	}

	if (gerente->QPressed)
	{
		std::cout << "EARTHSHOCK" << std::endl;

		if (skillSound.getStatus() != sf::Sound::Playing)
		{
			skillSound.setBuffer(skillQ_Buffer);
			skillSound.play();
		}
		if (coolDownEarthshock <= 0)
		{
			for (Objeto* obj : gerente->objetos)
			{
				if (obj->GetTipo() != creep_dire)
					continue;

				float catX = obj->GetPosX() - posX;
				float catY = obj->GetPosY() - posY;

				float dis = sqrt((catY * catY) + (catX * catX));

				if (dis < 80)
				{
					obj->reduzirVelocidade(3000);
				}
			}

			coolDownEarthshock = 7000;
		}
		else
		{
			notSound.setBuffer(*not_buffer[rand() % 3]);
			notSound.play();
		}
	}

	if (coolDownOverpower > 0)
	{
		coolDownOverpower--;
	}

	if (gerente->WPressed)
	{
		std::cout << "OVERPOWER INICIADO" << std::endl;
		if (skillSound.getStatus() != sf::Sound::Playing)
		{
			skillSound.setBuffer(skillW_Buffer);
			skillSound.play();
		}

		if (coolDownOverpower == 0)
		{
			contadorOverpower = 6;
			coolDownOverpower = 7000;
		}
		else
		{
			notSound.setBuffer(*not_buffer[rand() % 3]);
			notSound.play();
		}
	}

	if (coolDownEnrage > 0)
	{
		coolDownEnrage--;
	}

	if (contadorEnrage > 0)
	{
		contadorEnrage--;
	}

	if (gerente->RPressed)
	{
		std::cout << "BERSERK" << std::endl;

		if (skillSound.getStatus() != sf::Sound::Playing)
		{
			skillSound.setBuffer(skillR_Buffer);
			skillSound.play();
		}

		if (coolDownEnrage == 0)
		{
			contadorEnrage = 5000;
			coolDownEnrage = 7000;
		}
		else
		{
			notSound.setBuffer(*not_buffer[rand() % 3]);
			notSound.play();
		}
	}


	Sprite.setPosition(posX, posY);

	switch (estado)
	{
	case ursa_default:
		Default();
		break;
	case ursa_perseguindo:
		Perseguir();
		break;
	case ursa_atacando:
		Atacar();
		break;
	}
}

void Heroi::Default()
{
	float catX = alvoX - posX;
	float catY = alvoY - posY;

	float dis = sqrt((catY * catY) + (catX * catX)); // calculando distancia entre os dois pontos

	if (dis > velocidade)
	{
		float PassoY = (catY * velocidade) / dis;
		float PassoX = (catX * velocidade) / dis;

		posX += PassoX;
		posY += PassoY;
	}
}

void Heroi::Perseguir()
{
	if (AlvoPentelho->GetVida() <= 0)
	{
		estado = ursa_default;
		alvoX = posX - 52;
		alvoY = posY - 40;
		return;
	}

	float catX = AlvoPentelho->GetPosX() - posX;
	float catY = AlvoPentelho->GetPosY() - posY;

	float dis = sqrt((catY * catY) + (catX * catX));

	if (dis < 60)
	{
		estado = ursa_atacando;
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

void Heroi::Atacar()
{
	if (AlvoPentelho->GetVida() <= 0)
	{
		estado = ursa_default;
		return;
	}

	float catX = AlvoPentelho->GetPosX() - posX;
	float catY = AlvoPentelho->GetPosY() - posY;

	float dis = sqrt((catY * catY) + (catX * catX));

	if (dis > 80)
	{
		estado = ursa_perseguindo;
		return;
	}

	contadorAtaque--;

	if (contadorAtaque == 0)
	{
		AlvoPentelho->tomaDano(5);
		AlvoPentelho->Sangra();

		if (contadorOverpower > 0)
		{
			contadorAtaque = 100;
			contadorOverpower--;
		}
		else
		{
			contadorAtaque = 800 + rand() % 500;
		}
	}
}

void Heroi::tomaDano(int dano)
{
	if (contadorEnrage > 0)
	{
		vida -= dano*0.2;
	}
	else
	{
		vida -= dano;
	}
}

void Heroi::Desenha(sf::RenderWindow *window)
{
	window->draw(Sprite);

	if (vida > 0)
	{
		window->draw(bgShape);
		window->draw(vidaShape);
	}
}

Heroi::~Heroi()
{

}
