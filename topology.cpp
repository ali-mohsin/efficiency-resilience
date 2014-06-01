#include "topology.h"

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
		cout<<"iteration: "<<i<<endl;
		tab+="\t";
		coreSwitches[i]->dfsPrint(tab);
		tab.erase(0,1);
	}
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
