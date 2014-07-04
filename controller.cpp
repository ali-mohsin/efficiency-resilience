#include "controller.h"
#include "flow.h"
#include <math.h>
#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <string>
#include "time.h"

using namespace std;

class Topology;

Topology* Controller::createTopology(int tor,int aggr,int core)
{
	Topology* tree = new Topology(k,tor,aggr,core);
	tree->createFatTree();
	all_cores = tree->getCores();
	all_switches = tree->getSwitches();
	all_hosts = tree->getHosts();
	all_links = tree->getLinks();
 		// tree->printTopology();
}

Controller::Controller(int kay,int tor,int aggr,int core,int back,int share, int runFor,int makeFlows)
{
	downTime=0;
	flows_on_share=0;
	srand(time(0));
	k=kay;
	torCap=tor;
	aggrCap=aggr;
	coreCap=core;
	flowNumber = 0;
	createTopology(tor,aggr,core);
	backUp=back;
	tor_to_tor=0;
	end_to_end=0;
	if(back==1)
		tor_to_tor=1;
	if(back==2)
		end_to_end=1;

	sharing = share;
	backup=0;
	// TODO seperate variable for backup
	// TODO intra-rack communication, path assigned goes all the way round from core
	failures=0;
	totalTime=runFor;
	assignResilience();
	
	int increase_by = 20; // increase capacities of links by this num
	
	if(makeFlows)
	{
		createFlows();
		
		for (int i =0; i<all_links.size();i++) {
			all_links[i]->total_cap+=2*increase_by;
			all_links[i]->available_cap_down+=increase_by;
			all_links[i]->available_cap_up+=increase_by;
		}
		
	}



	// vector<float> b=getAllocation(1);
	// vector<float> p=getAllocation(0);

	// cout<<"[";
	// for(int i=0;i<p.size();i++)
	// {
	// 	cout<<p[i]<<",";
	// }
	// cout<<"]"<<endl;

	// int x=1/0;
	// for(int i=0;i<all_links.size();i++)
	// {
	// 	cout<<"Link with ID: "<<all_links[i]->link_id<<" has "<<all_links[i]->flows_primary.size()<<" Flows passing through"<<endl;
	// 	cout<<"Link with ID: "<<all_links[i]->link_id<<" has "<<all_links[i]->flows_back.size()<<" Flows passing through"<<endl;

	// 	// if(all_links[i]->flows_primary.size()==0 && all_links[i]->flows_back.size()==0)
	// 	// {
	// 	// 	int x=1/0;
	// 	// 	// //cout<<"Link with ID: "<<all_links[i]->link_id<<" has "<<all_links[i]->flows_primary.size()<<" Flows passing through"<<endl;
	// 	// 	// //cout<<"Link with ID: "<<all_links[i]->link_id<<" has "<<all_links[i]->flows_back.size()<<" Flows passing through"<<endl;
	// 	// }
	// 	// else
	// 	// {
	// 	// 	// //cout<<"Link with ID: "<<all_links[i]->link_id<<" has "<<all_links[i]->flows.size()<<" Flows passing through"<<endl;
	// 	// 	int x=1/0;
	// 	// }
	// }++

	//cout<<"Flows on share are: "<<flows_on_share<<" out of "<<all_flows.size()<<endl;
}

//gohar
bool Controller::makeBackUp(Flow* flow, int rate) { 
	Path* primaryPath = flow->primaryPath; 
	int src = primaryPath->getSrcHost(); 
	int dest = primaryPath->getDestHost(); 
	SprayData* sprayData = getSprayPath(src, dest, rate, primaryPath);
				
	if (!sprayData)
		return false;
					
	//for(int i=0;i<backUpPath->switches.size();i++)             
	//	backUpPath->switches[i]->addBackFlow(flow);
	//			
	//for(int i=0;i<backUpPath->links.size();i++)             
	//	backUpPath->links[i]->addBackFlow(flow,flow->rate,backUpPath->direction[i],0, 0); 
	
	for (int i = 0; i < sprayData->paths.size(); i++) {
		flow->backUpPath.push_back(sprayData->paths[i]);
		flow->commitPathAndReserve(sprayData->paths[i], sprayData->toReserve[i]);
	}
	
	return true;
}

vector<float> Controller::getAllocation(int p)
{
	vector<float> v;
	for(int i=0;i<all_switches.size();i++)
	{
		v.push_back(all_switches[i]->get_ratio(p));
	}
	return v;
}

Switch* Controller::getTorFromAnotherPod(int pod)
{
	int otherPod=pod;
	Switch* curSwitch=all_switches[0];

	while(otherPod==pod || curSwitch->level!=2)
	{
		curSwitch=all_switches[rand()%all_switches.size()];
		otherPod=curSwitch->getPodID();
	}
	return curSwitch;
}

void Controller::createFlows()
{
	int factor=8; // ihave temporarily disabled this
	if(end_to_end)
		factor=16;
	int total_flows=0;
	for (int i=0;i<all_switches.size();i++)
	{
		Switch* curSwitch=all_switches[i];
		if(curSwitch->level==2)
		{
			int pod=curSwitch->getPodID();
			for(int j=0;j<k*k/4;j++)
			{
				Switch* otherTor=getTorFromAnotherPod(pod);
				Host* start=curSwitch->down_links[rand()%curSwitch->down_links.size()]->host;
				Host* end=otherTor->down_links[rand()%curSwitch->down_links.size()]->host;
				// //cout<<"Flow started from "<<curSwitch->toString()<<" to "<<otherTor->toString()<<endl;
				total_flows+=instantiateFlow(start,end,100,10,0);

			}	
		}
		// for (int j=0;j<all_hosts.size();j++)
		// {
		// 	ifll_hosts[i],all_hosts[j],10,10,0);
		// }
	}

	cout<<"Flows generated "<<total_flows<<endl;
	// int x = 1/0;
}

void Controller::checkProb(vector<Switch*> Tors, int prob, float factor)
{


	float pb=float(prob)/float(1000);
	int a_size=(Tors.size()*(1-pb));
	int b_size=ceil(Tors.size()*(pb/2));
	int c_size=ceil(Tors.size()*(pb/2));

	int counter=0;

	while(counter<c_size)
	{
		int failAt=rand()%totalTime;
		//cout<<failAt<<",";
		int index=rand()%Tors.size();
		Switch* curSwitch=Tors[index];
		prone_switches.push_back(curSwitch);
		Tors[index]->resilience=2;
		Tors[index]->failAt=failAt;
		Tors.erase(Tors.begin()+index);
		counter++;
	}

	counter=0;
	while(counter<b_size)
	{
		int failAt=rand()%totalTime;
		//cout<<failAt<<",";
		int index=rand()%Tors.size();
		Switch* curSwitch=Tors[index];
		Tors[index]->resilience=1;
		prone_switches.push_back(curSwitch);

		Tors[index]->failAt=failAt;
		Tors.erase(Tors.begin()+index);
		counter++;
	}

	counter=0;
	while(counter<a_size && Tors.size()!=0)
	{
		int index=rand()%Tors.size();
		Switch* curSwitch=Tors[index];
		Tors[index]->resilience=0;
		Tors.erase(Tors.begin()+index);
		counter++;
	}

}

void Controller::checkProb(vector<Link*> Tors, int prob, float factor)
{


	float pb=float(prob)/float(1000);
	int a_size=(Tors.size()*(1-pb));
	int b_size=ceil(Tors.size()*(pb/2));
	int c_size=ceil(Tors.size()*(pb/2));

	int counter=0;

	while(counter<c_size)
	{
		int failAt=rand()%totalTime;
		//cout<<failAt<<",";
		int index=rand()%Tors.size();
		Link* curSwitch=Tors[index];
		Tors[index]->resilience=2;
		prone_links.push_back(curSwitch);
		Tors[index]->failAt=failAt;
		Tors.erase(Tors.begin()+index);
		counter++;
	}

	counter=0;
	while(counter<b_size)
	{
		int failAt=rand()%totalTime;
		//cout<<failAt<<",";

		int index=rand()%Tors.size();
		Link* curSwitch=Tors[index];
		Tors[index]->resilience=1;
		prone_links.push_back(curSwitch);
		Tors[index]->failAt=failAt;
		Tors.erase(Tors.begin()+index);
		counter++;
	}


	counter=0;
	while(counter<a_size && Tors.size()!=0)
	{
		int failAt=rand()%totalTime;
		int index=rand()%Tors.size();
		Link* curSwitch=Tors[index];
		Tors[index]->resilience=0;
		Tors.erase(Tors.begin()+index);
		counter++;
	}

}

