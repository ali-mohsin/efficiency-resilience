#ifndef HOST_H
#define HOST_H


#include <vector>
#include "address.h"
#include "device.h"
#include "link.h"
#include "switch.h"
#include "vm.h"



class Host: public Device
{
public:
	Link* link;
	void connectToSwitch(Switch* dev,Link* link); //always called by the switch higher in the hierarchy
	
	Host(int pid,int did,string label):Device(new Address(pid, did),label)
	{
		link=NULL;
		isHost=1;
		for(int i=0;i<8;i++)
		{
			all_vms.push_back(new VM());
		}
	}
	string toString();
	Switch* getTor();
	int getPodID();
	int getDeviceID();
	Link* getLink();
	int availableVMs();
	void mark(int);
	vector<VM*> all_vms;
};

#endif /* HOST_H */
