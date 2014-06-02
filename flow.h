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
	int size;
	double startTime;
	double activeTime;
	int dur;
	bool done;
	int oneToOne;
	int down;

	Host* source;
	Host* dest;
	Path* primaryPath;
	Path* backUpPath;
	Flow(Host* src,Host* dst,Path* pp, Path* bp, int rate, int size,int,double);
	bool commitPath(Path* path, int back);
	void antiCommitPath(Path* path);
	int getID();
	void setID(int id);
	double getStart();
	double getActive();
	void setDone(bool);
	bool getDone();
	void activateFlow(double curTime);
};

#endif /* FLOW_H */