void Controller::counter(vector<Switch*> Tors)
{
	//cout<<"Size of device: " << Tors.size()<<endl;
	int zero_count=0;
	int one_count=0;
	int two_count=0;
	for(int i =0 ; i < Tors.size();i++)
	{
		if(Tors[i]->resilience==0)
			zero_count++;
		else if (Tors[i]->resilience==1)
			one_count++;
		else
			two_count++;
	}

	int sum=Tors.size();
	//cout<< "zero_count ratio: " << (float)zero_count/(float)sum <<endl;
	//cout<< "one_count ratio: " << (float)one_count/(float)sum <<endl;
	//cout<< "two_count ratio: " << (float)two_count/(float)sum <<endl;
	float one=(float)one_count/(float)sum;
	float two=(float)two_count/(float)sum;
	float diff= one -two;
	if(diff<0)
		diff=-diff;

	if(diff> 0.015)
		int x=1/0;
}


void Controller::counter(vector<Link*> Tors){

	int zero_count=0;
	int one_count=0;
	int two_count=0;
	for(int i =0 ; i < Tors.size();i++)
	{
		if(Tors[i]->resilience==0)
			zero_count++;
		else if (Tors[i]->resilience==1)
			one_count++;
		else
			two_count++;
	}

	int sum=Tors.size();
	//cout<< "zero_count ratio: " << (float)zero_count/(float)sum <<endl;
	//cout<< "one_count ratio: " << (float)one_count/(float)sum <<endl;
	//cout<< "two_count ratio: " << (float)two_count/(float)sum <<endl;

}



void Controller::assignResilience()
{
	//works for mochis filure model
	vector<Switch*> Tors = getAllTors();
	vector<Switch*> Aggrs = getAllAggrs();
	vector<Switch*> Cores = getAllCores();

	int factor=2;
	int k=1000;
	checkProb(Tors,0.039*k,factor);
	checkProb(Aggrs,0.07*k,factor);
	checkProb(Cores,0.02*k,factor);


	//TODO check this number for core prob

	vector<Link*> TorsL = getAllTorLinks();
	vector<Link*> AggrsL = getAllAggrLinks();
	vector<Link*> CoresL = getAllCoreLinks();
	
	checkProb(TorsL,0.054*k,factor);
	checkProb(AggrsL,0.054*k,factor);
	checkProb(CoresL,0.095*k,factor);

	vector<Link*> prone_copy=prone_links;
	int count=prone_copy.size()/2;
	int singles=count*.6;
	int doubles=count*.1;
	int triples=count*.1; 
	int tetra=count*.2; 


	for(int i=0;i<prone_copy.size();i++)
	{
		Link* curLink=prone_copy[i];
		if(curLink->resilience==1)
		{
			all_groups.push_back(new Group(curLink,1));
			prone_copy.erase(prone_copy.begin()+i);
			i--;
		}
	}

	int total=0;
	while(singles>0)
	{
		int index=rand()%prone_copy.size();
		Link* curLink=prone_copy[index];
		all_groups.push_back(new Group(curLink,2));
		prone_copy.erase(prone_copy.begin()+index);
		singles--;
		total++;
	}

	//cout<<"num of singles: "<<total<<endl;
	total=0;
	while(doubles>0)
	{
		int index=rand()%prone_copy.size();
		Link* curLink=prone_copy[index];
		Group* g=new Group(curLink,2);
		all_groups.push_back(g);
		prone_copy.erase(prone_copy.begin()+index);
		doubles--;
		index=rand()%prone_copy.size();
		curLink=prone_copy[index];
		g->insert(curLink);
		prone_copy.erase(prone_copy.begin()+index);
		doubles--;
		total++;

	}


	//cout<<"num of doubles: "<<total*2<<endl;
	total=0;

	while(triples>0)
	{
		int index=rand()%prone_copy.size();
		Link* curLink=prone_copy[index];
		Group* g=new Group(curLink,2);
		all_groups.push_back(g);
		prone_copy.erase(prone_copy.begin()+index);
		triples--;
		index=rand()%prone_copy.size();
		curLink=prone_copy[index];
		g->insert(curLink);
		prone_copy.erase(prone_copy.begin()+index);
		triples--;	
		index=rand()%prone_copy.size();
		curLink=prone_copy[index];
		g->insert(curLink);
		prone_copy.erase(prone_copy.begin()+index);
		triples--;	
		total++;
	}


	//cout<<"num of triples: "<<total*3<<endl;
	total=0;
	while(tetra>0)
	{
		int index=rand()%prone_copy.size();
		Link* curLink=prone_copy[index];
		Group* g=new Group(curLink,2);
		all_groups.push_back(g);
		prone_copy.erase(prone_copy.begin()+index);
		tetra--;
		if(prone_copy.size()==0)
			break;
		index=rand()%prone_copy.size();
		curLink=prone_copy[index];
		g->insert(curLink);
		prone_copy.erase(prone_copy.begin()+index);
		tetra--;	
		if(prone_copy.size()==0)
			break;
		index=rand()%prone_copy.size();
		curLink=prone_copy[index];
		g->insert(curLink);
		prone_copy.erase(prone_copy.begin()+index);
		if(prone_copy.size()==0)
			break;
		tetra--;	
		index=rand()%prone_copy.size();
		curLink=prone_copy[index];
		g->insert(curLink);
		prone_copy.erase(prone_copy.begin()+index);
		tetra--;	
		total++;

	}


	//cout<<"num of tetra: "<<total*4<<endl;
	total=0;
	//cout<<"Total left: "<<prone_copy.size()<<endl;
	//cout<<count<<" "<<singles<<" "<<doubles<<" "<<triples<<" "<<tetra<<endl;
//***Printing for debugging purposes
	//cout<< "TORs" <<endl;
	counter(Tors);
	//cout<< "Aggr" <<endl;
	counter(Aggrs);
	//cout<< "Cores" <<endl;
	counter(Cores);
	//cout<< "TorsL" <<endl;
	counter(TorsL);
	//cout<< "AggrsL" <<endl;
	counter(AggrsL);
	//cout<< "CoresL" <<endl;
	counter(CoresL);

}



vector<Switch*> Controller::getAllTors()
{
	vector<Switch*> TORs;
	for (int i=0; i<all_switches.size();i++)
	{
		if(all_switches[i]->level == 2)
			TORs.push_back(all_switches[i]);

	}
	return TORs;
}

vector<Switch*> Controller::getAllAggrs()
{
	vector<Switch*> aggrs;
	for (int i=0; i<all_switches.size();i++)
	{
		if(all_switches[i]->level == 1)
			aggrs.push_back(all_switches[i]);

	}
	return aggrs;
}

vector<Switch*> Controller::getAllCores()
{
	vector<Switch*> cores;
	for (int i=0; i<all_switches.size();i++)
	{
		if(all_switches[i]->level == 0)
		{
			cores.push_back(all_switches[i]);
			// //cout<< "I'm  meeting" << endl;
		}
	}
	return cores;
}

vector<Link*> Controller::getAllCoreLinks()
{
	vector<Link*> cores;
	for (int i=0; i<all_links.size();i++)
	{
		if(all_links[i]->label == "Core")
			cores.push_back(all_links[i]);

	}
	return cores;
}

vector<Link*> Controller::getAllAggrLinks()
{
	vector<Link*> aggrs;
	for (int i=0; i<all_links.size();i++)
	{
		if(all_links[i]->label == "Aggr")
			aggrs.push_back(all_links[i]);
	}
	return aggrs;
}

vector<Link*> Controller::getAllTorLinks()
{
	vector<Link*> tors;
	for (int i=0; i<all_links.size();i++)
	{
		if(all_links[i]->label == "Tor")
			tors.push_back(all_links[i]);
	}
	return tors;
}


vector<Flow*> Controller::getCommonFlows(vector<Flow*> u,vector<Flow*> d)
{
	vector<Flow*> flows;
	int* arr =  new int(all_flows.size());

	for(int i=0;i<all_flows.size();i++)
	{
		arr[i]=0;
	}

	for (int i=0;i<u.size();i++)
	{
		arr[u[i]->flow_id]+=1;
	}

	for (int i=0;i<d.size();i++)
	{
		int h=d[i]->flow_id;
		int val=arr[h];
		if(val>0 && val < 2)
		{
			flows.push_back(d[i]);
			arr[h]+=1;
		}
		// if(val>2)
		// 	cout<<"ERROR,Collision-------------------------"<<endl;
	}
	return flows;

	// sort(u.begin(), u.end());
	// sort(d.begin(), d.end());
	// vector<Flow*> flows;
	// set_intersection(u.begin(), u.end(), d.begin(), d.end(), back_inserter(flows));
	// for (int i=0;i<u.size();i++)
	// {
	// 	for(int j=0;j<d.size();j++)
	// 	{
	// 		if(u[i]==d[j])
	// 		{
	// 			flows.push_back(u[i]);
	// 		}
	// 	}
	// }
	return flows;
}


bool Controller::duplicateIn(vector<Flow*> v)
{
	for(int i=0;i<v.size();i++)
	{
		for(int j=i+1;j<v.size();j++)
		{
			if(v[i]==v[j])
			{
				return true;
			}
		}
	}
	return false;
}


