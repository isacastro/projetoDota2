#include "MiniMapa.h"

HUD::HUD(Heroi* hero)
{
	heroi = hero;
	MiniMapTexture.loadFromFile("minimapa.jpg");
	MiniMap.setTexture(MiniMapTexture);

	ursaTexture.loadFromFile("ursa_minimap.png");	
	ursa.setTexture(ursaTexture);

	MiniMapView.setCenter(256, 256);
	MiniMapView.setSize(512, 512);
	MiniMapView.setViewport(sf::FloatRect(0.8, 0.8, 0.2, 0.2));

	//portraitView.setCenter(136, 136);
	//portraitView.setSize(272, 272);
	//portraitView.setViewport(sf::FloatRect(0, 0.8, 0.2, 0.2));

	//portraitTexture.loadFromFile("ursa_portrait.jpg");
	//portrait.setTexture(portraitTexture);

	vidaView.setSize(600, 200);
	vidaView.setCenter(300, 100);
	vidaView.setViewport(sf::FloatRect(0.2, 0.8, 0., 0.2));

	//bgBarra.setSize(sf::Vector2f(600, 100));
	////bgBarra.setFillColor(sf::Color(0, 0, 0, 255));
	//vidaBarra.setSize(sf::Vector2f(600, 100));
	////vidaBarra.setFillColor(sf::Color(0, 255, 0, 255));
	//bg
	bgShape.setSize(sf::Vector2f(80, 10));
	bgShape.setPosition(600, 100);
	bgShape.setFillColor(sf::Color(0, 0, 0, 255));
	//vida
	vidaShape.setSize(sf::Vector2f(80, 10));
	vidaShape.setPosition(600, 100);
	vidaShape.setFillColor(sf::Color(0, 255, 0, 255));
}

void HUD::DrawMiniMap(sf::RenderWindow *window)
{
	sf::View last_view = window->getView();
	window->setView(MiniMapView);
	window->draw(MiniMap);

	ursa.setPosition((heroi->GetPosX() / 4) - 30, (heroi->GetPosY() / 4) - 30);
	window->draw(ursa);	

	//window->setView(portraitView);
	//window->draw(portrait);

	float escala = 600 / 200;
	float largura = escala * heroi->GetVida();
	vidaBarra.setSize(sf::Vector2f(largura, 200));

	window->setView(vidaView);
	window->draw(bgBarra);
	window->draw(vidaBarra);

	window->setView(last_view);
}

HUD::~HUD()
{
}
