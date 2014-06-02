#ifndef SWITCH_H
#define SWITCH_H

#include <vector>
#include "link.h"
#include "flow.h"
#include "device.h"
#include <cstdlib>


class Flow;

class Switch:public Device
{
public:
	int status;		//alive or dead - can be bool
	int level;
	int num_ports;
	vector<Link*> up_links;
	vector<Link*> down_links;
	vector<Flow*> flows;
	int failAt;
	int resilience; // 0 = no fail, 1 = single failure, 2 = multi-failure


	Switch(int pid, int did, string label, int l,int num):Device(new Address(pid, did),label)
	{
		status=0;
		level=l;
		num_ports=num;
		failAt=-1;
	}

	void connectToSwitch(Switch* dev,Link* link); //always called by the switch higher in the hierarchy
	int getNumPorts();
	int getStatus();
	void setStatus(int stat);
	string toString();
	void dfsPrint(string tab);
	int getPodID();
	int getDeviceID();
	int getLevel();
	vector<Switch*> getDownSwitches();
	vector<Switch*> getUpSwitches();
	Link* getLinkBetween( Switch* dst);
	Link* getLinkBetween( Host* dst);
	void addFlow(Flow* f);
	void removeFlow(Flow* f);
	vector<Link*> getUpLinks();
	vector<Link*> getDownLinks();
	vector<Link*> getTORs();
	

};

#endif /* SWITCH_H */
