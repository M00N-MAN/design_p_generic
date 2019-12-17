#include <assert.h>
#include <vector>
#include <iostream>
#define PRINT(WHAT) std::cout<<WHAT<<std::endl
#define TRACE_WHERE PRINT(__FUNCTION__)

class Warrior //BASE
{
public:
	virtual void GetInfo() const = 0;
	virtual ~Warrior() {}
};//class Warrior


class Trooper: public Warrior //CHILD
{

public:
	Trooper(): Warrior() {TRACE_WHERE;}
	void GetInfo() const{PRINT("I'm Trooper");}
	~Trooper() {TRACE_WHERE;}
};//class Trooper

class Archer: public Warrior //CHILD
{

public:
	Archer(): Warrior() {TRACE_WHERE;}
	void GetInfo() const{PRINT("I'm Archer");}
	~Archer() {TRACE_WHERE;}
};//class Archer

class Horseman: public Warrior //CHILD
{

public:
	Horseman(): Warrior() {TRACE_WHERE;}
	void GetInfo() const{PRINT("I'm Horseman");}
	~Horseman() {TRACE_WHERE;}
};//class Horseman

class Factory
{

public:
	virtual Warrior* CreateWarrior() const = 0;
	virtual ~Factory() {TRACE_WHERE;}
};

class TroopFactory: public Factory
{

public:
	Warrior* CreateWarrior() const{return new Trooper;}
};

class ArchersFactory: public Factory
{

public:
	Warrior* CreateWarrior() const{return new Archer;}
};

class CavalryFactory: public Factory
{

public:
	Warrior* CreateWarrior() const{return new Horseman;}
};

TroopFactory   *troopers_factory = NULL;
ArchersFactory *archers_factory  = NULL;
CavalryFactory *cavalry_factory  = NULL;

typedef std::vector<Warrior *> Army_t;

void Create(Army_t &army)
{
	troopers_factory = new TroopFactory;
	archers_factory = new ArchersFactory;
	cavalry_factory = new CavalryFactory;

	army.push_back(troopers_factory->CreateWarrior());
	army.push_back(archers_factory->CreateWarrior());
	army.push_back(cavalry_factory->CreateWarrior());
}

void Play(Army_t &army)
{
	for(int i=0; i<army.size(); i++)
		{PRINT(i+1); army[i]->GetInfo();}
}

void Destroy(Army_t &army)
{
	delete troopers_factory;
	delete archers_factory;
	delete cavalry_factory;

	for(int i=0; i<army.size(); i++)
		delete army[i];
}

int main()
{
	Army_t army;

	Create(army);

	Play(army);

	Destroy(army);
	return 0;
}
