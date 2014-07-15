#ifndef SUBPOD_H
#define SUBPOD_H
class Subpod
{
public:
	vector<Switch*> beta_switches;
	vector<Switch*> alpha_switches;
	vector<Host*> hosts;

	Subpod(vector<Switch*> beta_switches,vector<Switch*> alpha_switches,vector<Host*> hosts)
	{
		this->beta_switches=beta_switches;
		this->alpha_switches=alpha_switches;
		this->hosts=hosts;
	}
};


class Pod
{
public:
	Subpod* left_sub_pod;
	Subpod* right_sub_pod;
	int id;
	vector <Switch*> aggrs;

	Pod(Subpod* l, Subpod* r, int i)
	{
		left_sub_pod=l;
		right_sub_pod=r;
		id=i;
		//for(int i =0; i <)
	}
};


#endif /* GROUP_H */
