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
	down=-1;
	on_back=0;

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
	// cout<<"+ commitPath";
	// path->print();

     if (!path->isUp())
     {
     	return false;
     }

     on_back=back;

    if(down==-1) // just started
    {
		for(int i=0;i<path->switches.size();i++)
		{
			path->switches[i]->addFlow(this);
		}

		for(int i=0;i<path->links.size();i++)
		{
			path->links[i]->addFlow(this,this->rate,path->direction[i],back);
		}
	}

	down=0;

	return true;
}

void Flow::antiCommitPath(Path* path, int completed)
{
	// cout<<"+ antiCommitPath ";
	// path->print();
	if(!completed)
		down=1;

	if(completed){
	 for(int i=0;i<path->switches.size();i++)
	 {
	 	path->switches[i]->removeFlow(this);
	 }

	 for(int i=0;i<path->links.size();i++)
	 {
	 	path->links[i]->removeFlow(this,this->rate,path->direction[i], on_back);
	 }
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
