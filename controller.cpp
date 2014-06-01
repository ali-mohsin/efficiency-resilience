#include "controller.h"
#include "flow.h"
#include <fstream>
#include <cstdlib>
#include <string>

class Topology;

Topology* Controller::createTopology(int tor,int aggr,int core)
{
	Topology* tree = new Topology(k,tor,aggr,core);
	tree->createFatTree();
	all_cores = tree->getCores();
	all_switches = tree->getSwitches();
	all_hosts = tree->getHosts();
	all_links = tree->getLinks();
}

Controller::Controller(int kay,int tor,int aggr,int core,int back,int runFor,int makeFlows)
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
	// TODO seperate variable for backup
	failures=0;
	totalTime=runFor;
	assignResilience();
	if(makeFlows)
	{
		createFlows();
	}
}


void Controller::createFlows()
{
	for (int i=0;i<all_hosts.size();i++)
	{
		for (int j=0;j<all_hosts.size();j++)
		{
			if(i!=j)
				instantiateFlow(all_hosts[i],all_hosts[j],10,10,0);
		}
	}
}

void Controller::checkProb(vector<Switch*> Tors, int prob, float factor)
{
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
				Tors[i]->resilience=2;
			}

		}
}



void Controller::checkProb(vector<Link*> Tors, int prob, float factor)
{
	for (int i =0; i < Tors.size(); i++)
		{
			int random = rand()%(1000);
			if (random > prob)
				Tors[i]->resilience=0;
			else if (random > prob/factor)
			{
				int failAt=rand()%totalTime;
				Tors[i]->failAt=failAt;
				Tors[i]->resilience=1;
			}

			else 
			{
				Tors[i]->resilience=2;
			}

		}
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
			cores.push_back(all_switches[i]);

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


void Controller::findFaults()
{
	//TODO implement for links as well
	int len = all_switches.size();
	for(int i=0; i<len; i++)
	{
		if( all_switches[i]->getStatus() < 0 )
		{
			vector<Flow*> flows=all_switches[i]->flows;
			for(int j=0;j<flows.size();j++)
			{
				cout <<"+ Critical Switch Failed with ID: "<<all_switches[i]->toString()<<endl;
				critical_switches.push_back(all_switches[i]);
				flows[j]->antiCommitPath(flows[j]->primaryPath);
				if(backUp)
				{
					int commit=flows[j]->commitPath(flows[j]->backUpPath,0);

					if(commit)
						flows_on_back.push_back(flows[j]);
					else
						flows_down.push_back(flows[j]);
				}
				else
				{
					flows_down.push_back(flows[j]);
				}
			}
		}
	}

//************For Links******************//

	flows.clear();
	len = all_links.size();
	for(int i=0; i<len; i++)
	{
		if( all_links[i]->getStatus() < 0 )
		{
			vector<Flow*> flows=all_links[i]->flows;
			for(int j=0;j<flows.size();j++)
			{
				cout <<"+ Critical Link Failed with ID: "<<all_links[i]->link_id()<<endl;
				critical_links.push_back(all_links[i]);
				flows[j]->antiCommitPath(flows[j]->primaryPath);
				if(backUp)
				{
					int commit=flows[j]->commitPath(flows[j]->backUpPath,0);

					if(commit)
						flows_on_back.push_back(flows[j]);
					else
						flows_down.push_back(flows[j]);
				}
				else
				{
					flows_down.push_back(flows[j]);
				}
			}
		}
	}



}


void Controller::revert_to_primary()
{
	for(int i=0;i<critical_switches.size();i++)
	{
		if(critical_switches[i]->status > 0)
		{
			cout<<downTime<<" is the new downtime"<<endl;
			cout<<"+ Critical Switch Back with ID :"<<critical_switches[i]->toString()<<endl;
			critical_switches.erase(critical_switches.begin()+i);
			cout<<"Number of flows on back:"<<flows_on_back.size()<<endl;;

		}
	}

	for(int i=0;i<critical_links.size();i++)
	{
		if(critical_links[i]->status > 0)
		{
			cout<<downTime<<" is the new downtime"<<endl;
			cout<<"+ Critical Link Back with ID :"<<critical_links[i]->link_id()<<endl;
			critical_links.erase(critical_links.begin()+i);
			cout<<"Number of flows on back:"<<flows_on_back.size()<<endl;;

		}
	}


	if(backUp)
	{
		for (int i=0;i<flows_on_back.size();i++)
		{
			Flow* f=flows_on_back[i];
			if(f->primaryPath->isUp())
			{
				cout<<"Reverting to primary"<<endl;
				f->antiCommitPath(f->backUpPath);
				f->commitPath(f->primaryPath,0); //Assumption is that link capacity would not be a bottleneck
				flows_on_back.erase(flows_on_back.begin()+i);
			}
		}
	}


	for (int i=0;i<flows_down.size();i++)
	{
		Flow* f=flows_down[i];
		if(f->primaryPath->isUp())
		{
			cout<<"Reverting to primary"<<endl;
			f->commitPath(f->primaryPath,0); //Assumption is that link capacity would not be a bottleneck
			flows_down.erase(flows_down.begin()+i);
		}
	}
}

void Controller::detect_downTime()
{
	if(backUp)
	{
		for(int i=0;i<flows_on_back.size();i++)
		{
			for (int j=i+1;j<flows_on_back.size();j++)
			{
				Flow* f1=flows_on_back[i];
				Flow* f2=flows_on_back[j];
				if(f1->backUpPath==f2->backUpPath)
				{
					downTime+=0.5;
					cout << downTime<<endl;
				}
			}
		}
	}

	downTime+=flows_down.size();
}

int Controller::getTTR(Switch* curSwitch)
{
	cout<<"+ Switch Failed with ID: "<<curSwitch->toString()<<endl;
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
		cout<<"+ Link Failed with ID: "<<curSwitch->link_id<<" with resilience "<<curSwitch->resilience<<endl;
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
	cout<<"+ Switch back with ID"<<curSwitch->toString()<< "with resilience: "<<curSwitch->resilience<<endl;
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
	cout<<"+ Link back with ID"<<curSwitch->link_id<<endl;
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
		if(curSwitch->resilience==1 && curSwitch->status >= 0 &&  curSwitch->failAt==curSec)
		{
			curSwitch->status=-getTTR(curSwitch);
			curSwitch->resilience-=1;
		}

		if(curSwitch->status < 0)
		{
			curSwitch->status+=1;
			if(curSwitch->resilience == 2 && curSwitch->status == -1)
			{
				curSwitch->status=getTTF(curSwitch);
			}
		}

		if(curSwitch->resilience == 2 && curSwitch->status > 0)
		{
			curSwitch->status-=1;
			if(curSwitch->status == 1)
			{
				curSwitch->status=-getTTR(curSwitch);
			}
		}

		if(curSwitch->status==0 && curSwitch->resilience==2)
		{
			curSwitch->status=rand()%getTTF(curSwitch);
			//TODO check this with dr ihsan ,dr fahad and dr zartash, how to induce first failure
		}

	}
}


