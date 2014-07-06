#include "link.h"

Link::Link(int id,int cap,string l)
{
	status=0;
	link_id=id;
	total_cap=cap;
	available_cap_up=total_cap;
	available_cap_down=total_cap;
	num_flows=0;
	host=NULL;
	label=l;
	resilience=0;
	failAt=-1;
	old_status=0;
}

int Link::getID()
{
	return link_id;
}

Switch* Link::getDownSwitch()
{
	return down_switch;
}

Switch* Link::getUpSwitch()
{
	return up_switch;
}

string Link::getLabel()
{
	return label;
}

int Link::getStatus()
{
	return status;
}

void Link::setStatus(int stat)
{
	status = stat;
}

int Link::getUsedUpBW()
{
	float used = (float)(total_cap) - (float)(available_cap_up);
	used = (100.0*used)/((float)(total_cap));

	int usedUp = (int)(used);
	return usedUp;
}

int Link::getUsedDownBW()
{
	float used = (float)(total_cap) - (float)(available_cap_down);
	used = (100.0*used)/((float)(total_cap));

	int usedDown = (int)(used);
	return usedDown;
}

void Link::printInfo()
{
	//cout<<"Link ID: "<<link_id<<endl;
	//cout<<"Label: "<<label<<endl;
	//cout<<"Status: "<<status<<endl;
	//cout<<"Total cap: "<<total_cap<<endl;
	//cout<<"Avail cap up: "<<available_cap_up<<endl;
	//cout<<"Avail cap down: "<<available_cap_down<<endl;
	//cout<<"Num ports:"<<num_flows<<endl;
}

int Link::reserve_BW_up(int bw)
{
	if(available_cap_up-bw < 0)
		return -1;
	available_cap_up-=bw;
}

int Link::reserve_BW_down(int bw)
{
	if(available_cap_down-bw < 0)
		return -1;
	available_cap_down-=bw;
}

bool Link::availAtUp(int bw)
{

	//cout<<"checking if bw "<<bw<<" is availAtUp and im left with "<<available_cap_up-bw <<" if i alot this"<<endl;
	return (available_cap_up-bw) >= 0;
}

bool Link::availAtDown(int bw)
{
	//cout<<"checking if bw "<<bw<<" is availAtDown and im left with "<<available_cap_down-bw <<" if i alot this"<<endl;

	return (available_cap_down-bw) >= 0;
}




Switch* Link::getOtherNode(Switch* cur)
{
	if(up_switch==cur)
	{
		// cout<<"get down"<<endl;
		return down_switch;
	}
	// cout<<"get up"<<endl;

	return up_switch;
}


void Link::addPrimaryFlow(Flow* f,int rate, int dir, int  back)
{
	//cout<<"Im here to add flow with directions as back= "<<back<<" and dir= "<<dir<<endl;
	flows_primary.push_back(f);
	num_flows++;
	if(dir==1)
	{
			available_cap_up-=rate;
	}
	else
	{
			available_cap_down-=rate;
	}

}

void Link::addBackFlow(Flow* f,int rate, int dir, int  back, int tor2tor)
{
	//cout<<"Im here to add flow with directions as back= "<<back<<" and dir= "<<dir<<endl;
	if(tor2tor && this->label=="Tor")
		return;
	
	if(dir==1)
	{
			backup_up+=rate;
			available_cap_up-=rate;
	}
	else
	{
			backup_down+=rate;
			available_cap_down-=rate;
	}

}

// this function does not push back flow again
void Link::addBackFlow(int rate, int dir)
{

		
	if(dir==1)
	{
		backup_up+=rate;
		available_cap_up-=rate;
	}
	else
	{
		backup_down+=rate;
		available_cap_down-=rate;
	}
}



vector<Flow*> Link::getFlowsOnPrimary()
{
	vector<Flow*> v;
	for(int i=0;i<flows_primary.size();i++)
	{
		if(flows_primary[i]->primaryPath->beingUsed)
			v.push_back(flows_primary[i]);
	}
	return v;
}

//potential bug, what if multiple flows are passing through same link?
vector<Flow*> Link::getFlowsOnBack()
{
	vector<Flow*> v;
	for(int i=0;i<flows_back.size();i++)
	{
		
			for(int j=0;j<flows_back[i]->backUpPath.size();j++)
			{
				if(flows_back[i]->backUpPath[j]->has(this) && flows_back[i]->backUpPath[j]->beingUsed)			
					v.push_back(flows_back[i]);
			}
	}
	return v;
}

void Link::addFlowDataEntry(int f_id, int r, Flow* flow,Path* path) {
	FlowData f;
	f.flow_id = f_id;
	f.rate = r;
	f.path=path;
	flowData.push_back(f);
	int check=0;
	//for(int i=0; i<flow_back.size();i++)
	//{
	//	if(flow_back[i]==f)
	//		check=1;
	//}

	//if(!check)
		flows_back.push_back(flow);
	
}

void Link::removeFlowDataEntry(int f_id,Path* path) {
	for(int i=0;i<flowData.size();i++)
	{
		if(flowData[i].flow_id==f_id && flowData[i].path==path) {
			flowData.erase(flowData.begin()+i);
			i--;
		}
	}
}
// vector<Flow*> Link::getActiveFlows()
// {
// 	vector<Flow*> v;
// 	for(int i=0;i<flows.size();i++)
// 	{
// 		if(flows[i]->down!=1)
// 			v.push_back(flows[i]);
// 	}
// 	return v;
// }

// void Link::removeFlow(Flow* f,int rate, int dir)
// {
// 	//cout<<"Im here to add flow with directions as back= "<<back<<" and dir= "<<dir<<endl;
// 	num_flows--;
// 	if(dir==1)
// 	{
// 			available_cap_up+=rate;
// 	}
// 	else
// 	{
		
// 			available_cap_down+=rate;
// 	}
// 	for(int i=0;i<flows.size();i++)
// 	{
// 		if(flows[i]==f)
// 		{
// 			flows.erase(flows.begin()+i);
// 		}
// 	}

// }
