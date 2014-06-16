#ifndef CONTROLLER_CPP
#define CONTROLLER_CPP


#include "link.h"
#include "switch.h"
#include "host.h"
#include "path.h"
#include "topology.h"
#include "group.h"
#include "pair.h"
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
	vector<Switch*> down_switches;
	vector<Link*> down_links;
	vector<Link*> prone_links;
	vector<Switch*> prone_switches;
	vector<Group*> all_groups;
	vector<Pair*> all_pairs;
	int flows_on_share;

	int tor_to_tor;	
	int end_to_end;

	double downTime;
	int torCap;
	int aggrCap;
	double backup;
	int coreCap;
	int k;				
	//k-ary tree
	int totalTime;
	int flowNumber;
	int oneToOne;
	long int t;
	int failures;
	bool backUp;
	int sharing;

	vector<int> violations;
	void createFlows();
	Host* getHostInTor(int id);

	void logFailures(int time);
	Topology* createTopology(int,int,int);				//to create topology
	void assignPaths();
	void autofail(int);									//primary + backups
	bool instantiateFlow(Host* source, Host* dest, double rate, int size,double);	//rate in MBps, size in MB
	void findFaults();
	Path* getPathRandom(Host* source, Host* dest);
	void getAllPaths(Switch* src,Switch* dst, vector<Switch*> switches,vector<Link*> links, vector<bool> direction, int dir);
	Controller(int kay,int,int,int,int,int,int,int);
	int commitPath(Path* path, int dur,int rate, int size);
//	void antiCommitPath();
//	void goToSwitch(Path* path, Switch* dst, Switch** tempSwitch);
//	void goToCore(Path* path,Switch** tempSwitch);
//	void goToPod(Path* path, Host* dst, Switch** tempSwitch);
	void filterPaths(int rate,Host* dst);
	void commitFlow(Flow* flow);
	Path* getBackUpPath(Path* primary,int rate);
	void revert_to_primary();
	Path* getReplicatedPath(int src, int dst, int rate);
	long int getTime();
	void detect_downTime();
	vector<float> getAllocation(int p);
	void checkProb(vector<Switch*> Tors, int prob, float factor);
	void checkProb(vector<Link*> Tors, int prob, float factor);
	void updateStatus(int,int);
	void updateStatusLink(int,int);
	void writeLog(string str);
	vector<Link*> critical_links;
	vector<Flow*> getCommonFlows(vector<Flow*> u,vector<Flow*> d);
	void getIntraPodPaths(Switch*, Switch*, Link*, std::vector<Switch*>, std::vector<Link*>, std::vector<bool>, int);
	void getInterPodPaths(Switch*, Switch*, Link*, std::vector<Switch*>, std::vector<Link*>, std::vector<bool>, int);
	bool getPaths(Host*, Host*, std::vector<Switch*>, std::vector<Link*>, std::vector<bool>, int);
	void counter(vector<Link*> Tors);
	void counter(vector<Switch*> Tors);
	vector<Link*> getFailingLink(int);
	Link* getMinLink(int);



	void uiFunc();			//is the UI - prints functions that we can do, like fail device/link and create flows
//	void createFailure(bool object, int id);
	void dumpData(long);
	vector<Switch*> getAllCores();
	vector<Switch*> getAllTors();
	vector<Switch*> getAllAggrs();
	vector<Link*> getAllCoreLinks();
	vector<Link*> getAllAggrLinks(); 
	vector<Link*> getAllTorLinks(); 	
	bool duplicateIn(vector<Switch*> v);
	bool duplicateIn(vector<Link*> v);
	bool duplicateIn(vector<Flow*> v);


	int getTTR(Switch* curSwitch);
	int getTTR(Link* curSwitch);
	int getTTF(Switch* curSwitch);
	int getTTF(Link* curSwitch);
	Switch* getTorFromAnotherPod(int pod);

	void assignResilience();

};

#endif /* CONTROLLER_H */