bool Controller::duplicateIn(vector<Switch*> v)
{
	for(int i=0;i<v.size();i++)
	{
		for(int j=i+1;j<v.size();j++)
		{
			if(v[i]==v[j])
			{
				return true;
			}
		}
	}
	return false;
}


bool Controller::duplicateIn(vector<Link*> v)
{
	for(int i=0;i<v.size();i++)
	{
		for(int j=i+1;j<v.size();j++)
		{
			if(v[i]==v[j])
			{
				return true;
			}
		}
	}
	return false;
}



bool notIn(vector<Switch*> v,Switch* e)
{
	for (int i=0;i<v.size();i++)
	{
		if(e==v[i])
			return false;
	}
	return true;
}

bool notIn(vector<Link*> v,Link* e)
{
	for (int i=0;i<v.size();i++)
	{
		if(e==v[i])
			return false;
	}
	return true;
}

bool notIn(vector<Flow*> v,Flow* e)
{
	for (int i=0;i<v.size();i++)
	{
		if(e==v[i])
			return false;
	}
	return true;
}


bool notIn(vector<Path*> v,Path* e)
{
	for (int i=0;i<v.size();i++)
	{
		if(e==v[i])
			return false;
	}
	return true;
}


void Controller::findFaults()
{
	//////startTimer();
	int len = prone_switches.size();
	for(int i=0; i<len; i++)
	{
		if( prone_switches[i]->getStatus() < 0 )
		{
			vector<Flow*> flows_primary=prone_switches[i]->getFlowsOnPrimary();
			vector<Flow*> flows_back=prone_switches[i]->getFlowsOnBack();
			// cout<<flows_back.size()<<" are the flows on back"<<endl;
			// if(duplicateIn(flows_primary) || duplicateIn(flows_back))
			// {
			// 	int x=1/0;
			// }

			if(flows_primary.size()>0 || flows_back.size()>0)
			{

				if(notIn(critical_switches,prone_switches[i]))
				{
					//cout <<"+ Critical Switch Failed with ID: "<<prone_switches[i]->toString()<<" For "<<prone_switches[i]->status<<endl;
					critical_switches.push_back(prone_switches[i]);					
				}
 			}

			for(int j=0;j<flows_primary.size();j++)
			{
				// cout<<"anti commiting 2"<<endl;
				flows_primary[j]->antiCommitPath(flows_primary[j]->primaryPath);
				if(backUp)
				{
					// cout<<"commiting on backup"<<endl;
//major implementation
					
					bool check = makeBackUp(flows_primary[j], flows_primary[j]->rate);
					if (check) {
						//cout << "backup found" << endl;
					} else {
						cout << "backup path not found" << endl;
					}
					
					//for(int k =0; k<flows_primary[j]->backUpPath.size();k++){
					//	if(flows_primary[j]->backUpPath[k]->isValid(flows_primary[j]->rate)) {
					//		
					//		commit=flows_primary[j]->commitPathAndReserve(flows_primary[j]->backUpPath[k],1);
					//	}
					//	if(commit)
					//		break;
					//}
					
					// cout<<"Primary Down: flow id: "<<flows_primary[j]->flow_id<<" ";
					// flows_primary[j]->primaryPath->print();

					if(check)
					{
						// cout<<"Going To Backup: flow id : "<< flows_primary[j]->flow_id<<" ";
						// flows_primary[j]->backUpPath->print();
						flows_on_back.push_back(flows_primary[j]);
						// cout<<"But Commit success, put on backup flows"<<endl;
					}
					else
					{
						// cout<<"Going Down the Backup is already down: flow id: "<<flows_primary[j]->flow_id<<" ";
						// flows_primary[j]->backUpPath->print();
						// if(!notIn(flows_down,flows_primary[j]))
						// {
						// 	int x=1/0;
						// }
						
						
						//add code here too
						flows_down.push_back(flows_primary[j]);

						// cout<<"And Commit Failed, put on down flows"<<endl;
						
					}
				}
				else
				{
					// if(!notIn(flows_down,flows_primary[j]))
					// {
					// 	int x=1/0;
					// }
					flows_down.push_back(flows_primary[j]);
				}
			}

			if(backUp)	
			{
				for(int j=0;j<flows_back.size();j++)
				{
					int index_of_backupPath=0;
					for(int l=0;l<flows_back[j]->backUpPath.size();l++)
					{
							vector<Switch*> switches=flows_back[j]->backUpPath[l]->getSwitches();
							for(int m=0;m<switches.size();m++)
							{
								if(switches[m]==prone_switches[i])
								{
									index_of_backupPath=l;
									break;
								}
									
							}
								
					}
					
					int anti_rate = flows_back[j]->antiCommitPathAndUnreserve(flows_back[j]->backUpPath[index_of_backupPath]);
					
					if (flows_back[j]->backUpPath.size() != 0)
						cout << "error = backup path size not 0" << endl;
					
					bool check = makeBackUp(flows_back[j], anti_rate);
					if (check) {
						//cout << "backup found" << endl;
					} else {
						flows_down.push_back(flows_back[j]);
						cout << "backup path not found" << endl;
					}
					
					//int commit=0;
					//for(int k =0; k<flows_back[j]->backUpPath.size();k++)
					//{
					//	if(flows_back[j]->backUpPath[k]->isValid(flows_back[j]->getBackUpRate())) {
					//		if (flows_back[j]->backUpPath[k]->isValid(flows_back[j]->getBackUpRate()))
					//			commit=flows_back[j]->commitPath(flows_back[j]->backUpPath[k],1);
					//	}
					//			if(commit)
					//				break;
					//}
					
				}				
			}


		}
	}
	//************For Links******************//

	len = prone_links.size();
	for(int i=0; i<len; i++)
	{
		if( prone_links[i]->getStatus() < 0 )
		{
			vector<Flow*> flows_primary=prone_links[i]->getFlowsOnPrimary();
			vector<Flow*> flows_back=prone_links[i]->getFlowsOnBack();


			// if(duplicateIn(flows_primary) || duplicateIn(flows_back))
			// {
			// 	int x=1/0;
			// }


			if(flows_primary.size()>0 || flows_back.size()>0)
			{

				if(notIn(critical_links,prone_links[i]))
				{
					//cout <<"+ Critical Link Failed with ID: "<<prone_links[i]->link_id<<" For "<<prone_links[i]->status<<" Seconds "<<endl;
					critical_links.push_back(prone_links[i]);
				}
				else
				{
					continue;
				}
 			}

			for(int j=0;j<flows_primary.size();j++)
			{
				// cout<<"anti commiting 2"<<endl;
				flows_primary[j]->antiCommitPath(flows_primary[j]->primaryPath);
				// cout<<"Primary Down: flow id: "<<flows_primary[j]->flow_id<<" ";
				// flows_primary[j]->primaryPath->print();
				// cout<<"culprit is: "<<prone_links[i]->link_id<<endl;
				if(backUp)
				{
					// cout<<"commiting on backup"<<endl;
					
					bool check = makeBackUp(flows_primary[j], flows_primary[j]->rate);
					if (check) {
						//cout << "backup found" << endl;
					} else {
						cout << "backup path not found" << endl;
					}
					
					//int commit =0;
					//for(int k =0; k<flows_primary[j]->backUpPath.size();k++){
					//	if(flows_primary[j]->backUpPath[k]->isValid(flows_primary[j]->getBackUpRate()))
					//			commit=flows_primary[j]->commitPath(flows_primary[j]->backUpPath[k],1);
					//			if(commit)
					//				break;
					//	}

					if(check)
					{
						// cout<<"Going To Backup: flow id : "<< flows_primary[j]->flow_id<<" ";
						// flows_primary[j]->backUpPath->print();
						flows_on_back.push_back(flows_primary[j]);

						 // cout<<"Commit success, put on backup flows"<<endl;
					}
					else
					{
						// cout<<"Going Down the Backup is already down: flow id: "<<flows_primary[j]->flow_id<<" ";
						// flows_primary[j]->backUpPath->print();

						// if(!notIn(flows_down,flows_primary[j]))
						// {

						// 	// flows_primary[j]->primaryPath->print();
						// 	// flows_primary[j]->backUpPath->print();
						// 	int x=1/0;
						// }

						flows_down.push_back(flows_primary[j]);
						// cout<<"Mayday: "<<endl;
						// flows_primary[j]->primaryPath->print();
						// flows_primary[j]->backUpPath->print();
						 // cout<<"Commit Failed, put on down flows"<<endl;
					}
				}
				else
				{
					flows_down.push_back(flows_primary[j]);
				}
			}


			if(backUp)
			{
				for(int j=0;j<flows_back.size();j++)
				{
					
					//int index_of_backupPath=0;
					//for(int l=0;l<flows_back[j]->backUpPath.size();l++)
					//{
					//	vector<Switch*> switches=flows_back[j]->backUpPath[l]->getSwitches();
					//	for(int m=0;m<switches.size();m++)
					//	{
					//		if(switches[m]==prone_switches[i])
					//		{
					//			index_of_backupPath=l;
					//			break;
					//		}
					//		
					//	}
					//	
					//}
					
					int anti_rate = flows_back[j]->antiCommitPathAndUnreserve(flows_back[j]->backUpPath[0]);
					
					if (flows_back[j]->backUpPath.size() != 0)
						cout << "error = backup path size not 0" << endl;
					
					
					bool check = makeBackUp(flows_back[j], anti_rate);
					if (check) {
						//cout << "backup found" << endl;
					} else {
						cout << "backup path not found" << endl;
						flows_down.push_back(flows_back[j]);
					}
					
					//int commit=0;
					//for(int k =0; k<flows_back[j]->backUpPath.size();k++)
					//{
					//	if(flows_back[j]->backUpPath[k]->isValid(flows_back[j]->rate)) {
					//		if (flows_back[j]->backUpPath[k]->isValid(flows_back[j]->getBackUpRate()))
					//			commit=flows_back[j]->commitPath(flows_back[j]->backUpPath[k],1);
					//	}
					//			if(commit)
					//				break;
					//	}
								
				}	
			}
		
		}
	}

	// cout<<"Num of flows down: "<<flows_down.size()<<endl;
}


