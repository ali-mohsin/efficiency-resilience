#ifndef CONTROLLER_CPP
#define CONTROLLER_CPP


#include "link.h"
#include "switch.h"
#include "host.h"
#include "path.h"
#include "topology.h"
#include "group.h"
#include "pair.h"
#include "tenant.h"
#include "hostpair.h"
#include "pairs.h"
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
	vector<Tenant*> all_tenants;
	vector<HostPair*> all_host_pairs;
	vector<Link*> usedLinks;
	int flows_on_share;
	int ones;
	int twos;
	int threes;
	int tor_to_tor;	
	int end_to_end;
	int curLevel;

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
	int oct;
	long int t;
	int failures;
	bool backUp;
	int sharing;
	vector<PodPair*> all_pod_pairs;
	vector<TorPair*> all_tor_pairs;
	vector<Host*> tenant_vms;
	vector<TenantFlow*> tenant_flows;
	vector<Link*> cLinks;
	vector<int> cBws;

	vector<int> violations;
	void createFlows();
	Host* getHostInTor(int id);
	vector<Switch*> getAggrSwitches(int pod);

	void logFailures(int time);
	Topology* createTopology(int,int,int);				//to create topology
	void assignPaths();
	int alloc(int v,int b,Host* h,Switch* s);
	vector<Host*> octopus(int v, int b);
	int computeMx(Switch*,int);
	int computeMx(Link* l,int bw);
	int TorCount(Switch* d,int bw);
	int aggrCount(Switch* d,int bw);
	int coreCount(Switch* d,int bw);



	void autofail(int);									//primary + backups
	Flow* instantiateFlow(Host* source, Host* dest, double rate, int size,double);	//rate in MBps, size in MB
	bool instantiateTenant(int vms, int bw);	//rate in MBps, size in MB
	void findFaults();
	Path* getPathRandom(Host* source, Host* dest);
	void getAllPaths(Switch* src,Switch* dst, vector<Switch*> switches,vector<Link*> links, vector<bool> direction, int dir);
	Controller(int kay,int,int,int,int,int,int,int,int);
	int commitPath(Path* path, int dur,int rate, int size);
//	void antiCommitPath();
//	void goToSwitch(Path* path, Switch* dst, Switch** tempSwitch);
//	void goToCore(Path* path,Switch** tempSwitch);
//	void goToPod(Path* path, Host* dst, Switch** tempSwitch);
	void filterPaths(int rate,Host* dst);
	Path* chooseBest(int,int);
	int vmCount(Link*, int, vector<Host*>, int);
	void commitFlow(Flow* flow);
	bool checkPath(Path*, std::vector<Host*>, int, int, std::vector<PodPair*>, std::vector<TorPair*>);
	Path* getBackUpPath(Path* primary,int rate);
	bool checkBW(std::vector<Host*>, int);
	void revert_to_primary();
	Path* getReplicatedPath(int src, int dst, int rate);
	long int getTime();
	void detect_downTime(int);
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
