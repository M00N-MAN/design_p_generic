#include <assert.h>
#include <vector>
#include <iostream>
#define PRINT(WHAT) std::cout<<WHAT<<std::endl


enum EntityID_e { eEntityID_Trooper, eEntityID_Archer, eEntityID_Horseman};

class Entity //BASE
{
	Entity* p;

public:
	Entity(): p(NULL) { }
	Entity(EntityID_e id);
	virtual void GetInfo() const { p->GetInfo(); } //HOMOMORPHIC
	virtual ~Entity(){ /*if(p!=NULL)*/{delete p;p=0;}}
};//class Entity

class Trooper: public Entity //CHILD
{
	Trooper(): Entity() {}
	Trooper(Trooper&);
	Trooper operator=(Trooper&);
	friend class Entity;

public:
	void GetInfo() const{PRINT("Trooper");}
};//class Trooper

class Archer: public Entity //CHILD
{
	Archer(): Entity() {}
	Archer(Archer&);
	Archer operator=(Archer&);
	friend class Entity;

public:
	void GetInfo() const{PRINT("Archer");}
};//class Archer

class Horseman: public Entity //CHILD
{
	Horseman(): Entity() {}
	Horseman(Horseman&);
	Horseman operator=(Horseman&);
	friend class Entity;

public:
	void GetInfo() const{PRINT("Horseman");}
};//class Horseman

Entity::Entity( EntityID_e eID)
{
	if (eID == eEntityID_Trooper) p = new Trooper;
	else if (eID == eEntityID_Archer) p = new Archer;
	else if (eID == eEntityID_Horseman) p = new Horseman;
	else assert(false);
}

typedef std::vector<Entity *> Army_t;

void Create(Army_t &army)
{
	army.push_back(new Entity( eEntityID_Trooper));
	army.push_back(new Entity( eEntityID_Archer));
	army.push_back(new Entity( eEntityID_Horseman));
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