void Controller::revert_to_primary()
{
	//////startTimer();
	bool revert=false;
	for(int i=0;i<critical_switches.size();i++)
	{
		if(critical_switches[i]->status >= 0)
		{
			//cout<<downTime<<" is the new downtime"<<endl;
			//cout<<backup<<" is the new down due to sharing"<<endl;
			//cout<<"+ Critical Switch Back with ID :"<<critical_switches[i]->toString()<<endl;
			critical_switches.erase(critical_switches.begin()+i);
			i--;
			revert=true;
			// if(duplicateIn(critical_switches))
			// {
			// 	//cout<<"++++++++ ERROR, DUPLICATES IN CRITICAL SWITCHES"<<endl;
			// }
		}
	}
	//////stopTimer("for switches to revert");
	//////startTimer();

	for(int i=0;i<critical_links.size();i++)
	{
		if(critical_links[i]->status >= 0)
		{
			//cout<<downTime<<" is the new downtime"<<endl;
			//cout<<backup<<" is the new down due to sharing"<<endl;

			//cout<<"+ Critical Link Back with ID :"<<critical_links[i]->link_id<<endl;
			critical_links.erase(critical_links.begin()+i);
			i--;
			// if(duplicateIn(critical_links))
			// {
			// 	cout<<"++++++++ ERROR, DUPLICATES IN CRITICAL LINKS"<<endl;
			// }
			revert=true;
		}
	}

	//////stopTimer("for links to revert");
	if(backUp && revert)
	{
		for (int i=0;i<flows_on_back.size();i++)
		{
			Flow* f=flows_on_back[i];
			// if(f->down!=1)
			// 	continue;
			if(f->primaryPath->isUp())
			{
				for (int j =0 ; j < f->backUpPath.size();j++) {
					int count = 0;
					if (f->backUpPath[j]->beingUsed == 1) {
						f->antiCommitPathAndUnreserve(f->backUpPath[j]);
						count++;
					}
					if (count >= 2)
						int x = 1/0;
				}
				bool check=f->commitPath(f->primaryPath,0); //Assumption is that link capacity would not be a bottleneck
				if(!check)
				{
					int x=1/0;
				}
				flows_on_back.erase(flows_on_back.begin()+i);
				i--;
				// cout<<"-- Num of flows on backup are: "<<flows_on_back.size()<<endl;
			}
		}
	}
	
	// gohar
	// check again for backup paths here, backup path can be up
	if(revert)
	{
		for (int i=0;i<flows_down.size();i++)
		{
			Flow* f=flows_down[i];
			// if(f->down!=1)
			// 	continue;
			bool check=f->primaryPath->isUp();
			if(check)
			{
				f->commitPath(f->primaryPath,0); //Assumption is that link capacity would not be a bottleneck
				flows_down.erase(flows_down.begin()+i);
				i--;
				// cout<<"revert to primary from down: flow_id: "<<f->flow_id<<" ";
				// f->primaryPath->print(); 
				// cout<<"-- Num of flows down: "<<flows_down.size()<<endl;
				continue;
			}

			if(backUp)
			{
				int index=-1;
				for(int j =0; j < f->backUpPath.size();j++){
						if(f->backUpPath[j]->isUp())
							index=j;
				}
				
				if(index!=-1)
				{
					if (f->backUpPath[index]->isValid(f->getBackUpRate()))
						f->commitPath(f->backUpPath[index],1); //Assumption is that link capacity would not be a bottleneck
					// cout<<"I am here here----------------------------------------------"<<endl;
					// cout<<"revert to backup from down: flow id: "<<f->flow_id<<" ";
					// f->backUpPath->print(); 
					flows_down.erase(flows_down.begin()+i);
					i--;

					flows_on_back.push_back(f);
					// cout<<"-- Num of flows down: "<<flows_down.size()<<endl;
				}
			}
		}
	}
}

void Controller::detect_downTime()
{
	
	downTime+=flows_down.size();
	
//	if(backUp && sharing)
//	{
////		// cout<<"Num of flows on backup are "<<flows_on_back.size()<<endl;
//		for(int i=0;i<flows_on_back.size();i++)
//		{
//			for (int j=i+1;j<flows_on_back.size();j++)
//			{
//				Flow* f1=flows_on_back[i];
//				Flow* f2=flows_on_back[j];
////Rufy: This looks wrong
//				if(f1!=f2 && f1->backUpPath==f2->backUpPath)// && f1->on_back && f2->on_back)
//				{
//					
//					downTime+=1;
//					backup+=1;
//					
//				}
//			}
//		}
// }


	// cout<<"downtime+= "<<flows_down.size() <<endl;

}

int Controller::getTTR(Switch* curSwitch)
{
	int random;
	if(curSwitch->level==2)//TOR
	{
		random=rand()%100;
		if(random < 40)
		{
			return 100+rand()%(5*60-100);
		}
		if(random < 50)
		{
			return 300+rand()%(1200-300);
		}
		if(random < 80)
		{
			return 1200+rand()%(60*60-1200);
		}

		if(random < 90)
		{
			return 3600+rand()%(10000-3600);
		}

		if(random < 98)
		{
			return 10000+rand()%(24*60*60-10000);
		}

		if(random < 100)
		{
			return 24*3600+rand()%(7*24*60*60-24*60*60);
		}		
	}

	if(curSwitch->level==1)//AGGR
	{
		random=rand()%100;
		if(random < 20)
		{
			return 100+rand()%(5*60-100);
		}
		if(random < 80)
		{
			return 300+rand()%(562-300);
		}

		if(random < 90)
		{
			return 300+rand()%(1000-30);
		}

		if(random < 97)
		{
			return 1000+rand()%(60*60-1000);
		}

		if(random < 100)
		{
			return 3600+rand()%(10000-3600);
		}	
	}


	// TODO. currently overall graph used for core 
	if(curSwitch->level==0)//CORE
	{
		random=rand()%100;
		if(random < 50)
		{
			return 100+rand()%(5*60-100);
		}
		if(random < 70)
		{
			return 300+rand()%(1000-300);
		}
		if(random < 100)
		{
			return 1000+rand()%(7*24*60*60-1000);
		}	
	}
}

int Controller::getTTR(Link* curSwitch)
{
		int random;
		random=rand()%100;
		if(random < 20)
		{
			return 100+rand()%(177-100);
		}

		if(random < 40)
		{
			return 177+rand()%(251-177);
		}

		if(random < 60)
		{
			return 251+rand()%(5*60-251);
		}

		if(random < 80)
		{
			return 251+rand()%(400-251);
		}
		if(random < 90)
		{
			return 251+rand()%(1000-251);
		}

		if(random < 95)
		{
			return 1000+rand()%(3600-1000);
		}


		if(random < 98)
		{
			return 3600+rand()%(24*60*60-3600);
		}

		if(random < 100)
		{
			return 24*60*60+rand()%(7*24*60*60-24*60*60);
		}
			
}