void Controller::updateStatus(vector<Link*> all_switches,int curSec)
{
	for(int i=0;i<all_switches.size();i++)
	{
		Link* curSwitch=all_switches[i];
		if(curSwitch->resilience==1 && curSwitch->status >= 0 &&  curSwitch->failAt==curSec)
		{
			curSwitch->status=-getTTR(curSwitch);
			curSwitch->resilience-=1;
		}

		if(curSwitch->status < 0)
		{
			curSwitch->status+=1;
			if(curSwitch->resilience == 2 && curSwitch->status == -1)
			{
				curSwitch->status=getTTF(curSwitch);
			}
		}

		if(curSwitch->resilience == 2 && curSwitch->status > 0)
		{
			curSwitch->status-=1;
			if(curSwitch->status == 1)
			{
				curSwitch->status=-getTTR(curSwitch);
			}
		}

		if(curSwitch->status==0 && curSwitch->resilience==2)
		{
			curSwitch->status=rand()%getTTF(curSwitch);
			//TODO check this with dr ihsan ,dr fahad and dr zartash, how to induce first failure
		}

	}
}
void Controller::autofail(int curSec)
{
	// This function needs to be rewritten, from insights from philipa gill
	revert_to_primary();
	detect_downTime();
	findFaults();
	updateStatus(all_switches,curSec);
	updateStatus(all_links,curSec);
	if(curSec%10)
	{
		logFailures(curSec);
	}
	//TODO plot the cdfs to verify the sampling
}


void Controller::getAllPaths(Switch* src,Switch* dst, vector<Switch*> switches,vector<Link*> links, vector<bool> directions, int dir)
{

	vector<Link*> poolToVisit;

	if(src==NULL or dst==NULL)
	{
		cout<<"moving back; base case"<<endl;
		return;
	}

	//cout<<"SRC: "<<src->toString()<<"\nDST: "<< dst->toString()<<endl; 

	if(dir==1)
		poolToVisit=src->getUpLinks();
	else
		poolToVisit=src->getDownLinks();

	for(int i=0;i<poolToVisit.size();i++)
	{
		Link* curLink=poolToVisit[i];
		Switch* curDst=curLink->getOtherNode(src);
		if(curDst==NULL)
		{
			switches.pop_back();
			links.pop_back();
			directions.pop_back();
			return;
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
			Path* p= new Path(switches,links,directions);
			paths.push_back(p);
		}
		getAllPaths(curDst,dst,switches,links,directions,dir);
		links.pop_back();
		directions.pop_back();
		if(switches.back()->level==0)
		{
			if(dir==0)
				dir=1;
			else
				dir=0	;	}	
		switches.pop_back();
	}

}

