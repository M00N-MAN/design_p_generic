#include <time.h>
#include <cstdlib>
#include <assert.h>
#include <vector>
#include <sstream>
#include <iostream>
#define PRINT(WHAT) std::cout<<WHAT<<std::endl


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

enum LogLevel_e
{
	eLogLevel_Empty=0
	,eLogLevel_Fault/*=1*/
	,eLogLevel_Alarm/*=2*/
	,eLogLevel_Event/*=3*/
	,eLogLevel_Debug/*=4*/
	,eLogLevel_Trace/*=5*/
	,eLogLevel_SIZE
};

class Logger
{
	LogLevel_e eLimit;
	std::vector<std::string> xLevels;

public:
	Logger(LogLevel_e eBorder=eLogLevel_Debug):eLimit(eBorder)
	{
		xLevels.push_back("Empty");
		xLevels.push_back("Fault");
		xLevels.push_back("Alarm");
		xLevels.push_back("Event");
		xLevels.push_back("Debug");
		xLevels.push_back("Trace");
	}
	
	void Put(LogLevel_e eLevel,const std::string & sFileName, const std::string & sFunctionName, size_t iCodeLine, const std::string & sMessage)
	{
		if(eLevel<=eLimit) PRINT(xLevels[eLevel]<<" "
									 <<sFileName<<" "
									 <<iCodeLine<<" "
									 <<sFunctionName
									 <<": "<<sMessage);
	}
};

Logger log;

template <typename T>
std::string tostr(const T& t)
{
	std::ostringstream os;os<<t;
	return os.str();
}

};//namespace tools

#define LOG_Fault(ONEARG) tools::log.Put(tools::eLogLevel_Fault,__FILE__,__FUNCTION__,__LINE__,tools::tostr(ONEARG))
#define LOG_Alarm(ONEARG) tools::log.Put(tools::eLogLevel_Alarm,__FILE__,__FUNCTION__,__LINE__,tools::tostr(ONEARG))
#define LOG_Event(ONEARG) tools::log.Put(tools::eLogLevel_Event,__FILE__,__FUNCTION__,__LINE__,tools::tostr(ONEARG))
#define LOG_Debug(ONEARG) tools::log.Put(tools::eLogLevel_Debug,__FILE__,__FUNCTION__,__LINE__,tools::tostr(ONEARG))
#define LOG_Trace(ONEARG) tools::log.Put(tools::eLogLevel_Trace,__FILE__,__FUNCTION__,__LINE__,tools::tostr(ONEARG))

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
	Trooper() {LOG_Debug("");}
	virtual ~Trooper() {LOG_Debug("");}
	virtual void GetInfo() const = 0;
};//class Trooper

class Archer
{

public:
	Archer() {LOG_Debug("");}
	virtual ~Archer() {LOG_Debug("");}
	virtual void GetInfo() const = 0;
};//class Archer

class Horseman
{

public:
	Horseman() {LOG_Debug("");}
	virtual ~Horseman() {LOG_Debug("");}
	virtual void GetInfo() const = 0;
};//class Horseman

class Catapult
{

public:
	Catapult() {LOG_Debug("");}
	virtual ~Catapult() {LOG_Debug("");}
	virtual void GetInfo() const = 0;
};//class Catapult

class Elephant
{

public:
	Elephant() {LOG_Debug("");}
	virtual ~Elephant() {LOG_Debug("");}
	virtual void GetInfo() const = 0;
};//class Elephant

class DistanceAdjustable
{
protected:
	float highErrorLimit;
	float lowErrorLimit;
	virtual void adjust(float lowOffset,float highOffset)
	{
		lowErrorLimit+=lowOffset;
		highErrorLimit+=highOffset;
	}
public:
	DistanceAdjustable():highErrorLimit(0.0),lowErrorLimit(0.0){}
};

class RomanDistance :public DistanceAdjustable
{

public:
	RomanDistance()
	{
		highErrorLimit=1.02f;
		lowErrorLimit=1.21f;
	}
	float getMiles(float test_value=32.0)
	{
		float t = test_value;
		// ...
		return t*tools::getRandomNumberXtoY(lowErrorLimit,highErrorLimit);
	}

	void MXVII(){adjust(1.0,-0.1);}
	void XI(){adjust(-0.1,1.0);}
};

class CarthaginianDistance :public DistanceAdjustable
{

public:
	CarthaginianDistance()
	{
		highErrorLimit=1.22f;
		lowErrorLimit=1.01f;
	}

	float getParasas(float test_value=32.0)
	{
		float t = test_value;
		// ...
		return t*tools::getRandomNumberXtoY(lowErrorLimit,highErrorLimit);
	}

	void Dalt(){adjust(-0.2,2.0);}
	void Tet(){adjust(1.0,-0.1);}
};