int Controller::getTTF(Switch* curSwitch)
{
	int random;
	if(curSwitch->level==2)//TOR
	{
		random=rand()%100;
		if(random < 8)
		{
			return 5+rand()%(5*60);
		}

		if(random < 20)
		{
			return 300+rand()%(1000-300);
		}

		if(random < 40)
		{
			return 1000+rand()%(60*60-1000);
		}

		if(random < 50)
		{
			return 1000+rand()%(17782-1000);
		}

		if(random < 60)
		{
			return 17782+rand()%(24*60*60-17782);
		}


		if(random < 70)
		{
			return 24*60*60+rand()%(316227-24*60*60);
		}		


		if(random < 80)
		{
			return 316227+rand()%(7*24*60*60-316227);
		}		
		

		if(random < 90)
		{
			return 7*24*60*60+rand()%(1995262-7*24*60*60);
		}

		if(random < 100)
		{
			return 1995262+rand()%(10000000-1995262);
		}		
	}

	if(curSwitch->level==1)//AGGR
	{
		random=rand()%100;
		if(random < 2)
		{
			return 5+rand()%(100);
		}
		if(random < 30)
		{
			return 100+rand()%(300-100);
		}

		if(random < 40)
		{
			return 300+rand()%(60*60-300);
		}
	
		if(random < 65)
		{
			return 3600+rand()%(24*60*60-3600);
		}
	
		if(random < 82)
		{
			return 24*60*60+rand()%(7*24*60*60-3600);
		}
	
		if(random < 100)
		{
			return 7*24*60*60+rand()%(3162277-7*24*60*60);
		}	
	}


	// TODO. currently overall graph used for core 
	if(curSwitch->level==0)//CORE
	{
		random=rand()%100;
		if(random < 2)
		{
			return 5+rand()%(100);
		}

		if(random < 45)
		{
			return 100+rand()%(1000-100);
		}
		if(random < 70)
		{
			return 1000+rand()%(60*60-1000);
		}
		if(random < 100)
		{
			return 60*60+rand()%(10000000-60*60);
		}	
	}

}

int Controller::getTTF(Link* curSwitch)
{
    int random;
	if(curSwitch->label=="Tor" || curSwitch->label=="Aggr")// TOR and aggr
	{
		random=rand()%100;
		if(random < 20)
		{
			return 100+rand()%(5*60-100);
		}
		if(random < 40)
		{
			return 300+rand()%(1000-300);
		}
		if(random < 60)
		{
			return 1000+rand()%(60*60-1000);
		}
		if(random < 70)
		{
			return 3600+rand()%(50118-3600);
		}
		if(random < 82)
		{
			return 50118+rand()%(7*24*60*60-50118);
		}
		if(random < 91)
		{
			return 50118+rand()%(1995262-50118);
		}
		if(random < 100)
		{
			return 1995262+rand()%(7000000-1995262);
		}
	}

	if(curSwitch->label=="Core")//Core
	{
		random=rand()%100;
		if(random < 20)
		{
			return 100+rand()%(300-100);
		}
		if(random < 40)
		{
			return 300+rand()%(60*60-300);
		}
		if(random < 63)
		{
			return 60*60+rand()%(24*60*60-60*60);
		}	

		if(random < 67)
		{
			return 24*60*60+rand()%(7*24*60*60-24*60*60);
		}	

		if(random < 80)
		{
			return 7*24*60*60+rand()%(1000000-7*24*60*60);
		}	

		if(random < 90)
		{
			return 7*24*60*60+rand()%(3162277-7*24*60*60);
		}	

		if(random < 100)
		{
			return 3162277+rand()%(10000000-3162277);
		}	

	}
}


Link* Controller::getMinLink(int thresh)
{
	Link* myLink;
	int min_status=10000000;
	for(int i=0;i<prone_links.size();i++)
	{
		Link* curLink=prone_links[i];
		if(curLink->resilience==2 && curLink->status > 0 && curLink->status < min_status && curLink-> status > thresh)
		{
			min_status=curLink->status;
			myLink=curLink;
		}
	}
	return myLink;
}

vector<Link*> Controller::getFailingLink(int num)
{
	vector<Link*> v;
	v.push_back(getMinLink(0));
	if(num == 2)
	{
		v.push_back(getMinLink(v[0]->status));
	}
	if(num == 3)
	{
		v.push_back(getMinLink(v[1]->status));
	}
	return v;
}



void Controller::updateStatus(int curSec, int factor)
{
	for(int i=0;i<prone_switches.size();i++)
	{
		Switch* curSwitch=prone_switches[i];

		if(curSwitch->status==0 && curSwitch->resilience==2 && curSwitch->failAt<curSec)
		{
			int ttr=-getTTR(curSwitch);
			writeLog("Switch with id: "+curSwitch->toString()+" has become failure prone");
			curSwitch->status=ttr;
			//TODO check this with dr ihsan ,dr fahad and dr zartash, how to induce first failure
			return;
		}


		if(curSwitch->resilience==1 && curSwitch->status == 0 &&  curSwitch->failAt<curSec)
		{
			// cout<<"++ Failed at res=1"<<endl;
			curSwitch->status=-getTTR(curSwitch);
			return;
		}

		if(curSwitch->status < 0)
		{
			curSwitch->status+=factor;

			if(curSwitch->resilience == 1 && curSwitch->status > -factor)
			{
				curSwitch->status=factor;
			}

			if(curSwitch->resilience == 2 && curSwitch->status > -factor)
			{
				curSwitch->status=getTTF(curSwitch);
			}
			return;
		}

		if(curSwitch->resilience == 2 && curSwitch->status > 0)
		{
			curSwitch->status-=factor;
			if(curSwitch->status < factor)
			{
				curSwitch->status=-getTTR(curSwitch);
				
			}
		}
	}
}


void Controller::updateStatusLink(int curSec, int factor)
{
	// cout<<"CurSec: "<<curSec<<endl;
	for(int i=0;i<all_groups.size();i++)
	{
		Group* curGroup=all_groups[i];

		if(curGroup->getStatus()==0 && curGroup->resilience==2 && curGroup->getFailAt()<curSec)
		{
			int id=curGroup->leader->link_id;
			stringstream o;
			o<<id;
			string idd=o.str();
			writeLog("Group with leader: Link with id: "+idd+" has become failure prone");
			int ttr=-getTTR(curGroup->leader);
			curGroup->setStatus(ttr);
			//TODO check this with dr ihsan ,dr fahad and dr zartash, how to induce first failure
			return;
		}

		// if(curGroup->resilience==1 && curGroup->status == 0 &&  curGroup->failAt<curSec)
		// {
		// 	cout<<"Scheduled to fail at: "<<curGroup->failAt<<endl;
		// 	int x=1/0;
		// }


		if(curGroup->resilience==1 && curGroup->getStatus() == 0 &&  curGroup->getFailAt() < curSec)
		{
			// cout<<"++ Failed at res=1"<<endl;
			curGroup->setStatus(-getTTR(curGroup->leader));
			// int x=1/0;
			return;
		}

		if(curGroup->getStatus() < 0)
		{
			curGroup->addStatus(factor);

			if(curGroup->resilience == 1 && curGroup->getStatus() > -factor)
			{
				curGroup->leader->status=factor;
			}

			if(curGroup->resilience == 2 && curGroup->getStatus() > -factor)
			{
					int ttf=getTTF(curGroup->leader);
					curGroup->setStatus(ttf);
			}
			return;
		}

		if(curGroup->resilience == 2 && curGroup->getStatus() > 0)
		{
			curGroup->addStatus(-factor);
			if(curGroup->getStatus() < factor)
			{
				curGroup->setStatus(-getTTR(curGroup->leader));
			}
		}
	}
}
void Controller::autofail(int curSec)
{
	// This function needs to be rewritten, from insights from philipa gill

	int factor=10;


	// startTimer();
	detect_downTime();
	// stopTimer("detect_downTime");

	if(curSec%10==0)
	{



	// startTimer();
	updateStatus(curSec,factor);
	// stopTimer("updateStatus 1");

	// startTimer();
	updateStatusLink(curSec,factor);
	// stopTimer("updateStatus 2");

	if(curSec%100==0)
	{
		// startTimer();
		revert_to_primary();
		// stopTimer("revert_to_primary");

		// startTimer();
		findFaults();
		// stopTimer("find faults");

		// startTimer();
		logFailures(curSec);
		// stopTimer("log failures");
	}
	//TODO plot the cdfs to verify the sampling
	}
}

