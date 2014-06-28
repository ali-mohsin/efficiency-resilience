#ifndef HOSTPAIR_H
#define HOSTPAIR_H
class HostPair
{
public:
	Host* h1;
	Host* h2;
	HostPair(Host* a,Host* b)
	{
		h1=a;
		h2=b;
	}

};


#endif /* GROUP_H */