void Controller::filterPaths(int rate,Host* dest)
{

	for(int i=0;i<paths.size();i++)
	{
		Path* curPath=paths[i];
		curPath->links.push_back(dest->link);
		curPath->direction.push_back(0);
		if(!curPath->isValid(rate))
		{
			paths.erase(paths.begin()+i);
			i--;
			continue;
		}
	}
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

void Controller::logFailures(int time)
{
	string t;
	stringstream out;
	out<<time;
	t=out.str()+'\n';

	for(int i=0;i<down_switches.size();i++)
	{
		if(down_switches[i]->status > 0)
		{	
			writeLog("Switch "+down_switches[i]->toString()+" Up "+t);
			down_switches.erase(down_switches.begin()+i);
			//TODO check if this causes seg fault
		}
	}

	for(int i=0;i<down_links.size();i++)
	{
		if(down_links[i]->status > 0)
		{	
			stringstream o;
			int idd=down_links[i]->link_id;
			o<<idd;
			string id=o.str();
			writeLog("Link "+id+" Up "+t);
			down_links.erase(down_links.begin()+i);
			//TODO check if this causes seg fault
		}
	}

	for(int i=0;i<all_switches.size();i++)
	{
		if(all_switches[i]->status < 0 && notIn(down_switches,all_switches[i]))
		{	
			writeLog("Switch "+all_switches[i]->toString()+" Down "+t);
			down_switches.push_back(all_switches[i]);
		}
	}

	for(int i=0;i<all_links.size();i++)
	{
		if(all_links[i]->status < 0 && notIn(down_links,all_links[i]))
		{	
			stringstream o;
			int idd=all_links[i]->link_id;
			o<<idd;
			string id=o.str();
			writeLog("Link "+id+" Down "+t);
			down_links.push_back(all_links[i]);
		}
	}


}

bool Controller::instantiateFlow(Host* source, Host* dest, double rate, int size,double sTime)	//rate in MBps, size in MB
{
	vector<Switch*> switches;
	vector<Link*> links;
	vector<bool> directions;
	switches.push_back(source->getTor());
	directions.push_back(1);
	links.push_back(source->link);
	getAllPaths(source->getTor(),dest->getTor(), switches, links, directions,1);
	filterPaths(rate,dest);
	if(paths.size()<2)
	{
		cout<<"ERROR: Request could not be entertained with Rate: "<<rate<<" Size: "<<size<<", Not enough Bandwith remaining on Candidate Paths"<<endl;
		return 0;
	}

	cout << "Request Entertained: Rate: "<<rate<<" Size: "<<size<<endl;
	int ind=rand()%paths.size();
	Path* primary=paths[ind];
	paths.erase(paths.begin()+ind);
	cout<<"Primary Path is: "<<endl;
	primary->print();
	Path* back=NULL;

	if(backUp)
	{
		Path* back=	getBackUpPath(primary);
		cout<<"Backup Path is: "<<endl;
		back->print();
		paths_to_be_shared.push_back(back);
	}


	// TODO fix the error of multiple ppl sharing one pathF

	Flow* flow= new Flow(source,dest,primary,back,rate,size,oneToOne,sTime);
	flow->setID(flowNumber);
	all_flows.push_back(flow);
	flowNumber++;
	paths.clear();
	return 1;
}

int getCommonCount(vector<Link*> a,vector<Link*> b)
{
	int count=0;
	for(int i=0;i<a.size();i++)
	{
		Link* aCand=a[i];
		for(int j=0;j<b.size();j++)
		{
			Link* bCand=b[i];
			if(aCand==bCand)
				count++;
		}
	}
	return count;
}

Path* Controller::getBackUpPath(Path* primary)
{
	int overlap=-1;
	Path* back=NULL;
	int index=0;
	for(int i=0;i<paths.size();i++)
	{
		for (int j=0;j<paths_to_be_shared.size();j++)
		{
			Path* p1=paths[i];
			Path* p2=paths_to_be_shared[j];

			if(p2->getSrcPod()==p1->getSrcPod() && p2->getDstPod()==p1->getDstPod() && p1!=p2)
			{
				vector<Link*> links=p1->links;
				vector<Link*> otherLinks=p2->links;
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

	overlap=10*k;

	// TODO possible error can occur un tested code added above

	if(back!=NULL)
	{
		paths_to_be_shared.erase(paths_to_be_shared.begin()+index);
		cout<<"+ Sharing Back Up path with: "<<endl;
		back->print();
	}
	else
	{
		overlap=10*k;
		vector<Link*> links=primary->links;
        for(int i=0;i<paths.size();i++)
        {
            Path* cand=paths[i];
            vector<Link*> otherLinks=cand->links;
            int common=getCommonCount(links,otherLinks);
            if(common<overlap)
            {
                back=cand;
                overlap=common;
            }
        }

	}
	return back;
}

void Controller::writeLog(string str)
{
	ofstream fout;
	fout.open("logs.txt",ios::app);
	fout<<str;
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


