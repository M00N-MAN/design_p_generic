#include <assert.h>
#include <vector>
#include <iostream>
#define PRINT(WHAT) std::cout<<WHAT<<std::endl
#define TRACE_WHERE PRINT(__FUNCTION__)
//#define TRACE_WHERE

class IEntity //BASE
{

public:
	virtual void GetInfo() const = 0;
	virtual ~IEntity() {}
};//class IEntity

//Abstract classes of all warriors
class Trooper
{

public:
	Trooper() {TRACE_WHERE;}
	virtual ~Trooper() {TRACE_WHERE;}
	virtual void GetInfo() const = 0;
};//class Trooper

class Archer
{

public:
	Archer() {TRACE_WHERE;}
	virtual ~Archer() {TRACE_WHERE;}
	virtual void GetInfo() const = 0;
};//class Archer

class Horseman
{

public:
	Horseman() {TRACE_WHERE;}
	virtual ~Horseman() {TRACE_WHERE;}
	virtual void GetInfo() const = 0;
};//class Horseman

class Catapult
{

public:
	Catapult() {TRACE_WHERE;}
	virtual ~Catapult() {TRACE_WHERE;}
	virtual void GetInfo() const = 0;
};//class Catapult

class Elephant
{

public:
	Elephant() {TRACE_WHERE;}
	virtual ~Elephant() {TRACE_WHERE;}
	virtual void GetInfo() const = 0;
};//class Elephant


// classes of all types of warriors in Roman army
class RomanTrooper: public Trooper
{

public:
	void GetInfo() const{PRINT("I'm Roman Trooper");}
};//class RomanTrooper

class RomanArcher: public Archer
{

public:
	void GetInfo() const{PRINT("I'm Roman Archer");}
};//class RomanArcher

class RomanHorseman: public Horseman
{

public:
	void GetInfo() const{PRINT("I'm Roman Horseman");}
};//class RomanHorseman

class RomanCatapult: public Catapult
{

public:
	void GetInfo() const{PRINT("I'm Roman Catapult");}
};//class RomanCatapult

class RomanElephant: public Elephant
{

public:
	void GetInfo() const{PRINT("I'm Roman Elephant");}
};//class RomanElephant



class CarthaginianTrooper: public Trooper
{
// classes of all types of warriors in Carthaginian army
public:
	void GetInfo() const{PRINT("I'm Carthaginian Trooper");}
};//class CarthaginianTrooper

class CarthaginianArcher: public Archer
{

public:
	void GetInfo() const{PRINT("I'm Carthaginian Archer");}
};//class CarthaginianArcher

class CarthaginianHorseman: public Horseman
{

public:
	void GetInfo() const{PRINT("I'm Carthaginian Horseman");}
};//class CarthaginianHorseman

class CarthaginianCatapult: public Catapult
{

public:
	void GetInfo() const{PRINT("I'm Carthaginian Catapult");}
};//class CarthaginianCatapult

class CarthaginianElephant: public Elephant
{

public:
	void GetInfo() const{PRINT("I'm Carthaginian Elephant");}
};//class CarthaginianElephant


class ArmyFactory
{
// Abstract factory to produce warriors
public:
	virtual Trooper* CreateTrooper() const = 0;
	virtual Archer* CreateArcher() const = 0;
	virtual Horseman* CreateHorseman() const= 0;
	virtual Catapult* CreateCatapult() const= 0;
	virtual Elephant* CreateElephant() const= 0;
	virtual ~ArmyFactory() {}
};//class ArmyFactory


class RomanArmyFactory: public ArmyFactory
{
// Factory tor procude warriors of Roman army
public:
	Trooper* CreateTrooper() const{return new RomanTrooper;}
	Archer* CreateArcher() const{return new RomanArcher;}
	Horseman* CreateHorseman() const{return new RomanHorseman;}
	Catapult* CreateCatapult() const{return new RomanCatapult;}
	Elephant* CreateElephant() const{return new RomanElephant;}
};//class RomanArmyFactory



class CarthaginianArmyFactory: public ArmyFactory
{
// Factory tor procude warriors of Carthaginian army
public:
	Trooper* CreateTrooper() const{return new CarthaginianTrooper;}
	Archer* CreateArcher() const{return new CarthaginianArcher;}
	Horseman* CreateHorseman() const{return new CarthaginianHorseman;}
	Catapult* CreateCatapult() const{return new CarthaginianCatapult;}
	Elephant* CreateElephant() const{return new CarthaginianElephant;}
};

class Army
{
// Class which contains all warriors of some army

public:
	std::vector<Trooper *> vt;
	std::vector<Archer *> va;
	std::vector<Horseman *> vh;
	std::vector<Catapult *> vc;
	std::vector<Elephant *> ve;
	
	Army(){}
	
	virtual ~Army()
	{
		int i;
		for(i=0; i<vt.size(); ++i) delete vt[i];
		for(i=0; i<va.size(); ++i) delete va[i];
		for(i=0; i<vh.size(); ++i) delete vh[i];
		for(i=0; i<vc.size(); ++i) delete vc[i];
		for(i=0; i<ve.size(); ++i) delete ve[i];
	}
	
	void GetInfo() const
	{
		int i;
		for(i=0; i<vt.size(); ++i)vt[i]->GetInfo();
		for(i=0; i<va.size(); ++i)va[i]->GetInfo();
		for(i=0; i<vh.size(); ++i)vh[i]->GetInfo();
		for(i=0; i<vc.size(); ++i)vc[i]->GetInfo();
		for(i=0; i<ve.size(); ++i)ve[i]->GetInfo();
	}
	
};//class Army


class Game
{
// Scope of game including any army

	RomanArmyFactory ra_factory;
	CarthaginianArmyFactory ca_factory;

	Army *romanArmy;
	Army *carthaginianArmy;


	Army* createArmy(ArmyFactory &factory)
	{
		Army* p = new Army;

		p->vt.push_back(factory.CreateTrooper());
		p->va.push_back(factory.CreateArcher());
		p->vh.push_back(factory.CreateHorseman());
		p->vc.push_back(factory.CreateCatapult());
		p->ve.push_back(factory.CreateElephant());
		return p;
	}

public:
	Game()
		:romanArmy(createArmy(ra_factory))
		,carthaginianArmy(createArmy(ca_factory))
	{
		TRACE_WHERE;
	}

	void Play() const
	{
		PRINT("Roman army:");romanArmy->GetInfo();
		PRINT("Carthaginian army:");carthaginianArmy->GetInfo();
	}

	~Game()
	{
		TRACE_WHERE;
		delete romanArmy;
		delete carthaginianArmy;
	}
};//class Game

int main()
{
	Game game;
	game.Play();

	return 0;
}
