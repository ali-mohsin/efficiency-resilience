#ifndef PAIRS_H
#define PAIRS_H
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

	TenantFlow()
	{

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

	void insert(LinkPair* lp)
	{
		links_pairs.push_back(lp);
		Link* l=lp->primary;
		Link* l1=lp->back;

		Switch* s1=l->up_switch;
		Switch* s2=l1->up_switch;

		SwitchPair* sp=new SwitchPair(s1,s2);

		switches.push_back(sp);

	}

	bool isDown()
	{
		for(int i=0;i<links_pairs.size();i++)
		{
			LinkPair* lp=links_pairs[i];
			if(lp->primary->status < 0 && lp->back->status < 0)
				return true;
		}

		for(int i=0;i<switches.size();i++)
		{
			SwitchPair* lp=switches[i];
			if(lp->primary->status < 0 && lp->back->status < 0)
				return true;
		}
		return false;
	}
};

#endif /* GROUP_H */
