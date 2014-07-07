#include "path.h"

	void Path::addLink(Link* s)
	{
		links.push_back(s);
	}

	void Path::addSwitch(Switch* s)
	{
		switches.push_back(s);
	}

	Path::Path(vector<Switch*> s , vector<Link*> l, vector<bool> dir)
	{
		beingUsed=0;

		for(int i=0;i<s.size();i++)
		{
			switches.push_back(s[i]);
		}

		for(int i=0;i<l.size();i++)
		{
			links.push_back(l[i]);
		}

		for(int i=0;i<dir.size();i++)
		{
			direction.push_back(dir[i]);
		}

	}


	bool Path::isUp()
	{
		for(int i=0;i<switches.size();i++)
		{
			if(switches[i]->status < 0)
				return false;
		}

		for(int i=0;i<links.size();i++)
		{
			if(links[i]->status < 0)
				return false;
		}
		return true;

	}

	void Path::print()
	{
		for(int i=0;i<switches.size();i++)
		{

			string dir;
			cout<<switches[i]->toString()<<",";
		}
		cout<<endl;

		for(int i=0;i<links.size();i++)
		{

			cout<<links[i]->link_id<<" -> ";
		}
		cout<<endl;

	}

	vector<Switch*> Path::getSwitches()
	{
		return switches;
	}

	bool Path::isValid(int rate, int tor2tor)
	{
//		cout<<"is "<<endl;
//		cout<<links.size()<<endl;
		for(int i=0;i<links.size();i++)
		{
			Link* curLink=links[i];
			bool dir=direction[i];
			if(tor2tor){
				if(links[i]->label=="Tor")
					continue;
			}
			if(dir)
			{
				if(!curLink->availAtUp(rate))
					return 0;
			}
			else
			{
				if(!curLink->availAtDown(rate))
					return 0;
			}
		}	
		return 1;
	}

	bool Path::isValid(int rate)
	{
//		cout<<"is "<<endl;
//		cout<<links.size()<<endl;
		for(int i=0;i<links.size();i++)
		{
			Link* curLink=links[i];
			bool dir=direction[i];
			if(dir)
			{
				if(!curLink->availAtUp(rate))
					return 0;
			}
			else
			{
				if(!curLink->availAtDown(rate))
					return 0;
			}
		}	
		return 1;
	}




	 Path::getSrcPod()
	{
		return switches[0]->getPodID();
	}
	
	// gohar
	Switch* Path::getSrcHost()
	{
		return switches[0];
	}
	
	// gohar
	Switch* Path::getDestHost()
	{
		return switches[switches.size()-1];
	}

	int Path::getDstPod()
	{
		return switches[switches.size()-1]->getPodID();
	}

	
	int Path::contains(vector<Path*> pathVec)
	{
		for(int i =0; i<pathVec.size();i++)
		{
			if(pathVec[i]==this)
				return i;
		}
		return -1;
	}	
	
	bool Path::has(Link* link)
	{
		for(int i=0; i<links.size();i++)
		{
				if(link==links[i])
						return true;
		}	
		return false;
	}	

	bool Path::has(Switch* s)
	{
		for(int i=0; i<switches.size();i++)
		{
			if(s==switches[i])
				return true;
		}	
		return false;
	}	
