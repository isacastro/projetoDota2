#pragma once
#include <iostream>
#include "Objeto.h"

class GerenteObjeto
{
private:

	int contadorSpawn; 
public:
	bool RightMouseClicked;
	bool LeftMouseClicked;
	bool QPressed;
	bool WPressed;
	bool RPressed;

	GerenteObjeto();

	std::vector<Objeto*> objetos;

	~GerenteObjeto();

	void addObject(Objeto* object);

	void UpdateAll();

	void DesenhaArcoIro(sf::RenderWindow* window);

	void operator+=(Objeto* obj);
	
	void SpawnCreeps();

	bool operator>(GerenteObjeto *gerente);

};

