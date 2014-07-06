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


#endif /* GROUP_H */
