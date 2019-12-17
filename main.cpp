#include <vector>
#include <iostream>
#define PRINT(WHAT) std::cout<<WHAT<<std::endl

class Entity //BASE
{
public:
	virtual void GetInfo() const = 0;
	virtual ~Entity(){}
};//class Entity

class Trooper: public Entity //CHILD
{
public:
	void GetInfo() const {PRINT("Trooper");}
};//class Trooper

class Archer: public Entity //CHILD
{
public:
	void GetInfo() const{PRINT("Archer");}
};//class Archer

class Horseman: public Entity //CHILD
{
public:
	void GetInfo() const{PRINT("Horseman");}
};//class Horseman

typedef std::vector<Entity *> Army_t;

void Create(Army_t &army)
{
	army.push_back(new Trooper());
	army.push_back(new Archer());
	army.push_back(new Horseman());
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
