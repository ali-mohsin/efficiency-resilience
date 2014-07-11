#ifndef FLOWDATA_H
#define FLOWDATA_H
#include "path.h"
class FlowData
{
public:
	int flow_id;
	int rate;
	Path* path;
};


#endif /* FLOWDATA_H */

