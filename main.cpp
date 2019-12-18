#include <time.h>
#include <cstdlib>
#include <assert.h>
#include <vector>
#include <iostream>
#define PRINT(WHAT) std::cout<<WHAT<<std::endl
#define TRACE_HERE PRINT(__FUNCTION__)
//#define TRACE_HERE

namespace tools
{
template <typename Type>
static Type getRandomNumber0to1()
{
	return static_cast <Type> (rand()) / static_cast <Type> (RAND_MAX);
}
template <typename Type>
static Type getRandomNumber0toX(Type X)
{
	return static_cast <Type> (rand()) / (static_cast <Type> (RAND_MAX/X));
}
template <typename Type>
static Type getRandomNumberXtoY(Type LO,Type HI)
{
	return LO + static_cast <Type> (rand()) /( static_cast <Type> (RAND_MAX/(HI-LO)));
}

template<typename T> T MAX(const T &t1,const T &t2){return t1>=t2?t1:t2;}
template<typename T> T MIN(const T &t1,const T &t2){return t1<=t2?t1:t2;}

template <typename SrcType,typename DstType,typename MiddleType=float>
DstType convertValue(const SrcType &value, const SrcType &srcMin, const SrcType &srcMax, const DstType &dstMin, const DstType &dstMax)
{
	return static_cast<DstType>((MAX(value,srcMin) - MIN(value,srcMin)) * (static_cast<MiddleType>(dstMax - dstMin) / static_cast<MiddleType>(MAX(srcMax,srcMin) - MIN(srcMin,srcMax))) + dstMin);
}

};//namespace tools

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
	Trooper() {TRACE_HERE;}
	virtual ~Trooper() {TRACE_HERE;}
	virtual void GetInfo() const = 0;
};//class Trooper

class Archer
{

public:
	Archer() {TRACE_HERE;}
	virtual ~Archer() {TRACE_HERE;}
	virtual void GetInfo() const = 0;
};//class Archer

class Horseman
{

public:
	Horseman() {TRACE_HERE;}
	virtual ~Horseman() {TRACE_HERE;}
	virtual void GetInfo() const = 0;
};//class Horseman

class Catapult
{

public:
	Catapult() {TRACE_HERE;}
	virtual ~Catapult() {TRACE_HERE;}
	virtual void GetInfo() const = 0;
};//class Catapult

class Elephant
{

public:
	Elephant() {TRACE_HERE;}
	virtual ~Elephant() {TRACE_HERE;}
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
		for(size_t i=0; i<vt.size(); ++i) delete vt[i];
		for(size_t i=0; i<va.size(); ++i) delete va[i];
		for(size_t i=0; i<vh.size(); ++i) delete vh[i];
		for(size_t i=0; i<vc.size(); ++i) delete vc[i];
		for(size_t i=0; i<ve.size(); ++i) delete ve[i];
	}
	
	void GetInfo() const
	{
		for(size_t i=0; i<vt.size(); ++i)vt[i]->GetInfo();
		for(size_t i=0; i<va.size(); ++i)va[i]->GetInfo();
		for(size_t i=0; i<vh.size(); ++i)vh[i]->GetInfo();
		for(size_t i=0; i<vc.size(); ++i)vc[i]->GetInfo();
		for(size_t i=0; i<ve.size(); ++i)ve[i]->GetInfo();
	}
	
};//class Army

class ArmyBuilder
{
//vasic class to build army with default impl
protected:
	Army* a;

public:
	ArmyBuilder(): a(0) {}
	virtual ~ArmyBuilder() {}
	virtual void CreateArmy() {}
	virtual void BuildTrooper() {}
	virtual void BuildArcher() {}
	virtual void BuildHorseman() {}
	virtual void BuildCatapult() {}
	virtual void BuildElephant() {}
	virtual Army* GetArmy() {return a;}
};//class ArmyBuilder

// Roman army has no elephants
class RomanArmyBuilder: public ArmyBuilder
{
public:
	void CreateArmy() {a = new Army;}
	void BuildTrooper() {a->vt.push_back(new RomanTrooper());}
	void BuildArcher() {a->va.push_back(new RomanArcher());}
	void BuildHorseman() {a->vh.push_back(new RomanHorseman());}
	void BuildCatapult() {a->vc.push_back(new RomanCatapult());}
};


// Carthaginian army has no catapults
class CarthaginianArmyBuilder: public ArmyBuilder
{
public:
	void CreateArmy() {a = new Army;}
	void BuildTrooper() {a->vt.push_back(new CarthaginianTrooper());}
	void BuildArcher() {a->va.push_back(new CarthaginianArcher());}
	void BuildHorseman() {a->vh.push_back(new CarthaginianHorseman());}
	void BuildElephant() {a->ve.push_back(new CarthaginianElephant());}
};


class Director
{
//Building decision responcible
public:
	Army* createArmy(ArmyBuilder & builder )
	{
		builder.CreateArmy();
		builder.BuildTrooper();
		builder.BuildArcher();
		builder.BuildHorseman();
		builder.BuildCatapult();
		builder.BuildElephant();
		return(builder.GetArmy());
	}
};

class Game
{
// Scope of game including any army

	Director dir;
	RomanArmyBuilder roman_builder;
	CarthaginianArmyBuilder carf_builder;

	Army *romanArmy;
	Army *carthaginianArmy;

public:
	Game()
		:romanArmy(dir.createArmy(roman_builder))
		,carthaginianArmy(dir.createArmy(carf_builder))
	{
		TRACE_HERE;
	}

	void Play() const
	{
		PRINT("Roman army:");romanArmy->GetInfo();
		PRINT("Carthaginian army:");carthaginianArmy->GetInfo();
	}

	~Game()
	{
		TRACE_HERE;
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
