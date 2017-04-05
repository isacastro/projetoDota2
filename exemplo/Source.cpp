#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Objeto.h"
#include "GerenteObjeto.h"
#include "Heroi.h"
#include "Creep.h"
#include "Torre.h"
#include "Ancient.h"
#include "Mapa.h"
#include "MiniMapa.h"

int main()
{
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(650, 607), "Dota 2"); //criando janela

	sf::Music music;
	music.openFromFile("musica.wav");
	music.play();
	music.setLoop(true);

	GerenteObjeto gerente;
	gerente.addObject(new Mapa(&gerente));
	gerente.addObject(new Torre(&gerente, true, "radianttower.png", 392, 1600)); //radiant tower
	gerente.addObject(new Torre(&gerente, true, "radianttower.png", 630, 1380)); //radiant tower
	gerente.addObject(new Torre(&gerente, true, "radianttower.png", 890, 1100)); //radiant tower
	gerente.addObject(new Torre(&gerente, false, "diretower.png", 1140, 830)); //dire tower
	gerente.addObject(new Torre(&gerente, false, "diretower.png", 1400, 540)); //dire tower
	gerente.addObject(new Torre(&gerente, false, "diretower.png", 1680, 360)); //dire tower
	gerente.addObject(new Ancient(&gerente, false, "ancientdire.png", 1730, 229)); //dire ancient
	gerente.addObject(new Ancient(&gerente, true, "ancientradiant.png", 200, 1750)); //radiant ancient

	Heroi* heroi = new Heroi(&gerente, &window, 90, 1800, 0.2);
	gerente.addObject(heroi); //ursa

	gerente.addObject(new Objeto(&gerente, "trees.png", 0, 0));
	HUD* mapa = new HUD(heroi);

	sf::View HeroView(sf::Vector2f(heroi->GetPosX(), heroi->GetPosY()), sf::Vector2f(800, 600));

	while (window.isOpen())
	{
		window.clear();

		
		sf::Event event;
		gerente.RightMouseClicked = false;
		gerente.LeftMouseClicked = false;
		gerente.QPressed = false;
		gerente.WPressed = false;
		gerente.RPressed = false;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Q:
					gerente.QPressed = true;
					break;
				case sf::Keyboard::W:
					gerente.WPressed = true;
					break;
				case sf::Keyboard::R:
					gerente.RPressed = true;
					break;
				}
				break;
			case sf::Event::MouseButtonPressed:
				switch (event.mouseButton.button)
				{
				case sf::Mouse::Right:
					gerente.RightMouseClicked = true;
					break;
				case sf::Mouse::Left:
					gerente.LeftMouseClicked = true;
					break;
				}
				break;
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
			}
		}

		gerente.UpdateAll();

		float cameraX = heroi->GetPosX();
		float cameraY = heroi->GetPosY();
		if (cameraX < 400)
			cameraX = 400;
		if (cameraX > 1648)
			cameraX = 1648;
		if (cameraY < 300)
			cameraY = 300;
		if (cameraY > 1748)
			cameraY = 1748;
		HeroView.setCenter(cameraX, cameraY);

		window.setView(HeroView);

		gerente.DesenhaArcoIro(&window);

		mapa->DrawMiniMap(&window);

		window.display();
	}

	return 0;
}