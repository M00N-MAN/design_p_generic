#include <assert.h>
#include <vector>
#include <iostream>
#define PRINT(WHAT) std::cout<<WHAT<<std::endl


enum EntityID_e {eEntityID_Trooper=0, eEntityID_Archer, eEntityID_Horseman};

class Entity //BASE
{
public:
	virtual void GetInfo() const = 0;
	virtual ~Entity() {}
	static Entity* createEntity(EntityID_e id );
};//class Entity


class Trooper: public Entity //CHILD
{

public:
	Trooper(): Entity() {}
	void GetInfo() const{PRINT("Trooper");}
};//class Trooper

class Archer: public Entity //CHILD
{
public:
	Archer(): Entity() {}
	void GetInfo() const{PRINT("Archer");}
};//class Archer

class Horseman: public Entity //CHILD
{
public:
	Horseman(): Entity() {}
	void GetInfo() const{PRINT("Horseman");}
};//class Horseman

Entity * Entity::createEntity(EntityID_e eID)
{
	Entity * p;
	switch (eID)
	{
		case eEntityID_Trooper:
			p = new Trooper();
			break;
		case eEntityID_Archer:
			p = new Archer();
			break;
		case eEntityID_Horseman:
			p = new Horseman();
			break;
		default:
			assert( false);
	}
	return p;
}

typedef std::vector<Entity *> Army_t;

void Create(Army_t &army)
{
	army.push_back(Entity::createEntity(eEntityID_Trooper));
	army.push_back(Entity::createEntity(eEntityID_Archer));
	army.push_back(Entity::createEntity(eEntityID_Horseman));
}

int main()
{
	
	Army_t army;

	Create(army);

	for(int i=0; i<army.size(); i++)
		{PRINT(i+1); army[i]->GetInfo();}

	for(int i=0; i<army.size(); i++)
		delete army[i];
	return 0;
}
