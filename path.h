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
	Path(Path* other);

	void print();
	vector<Switch*> getSwitches();
	bool isValid(int rate);
	int getSrcPod();
	int getDstPod();
};

#endif /* FLOW_H */
