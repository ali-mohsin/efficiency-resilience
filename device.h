#ifndef DEVICE_H
#define DEVICE_H

#include "address.h"
#include <vector>
class Flow;
class Device
{
	public:
	Address* addr;
	string label;
	vector<Flow*> allFlows;
	Device(Address* ad,string s)
	{
		addr=ad;
		label=s;
	}

	void printDevice()
	{
		addr->printAddress();
		cout<<"label: "<<label<<"\n";
	}

	string toString()
	{
		return addr->toString();
	}

	void addFlow(Flow* flow)
	{
		allFlows.push_back(flow);
	}

	int getPodID()
	{
		return addr->getPodID();
	}

	int getDeviceID()
	{
		return addr->getPodID();
	}

};

#endif /* DEVICE_H */
