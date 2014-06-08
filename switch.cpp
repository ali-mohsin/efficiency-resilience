#include <assert.h>
#include "switch.h"
#include "sstream"

void Switch::connectToSwitch(Switch* dev,Link* link)
{
	//cout<<"trying to connect "<< this->toString()<< " with " << dev->toString() <<endl;
	assert(this->level < dev->level);
	assert(link->up_switch != this || link->down_switch!=this);
	assert(link->up_switch != dev || link->down_switch!=dev);
	assert(this->down_links.size() < this->num_ports);
	assert(dev->up_links.size() < dev->num_ports);
	link->up_switch=this;
	link->down_switch=dev;
	this->down_links.push_back(link);
	dev->up_links.push_back(link);
	//cout<<"successfully connected"<<endl;
}

int Switch::getPodID()
{
	return addr->getPodID();
}

int Switch::getDeviceID()
{
	return addr->getDeviceID();
}

int Switch::getLevel()
{
	return level;
}

// vector<Flow*> Switch::getActiveFlows()
// {
// 	vector<Flow*> v;
// 	for(int i=0;i<flows.size();i++)
// 	{
// 		if(flows[i]->down!=1)
// 			v.push_back(flows[i]);
// 	}
// 	return v;
// }

vector<Flow*> Switch::getFlowsOnPrimary()
{
	vector<Flow*> v;
	for(int i=0;i<primary_flows.size();i++)
	{
		if(primary_flows[i]->primaryPath->beingUsed)
			v.push_back(primary_flows[i]);
	}
	return v;
}


vector<Flow*> Switch::getFlowsOnBack()
{
	vector<Flow*> v;
	for(int i=0;i<back_flows.size();i++)
	{
		if(back_flows[i]->backUpPath->beingUsed)
			v.push_back(back_flows[i]);
	}
	return v;
}


vector<Switch*> Switch::getDownSwitches()
{
	vector<Switch*> switches;
	for(int i=0;i<down_links.size();i++)
	{
		Link* link=down_links[i];
		switches.push_back(link->getDownSwitch());
	}

	return switches;
}


vector<Switch*> Switch::getUpSwitches()
{
	vector<Switch*> switches;
	for(int i=0;i<up_links.size();i++)
	{
		Link* link=up_links[i];
		switches.push_back(link->getUpSwitch());
	}

	return switches;
}


vector<Link*> Switch::getUpLinks()
{
	return up_links;
}

vector<Link*> Switch::getDownLinks()
{
	return down_links;
}


Link* Switch::getLinkBetween(Host* dst)
{
	vector<Link*> down=getDownLinks();
	for(int i=0;i<down.size();i++)
	{
		Link* link=down[i];
		if(link->host==dst)
		{
			return link;
		}
	}

	return NULL;
}


Link* Switch::getLinkBetween(Switch* dst)
{
	vector<Link*> down=getDownLinks();
	vector<Link*> up=getUpLinks();
	for(int i=0;i<down.size();i++)
	{
		Link* link=down[i];
		if(link->getDownSwitch()==dst)
		{
			return link;
		}
	}


	for(int i=0;i<up.size();i++)
	{
		Link* link=up[i];
		if(link->getUpSwitch()==dst)
		{
			return link;
		}
	}

	return NULL;
}



void Switch::dfsPrint(string tab)
{
	for (int i=0;i<down_links.size();i++)
	{
		Link* curLink=down_links[i];
		if(curLink->host!=NULL)
		{
			cout<<tab<<" Host: "<<curLink->host->toString()<<endl; 
			continue;
		}
		Switch* curSwitch= curLink->down_switch;
		cout<<tab<<curSwitch->toString()<<endl;
		tab+="\t";
		curSwitch->dfsPrint(tab);
		tab.erase(0,1);
	}
}

int Switch::getNumPorts()
{
	return num_ports;
}

int Switch::getStatus()
{
	return status;
}

void Switch::setStatus(int stat)
{
	status = stat;
}

string Switch::toString()
{
	stringstream ss;
	ss << level;
	string s = ss.str();
	return "["+s + ","+ Device::toString();//+"\t\t------------------------------------------\n";
}


void Switch::addPrimaryFlow(Flow* flow)
{
	primary_flows.push_back(flow);
}

void Switch::addBackFlow(Flow* flow)
{
	back_flows.push_back(flow);
}


// void Switch::removeFlow(Flow* flow)
// {

// 	// startTimer();
// 	for(int i=0;i<flows.size();i++)
// 	{
// 		if(flows[i]->flow_id==flow->flow_id)
// 		{
// 			flows.erase(flows.begin()+i);
// 			i--;
// 			// stopTimer("To remove flow");
// 			return;
// 		}
// 	}
// }
