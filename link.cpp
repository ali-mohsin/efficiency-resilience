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
	failAt=-1;
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


void Link::addFlow(int rate, int dir, int  back)
{
	//cout<<"Im here to add flow with directions as back= "<<back<<" and dir= "<<dir<<endl;
	num_flows++;
	if(dir==1)
	{
		if(back)
			backup_up+=rate;
		else
			available_cap_up-=rate;
	}
	else
	{
		if(back)
			backup_down+=rate;
		else
		{
			available_cap_down-=rate;
		}
	}

}


void Link::removeFlow(int rate, int dir)
{
	//cout<<"Im here to add flow with directions as back= "<<back<<" and dir= "<<dir<<endl;
	num_flows--;
	if(dir==1)
	{
			available_cap_up+=rate;
	}
	else
	{
		
			available_cap_down+=rate;
	}

}