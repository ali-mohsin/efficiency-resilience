#include "controller.h"
#include "flow.h"
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
	srand(time(0));
	k=kay;
	torCap=tor;
	aggrCap=aggr;
	coreCap=core;
	flowNumber = 0;
	createTopology(tor,aggr,core);
	backUp=back;
	sharing = share;
	backup=0;
	// TODO seperate variable for backup
	// TODO intra-rack communication, path assigned goes all the way round from core
	failures=0;
	totalTime=runFor;
	assignResilience();
	if(makeFlows)
	{
		createFlows();
	}





	for(int i=0;i<all_links.size();i++)
	{
		cout<<"Link with ID: "<<all_links[i]->link_id<<" has "<<all_links[i]->flows_primary.size()<<" Flows passing through"<<endl;

		if(all_links[i]->flows_primary.size()!=0 || all_links[i]->flows_back.size()!=0)
		{
			int a=0;
			// cout<<"Link with ID: "<<all_links[i]->link_id<<" has "<<all_links[i]->flows_primary.size()<<" Flows passing through"<<endl;
			// cout<<"Link with ID: "<<all_links[i]->link_id<<" has "<<all_links[i]->flows_back.size()<<" Flows passing through"<<endl;
		}
		// else
		// {
		// 	// cout<<"Link with ID: "<<all_links[i]->link_id<<" has "<<all_links[i]->flows.size()<<" Flows passing through"<<endl;
		// 	int x=1/0;
		// }
	}
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
	for (int i=0;i<all_switches.size();i++)
	{
		Switch* curSwitch=all_switches[i];
		if(curSwitch->level==2)
		{
			int pod=curSwitch->getPodID();
			for(int j=0;j<k*k/16;j++)
			{
				Switch* otherTor=getTorFromAnotherPod(pod);
				Host* start=curSwitch->down_links[rand()%curSwitch->down_links.size()]->host;
				Host* end=otherTor->down_links[rand()%curSwitch->down_links.size()]->host;
				// cout<<"Flow started from "<<curSwitch->toString()<<" to "<<otherTor->toString()<<endl;
				instantiateFlow(start,end,10,10,0);

			}	
		}
		// for (int j=0;j<all_hosts.size();j++)
		// {
		// 	if(all_hosts[i]->getPodID()!=all_hosts[j]->getPodID())
		// 		instantiateFlow(all_hosts[i],all_hosts[j],10,10,0);
		// }
	}
}

void Controller::checkProb(vector<Switch*> Tors, int prob, float factor)
{

	//TODO- assign classes B,C with equal number, small k not letting them be equal
	for (int i =0; i < Tors.size(); i++)
	{
		int random = rand()%(1000);
		if (random > prob)
			Tors[i]->resilience=0;
		else if (random > prob/factor)
		{
			int failAt=rand()%totalTime;
			Tors[i]->resilience=1;
			Tors[i]->failAt=failAt;
		}
		else 
		{
			int failAt=rand()%totalTime;
			Tors[i]->resilience=2;
			Tors[i]->failAt=failAt;

		}
	}
}



void Controller::checkProb(vector<Link*> Tors, int prob, float factor)
{
	int ones=0;
	int twos=0;
	cout<<"Size of links: " << Tors.size()<<endl;	
	for (int i =0; i < Tors.size(); i++)
	{
		cout<<ones<<" ones"<<endl;
		cout<<twos<<" twos"<<endl;
		int diff=ones-twos;
		int random = rand()%(1000);
		if (random > prob)
		{
			Tors[i]->resilience=0;
		}	
		else if (random > prob/factor && diff <= 1)
		{
			int failAt=rand()%totalTime;
			Tors[i]->failAt=failAt;
			Tors[i]->resilience=1;
			ones++;
		}
		else if(diff >= -1)
		{
			int failAt=rand()%totalTime;
			Tors[i]->failAt=failAt;
			Tors[i]->resilience=2;		
			twos++;
		}
		else
		{
			i--;
			continue;
		}


	}
}

