#ifndef TOPOLOGY_H
#define TOPOLOGY_H


#include <vector>
#include <string>
#include "address.h"
#include "device.h"
#include "link.h"
#include "switch.h"
#include "host.h"
#include "subpod.h"


/* This class creates a topology, primarily fat tree using the basic building blocks of switches, links and hosts. */

class Topology
{
	public:
		vector<Switch*> coreSwitches;	// holds the pointers to all the core switches
		//Additions by saad
		vector<Switch*> allSwitches;
		vector<Host*> allHosts;
		vector<Link*> allLinks;
		//End additions by saad
		int k;				// k refers to a k-ary fat-tree
		int netDeviceID;	// global variable which is used to assign each network device a unique id
		int coreID;	// global variable which is used to assign each network device a unique id
		int t_aggrID;	// global variable which is used to assign each network device a unique id
		int b_aggrID;	// global variable which is used to assign each network device a unique id
		int hostID;	// global variable which is used to assign each network device a unique id
		int podID;		// global variable which is used to assign each pod a unique id
		int netLinkID;	// global variable which is used to assign each link a unique id
		int torCap;
		int coreCap;
		int aggrCap;


		Topology(int kVal,int tor,int aggr,int core)
		{
			k=kVal;
			netDeviceID = 0;
			coreID = 0;
			t_aggrID = 0;
			b_aggrID = 0;
			hostID = 0;
			podID = 0;
			netLinkID = 0;
			torCap=tor;
			aggrCap=aggr;
			coreCap=core;
		}

		vector<Switch*> createPod(int id); // constructs a pod (specific to fat-tree) and returns the vector containing pointers to the aggregation level switches
		void createFatTree(); // constructs the fat tree using the value of k initialized by the constructor
		void printTopology(); // prints out the network devices and hosts in a depth-first manner

		Pod* createMusaPod(int podId);
		void createMusaTree();
		Subpod* createSubPod(int);



		//getter functions
		vector<Switch*> getCores();
		vector<Switch*> getSwitches();
		vector<Host*> getHosts();
		vector<Link*> getLinks();
};

#endif /* TOPOLOGY_H */