void Controller::getIntraPodPaths(Switch* src, Switch* dst, Link* destLink, vector<Switch*> switches,vector<Link*> links, vector<bool> directions, int dir)
{
	// cout<<paths.size()<<" is the num of paths found "<<endl;
	vector<Link*> poolToVisit;
	int size=paths.size();
	// if(size>5)
	// 	return;

	if(src==NULL || dst==NULL)
	{
		cout<<"moving back; base case"<<endl;
		return;
	}

	if(dir==1 && src->level!=1)
	{
			poolToVisit=src->up_links;
	}
	else
	{
		poolToVisit=src->down_links;
	}
	for(int i=0;i<poolToVisit.size();i++)
	{
		Link* curLink=poolToVisit[i];
		if(curLink->label=="Tor")
			continue;
		Switch* curDst=curLink->getOtherNode(src);
		if(curDst==NULL)
		{
			switches.pop_back();
			links.pop_back();
			directions.pop_back();
			return;
		}
		if(curDst->num_ports==0)
		{
			cout<<"culprit link: "<<curLink->label<<endl;
		}

		if(dir==0 && src->level==1)
		{
			int id=curDst->getPodID();
			if(id!=dst->getPodID())
				continue;
		}
		switches.push_back(curDst);
		links.push_back(curLink);
		directions.push_back(dir);

		if(curDst->level==1)
		{
			if(dir==0)
				dir=1;
			else
				dir=0;
		}

		if(curDst==dst)
		{
			links.push_back(destLink);
			directions.push_back(dir);
			Path* p= new Path(switches,links,directions);
			paths.push_back(p);
		}

		getIntraPodPaths(curDst,dst,destLink,switches,links,directions,dir);
		links.pop_back();
		directions.pop_back();
		if(switches.back()->level==1)
		{
			if(dir==0)
				dir=1;
			else
				dir=0;	
		}	
		switches.pop_back();
	}
}

void Controller::getInterPodPaths(Switch* src, Switch* dst, Link* destLink, vector<Switch*> switches,vector<Link*> links, vector<bool> directions, int dir)
{
	// cout<<paths.size()<<" is the num of paths found "<<endl;
	vector<Link*> poolToVisit;
	int size=paths.size();
	// if(size>30)
		// return;

	if(src==NULL || dst==NULL)
	{
		cout<<"moving back; base case"<<endl;
		return;
	}

	//cout<<"SRC: "<<src->toString()<<"\nDST: "<< dst->toString()<<endl; 

	if(dir==1 && src->level!=0)
	{
		// cout<<src->toString()<<endl;
			// cout<<src->level<<endl;			
			// cout<<src->num_ports<<" are the ports"<<endl;			
			poolToVisit=src->up_links;
	}
	else
	{
		// cout<<src->level<<endl;			
		// cout<<src->down_links.size()<<endl;	
		// if(src->down_links.size()>k*k/4)
		// {
		// 	cout<<"ALARM"<<endl;
		// 	return;
		// }		
		// cout<<src->num_ports<<" are the ports"<<endl;			

		poolToVisit=src->down_links;
	}
	for(int i=0;i<poolToVisit.size();i++)
	{
		// int index=rand()%poolToVisit.size();
		Link* curLink=poolToVisit[i];
		//TODO randomization done here beware
		if(curLink->label=="Tor")
			continue;
		Switch* curDst=curLink->getOtherNode(src);
		if(curDst==NULL)
		{
			switches.pop_back();
			links.pop_back();
			directions.pop_back();
			return;
		}
		if(curDst->num_ports==0)
		{
			cout<<"culprit link: "<<curLink->label<<endl;
		}

		if(dir==0 && src->level==0)
		{
			int id=curDst->getPodID();
			if(id!=dst->getPodID())
				continue;
		}
		switches.push_back(curDst);
		links.push_back(curLink);
		directions.push_back(dir);

		if(curDst->level==0)
		{
			if(dir==0)
				dir=1;
			else
				dir=0;
		}

		if(curDst==dst)
		{
			links.push_back(destLink);
			directions.push_back(dir);
			Path* p= new Path(switches,links,directions);
			paths.push_back(p);
			// p->print();
			// cout<<"found path"<<endl;
		}
		// cout<<"calling rec"<<endl;
		// cout<<curDst->level<<" is the next level"<<endl;
		getInterPodPaths(curDst,dst,destLink,switches,links,directions,dir);
		links.pop_back();
		directions.pop_back();
		if(switches.back()->level==0)
		{
			if(dir==0)
				dir=1;
			else
				dir=0;	
		}	
		switches.pop_back();
	}

}

void Controller::filterPaths(int rate,Host* dest)
{
	for(int i=0;i<paths.size();i++)
	{
		Path* curPath=paths[i];
		// curPath->links.push_back(dest->link);
		// curPath->direction.push_back(0);
		if(!curPath->isValid(rate))
		{
			paths.erase(paths.begin()+i);
			i--;
			//TODO remove this erase

			continue;
		}
	}
}



void Controller::logFailures(int time)
{
	string t;
	stringstream out;
	out<<time;
	t=out.str();

	for(int i=0;i<down_switches.size();i++)
	{
		if(down_switches[i]->status > 1)
		{	

			int level=down_switches[i]->level;
			string l;
			if(level==0)
				l="Core";
			if(level==1)
				l="Aggr";
			if(level==2)
				l="Tor";
			
			stringstream o;
			int a=down_switches[i]->status;
			o<<a;
			string st=o.str();
			writeLog("Switch "+l+" "+down_switches[i]->toString()+" Up curTime: "+t+" upFor: "+st);
			down_switches.erase(down_switches.begin()+i);
			i--;
			//TODO check if this causes seg fault
		}
	}

	for(int i=0;i<down_links.size();i++)
	{
		if(down_links[i]->status > 1)
		{	
			stringstream o,oo;
			int idd=down_links[i]->link_id;
			o<<idd;
			string id=o.str();
			int a=down_links[i]->status;
			oo<<a;
			string st=oo.str();
			writeLog("Link "+down_links[i]->label+" "+ id+" Up curTime "+t+" upFor: "+st);
			down_links.erase(down_links.begin()+i);
			i--;
			//TODO check if this causes seg fault
		}
	}

	for(int i=0;i<prone_switches.size();i++)
	{
		if(prone_switches[i]->status < 0 && notIn(down_switches,prone_switches[i]))
		{	
			int level=prone_switches[i]->level;
			string l;
			if(level==0)
				l="Core";
			if(level==1)
				l="Aggr";
			if(level==2)
				l="Tor";
			stringstream o;
			stringstream oo;
			int a=prone_switches[i]->status;
			o<<a;
			string st=o.str();
			oo<<prone_switches[i]->resilience;
			string res=oo.str();
			writeLog("Switch "+l+" "+prone_switches[i]->toString()+" Down curTime: "+t+" downFor: "+st+" resLevel: "+res);
			down_switches.push_back(prone_switches[i]);
		}
	}

	for(int i=0;i<prone_links.size();i++)
	{
		if(prone_links[i]->status < 0 && notIn(down_links,prone_links[i]))
		{	
			stringstream o,oo,ooo;
			int idd=prone_links[i]->link_id;
			o<<idd;
			string id=o.str();
			int a=prone_links[i]->status;
			oo<<a;
			string st=oo.str();
			ooo<<prone_links[i]->resilience;
			string res=ooo.str();
			writeLog("Link "+prone_links[i]->label+" "+ id+" Down curTime: "+t+" downFor: "+st+" resLevel: "+res);
			down_links.push_back(prone_links[i]);
		}
	}
}

bool Controller::getPaths(Host* source, Host* dest, vector<Switch*> switches,vector<Link*> links, vector<bool> directions, int dir)
{
	switches.push_back(source->getTor());
	links.push_back(source->getLink());
	directions.push_back(1);

	Link* destLink = dest->getLink();
	Switch* src = source->getTor();
	Switch* dst = dest->getTor();

	bool intraRack = false;
	if(src == dst)		// the end hosts are under the same ToR switch
	{
		links.push_back(destLink);
		directions.push_back(0);
		Path* p= new Path(switches,links,directions);
		paths.push_back(p);
		intraRack = true;
	}
	else if(src->getPodID() == dst->getPodID())		// the end hosts are in the same pod
	{
		getIntraPodPaths(src, dst, destLink, switches, links, directions,1);
	}
	else				// the end hosts are in different pods
	{
		getInterPodPaths(src, dst, destLink, switches, links, directions,1);
	}

	return intraRack;
}

bool Controller::instantiateFlow(Host* source, Host* dest, double rate, int size,double sTime)	//rate in MBps, size in MB
{
	// if 'intraRack' is true, then there will be no backup path, only 1 path
	vector<Switch*> switches;
	vector<Link*> links;
	vector<bool> directions;
	bool intraRack = getPaths(source, dest, switches, links, directions, 1);

	// cout<<paths.size()<<" is the num of paths"<<endl;
	filterPaths(rate,dest);
	// check for only one path..n
	
	 if(intraRack && paths.size()!=1)
 	 {
 		int x=1/0;
 	 	return 0;
 	 }
	if(!intraRack && paths.size()<1)
	{
		paths.clear();
//		cout<<"ERROR: Request could not be entertained with Rate: "<<rate<<" Size: "<<size<<", Not enough Bandwith remaining on Candidate Paths"<<endl;

		return 0;
	}

//	cout << "Request Entertained: Rate: "<<rate<<" Size: "<<size<<endl;
	int ind=rand()%paths.size();
	Path* primary=paths[ind];
	paths.erase(paths.begin()+ind);
	// cout<<"Primary Path is: "<<endl;
	// primary->print();
	Path* back=NULL;
	vector<Path*> backups;



//	if(backUp)
//	{
//		if(end_to_end)
//		{
//			paths.clear();
//		}

//		backups=getBackUpPathVector(primary,rate);
 //		// cout<<"Backup Path is: "<<endl;
 //		// back->print();
 //		if(backups.size()==0)
 //		{
 ////			int x=1/0;
//		// cout<<"Backup Bandwidth not available"<<endl;
//			return 0;
//		}

 //		// if(sharing)
 //		// {
 //		// 	paths_to_be_shared.push_back(back);
 //		// }
//	}


	// TODO fix the error of multiple ppl sharing one pathF

	// if(duplicateIn(back->links))
	// 	back->print();

	Flow* flow= new Flow(source,dest,primary,backups,rate,size,oneToOne,sTime,sharing,tor_to_tor);
	flow->setID(flowNumber);
	all_flows.push_back(flow);
	flowNumber++;
	if(flowNumber%1000==0)
		cout<<flowNumber<<" is the num of flows committed"<<endl;
	paths.clear();
	// cout << "Flows generated ";
	return 1;
}

