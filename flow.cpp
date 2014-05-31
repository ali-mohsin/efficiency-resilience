#include "flow.h"

Flow::Flow(Host* src,Host* dst,Path* pp, Path* bp, int r, int s,int one,double sTime)
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
	// if(oneToOne)
	// 	commitPath(backUpPath,0);
	// else
	// 	commitPath(backUpPath,1);
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

bool Flow::commitPath(Path* path,int back)
{
	cout << "+ Commiting path" << endl;
	path->print();

     if (!path->isUp())
     {
     	cout <<"+ Commit Failed"<<endl;
     	return false;
     }
	for(int i=0;i<path->switches.size();i++)
	{
		path->switches[i]->addFlow(this);
	}

	for(int i=0;i<path->links.size();i++)
	{
		path->links[i]->addFlow(this->rate,path->direction[i],back);
	}
	cout <<"+ Committed "<<endl;
	return true;
}

void Flow::antiCommitPath(Path* path)
{
	cout << "+ Anti Commiting path" << endl;
	for(int i=0;i<path->switches.size();i++)
	{
		path->switches[i]->removeFlow(this);
	}

	for(int i=0;i<path->links.size();i++)
	{
		path->links[i]->removeFlow(this->rate,path->direction[i]);
	}
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