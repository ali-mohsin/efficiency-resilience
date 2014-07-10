#ifndef FLOW_H
#define FLOW_H

#include <vector>
#include <string>
#include "address.h"
#include "device.h"
#include "host.h" 
#include "switch.h" 
#include "link.h" 
#include "path.h" 

class Flow{
public:
	int flow_id;
	string label;

	double rate;
	int factor;
	int size;
	double startTime;
	double activeTime;
	int dur;
	bool done;
	int oneToOne;
	int down;
	int on_back;
	int allBackups;
	Host* source;
	Host* dest;
	Path* primaryPath;
	vector <Path*> backUpPath;
	vector <Path*> potentialBackUpPath;
	Flow(Host* src,Host* dst,Path* pp, vector<Path*> bp, int rate, int size,int,double,int,int);
	bool commitPath(Path* path, int back);
	void antiCommitPath(Path* path);
	int getID();
	void setID(int id);
	double getStart();
	double getActive();
	void setDone(bool);
	bool getDone();
	void activateFlow(double curTime);
	bool commitPathAndReserve(Path* path,int beingUsed);
	int antiCommitPathAndUnreserve(Path* path);
	double getBackUpRate();
	int contains(vector<Flow*> pathVec);
	
	//gohar
	void removeBackUpFlow(Path* path);
};

#endif /* FLOW_H */
