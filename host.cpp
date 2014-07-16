#include <assert.h>
#include "host.h"
void Host::connectToSwitch(Switch* dev,Link* link)
{
	assert(link->host!=this);
	assert(link->up_switch != dev || link->down_switch!=dev);
	assert(dev->down_links.size() < dev->num_ports);
	assert(this->link==NULL || this->otherLink==NULL);
	link->host=this;
	link->up_switch=dev;
	if(this->link==NULL)	
		this->link=link;
	else
		this->otherLink=link;
	dev->down_links.push_back(link);
}

Link* Host::getLink()
{
	return link;
}


string Host::toString()
{
	return Device::toString();
}

Switch* Host::getTor(Link* l)
{
	return l->getUpSwitch();
}


Switch* Host::getTor()
{
	return link->getUpSwitch();
}

int Host::getPodID()
{
	return addr->getPodID();
}

int Host::getDeviceID()
{
	return addr->getDeviceID();
}

int Host::availableVMs()
{
	int count=0;
	for(int i=0;i<all_vms.size();i++)
	{
		if(!all_vms[i]->marked)
			count++;
	}
	return count;
}

void Host::mark(int num)
{
	for(int i=0;i<all_vms.size();i++)
	{
		if(!all_vms[i]->marked)
		{
			all_vms[i]->mark();
			num--;			
		}
		if(num==0)
			return;
	}
}

void Host::unmark(int num)
{
	for(int i=0;i<all_vms.size();i++)
	{
		if(all_vms[i]->marked)
		{
			all_vms[i]->unmark();
			num--;			
		}
		if(num==0)
			return;
	}
}