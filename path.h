#ifndef PATH_H
#define PATH_H

#include <vector>
#include <string>
#include "address.h"
#include "device.h"
#include "host.h" 
#include "switch.h" 
#include "link.h" 

class Path {
public:
	int pathID;
	string label;
	int beingUsed;
	vector<Switch*> switches;
	vector<Link*> links;
	vector<bool> direction;

	bool isUp();
	void addLink(Link* s);
	void addSwitch(Switch* s);
	Path(vector<Switch*> s , vector<Link*> l, vector<bool> dir);
	void print();
	vector<Switch*> getSwitches();
	bool isValid(int rate,int);
	bool isValid(int rate);
	int contains(vector<Path*> pathVec);
	bool has(Link* link);
	bool has(Switch* link);
	int getSrcPod();
	int getDstPod();
	
	// gohar
	int getDestHost();
	int getSrcHost();
};

#endif /* FLOW_H */
