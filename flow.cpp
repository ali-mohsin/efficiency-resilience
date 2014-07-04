#include "flow.h"

Flow::Flow(Host* src,Host* dst,Path* pp, vector<Path*> bp, int r, int s,int one,double sTime, int sharing, int tor2tor)
{
	source=src;
	dest=dst;
	rate=r;
	size=s;
	startTime=sTime;
	primaryPath=pp;
	activeTime = (double)size/rate; // Time it would be active for
	vector<Path*> backUpPath=bp;
	done = false;
	oneToOne=one;
	down=-1;
	on_back=0;
	factor = 4;

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

	//if(sharing)
	//	rate=rate/factor;
	
	//if(backUpPath.size()!=0)
	//{

	//	for(int j=0; j<backUpPath.size();j++){
	//		for(int i=0;i<backUpPath[j]->switches.size();i++)
	//		{
	//			
	//			backUpPath[j]->switches[i]->addBackFlow(this);
	//		}

	//		for(int i=0;i<backUpPath[j]->links.size();i++)
	//		{
	//			backUpPath[j]->links[i]->addBackFlow(this,this->rate,backUpPath[j]->direction[i],on_back, tor2tor);
	//		}
	//	}

	//}

	commitPath(primaryPath,0);
	
}

//void Flow::activateFlow(double curTime)
//{
//	if(curTime<startTime)
//		return ;
//	if(oneToOne)
//		commitPath(backUpPath,0);
//	else
//		commitPath(backUpPath,1);
//	commitPath(primaryPath,0);
//}

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
		if(backUpPath.size()!=0)
			allBackups=0;
	}	

	for(int i=0;i<backUpPath.size();i++){
		if(path==backUpPath[i])
		{
			on_back=1;
			allBackups=1;
			primaryPath->beingUsed=0;
			backUpPath[i]->beingUsed=1;
			break;

		}
	}
	
	
	return true;
}

bool Flow::commitPathAndReserve(Path* path,int rate)
{
	int beingUsed = 1;
    if (!path->isUp())
    {
		cout << "error = path down" << endl;
     	return false;
    }

	if(path==primaryPath)
	{
		primaryPath->beingUsed=1;
		on_back=0;
		if(backUpPath.size()!=0)
			allBackups=0;
	}	
	
	if (backUpPath.size() > 1) {
		cout << "error = backup path size greater than 1" << endl;
		cout << "backup path size is " << backUpPath.size() << endl;
		return false;
	}
	
	// gohar: need to make fixes here, try clearing backuppath vector
	int selected = -1;
	for(int i=0;i<backUpPath.size();i++){
		if(path==backUpPath[i])
		{
			on_back=1;
			allBackups=1;
			primaryPath->beingUsed=0;
			backUpPath[i]->beingUsed=1;
			selected = i;
			break;

		}
	}
	
	if (selected != -1) {
		cout << "selected = " << selected << endl;	
		for (int i = 0; i < backUpPath[selected]->links.size(); i++) {
			backUpPath[selected]->links[i]->addFlowDataEntry(flow_id, rate);
			backUpPath[selected]->links[i]->addBackFlow(rate,backUpPath[selected]->direction[i]);
		}
		for (int i = 0; i < backUpPath[selected]->switches.size(); i++) {			
			backUpPath[selected]->switches[i]->addBackFlow(this);
		}
	} else {
		cout << "selected = " << selected << endl;
	}
	
	return true;
}



void Flow::antiCommitPath(Path* path)
{
	// cout<<"+ antiCommitPath ";
	// path->print();

	path->beingUsed = 0;

	int contains=path->contains(backUpPath);
	if(contains!=-1)
		on_back=0; //verify this

	// for(int i=0;i<path->switches.size();i++)
	// {
	// 	path->switches[i]->removeFlow(this);
	// }

	// for(int i=0;i<path->links.size();i++)
	// {
	// 	path->links[i]->removeFlow(this,this->rate,path->direction[i]);
	// }
}

int Flow::antiCommitPathAndUnreserve(Path* path)
{
	
	path->beingUsed = 0;

	int contains=path->contains(backUpPath);
	
	if(contains!=-1)
		on_back=0; //verify this
	
	int size = path->links.size();
	
	int rate_return = 0;
	
	for (int j = 0; j < path->links[0]->flowData.size(); j++) {
		if (path->links[0]->flowData[j].flow_id == flow_id) {
			rate_return = path->links[0]->flowData[j].rate;
		}
	}
	
	for (int i = 0; i < size; i++) {
		path->links[i]->addBackFlow(-rate_return,path->direction[i]);		
	}
	
	removeBackUpFlow();
	if (rate_return == 0) {
		cout << "rate return is 0" << endl;
	}
	return rate_return;
}

//gohar
// can also implement this by passing Path* passed to the above function
void Flow::removeBackUpFlow() {
	
	int check1 = 0;
	int check2 = 0;
	
	for (int i = 0; i < backUpPath[0]->switches.size(); i++) {
		for (int j = 0; j < backUpPath[0]->switches[i]->back_flows.size(); j++) {
			if (backUpPath[0]->switches[i]->back_flows[j] == this) {
				(backUpPath[0]->switches[i]->back_flows).erase(backUpPath[0]->switches[i]->back_flows.begin()+j);
				check1 = 1;
			}
		}
	}
	
	for (int i = 0; i < backUpPath[0]->links.size(); i++) {
		for (int j = 0; j < backUpPath[0]->links[i]->flows_back.size(); j++) {
			if (backUpPath[0]->links[i]->flows_back[j] == this) {
				(backUpPath[0]->links[i]->flows_back).erase(backUpPath[0]->links[i]->flows_back.begin()+j);
				check2 = 1;
			}
		}
	}
	
	if (check1 == 1 && check2 == 1)
		cout << "flow removed successfully" << endl;
	else {
		cout << "error in removing flow" << endl;
		cout << "backup path size is " << backUpPath.size() << endl;
		cout << "check1 is " << check1 << " check2 is " << check2 << endl;
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

double Flow::getBackUpRate()
{
	// uses factor to update rate
	return (rate-(rate/factor));
}
