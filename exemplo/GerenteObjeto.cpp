#include "GerenteObjeto.h"
#include "Objeto.h"
#include "Creep.h"

GerenteObjeto::GerenteObjeto()
{
	contadorSpawn = 1000;
}

void GerenteObjeto::addObject(Objeto* object)
{
	objetos.push_back(object);
}

void GerenteObjeto::UpdateAll()
{
	contadorSpawn--;

	if (contadorSpawn == 0)
	{
		SpawnCreeps();
		contadorSpawn = 10000;
	}

	for (Objeto* obj : objetos)
	{
		if (obj->GetTipo() != default)
		{
			if (obj->GetVida() <= 0)
			{
				obj->Morrer();
			}
		}
	}

	for (Objeto* obj : objetos)
	{
		obj->update();
	}
}

void GerenteObjeto::DesenhaArcoIro(sf::RenderWindow* window)
{
	for (Objeto* obj : objetos)
	{
		obj->Desenha(window);
		/*	window->draw(obj->RetornaSprite());*/
	}
}

void GerenteObjeto::operator+=(Objeto* obj)
{
	objetos.push_back(obj);
}

bool GerenteObjeto::operator>(GerenteObjeto *gerente)
{
	return (objetos.size() > gerente->objetos.size());
}

void GerenteObjeto::SpawnCreeps()
{
	addObject(new Creep(this, true, "radiantcreep.png", 0.09)); //radiant creep
	addObject(new Creep(this, true, "radiantcreep.png", 0.09)); //radiant creep
	addObject(new Creep(this, true, "radiantcreep.png", 0.09)); //radiant creep
	addObject(new Creep(this, true, "radiantcreep.png", 0.09)); //radiant creep
	addObject(new Creep(this, true, "radiantcreep.png", 0.09)); //radiant creep
	addObject(new Creep(this, false, "direcreep.png", 0.09)); //dire creep
	addObject(new Creep(this, false, "direcreep.png", 0.09)); //dire creep
	addObject(new Creep(this, false, "direcreep.png", 0.09)); //dire creep
	addObject(new Creep(this, false, "direcreep.png", 0.09)); //dire creep
	addObject(new Creep(this, false, "direcreep.png", 0.09)); //dire creep
}

GerenteObjeto::~GerenteObjeto()
{
}
