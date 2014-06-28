#ifndef TENANT_H
#define TENANT_H
class Tenant
{
public:
	vector<VM*> vms;
	vector<Flow*> flows;
	int level;
	int downTime;

	void setFlows(vector<Flow*> f)
	{
		flows=f;
	}

	Tenant()
	{
		downTime=0;
	}
	
	void setLevel(int l)
	{
		level=l;
	}


};


#endif /* GROUP_H */
