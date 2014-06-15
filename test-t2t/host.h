#ifndef HOST_H
#define HOST_H


#include <vector>
#include "address.h"
#include "device.h"
#include "link.h"
#include "switch.h"



class Host: public Device
{
public:
	Link* link;
	void connectToSwitch(Switch* dev,Link* link); //always called by the switch higher in the hierarchy
	
	Host(int pid,int did,string label):Device(new Address(pid, did),label){link=NULL;}
	string toString();
	Switch* getTor();
	int getPodID();
	int getDeviceID();
	Link* getLink();
};

#endif /* HOST_H */
