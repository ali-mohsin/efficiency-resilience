#ifndef CONTROLLER_CPP
#define CONTROLLER_CPP


#include "link.h"
#include "switch.h"
#include "host.h"
#include "path.h"
#include "topology.h"
//this is to control the whole thing...includes a UI function
class Flow;

class Controller
{
public:
	vector<Switch*> all_cores;
	vector<Switch*> all_switches;
	vector<Host*> all_hosts;
	vector<Link*> all_links;
	vector<Flow*> all_flows;
	vector<Path*> paths;
	vector<Flow*> flows_on_back;
	vector<Switch*> critical_switches;
	vector<Flow*> flows_down;
	vector<Path*> paths_to_be_shared;
	float downTime;
	int torCap;
	int aggrCap;
	int coreCap;
	int k;				
	//k-ary tree
	int totalTime;
	int flowNumber;
	int oneToOne;
	long int t;
	int failures;
	bool backUp;
	vector<int> violations;
	void createFlows();
	Topology* createTopology(int,int,int);				//to create topology
	void assignPaths();
	void autofail(int);									//primary + backups
	bool instantiateFlow(Host* source, Host* dest, double rate, int size,double);	//rate in MBps, size in MB
	void findFaults();
	Path* getPathRandom(Host* source, Host* dest);
	void getAllPaths(Switch* src,Switch* dst, vector<Switch*> switches,vector<Link*> links, vector<bool> direction, int dir);
	Controller(int kay,int,int,int,int,int,int);
	int commitPath(Path* path, int dur,int rate, int size);
//	void antiCommitPath();
//	void goToSwitch(Path* path, Switch* dst, Switch** tempSwitch);
//	void goToCore(Path* path,Switch** tempSwitch);
//	void goToPod(Path* path, Host* dst, Switch** tempSwitch);
	void filterPaths(int rate,Host* dst);
	void commitFlow(Flow* flow);
	Path* getBackUpPath(Path* primary);
	void revert_to_primary();
	long int getTime();
	void detect_downTime();
	void checkProb(vector<Switch*> Tors, int prob, float factor);
	void checkProb(vector<Link*> Tors, int prob, float factor);
	void updateStatus(vector<Switch*> all_switches,int);
	void updateStatus(vector<Link*> all_switches,int);



	void uiFunc();			//is the UI - prints functions that we can do, like fail device/link and create flows
//	void createFailure(bool object, int id);
	void dumpData(long);
	vector<Switch*> getAllCores();
	vector<Switch*> getAllTors();
	vector<Switch*> getAllAggrs();
	vector<Link*> getAllCoreLinks();
	vector<Link*> getAllAggrLinks(); 
	vector<Link*> getAllTorLinks(); 

	int getTTR(Switch* curSwitch);
	int getTTR(Link* curSwitch);
	int getTTF(Switch* curSwitch);
	int getTTF(Link* curSwitch);
	void assignResilience();

};

#endif /* CONTROLLER_H */