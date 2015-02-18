#ifndef __Qt4All__
# include <Gui/Qt4All.h>
#endif
#include <Base/Placement.h>
 
#define DELTA_TIME (1000/30)
template<typename T>
class Action : public QObject, public QBasicTimer 
{

protected:
float duration;
float elapsedTime;
T startValue;
T endValue;
 

public:	
	
Action() : QBasicTimer()
{
	this->elapsedTime = 0;
	this->duration = 1.0;	
	this->start(DELTA_TIME,this);
}

void setDuration(float d) { duration = d; }
virtual void update()
{
	elapsedTime += DELTA_TIME;
}

void timerEvent ( QTimerEvent * event ) 
{
	update();
}

};



class PlacementAction : public Action<Base::Placement>
{
private:
App::DocumentObject* target;
float evolution;
public:
PlacementAction() : Action()
{
	target = NULL;
}

void setTargetAndEndValue(App::DocumentObject* obj,Base::Placement dest)
{
	target = obj;
	App::GeoFeature* geo = (App::GeoFeature*)obj;
	this->startValue = geo->Placement.getValue();
	this->endValue = dest;
	evolution = 0;
}

void setTargetAndEndValueAndInitialEvolution(App::DocumentObject* obj,Base::Placement dest, float evolution)
{
	target = obj;
	App::GeoFeature* geo = (App::GeoFeature*)obj;
	this->startValue = geo->Placement.getValue();
	this->endValue = dest;
	this->evolution = evolution;
	this->elapsedTime = evolution * duration * 1000;
}

float getOppositeEvolution() {
	return 1.0f - evolution;	
}


virtual void  update()
{
	if(target == NULL)
		return;

	Action::update();
	evolution = (elapsedTime)/(duration*1000);
	if(evolution > 1.0)
	{
		evolution = 1.0;
		stop();
	}

	App::GeoFeature* geo = (App::GeoFeature*)target;
	geo->Placement.setValue(Base::Placement::slerp(startValue, endValue, evolution) );
	
}

};

