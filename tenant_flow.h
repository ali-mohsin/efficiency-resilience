#ifndef PAIRS_H
#define PAIRS_H

class LinkPair
{
public:
	Link* primary;
	Link* back;
	Link* otherBack;

	LinkPair(Link* p,Link* b,Link* bb)
	{
		primary=p;
		back=b;
		otherBack=bb;
	}
};


class SwitchPair
{
public:
	Switch* primary;
	Switch* back;
	Switch* otherBack;

	SwitchPair(Switch* p,Switch* b,Switch* bb)
	{
		primary=p;
		back=b;
		otherBack=bb;
	}
};

class TenantFlow
{
public:

	vector<LinkPair*> links_pairs;
	vector<SwitchPair*> switches;
	vector<Switch*> raw_switches;
	vector<Link*> raw_links;
	vector<int> bws;
	vector<Host*> vms;
	TenantFlow* backup;
	TenantFlow* back_backup;
	Switch* root;
	int downTime;

	TenantFlow(vector<Host*> hosts)
	{
		backup=NULL;
		downTime=0;
		vms=hosts;
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

	void destroy()
	{
		for(int i=0;i<raw_links.size();i++)
		{
			raw_links[i]->available_cap_up-=bws[i];
			raw_links[i]->available_cap_down-=bws[i];
		}

		for(int i=0;i<vms.size();i++)
		{
			vms[i]->unmark(1);
		}

	}

	void insert(LinkPair* lp, int bw)
	{

		Link* l=lp->primary;
		Link* l1=lp->back;
		Link* l2=lp->otherBack;
		// cout<<"link: "<<l->link_id<<" came in"<<endl;
		if(!notIn(raw_links,l))
			return;

		raw_links.push_back(l);
		bws.push_back(bw);

		if(l->resilience > 0 || l1->resilience>0)
		{
			links_pairs.push_back(lp);
		}

		Switch* s1=l->up_switch;
		Switch* s2=l1->up_switch;
		if(l2==NULL)
			int x=1/0;
		Switch* s3=l2->up_switch;
		// cout<<"switch: "<<s1->toString()<<" should be pushed in"<<endl;


		if(!notIn(raw_switches,s1))
			return;
		
		raw_switches.push_back(s1);

		SwitchPair* sp=new SwitchPair(s1,s2,s3);

		if(s1->resilience > 0 || s2->resilience>0)
			switches.push_back(sp);
	}

	bool isPrimaryDown()
	{
		for(int i=0;i<links_pairs.size();i++)
		{
			LinkPair* lp=links_pairs[i];
			if(lp->primary->status < 0 && lp->back->status < 0 && lp->otherBack->status < 0)
			{
				// cout<<"Link "<<lp->primary->link_id<<" label: "<<lp->primary->label<<" is down"<<endl;
				return true;				
			}
		}

		for(int i=0;i<switches.size();i++)
		{
			SwitchPair* lp=switches[i];
			if(lp->primary->status < 0 && lp->back->status < 0 && lp->otherBack->status < 0)
			{
				// cout<<"Switch "<<lp->primary->toString()<<" is down"<<endl;
				return true;
			}	
		}
		return false;
	}

	bool isBackupDown()
	{
		return backup->isPrimaryDown();
	}

	bool isBackBackDown()
	{
		return back_backup->isPrimaryDown();
	}

	bool isDown()
	{
		if(backup==NULL)
			return isPrimaryDown();
		else
			return isPrimaryDown() && isBackupDown() && isBackBackDown();
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

};


class TorPair
{
public:
	Switch* h1;
	Switch* h2;
	TorPair(Switch* a,Switch* b)
	{
		h1=a;
		h2=b;
	}

};

class PodPair
{
public:
	int h1;
	int h2;
	PodPair(int a,int b)
	{
		h1=a;
		h2=b;
	}

};
#endif /* GROUP_H */
