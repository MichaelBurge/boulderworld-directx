// ai.cpp: implementation of the ai class.
//
//////////////////////////////////////////////////////////////////////

#include "main.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ai::ai()
{
	player=0;
}

ai::~ai()
{

}
void ai::regetunits(void) {
	units.clear();
	for (int temp=0;temp<gameengine.unitcount;temp++)
		if (gameengine.units[temp].side==player) 
			units.push_back(&gameengine.units[temp]);//Stuff the unit's addresses into the vector of pointers for later use

}
void ai::checkplanets(void) {
	untakenplanets.clear();
	bool planetfine=false;
	for (int temp=0;temp<gameengine.planetcount;temp++,planetfine=false) {
		for (int temp2=0;temp2<units.size();temp2++)
			if (DistanceToPoint(units[temp2]->x,units[temp2]->y,gameengine.planets[temp].positionx,gameengine.planets[temp].positiony)<500.0f)
				planetfine=true;
		if (!planetfine) untakenplanets.push_back(&gameengine.planets[temp]);
	}
}
void ai::process(void) {
	regetunits();
	checkplanets();
	for (int temp=0;temp<units.size();temp++)
		processunit(units[temp]);
	if (gameengine.players[player].productionpoints>=1000) CreateShip();
}

bool ai::safe(int x,int y,double distance) {
	for (int temp=0;temp<gameengine.unitcount;temp++)//Loop through all units, checking distance from spot
		if (gameengine.units[temp].side!=player&&DistanceToPoint(gameengine.units[temp].x,gameengine.units[temp].y,x,y)<distance)
			return false;//If enemy unit is close to the spot, the spot isn't fine, so return false
	return true;//If all enemy units weren't close to the spot, the spot must be fine, so return true
}
void ai::processunit(unit *theunit) {
	if (untakenplanets.size()) {
		if (safe(untakenplanets[0]->positionx,untakenplanets[0]->positiony,200)) {
			theunit->destx=untakenplanets[0]->positionx+128;//If planet's safe, destination of unit is in the middle of the planet
			theunit->desty=untakenplanets[0]->positiony+128;
		} else {
			int unitcount=0;
			planet *closest=&gameengine.planets[0];
			double currentdistance=5000000,temp2;
			for (int temp=0;temp<untakenplanets.size();temp++)
				if ((temp2=DistanceToPoint(gameengine.planets[temp].positionx,gameengine.planets[temp].positiony,closest->positionx,closest->positiony))<currentdistance) {
					currentdistance=temp2;
					closest=&gameengine.planets[temp];
				}
			for (temp=0;temp<gameengine.unitcount;temp++)
				if (gameengine.units[temp].side==player&&DistanceToPoint(gameengine.units[temp].x,gameengine.units[temp].y,untakenplanets[0]->positionx,untakenplanets[0]->positiony)<200)
					unitcount++;//If the unit's close to the planet, increment the number of units close to the planet
				if (unitcount>=units.size()&&units.size()) for (temp=0;temp<unitcount;temp++) {
					units[temp]->destx=untakenplanets[0]->positionx;
					units[temp]->desty=untakenplanets[0]->positiony;
				} else {theunit->destx = untakenplanets[0]->positionx-128;theunit->desty = untakenplanets[0]->positiony-128;}
		}
	}
}

void ai::CreateShip(void) {
	if (gameengine.players[player].productionpoints>=1000) {
		unit theunit;
		theunit.attack=1;
		theunit.maxhealth=32;
		theunit.health=32;
		theunit.range=70;
		theunit.speed=1;
		theunit.side=player;
		theunit.type=0;
		theunit.width=32;
		theunit.height=32;
		theunit.destx=theunit.x;
		theunit.desty=theunit.y;
		for (int temp=0;temp<gameengine.planetcount;temp++)
			if (gameengine.planets[temp].player==player) {
				theunit.x=gameengine.planets[temp].positionx+128;
				theunit.y=gameengine.planets[temp].positiony+128;
				theunit.destx=theunit.x;
				theunit.desty=theunit.y;
				break;
			}
			gameengine.AddUnit(&theunit);
			gameengine.players[player].productionpoints-=1000;
	}
}