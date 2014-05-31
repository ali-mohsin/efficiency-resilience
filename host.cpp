#include <assert.h>
#include "host.h"
void Host::connectToSwitch(Switch* dev,Link* link)
{
	assert(link->host!=this);
	assert(link->up_switch != dev || link->down_switch!=dev);
	assert(dev->down_links.size() < dev->num_ports);
	assert(this->link==NULL);
	link->host=this;
	link->up_switch=dev;
	this->link=link;
	dev->down_links.push_back(link);
}

string Host::toString()
{
	return Device::toString();
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