#include "topology.h"
#include <assert.h>

vector<Switch*> Topology::createPod(int podId)
{
	t_aggrID=0;
	b_aggrID=0;
//	int hostID=0; // global variable that is used to assign unique ids to each host in a pod
	vector<Switch*> upperSwitches; // holds upper aggr level switches
	vector<Switch*> lowerSwitches; // holds lower aggr level switches
	for (int i=0;i<k/2;i++) 	// create aggr upper level switches
	{
		Switch* upSwitch = new Switch(podId, t_aggrID++, "aggr top level", 1, k); // create new switch and assign unique id,label,level,pod id
		upperSwitches.push_back( upSwitch );
		allSwitches.push_back( upSwitch ); 
	}

	for (int i=0;i<k/2;i++) 	//create aggr bottom level
	{
		Switch* downSwitch = new Switch(podId, b_aggrID++, "aggr bottom level", 2, k); // create new switch and assign unique id,label,level,pod id
		lowerSwitches.push_back( downSwitch );
		allSwitches.push_back( downSwitch );
	}
	//
	//cout  << "check1"<<endl;
	//cout<<"size of lower switch: "<<lowerSwitches.size()<<endl;
	for (int i=0; i<upperSwitches.size(); i++)
	{
		for (int j=0; j<lowerSwitches.size(); j++)
		{
			//cout<<upperSwitches[i]->toString()<< " is the current UPPER switch"<<endl;
			//cout<<lowerSwitches[j]->toString()<< " is the current LOWER switch"<<endl;
			Link* link = new Link(netDeviceID++, aggrCap,"Aggr");
			upperSwitches[i]->connectToSwitch(lowerSwitches[j],link); // connect all the links amongst the aggregation level
			allLinks.push_back( link );
		}
		//cout <<" one switch completed"<<endl;
	}

	//cout  << "check2"<<endl;

	for (int j=0; j<lowerSwitches.size(); j++)
	{
		for (int i=0;i<k/2;i++)
		{
			Host* host=new Host(podId, hostID++, "random host"); // create a new host using a new address consisting of host id and pod id, increment hostId so that it remains unique
			Link* l=new Link(netDeviceID++,torCap,"Tor");
			allLinks.push_back(l);
			host->connectToSwitch(lowerSwitches[j],l);
			allHosts.push_back( host );
		}
	}

	return upperSwitches;
}

void Topology::createFatTree()
{

	vector< vector<Switch*> > allAggrs; // 2D vector that contains vectors of switches holding pointers to all the top level aggr switches of each pod
	for (int i=0;i<k;i++)
	{
		allAggrs.push_back(createPod(podID++)); // create a pod and append top level aggr switches to our allAggr vector
	}

	//cout << "first level done" << endl;

	for(int i=0;i<k*k/4;i++)
	{
		Switch* curCore=new Switch(-1, coreID++, "core switch", 0, k); //new Address(deviceID++,-1),"core switch",0);
		coreSwitches.push_back(curCore);
		allSwitches.push_back(curCore);
	}

	for (int i=0;i<k/2;i++)
	{
		for (int j=0;j<k/2;j++)
		{
			Switch* curCore=coreSwitches[i*k/2+j];
			for (int x=0;x<k;x++)
			{
				Switch* aggr=allAggrs[x][i]; // #beauty
				Link* l=new Link(netDeviceID++,coreCap,"Core");
				allLinks.push_back(l);
				curCore->connectToSwitch(aggr,l);
			}
		}	
	}
}

void Topology::printTopology()
{
	string tab="";
	for (int i=0;i<coreSwitches.size();i++)
	{
		cout<<"root: "<<coreSwitches[i]->toString()<<endl;
		tab+="\t";
		coreSwitches[i]->dfsPrint(tab);
		tab.erase(0,1);
	}

	for (int i=0;i<coreSwitches.size();i++)
	{
		cout<<coreSwitches[i]->down_links.size()<<" "<<coreSwitches[i]->up_links.size()<<endl;
	}
}

Subpod* Topology::createSubPod(int podId)
{
		t_aggrID=0;
		b_aggrID=0;
	//	int hostID=0; // global variable that is used to assign unique ids to each host in a pod
		vector<Switch*> upperSwitches; // holds upper aggr level switches
		vector<Switch*> lowerSwitches; // holds lower aggr level switches
		vector<Host*> my_hosts;
		for (int i=0;i<k/4;i++) 	// create aggr upper level switches
		{
			Switch* upSwitch = new Switch(podId, t_aggrID++, "aggr top level", 1, k); // create new switch and assign unique id,label,level,pod id
			upperSwitches.push_back( upSwitch );
			allSwitches.push_back( upSwitch ); 
		}

		for (int i=0;i<k/4;i++) 	//create aggr bottom level
		{
			Switch* downSwitch = new Switch(podId, b_aggrID++, "aggr bottom level", 2, k); // create new switch and assign unique id,label,level,pod id
			lowerSwitches.push_back( downSwitch );
			allSwitches.push_back( downSwitch );
		}
		//
		//cout  << "check1"<<endl;
		//cout<<"size of lower switch: "<<lowerSwitches.size()<<endl;
		for (int i=0; i<upperSwitches.size(); i++)
		{
			for (int j=0; j<lowerSwitches.size(); j++)
			{
				//cout<<upperSwitches[i]->toString()<< " is the current UPPER switch"<<endl;
				//cout<<lowerSwitches[j]->toString()<< " is the current LOWER switch"<<endl;
				Link* link = new Link(netDeviceID++, aggrCap,"Aggr");
				upperSwitches[i]->connectToSwitch(lowerSwitches[j],link); // connect all the links amongst the aggregation level
				allLinks.push_back( link );
			}
			//cout <<" one switch completed"<<endl;
		}

		//cout  << "check2"<<endl;

		for (int j=0; j<lowerSwitches.size(); j++)
		{
			for (int i=0;i<k/2;i++)
			{
				Host* host=new Host(podId, hostID++, "random host"); // create a new host using a new address consisting of host id and pod id, increment hostId so that it remains unique
				Link* l=new Link(netDeviceID++,torCap,"Tor");
				allLinks.push_back(l);
				host->connectToSwitch(lowerSwitches[j],l);
				allHosts.push_back( host );
				my_hosts.push_back( host );
			}
		}

		return new Subpod(upperSwitches,lowerSwitches,my_hosts);
	}



