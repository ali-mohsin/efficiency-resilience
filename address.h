#ifndef ADDRESS_H
#define ADDRESS_H

#include <iostream>
using namespace std;
#include <sstream>
#define SSTR( x ) dynamic_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

// This class is the used to store a two touple contained by each host in order to be uniquely identified
class Address
{
	public:
	int podID;
	int hostID;

	Address(int pid,int hid)
	{
		podID=pid;
		hostID=hid;
	}


	int getPodID()
	{
		return podID;
	}
	int getDeviceID()
	{
		return hostID;
	}
	void printAddress()
	{
		cout<<"hello"<<endl;
	}

	string toString()
	{

		return SSTR( podID ) + ","+  SSTR( hostID )+"]";
	}
};

#endif /* ADDRESS_H */