int getCommonCount(vector<Switch*> a,vector<Switch*> b)
{
	int count=0;
	for(int i=0;i<a.size();i++)
	{
		Switch* aCand=a[i];
		for(int j=i+1;j<b.size();j++)
		{
			Switch* bCand=b[i];
			if(aCand==bCand)
				count++;
		}
	}
	return count;
}

int getCommonCount(vector<Link*> a,vector<Link*> b)
{
	int count=0;
	for(int i=0;i<a.size();i++)
	{
		Link* aCand=a[i];
		for(int j=i+1;j<b.size();j++)
		{
			Link* bCand=b[i];
			if(aCand==bCand)
				count++;
		}
	}
	return count;
}

Host* Controller::getHostInTor(int id)
{
	while(true)
	{
		Host* h=all_hosts[rand()%all_hosts.size()];
		if(h->getPodID()==id)
		{
			return h;
		}
	}
}

Path* Controller::getReplicatedPath(int src, int dst, int rate)
{
	int srcPod=src;
	int dstPod=dst;
	while(srcPod==src || dstPod==dst || srcPod==dstPod)
	{
		srcPod=rand()%k;
		dstPod=rand()%k;
	}

	vector<Switch*> switches;
	vector<Link*> links;
	vector<bool> directions;
	// cout<<"src: "<<srcPod<<" dst: "<<dstPod<<endl;
	Host* source=getHostInTor(srcPod);
	Host* dest= getHostInTor(dstPod);

	bool intraRack = getPaths(source, dest, switches, links, directions, 1);
	filterPaths(rate,dest);
		if(paths.size()==0)
		{
			return 0;			
		}

	Path* back=paths[rand()%paths.size()];
	
	
	
	paths.clear();
	return back;
}

SprayData* Controller::getSprayPath(int src, int dst, int rate, Path* primary_path)
{
	int srcPod=src;
	int dstPod=dst;
	while(srcPod==src || dstPod==dst || srcPod==dstPod)
	{
		srcPod=rand()%k;
		dstPod=rand()%k;
	}

	vector<Switch*> switches;
	vector<Link*> links;
	vector<bool> directions;
	// cout<<"src: "<<srcPod<<" dst: "<<dstPod<<endl;
	Host* source=getHostInTor(srcPod);
	Host* dest= getHostInTor(dstPod);

	bool intraRack = getPaths(source, dest, switches, links, directions, 1);
	//filterPaths(rate,dest);
	
	if(paths.size()==0)
		return NULL;

	//Path* back = NULL;
	//int highestCount = 0;
	
	int sent = 0;
	vector<int> toReserve;
	
	for (int i = 0; i < paths.size(); i++)
		toReserve.push_back(0);
	
	while (sent != rate) {	
		for (int i = 0; i < paths.size(); i++) {
			if (paths[i]->isValid(1) && paths[i]->isUp() && sent != rate) {
				toReserve[i]++;
				sent++;
			}
		}
	}
	
	SprayData* sprayData = new SprayData();
	sprayData->toReserve = toReserve;
	sprayData->paths = paths;
	
	// find highest matching/overlapping path
	//for (int i = 0; i < paths.size(); i++) {
	//	if (!paths[i]->isUp())
	//		continue;
	//	
	//	int tempCount = getCommonCount(paths[i]->links, primary_path->links);
	//	if (tempCount > highestCount) {
	//		highestCount = tempCount;
	//		back = paths[i];
	//	}
	//}
	
	paths.clear();
	return sprayData;
}


vector <Path*> Controller::getReplicatedPathVector(int src, int dst, int rate)
{
	vector <Path*> empty;
	
	int srcPod=src;
	int dstPod=dst;
	while(srcPod==src || dstPod==dst || srcPod==dstPod)
	{
		srcPod=rand()%k;
		dstPod=rand()%k;
	}

	vector<Switch*> switches;
	vector<Link*> links;
	vector<bool> directions;
	// cout<<"src: "<<srcPod<<" dst: "<<dstPod<<endl;
	Host* source=getHostInTor(srcPod);
	Host* dest= getHostInTor(dstPod);

	bool intraRack = getPaths(source, dest, switches, links, directions, 1);
	filterPaths(rate,dest);
	if(paths.size()==0)
	{
		return empty;			
	}

	Path* back=paths[rand()%paths.size()];
	
	// fix this
	vector<Path*> fourPaths;
	for (int i=0; i < 4; i++) { // 4 is hardcoded here, can be changed
		
		if(paths.size()==0)
		{
			return fourPaths;	
		}
		
		int randNum = rand()%paths.size();
		Path* p1 = paths[randNum];
		fourPaths.push_back(p1);
		paths.erase(paths.begin() + randNum);
	}
	
//	paths.clear();
	return fourPaths;
}



vector <Path*> Controller::getBackUpPathVector(Path* primary, int rate)
{
	vector <Path*> empty;
	// check for NULL condition
	int overlap=1;
	Path* back=NULL;
	int index=0;
	vector <Path*> backups;

	if(sharing && end_to_end)
	{
		for (int j=0;j<all_pairs.size();j++)
		{
			Path* p1=primary;
			Pair* curPair=all_pairs[j];
			Path* otherPrimary=curPair->primary;
			Path* otherBack=curPair->back;
			if(otherBack!=NULL){
				if( !otherBack->isValid(rate/4)) //divided by 2 
					continue;
			}
			else{
				cout<<"@mochi:continuing getBackUpPath, this shouldn't happen "<<endl;
				continue;
			}
			vector<Switch*> primaryLinks=p1->switches;
			vector<Switch*> otherPrimaryLinks=otherPrimary->switches;
			vector<Switch*> otherBackLinks=otherBack->switches;
			int commonPrimary=getCommonCount(primaryLinks,otherPrimaryLinks);
			int commonBack=getCommonCount(primaryLinks,otherBackLinks);
			if(commonPrimary==0 && commonBack==0)
			{
				if(notIn(paths_to_be_shared,otherBack))
				{
					continue;						
				}

				flows_on_share++;
//				back=otherBack;
				backups.push_back(otherBack);
				if(backups.size() <= 4)
					continue;
				else
					break;
				
			}
		}	
	}

	overlap=10*k;

	if(backups.size()>0)
	{
		int index=0;
		for(int j=0;j<backups.size();j++)
		{
			for(int i=0;i<paths_to_be_shared.size();i++)
			{
				if(paths_to_be_shared[i]==backups[j])
				{
					index=i;
					break;
				}
			}
			paths_to_be_shared.erase(paths_to_be_shared.begin()+index);
			all_pairs.push_back(new Pair(primary,backups[j]));

		}
	}
	if(backups.size() < 4)
	{

		if(end_to_end)
		{
			int srcTor=primary->getSrcPod();
			int dstTor=primary->getDstPod();
			if(sharing)
				backups=getReplicatedPathVector(srcTor,dstTor,rate/4);
			else{
				back=getReplicatedPath(srcTor,dstTor,rate);				
			}
			if(backups.size()==0)
				return empty;
			int limit=0;
			if(backups.size()>4)
				limit = 4;
			else
				limit=backups.size();
			
			for(int i=0;i<limit;i++)
				all_pairs.push_back(new Pair(primary,backups[i]));

			
			if(sharing)
			{
				for(int i=0;i<limit;i++)
					paths_to_be_shared.push_back(backups[i]);
			}

		}
		
		if(tor_to_tor)
		{
			overlap=10*k;
			vector<Switch*> links=primary->switches;
        	for(int i=0;i<paths.size();i++)
        	{
            	Path* cand=paths[i];
            	vector<Switch*> otherLinks=cand->switches;
            	int common=getCommonCount(links,otherLinks);
            	if(common<overlap)
            	{
                	back=cand;
					if( !back->isValid(rate, tor_to_tor)) //divided by 2 
						continue;
                	overlap=common;
            	}
        	}
		}
		
	}
	return backups;
}

