using namespace std;
#ifndef LINK_H
#define LINK_H


class Switch;
class Link;
class Host;
class Path;

#include "address.h"
#include "device.h"
#include "host.h"
#include "switch.h"

class Link
{
public:
	int link_id;
	string label;
	int status;		//alive or dead – can be bool
	int total_cap;	//capacity
	int available_cap_up;
	int available_cap_down;
	int backup_up;
	int backup_down;
	int num_flows;
	vector<Flow*> flows;
	Switch* up_switch;
	Switch* down_switch;
	Host* host;
	int failAt;
	int resilience; // 0 = no fail, 1 = single failure, 2 = multi-failure


	Link(int id,int cap,string l);
	int reserve_BW_up(int bw);
	int reserve_BW_down(int bw);
	bool availAtUp(int bw);
	bool availAtDown(int bw);
	Switch* getDownSwitch();
	Switch* getUpSwitch();
	int getUsedUpBW();
	int getUsedDownBW();
	int getID();
	string getLabel();
	int getStatus();
	vector<Flow*> getActiveFlows();
	void setStatus(int stat);
	void printInfo();
	Switch* getOtherNode(Switch* cur);
	void addFlow(Flow* f,int rate, int dir, int back);
	void removeFlow(Flow* f,int rate, int dir, int on_back);
	void commitPath(Path* p, int back);
	vector<Flow*> getFlowsOnPrimary();
	vector<Flow*> getFlowsOnBack();


};

#endif /* LINK_H */