class Sensor
{
public:
	virtual ~Sensor() {}
	virtual float getDistance(float test_value=32.0) = 0;
	virtual void Adjust(float,float)=0;
};

float CarthaginianParasa = 3648.0; //m
float RomanMile = 1480.0; //m

class CarthaginianAdapterDistanceSensor : public Sensor , private RomanDistance
{

public:
	float getDistance(float test_value=32.0)
	{
		return tools::convertValue(RomanDistance::getMiles(test_value),0.f,RomanMile,0.f,CarthaginianParasa/(CarthaginianParasa/RomanMile));
	}
	void Adjust(float LowOffset,float HighOffset)
	{
		RomanDistance::adjust(LowOffset,HighOffset);
	}
};

class RomanAdapterDistanceSensor : public Sensor, private CarthaginianDistance
{

public:
	float getDistance(float test_value=32.0)
	{
		return tools::convertValue(CarthaginianDistance::getParasas(test_value),0.f,CarthaginianParasa,0.f,RomanMile*(CarthaginianParasa/RomanMile));
	}
	void Adjust(float LowOffset,float HighOffset)
	{
		CarthaginianDistance::adjust(LowOffset,HighOffset);
	}
};

// classes of all types of warriors in Roman army
class RomanTrooper: public Trooper
{

public:
	void GetInfo() const{LOG_Event("I'm Roman Trooper");}
};//class RomanTrooper

class RomanArcher: public Archer
{

public:
	void GetInfo() const{LOG_Event("I'm Roman Archer");}
};//class RomanArcher

class RomanHorseman: public Horseman
{

public:
	void GetInfo() const{LOG_Event("I'm Roman Horseman");}
};//class RomanHorseman

class RomanCatapult: public Catapult
{

public:
	void GetInfo() const{LOG_Event("I'm Roman Catapult");}
};//class RomanCatapult

class RomanElephant: public Elephant
{

public:
	void GetInfo() const{LOG_Event("I'm Roman Elephant");}
};//class RomanElephant



class CarthaginianTrooper: public Trooper
{
// classes of all types of warriors in Carthaginian army
public:
	void GetInfo() const{LOG_Event("I'm Carthaginian Trooper");}
};//class CarthaginianTrooper

class CarthaginianArcher: public Archer
{

public:
	void GetInfo() const{LOG_Event("I'm Carthaginian Archer");}
};//class CarthaginianArcher

class CarthaginianHorseman: public Horseman
{

public:
	void GetInfo() const{LOG_Event("I'm Carthaginian Horseman");}
};//class CarthaginianHorseman

class CarthaginianCatapult: public Catapult
{

public:
	void GetInfo() const{LOG_Event("I'm Carthaginian Catapult");}
};//class CarthaginianCatapult

class CarthaginianElephant: public Elephant
{

public:
	void GetInfo() const{LOG_Event("I'm Carthaginian Elephant");}
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

	Sensor * cSensor;
	Sensor * rSensor;

public:
	Game()
		:romanArmy(dir.createArmy(roman_builder))
		,carthaginianArmy(dir.createArmy(carf_builder))
		,cSensor(new CarthaginianAdapterDistanceSensor)
		,rSensor(new RomanAdapterDistanceSensor)
	{
		
		srand(static_cast<unsigned>(time(NULL)));
	}

	void Play() const
	{
		LOG_Event("Roman army:");romanArmy->GetInfo();
		LOG_Event("Carthaginian army:");carthaginianArmy->GetInfo();
		LOG_Event("Carthaginian distance for Roman miles = ");
		LOG_Event(cSensor->getDistance(100.));
		LOG_Event("Raman distance for Carthaginian parasas = ");
		LOG_Event(rSensor->getDistance(100.));
		
		cSensor->Adjust(-0.21,-0.2);
		rSensor->Adjust(-0.22,-0.1);
		
		LOG_Event("Carthaginian distance for Roman miles = ");
		LOG_Event(cSensor->getDistance(100.));
		LOG_Event("Raman distance for Carthaginian parasas = ");
		LOG_Event(rSensor->getDistance(100.));
		
		cSensor->Adjust(2*0.21,2*0.2);
		rSensor->Adjust(2*0.22,2*0.1);
		
		LOG_Event("Carthaginian distance for Roman miles = ");
		LOG_Event(cSensor->getDistance(100.));
		LOG_Event("Raman distance for Carthaginian parasas = ");
		LOG_Event(rSensor->getDistance(100.));

	}

	~Game()
	{
		
		delete romanArmy;
		delete carthaginianArmy;
		delete cSensor;
		delete rSensor;
	}
};//class Game

int main()
{
	Game game;
	game.Play();

	return 0;
}
