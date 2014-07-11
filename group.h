#ifndef GROUP_H
#define GROUP_H
class Group
{
public:
	vector<Link*> links;
	int resilience;
	Link* leader;

	void insert(Link* l)
	{
		if(links.size()==0)
			leader=l;
		links.push_back(l);
	}

	Group(Link* l,int res)
	{
		leader=l;
		resilience=res;
		links.push_back(l);
	}

	Group(int res)
	{
		resilience=res;
	}


	int getStatus()
	{
		return leader->status;
	}

	int getFailAt()
	{
		return leader->failAt;
	}

	void setStatus(int times)
	{
		for(int i=0;i<links.size();i++)
		{
			links[i]->status=times;
		}
	}

	void addStatus(int add)
	{
		for(int i=0;i<links.size();i++)
		{
			links[i]->status+=add;
		}
	}

};


#endif /* GROUP_H */
