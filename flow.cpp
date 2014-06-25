#include "flow.h"

Flow::Flow(Host* src,Host* dst,Path* pp, Path* bp, int r, int s,int one,double sTime, int sharing, int tor2tor)
{
	source=src;
	dest=dst;
	rate=r;
	size=s;
	startTime=sTime;
	primaryPath=pp;
	activeTime = (double)size/rate; // Time it would be active for
	backUpPath=bp;
	done = false;
	oneToOne=one;
	down=-1;
	on_back=0;


	// if(oneToOne)
	// 	commitPath(backUpPath,0);
	// else
	// 	commitPath(backUpPath,1);
	for(int i=0;i<primaryPath->switches.size();i++)
	{
		primaryPath->switches[i]->addPrimaryFlow(this);
	}

	for(int i=0;i<primaryPath->links.size();i++)
	{
		primaryPath->links[i]->addPrimaryFlow(this,this->rate,primaryPath->direction[i],on_back);
	}

	if(sharing)
		rate=rate/4;
	
	if(backUpPath!=NULL)
	{
		for(int i=0;i<backUpPath->switches.size();i++)
		{
			
			backUpPath->switches[i]->addBackFlow(this);
		}

		for(int i=0;i<backUpPath->links.size();i++)
		{
			backUpPath->links[i]->addBackFlow(this,this->rate,backUpPath->direction[i],on_back, tor2tor);
		}

	}


	commitPath(primaryPath,0);


}

void Flow::activateFlow(double curTime)
{
	if(curTime<startTime)
		return ;
	if(oneToOne)
		commitPath(backUpPath,0);
	else
		commitPath(backUpPath,1);
	commitPath(primaryPath,0);
}

bool Flow::getDone()
{
	return done;
}

void Flow::setDone(bool d)
{
	done = d;
}

bool Flow::commitPath(Path* path,int beingUsed)
{
	// cout<<"+ commitPath";
	// path->print();

    if (!path->isUp())
    {
     	return false;
    }

	if(path==primaryPath)
	{
		primaryPath->beingUsed=1;
		on_back=0;
		if(backUpPath!=NULL)
			backUpPath->beingUsed=0;
	}	

	if(path==backUpPath)
	{
		on_back=1;
		primaryPath->beingUsed=0;
		backUpPath->beingUsed=1;
	}	

	return true;
}

void Flow::antiCommitPath(Path* path)
{
	// cout<<"+ antiCommitPath ";
	// path->print();

	path->beingUsed = 0;

	if(path==backUpPath)
		on_back=0;

	// for(int i=0;i<path->switches.size();i++)
	// {
	// 	path->switches[i]->removeFlow(this);
	// }

	// for(int i=0;i<path->links.size();i++)
	// {
	// 	path->links[i]->removeFlow(this,this->rate,path->direction[i]);
	// }
}


void Flow::setID(int id)
{
	flow_id = id;
}

int Flow::getID()
{
	return flow_id;
}

double Flow::getStart()
{
	return startTime;
}

double Flow::getActive()
{
	return activeTime;
}
