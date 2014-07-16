#ifndef PAIRS_H
#define PAIRS_H

class LinkPair
{
public:
	Link* primary;
	Link* back;

	LinkPair(Link* p,Link* b)
	{
		primary=p;
		back=b;
	}
};


class SwitchPair
{
public:
	Switch* primary;
	Switch* back;

	SwitchPair(Switch* p,Switch* b)
	{
		primary=p;
		back=b;
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
	Switch* root;
	int downTime;
	int bw;
	int vm;

	TenantFlow(vector<Host*> hosts,int v,int b)
	{
		backup=NULL;
		downTime=0;
		vms=hosts;
		vm=v;
		bw=b;
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
			raw_links[i]->available_cap_up+=bws[i];
			raw_links[i]->available_cap_down+=bws[i];
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
		// cout<<"switch: "<<s1->toString()<<" should be pushed in"<<endl;


		if(!notIn(raw_switches,s1))
			return;
		
		raw_switches.push_back(s1);

		SwitchPair* sp=new SwitchPair(s1,s2);

		if(s1->resilience > 0 || s2->resilience>0)
			switches.push_back(sp);
	}

	bool isPrimaryDown()
	{

		for(int i=0;i<links_pairs.size();i++)
		{
			LinkPair* lp=links_pairs[i];
			if(lp->primary->status < 0)
			{
				// cout<<"Link "<<lp->primary->link_id<<" label: "<<lp->primary->label<<" is down"<<endl;

				return true;				
			}
		}

		for(int i=0;i<switches.size();i++)
		{
			SwitchPair* lp=switches[i];
			if(lp->primary->status < 0)
			{
				// cout<<"Switch "<<lp->primary->toString()<<" is down"<<endl;
				return true;
			}	
		}
		return false;
	}

	bool isBackupDown()
	{
		// cout<<"checking for back"<<endl;
		return backup->isPrimaryDown();
	}


	void print()
	{
		cout<<"----------------------------------"<<endl;
		cout<<this<<endl;
		cout<<"Links: "<<endl;
		for(int i=0;i<raw_links.size();i++)
		{
			cout<<raw_links[i]->link_id<<" ";
		}
		cout<<endl;
		cout<<"Switches: "<<endl;

		for(int i=0;i<raw_switches.size();i++)
		{
			cout<<raw_switches[i]->toString()<<" ";
		}
		cout<<endl;

		if(backup)
		{
			cout<<this->backup<<endl;
			cout<<"backup Links: "<<endl;
			for(int i=0;i<backup->raw_links.size();i++)
			{
				cout<<backup->raw_links[i]->link_id<<" ";
			}
			cout<<endl;
			cout<<"backup Switches: "<<endl;

			for(int i=0;i<backup->raw_switches.size();i++)
			{
				cout<<backup->raw_switches[i]->toString()<<" ";
			}
			cout<<endl;		}
		cout<<"----------------------------------"<<endl;
	}

	bool isDown()
	{
		if(backup==NULL)
			return isPrimaryDown();
		else
		{
			// cout<<"checking for primary"<<endl;
			if(!isPrimaryDown())
				return false;
			// cout<<" primary was down"<<endl;

			if(!isBackupDown())
			{
				// cout<<"backup saved the day"<<endl;
				return false;
			}

			// cout<<"backup was also down"<<endl;
			return true;
		}
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