// finds disjoint primaries and pairs them
Path* Controller::getBackUpPath(Path* primary, int rate)
{
	// check for NULL condition
	int overlap=1;
	Path* back=NULL;
	int index=0;

	if(sharing && end_to_end)
	{
			for (int j=0;j<all_pairs.size();j++)
			{
				Path* p1=primary;
				Pair* curPair=all_pairs[j];
				Path* otherPrimary=curPair->primary;
				Path* otherBack=curPair->back;
				if(otherBack!=NULL){
					if( !otherBack->isValid(rate/4)) //divided by 2 
						continue;
				}
				else{
					cout<<"@mochi:continuing getBackUpPath, this shouldn't happen "<<endl;
					continue;
				}
				vector<Switch*> primaryLinks=p1->switches;
				vector<Switch*> otherPrimaryLinks=otherPrimary->switches;
				vector<Switch*> otherBackLinks=otherBack->switches;
				int commonPrimary=getCommonCount(primaryLinks,otherPrimaryLinks);
				int commonBack=getCommonCount(primaryLinks,otherBackLinks);
				if(commonPrimary==0 && commonBack==0)
				{
					if(notIn(paths_to_be_shared,otherBack))
					{
						continue;						
					}

					flows_on_share++;
					back=otherBack;
					break;
				}
			}	
	}

	overlap=10*k;

	if(back!=NULL)
	{
		int index=0;
		for(int i=0;i<paths_to_be_shared.size();i++)
		{
			if(paths_to_be_shared[i]==back)
			{
				index=i;
				break;
			}
		}
		paths_to_be_shared.erase(paths_to_be_shared.begin()+index);
		all_pairs.push_back(new Pair(primary,back));
	}
	else
	{

		if(end_to_end)
		{
			int srcTor=primary->getSrcPod();
			int dstTor=primary->getDstPod();
			if(sharing)
				back=getReplicatedPath(srcTor,dstTor,rate/4);
			else{
				back=getReplicatedPath(srcTor,dstTor,rate);				
			}
			if(back==NULL)
				return 0;	

			all_pairs.push_back(new Pair(primary,back));

			if(sharing)
			{
				paths_to_be_shared.push_back(back);
			}

		}
		
		if(tor_to_tor)
		{
			overlap=10*k;
			vector<Switch*> links=primary->switches;
        	for(int i=0;i<paths.size();i++)
        	{
            	Path* cand=paths[i];
            	vector<Switch*> otherLinks=cand->switches;
            	int common=getCommonCount(links,otherLinks);
            	if(common<overlap)
            	{
                	back=cand;
					if( !back->isValid(rate, tor_to_tor)) //divided by 2 
						continue;
                	overlap=common;
            	}
        	}
		}
		
	}
	return back;
}

void Controller::writeLog(string str)
{
	ofstream fout;
	fout.open("logs.txt",ios::app);
	fout<<str<<endl;
	fout.close();
}


//                    ************************ USEFUL CODE ENDS HERE *********************
void Controller::dumpData(long run_time)
{
	string str = "t: ";
	stringstream ss;
	ss << run_time;
	str = str + ss.str() + "\n";

	int len_cores = all_cores.size();
	for(int i=0; i<len_cores; i++)
	{
		stringstream pID, lev, dID;
		pID << all_cores[i]->getPodID();
		lev << all_cores[i]->getLevel();
		dID << all_cores[i]->getDeviceID();

		string stat = "";
		if(all_cores[i]->status >= 0)
			stat = "u";
		else
			stat = "d";

		str = str + "C: PodID:" + pID.str() + " Level:" + lev.str() + " DID:" + dID.str() + " Stat:" + stat + "\n";
	}

	int len_switches = prone_switches.size();
	for(int i=0; i<len_switches; i++)
	{
		stringstream pID, lev, dID;
		pID << prone_switches[i]->getPodID();
		lev << prone_switches[i]->getLevel();		
		dID << prone_switches[i]->getDeviceID();

		string stat = "";
		if(prone_switches[i]->status >= 0)
			stat = "u";
		else
			stat = "d";
		
		str = str + "S: PodID:" + pID.str() + " Level:" + lev.str() + " DID:" + dID.str() + " Stat:" + stat + "\n";
	}
	
	int len_links = prone_links.size();
	for(int i=0; i<len_links; i++)
	{
		stringstream id, upUtil, downUtil;
		id << prone_links[i]->getID();
		upUtil << prone_links[i]->getUsedUpBW();
		downUtil << prone_links[i]->getUsedDownBW();

		string stat = "";
		if(prone_links[i]->status >= 0)
			stat = "u";
		else
			stat = "d";

		str = str + "L: Label:" + prone_links[i]->getLabel() + " LID:" + id.str() + " UUtil:" + upUtil.str() + " DUtil:"+ downUtil.str() + " Stat:" + stat + "\n";
	}
/*
	string buff="Switches: ";
	for (int i=0;i<prone_switches.size();i++)
	{
		if(all_switches[i]->status < 0)
			buff+=" up";
		else
			buff+=" down";
	}

	buff+="\nLinks: ";
	for (int i=0;i<prone_links.size();i++)
	{
		if(prone_links[i]->status < 0)
			buff+=" up";
		else
			buff+=" down";
	}
*/
	ofstream fout;
	fout.open("logs.txt",ios::app);
//	fout<<"Time: "<<run_time<<"\n";
	fout<<str;
//	fout << buff;
	fout.close();
}
/*
void Controller::createFailure(bool object, int id)
{
	if(object)		// if "device"
	{
		failDevice(id);
	}
	else			//else "link"
	{
		failLink(id);
	}
}
*/
//need to check if modifications need to be made in paths



void Controller::assignPaths()									//primary + backups
{

}

/*
Path* getPathRandom(Host* src,Host* dst, double rate)
{
	Path* path= new Path();
	Switch* curSwitch=src->link->up_switch
	path->addLink(src->link);
	goToCore(path,curSwitch);
	goToPod(path,dst,&tempSwitch);
	Switch* dummyDst=dst->link->up_switch;
	goToSwitch(path,dummyDst,&tempSwitch);
	return path;
}


void goToPod(Path* path, Host* dst, Switch** tempSwitch)
{
	Address* add=dst->addr;curSwitch
	int podID=add->getPodID();
	vector<Link*> links=*(tempSwitch)->down_links;
	for(int i=0;i<links.size();i++)
	{
		Switch* curSwitch=links[i]->down_switch;
		if(curSwitch->getPodID==podID)
		{
			*tempSwitch=curSwitch;
			path->addSwitch(*(tempSwitch));
			path->addLink(links[i]);
			break;
		}
	}
}

void goToCore(Path* path,Switch** tempSwitch)
{
	while(*(tempSwitch)->level!=0)
	{
		path->addSwitch(*tempSwitch);
		int randInt=rand()%(*tempSwitch)->up_links.size();
		tempSwitch=*(tempSwitch)->up_links[randInt]->up_switch;
		path->addLink(*(tempSwitch)->up_links[randInt]);
	}
	path->addLink(NULL);
}

void goToSwitch(Path* path, Switch* dst, Switch** tempSwitch)
{
	vector<Switch*> downSwitches=*(tempSwitch)->getDownSwitches;
	for(int i=0;i<downSwitches.size();i++)
	{
		Switch* curSwitch=downSwitches[i];
		if(curSwitch==dst)
		{
			path.addSwitch(curSwitch);
			path.addLink(curSwitch->getLinkBetween(tempSwitch);
		}
	}
}

int commitPath(Path* path, int dur,int rate, int size)
{
	vector<Switch*> switches=path->getSwitches();
	for(int i=0;i<switches.size();i++)
	{
		switches[i]->addFlow();
	}
}
*/


/*
void Controller::uiFunc()
{
	int option = 0;

	while(1)
	{
		printf("Please select an operation: \n");
		printf("1) Create a Topology\n");
		printf("2) Fail Device\n");
		printf("3) Fail Link\n");
		printf("4)  Flows\n");

		cin>>option;

		if(option<0 || option>4)	//invalid option
		{
			printf("PLEASE INPUT A VALID OPTION! TRY AGAIN");
		}
		if(option == 1)		//create a topology
		{
			printf("Creating a topology\n");
			createTopology();
			printf("Topology finished\n");
		}
		if(option == 2)		//fail device
		{
			printf("Failing device...\n");
			failDevice();
			printf("Failed device\n");
		}
		if(otpion == 3)		//fail link
		{
			printf("Failing link\n");
			failLink();
			printf("Failed link\n");
		}
		if(option == 4)		// flow
		{
			printf("Creating paths\n");
			();
			printf("Assigned paths to flow\n");
		}
	}
}
*/

long int Controller::getTime()
{
	return t;
}