void Controller::counter(vector<Switch*> Tors)
{
	cout<<"Size of device: " << Tors.size()<<endl;
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
	cout<< "zero_count ratio: " << (float)zero_count/(float)sum <<endl;
	cout<< "one_count ratio: " << (float)one_count/(float)sum <<endl;
	cout<< "two_count ratio: " << (float)two_count/(float)sum <<endl;
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
	cout<< "zero_count ratio: " << (float)zero_count/(float)sum <<endl;
	cout<< "one_count ratio: " << (float)one_count/(float)sum <<endl;
	cout<< "two_count ratio: " << (float)two_count/(float)sum <<endl;

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

//***Printing for debugging purposes
	cout<< "TORs" <<endl;
	counter(Tors);
	cout<< "Aggr" <<endl;
	counter(Aggrs);
	cout<< "Cores" <<endl;
	counter(Cores);
	cout<< "TorsL" <<endl;
	counter(TorsL);
	cout<< "AggrsL" <<endl;
	counter(AggrsL);
	cout<< "CoresL" <<endl;
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
			cout<< "I'm  meeting" << endl;
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
		if(val>2)
			cout<<"ERROR,Collision-------------------------"<<endl;
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


void Controller::findFaults()
{
	//////startTimer();
	int len = all_switches.size();
	for(int i=0; i<len; i++)
	{
		if( all_switches[i]->getStatus() < 0 )
		{
			vector<Flow*> flows_primary=all_switches[i]->getFlowsOnPrimary();
			vector<Flow*> flows_back=all_switches[i]->getFlowsOnBack();

			if(duplicateIn(flows_primary) || duplicateIn(flows_back))
			{
				int x=1/0;
			}

			if(flows_primary.size()>0 || flows_back.size()>0)
			{

				if(notIn(critical_switches,all_switches[i]))
				{
					cout <<"+ Critical Switch Failed with ID: "<<all_switches[i]->toString()<<" For "<<all_switches[i]->status<<endl;
					critical_switches.push_back(all_switches[i]);					
				}
 			}

			for(int j=0;j<flows_primary.size();j++)
			{
				// cout<<"anti commiting 2"<<endl;
				flows_primary[j]->antiCommitPath(flows_primary[j]->primaryPath);
				if(backUp)
				{
					// cout<<"commiting on backup"<<endl;

					int commit=flows_primary[j]->commitPath(flows_primary[j]->backUpPath,1);
					// cout<<"Primary Down: flow id: "<<flows_primary[j]->flow_id<<" ";
					// flows_primary[j]->primaryPath->print();

					if(commit)
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
						if(!notIn(flows_down,flows_primary[j]))
						{
							int x=1/0;
						}
						flows_down.push_back(flows_primary[j]);

						// cout<<"And Commit Failed, put on down flows"<<endl;
						
					}
				}
				else
				{
					if(!notIn(flows_down,flows_primary[j]))
					{
						int x=1/0;
					}
					flows_down.push_back(flows_primary[j]);
				}
			}


			for(int j=0;j<flows_back.size();j++)
			{
				// cout<<"Culprit is "<<all_switches[i]->toString()<<endl;
				// cout<<"Backup is going down, flow id: "<<flows_back[j]->flow_id<<" ";
				// flows_back[j]->backUpPath->print();
				if(backUp)
				{
					// cout<<"Path is now down"<<endl;
					if(!notIn(flows_down,flows_back[j]))
					{

						flows_back[j]->primaryPath->print();
						int x=1/0;
					}
					flows_back[j]->antiCommitPath(flows_back[j]->backUpPath);
					flows_down.push_back(flows_back[j]);
					continue;
				}
			}
		}
	}
	//************For Links******************//

	len = all_links.size();
	for(int i=0; i<len; i++)
	{
		if( all_links[i]->getStatus() < 0 )
		{
			vector<Flow*> flows_primary=all_links[i]->getFlowsOnPrimary();
			vector<Flow*> flows_back=all_links[i]->getFlowsOnBack();


			if(duplicateIn(flows_primary) || duplicateIn(flows_back))
			{
				int x=1/0;
			}


			if(flows_primary.size()>0 || flows_back.size()>0)
			{

				if(notIn(critical_links,all_links[i]))
				{
					cout <<"+ Critical Link Failed with ID: "<<all_links[i]->link_id<<" For "<<all_links[i]->status<<" Seconds "<<endl;
					critical_links.push_back(all_links[i]);
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
				// cout<<"culprit is: "<<all_links[i]->link_id<<endl;
				if(backUp)
				{
					// cout<<"commiting on backup"<<endl;
					int commit=flows_primary[j]->commitPath(flows_primary[j]->backUpPath,1);

					if(commit)
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

						if(!notIn(flows_down,flows_primary[j]))
						{

							// flows_primary[j]->primaryPath->print();
							// flows_primary[j]->backUpPath->print();
							int x=1/0;
						}

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


			for(int j=0;j<flows_back.size();j++)
			{
				if(backUp)
				{
					// cout<<"Culprit is "<<all_links[i]->link_id<<endl;
					// cout<<"Backup is go/ing down, flow id: "<<flows_back[j]->flow_id<<" ";
					// flows_back[j]->backUpPath->print();
					// cout<<"Was already back up, now its down"<<endl;
					if(!notIn(flows_down,flows_back[j]))
					{
						flows_back[j]->primaryPath->print();
						flows_back[j]->backUpPath->print();

						int x=1/0;
					}
					flows_back[j]->antiCommitPath(flows_back[j]->backUpPath);
					flows_down.push_back(flows_back[j]);
					continue;
				}
			}
		}
	}

	// cout<<"Num of flows down: "<<flows_down.size()<<endl;
}


void Controller::revert_to_primary()
{
	//////startTimer();
	for(int i=0;i<critical_switches.size();i++)
	{
		if(critical_switches[i]->status >= 0)
		{
			cout<<downTime<<" is the new downtime"<<endl;
			cout<<backup<<" is the new down due to sharing"<<endl;
			cout<<"+ Critical Switch Back with ID :"<<critical_switches[i]->toString()<<endl;
			critical_switches.erase(critical_switches.begin()+i);
			// if(duplicateIn(critical_switches))
			// {
			// 	cout<<"++++++++ ERROR, DUPLICATES IN CRITICAL SWITCHES"<<endl;
			// }
		}
	}
	//////stopTimer("for switches to revert");
	//////startTimer();

	for(int i=0;i<critical_links.size();i++)
	{
		if(critical_links[i]->status >= 0)
		{
			cout<<downTime<<" is the new downtime"<<endl;
			cout<<backup<<" is the new down due to sharing"<<endl;

			cout<<"+ Critical Link Back with ID :"<<critical_links[i]->link_id<<endl;
			critical_links.erase(critical_links.begin()+i);
			// if(duplicateIn(critical_links))
			// {
			// 	cout<<"++++++++ ERROR, DUPLICATES IN CRITICAL LINKS"<<endl;
			// }

		}
	}

	//////stopTimer("for links to revert");
	if(backUp)
	{
		for (int i=0;i<flows_on_back.size();i++)
		{
			Flow* f=flows_on_back[i];
			// if(f->down!=1)
			// 	continue;
			if(f->primaryPath->isUp())
			{
				f->antiCommitPath(f->backUpPath);
				bool check=f->commitPath(f->primaryPath,0); //Assumption is that link capacity would not be a bottleneck
				if(!check)
				{
					int x=1/0;
				}
				flows_on_back.erase(flows_on_back.begin()+i);
				cout<<"-- Num of flows on backup are: "<<flows_on_back.size()<<endl;
			}
		}
	}



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
			// cout<<"revert to primary from down: flow_id: "<<f->flow_id<<" ";
			// f->primaryPath->print(); 
			cout<<"-- Num of flows down: "<<flows_down.size()<<endl;
			continue;
		}

		if(backUp)
		{
			bool check=f->backUpPath->isUp();
			if(check)
			{
				f->commitPath(f->backUpPath,1); //Assumption is that link capacity would not be a bottleneck
				// cout<<"I am here here----------------------------------------------"<<endl;
				// cout<<"revert to backup from down: flow id: "<<f->flow_id<<" ";
				// f->backUpPath->print(); 
				flows_down.erase(flows_down.begin()+i);
				flows_on_back.push_back(f);
				cout<<"-- Num of flows down: "<<flows_down.size()<<endl;
			}
		}
	}
}

void Controller::detect_downTime()
{
	if(backUp && sharing)
	{
		// cout<<"Num of flows on backup are "<<flows_on_back.size()<<endl;
		for(int i=0;i<flows_on_back.size();i++)
		{
			for (int j=i+1;j<flows_on_back.size();j++)
			{
				Flow* f1=flows_on_back[i];
				Flow* f2=flows_on_back[j];
				if(f1->backUpPath==f2->backUpPath && f1->on_back && f2->on_back)
				{
					downTime+=1;
					backup+=1;
				}
			}
		}
	}


	// cout<<"downtime+= "<<flows_down.size() <<endl;

	downTime+=flows_down.size();
	// for(int i=0;i<flows_down.size();i++)
	// {
	// 	// cout<<"flow in down's var down is"<<flows_down[i]->down<<endl;
	// 	// if(flows_down[i]->down)
	// 	// {
	// 		downTime+=1;
	// 	// }1
	// }
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
		if(random < 100)
		{
			return 3600+rand()%(7*24*60*60-60*60);
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
		if(random < 100)
		{
			return 562+rand()%(10000-562);
		}	
	}


	// TODO. currently overall graph used for core 
	if(curSwitch->level==2)//CORE
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
		if(random < 80)
		{
			return 100+rand()%(5*60-100);
		}
		if(random < 90)
		{
			return 300+rand()%(794-300);
		}
		if(random < 100)
		{
			return 794+rand()%(1000000-794);
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
			return rand()%(5*60);
		}
		if(random < 70)
		{
			return 300+rand()%(60*60-300);
		}
		if(random < 82)
		{
			return 60*60+rand()%(24*60*60-60*60);
		}
		if(random < 100)
		{
			return 7*24*60*60+rand()%(10000000-7*24*60*60);
		}		
	}

	if(curSwitch->level==1)//AGGR
	{
		random=rand()%100;
		if(random < 2)
		{
			return rand()%(100);
		}
		if(random < 30)
		{
			return 100+rand()%(300-100);
		}
		if(random < 100)
		{
			return 300+rand()%(3162277-300);
		}	
	}


	// TODO. currently overall graph used for core 
	if(curSwitch->level==2)//CORE
	{
		random=rand()%100;
		if(random < 2)
		{
			return rand()%(100);
		}
		if(random < 70)
		{
			return 100+rand()%(60*60-100);
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
		if(random < 60)
		{
			return 300+rand()%(60*60-300);
		}
		if(random < 100)
		{
			return 60*60+rand()%(10000000-60*60);
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

		if(random < 100)
		{
			return 7*24*60*60+rand()%(10000000-7*24*60*60);
		}	

	}
}



void Controller::updateStatus(vector<Switch*> all_switches,int curSec)
{
	for(int i=0;i<all_switches.size();i++)
	{
		Switch* curSwitch=all_switches[i];

		if(curSwitch->status==0 && curSwitch->resilience==2)
		{
			int ttf=getTTF(curSwitch);
			if(ttf==0)
				ttf=2;

			curSwitch->status=rand()%ttf;
			//TODO check this with dr ihsan ,dr fahad and dr zartash, how to induce first failure
			return;
		}


		if(curSwitch->resilience==1 && curSwitch->status == 0 &&  curSwitch->failAt==curSec)
		{
			curSwitch->status=-getTTR(curSwitch);
			return;
		}

		if(curSwitch->status < 0)
		{
			curSwitch->status+=1;

			if(curSwitch->resilience == 1 && curSwitch->status == -1)
			{
				curSwitch->status=1;
			}

			if(curSwitch->resilience == 2 && curSwitch->status == -1)
			{
				curSwitch->status=getTTF(curSwitch);
			}
			return;
		}

		if(curSwitch->resilience == 2 && curSwitch->status > 0)
		{
			curSwitch->status-=1;
			if(curSwitch->status == 1)
			{
				curSwitch->status=-getTTR(curSwitch);
			}
		}
	}
}


void Controller::updateStatus(vector<Link*> all_switches,int curSec)
{
	for(int i=0;i<all_switches.size();i++)
	{
		Link* curSwitch=all_switches[i];

		if(curSwitch->status==0 && curSwitch->resilience==2 && curSwitch->failAt>curSec)
		{
			int ttf=getTTF(curSwitch);
			if(ttf==0)
				ttf=2;

			curSwitch->status=rand()%ttf;
			//TODO check this with dr ihsan ,dr fahad and dr zartash, how to induce first failure
			return;
		}


		if(curSwitch->resilience==1 && curSwitch->status == 0 &&  curSwitch->failAt==curSec)
		{
			curSwitch->status=-getTTR(curSwitch);
			return;
		}

		if(curSwitch->status < 0)
		{
			curSwitch->status+=1;

			if(curSwitch->resilience == 1 && curSwitch->status == -1)
			{
				curSwitch->status=1;
			}

			if(curSwitch->resilience == 2 && curSwitch->status == -1)
			{
				curSwitch->status=getTTF(curSwitch);
			}
			return;
		}

		if(curSwitch->resilience == 2 && curSwitch->status > 0)
		{
			curSwitch->status-=1;
			if(curSwitch->status == 1)
			{
				curSwitch->status=-getTTR(curSwitch);
			}
		}
	}
}
void Controller::autofail(int curSec)
{
	// This function needs to be rewritten, from insights from philipa gill



	//startTimer();
	detect_downTime();
	//stopTimer("detect_downTime");


	//startTimer();
	updateStatus(all_switches,curSec);
	//stopTimer("updateStatus 1");

	// //////startTimer();
	updateStatus(all_links,curSec);
	// //////stopTimer("updateStatus 2");

	if(curSec%100==0)
	{
		//startTimer();
		revert_to_primary();
		//stopTimer("revert_to_primary");

		//startTimer();
		findFaults();
		//stopTimer("find faults");

		//startTimer();
		logFailures(curSec);
		//stopTimer("log failures");
	}
	//TODO plot the cdfs to verify the sampling
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
	// if(size>5)
	// 	return;

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
		if(down_switches[i]->status >= 0)
		{	

			int level=all_switches[i]->level;
			string l;
			if(level==0)
				l="Core";
			if(level==1)
				l="Aggr";
			if(level==2)
				l="Tor";
			writeLog("Switch "+l+" "+down_switches[i]->toString()+" Up "+t);
			down_switches.erase(down_switches.begin()+i);
			//TODO check if this causes seg fault
		}
	}

	for(int i=0;i<down_links.size();i++)
	{
		if(down_links[i]->status >= 0)
		{	
			stringstream o;
			int idd=down_links[i]->link_id;
			o<<idd;
			string id=o.str();
			writeLog("Link "+down_links[i]->label+" "+ id+" Up "+t);

			down_links.erase(down_links.begin()+i);
			//TODO check if this causes seg fault
		}
	}

	for(int i=0;i<all_switches.size();i++)
	{
		if(all_switches[i]->status < 0 && notIn(down_switches,all_switches[i]))
		{	
			int level=all_switches[i]->level;
			string l;
			if(level==0)
				l="Core";
			if(level==1)
				l="Aggr";
			if(level==2)
				l="Tor";
			stringstream o;
			stringstream oo;
			int a=all_switches[i]->status;
			o<<a;
			string st=o.str();
			oo<<all_switches[i]->resilience;
			string res=oo.str();
			writeLog("Switch "+l+" "+all_switches[i]->toString()+" Down curTime: "+t+" downFor: "+st+" resLevel: "+res);
			down_switches.push_back(all_switches[i]);
		}
	}

	for(int i=0;i<all_links.size();i++)
	{
		if(all_links[i]->status < 0 && notIn(down_links,all_links[i]))
		{	
			stringstream o,oo,ooo;
			int idd=all_links[i]->link_id;
			o<<idd;
			string id=o.str();
			int a=all_links[i]->status;
			oo<<a;
			string st=oo.str();
			ooo<<all_links[i]->resilience;
			string res=ooo.str();
			writeLog("Link "+all_links[i]->label+" "+ id+" Down curTime: "+t+" downFor: "+st+" resLevel: "+res);
			down_links.push_back(all_links[i]);
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
	 if(intraRack && paths.size()!=1)
 	 {
 		int x=1/0;
 	 	return 0;
 	 }
	if(!intraRack && paths.size()<2)
	{
		paths.clear();
		cout<<"ERROR: Request could not be entertained with Rate: "<<rate<<" Size: "<<size<<", Not enough Bandwith remaining on Candidate Paths"<<endl;

		return 0;
	}

//	cout << "Request Entertained: Rate: "<<rate<<" Size: "<<size<<endl;
	int ind=rand()%paths.size();
	Path* primary=paths[ind];
	paths.erase(paths.begin()+ind);
	// cout<<"Primary Path is: "<<endl;
	// primary->print();
	Path* back=NULL;

	if(backUp)
	{
		paths.clear();
		back=getBackUpPath(primary,rate);
 		// cout<<"Backup Path is: "<<endl;
 		// back->print();
 		if(!back)
 		{
 			int x=1/0;
 		}
 		if(sharing)
 		{
 			paths_to_be_shared.push_back(back);
 		}
	}


	// TODO fix the error of multiple ppl sharing one pathF

	// if(duplicateIn(back->links))
	// 	back->print();

	Flow* flow= new Flow(source,dest,primary,back,rate,size,oneToOne,sTime);
	flow->setID(flowNumber);
	all_flows.push_back(flow);
	flowNumber++;
	if(flowNumber%1000==0)
		cout<<flowNumber<<" is the num of flows committed"<<endl;
	paths.clear();
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

	Path* back=paths[rand()%paths.size()];
	paths.clear();
	return back;
}


Path* Controller::getBackUpPath(Path* primary, int rate)
{
	int overlap=-1;
	Path* back=NULL;
	int index=0;

	if(sharing)
	{
		for(int i=0;i<paths.size();i++)
		{
			for (int j=0;j<paths_to_be_shared.size();j++)
			{
				Path* p1=paths[i];
				Path* p2=paths_to_be_shared[j];
				if(p2->getSrcPod()==p1->getSrcPod() && p2->getDstPod()==p1->getDstPod() && p1!=p2)
				{
					vector<Switch*> links=p1->switches;
					vector<Switch*> otherLinks=p2->switches;
					int common=getCommonCount(links,otherLinks);
					if(common > overlap)
					{
						back=p2;
						overlap=common;
						index=j;
					}

				}	
			}
		}
	}

	overlap=10*k;

	// TODO possible error can occur un tested code added above

	if(back!=NULL)
	{
		paths_to_be_shared.erase(paths_to_be_shared.begin()+index);
		cout<<"+ Sharing Back Up path with: "<<endl;
		// back->print();
	}
	else
	{

		int srcTor=primary->getSrcPod();
		int dstTor=primary->getDstPod();

		back=getReplicatedPath(srcTor,dstTor,rate);
		// overlap=10*k;
		// vector<Switch*> links=primary->switches;
  //       for(int i=0;i<paths.size();i++)
  //       {
  //           Path* cand=paths[i];
  //           vector<Switch*> otherLinks=cand->switches;
  //           int common=getCommonCount(links,otherLinks);
  //           if(common<overlap)
  //           {
  //               back=cand;
  //               overlap=common;
  //           }
  //       }
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

	int len_switches = all_switches.size();
	for(int i=0; i<len_switches; i++)
	{
		stringstream pID, lev, dID;
		pID << all_switches[i]->getPodID();
		lev << all_switches[i]->getLevel();		
		dID << all_switches[i]->getDeviceID();

		string stat = "";
		if(all_switches[i]->status >= 0)
			stat = "u";
		else
			stat = "d";
		
		str = str + "S: PodID:" + pID.str() + " Level:" + lev.str() + " DID:" + dID.str() + " Stat:" + stat + "\n";
	}
	
	int len_links = all_links.size();
	for(int i=0; i<len_links; i++)
	{
		stringstream id, upUtil, downUtil;
		id << all_links[i]->getID();
		upUtil << all_links[i]->getUsedUpBW();
		downUtil << all_links[i]->getUsedDownBW();

		string stat = "";
		if(all_links[i]->status >= 0)
			stat = "u";
		else
			stat = "d";

		str = str + "L: Label:" + all_links[i]->getLabel() + " LID:" + id.str() + " UUtil:" + upUtil.str() + " DUtil:"+ downUtil.str() + " Stat:" + stat + "\n";
	}
/*
	string buff="Switches: ";
	for (int i=0;i<all_switches.size();i++)
	{
		if(all_switches[i]->status < 0)
			buff+=" up";
		else
			buff+=" down";
	}

	buff+="\nLinks: ";
	for (int i=0;i<all_links.size();i++)
	{
		if(all_links[i]->status < 0)
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
	Address* add=dst->addr;
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
		printf("4) Instantiate Flows\n");

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
		if(option == 4)		//instantiate flow
		{
			printf("Creating paths\n");
			instantiateFlow();
			printf("Assigned paths to flow\n");
		}
	}
}
*/

long int Controller::getTime()
{
	return t;
}