Pod* Topology::createMusaPod(int podId)
{
	Subpod* left=createSubPod(podId);
	Subpod* right=createSubPod(podId);

	for(int i=0;i<left->alpha_switches.size();i++)
	{
		Switch* curSwitch=left->alpha_switches[i];
		vector<Link*> down_links=curSwitch->down_links;

		vector<Host*> hosts;

		for(int x=0;x<down_links.size();x++)
		{
			hosts.push_back(down_links[x]->host);
		}

		Switch* otherSwitch=right->beta_switches[i];
		for(int j=0;j<hosts.size();j++)
		{
			Link* l=new Link(netDeviceID++,torCap,"Tor");
			assert(hosts[j]!=NULL);
			hosts[j]->connectToSwitch(otherSwitch,l);
		}
	}


	for(int i=0;i<right->alpha_switches.size();i++)
	{
		Switch* curSwitch=right->alpha_switches[i];
		vector<Link*> down_links=curSwitch->down_links;

		vector<Host*> hosts;

		for(int x=0;x<down_links.size();x++)
		{
			hosts.push_back(down_links[x]->host);
		}
		
		Switch* otherSwitch=left->beta_switches[i];
		for(int j=0;j<hosts.size();j++)
		{
			Link* l=new Link(netDeviceID++,torCap,"Tor");
			assert(hosts[j]!=NULL);
			hosts[j]->connectToSwitch(otherSwitch,l);
		}
	}

	return new Pod(left,right,podId);
}


vector<Switch*> insert(vector<Switch*> s, vector<Switch*> v)
{
	for(int i=0;i<v.size();i++)
	{
		s.push_back(v[i]);
	}
	return s;
}




void Topology::createMusaTree()
{

	vector<Pod*> allPods; // 2D vector that contains vectors of switches holding pointers to all the top level aggr switches of each pod
	vector<Switch*> allAggrs;

	for (int i=0;i<k;i++)
	{
		allAggrs.clear();
		cout<<"creating pod"<<i<<endl;
		Pod* mp=createMusaPod(podID++);
		allAggrs = insert(allAggrs,mp->left_sub_pod->alpha_switches);
		allAggrs = insert(allAggrs,mp->left_sub_pod->beta_switches);
		allAggrs = insert(allAggrs,mp->right_sub_pod->alpha_switches);
		allAggrs = insert(allAggrs,mp->right_sub_pod->beta_switches);
		mp->aggrs=allAggrs;
		allPods.push_back(mp); // create a pod and append top level aggr switches to our allAggr vector

	}


	for(int i=0;i<k*k/4;i++)
	{
		Switch* curCore=new Switch(-1, coreID++, "core switch", 0, k); //new Address(deviceID++,-1),"core switch",0);
		coreSwitches.push_back(curCore);
		allSwitches.push_back(curCore);
	}

	int switchNum=0;

	for(int i=0;i<coreSwitches.size();i++)
	{
		cout<<"vale of i was " <<i<<endl;
		for(int j=0;j<k;j++)
		{

			Switch* tobeConnected = allPods[j]->aggrs[switchNum%k];
			cout<<"testing for "<<tobeConnected->toString()<<" s num: "<<switchNum%k<<endl;
			Link* l=new Link(netDeviceID++,coreCap,"Core");
			allLinks.push_back(l);
			coreSwitches[i]->connectToSwitch(tobeConnected,l);

		}
		switchNum++;
	}

	// for (int i=0;i<k/2;i++)
	// {
	// 	for (int j=0;j<k/2;j++)
	// 	{
	// 		Switch* curCore=coreSwitches[i*k/2+j];
	// 		for (int x=0;x<k;x++)
	// 		{
	// 			Switch* aggr=allAggrs[x*k+i]; // #beauty
	// 			Link* l=new Link(netDeviceID++,coreCap,"Core");
	// 			allLinks.push_back(l);
	// 			curCore->connectToSwitch(aggr,l);
	// 		}
	// 	}	
	// }
}

vector<Switch*> Topology::getCores()
{
	return coreSwitches;
}

vector<Switch*> Topology::getSwitches()
{
	return allSwitches;
}

vector<Host*> Topology::getHosts()
{
	return allHosts;
}

vector<Link*> Topology::getLinks()
{
	return allLinks;
}
