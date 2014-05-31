#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>

#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <stdarg.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <pthread.h>
#include <time.h>

#include "path.h"
#include "flow.h"
#include "link.h"
#include "switch.h"
#include "topology.h"
#include "controller.h"

using namespace std;

#define PROTOPORT 1532
#define QLEN 6
extern int errno;

float end_delay = 10.0;
float stats_delay = 0.5;
float fault_delay = 0.1;
char recvBuf[1024];
bool finishThis = false;
float run_time = 0.0;
float run_stats = 0.0;
float run_faults = 0.0;
bool busy = false;
bool dump = false;
int seconds_run = 0;
int years_run = 0;		// 3,153,6000 seconds = 1 year
vector<float> failTimes;
vector<int> failPID;
vector<int> failLevel;
vector<int> failDID;
vector<float> failComplete;
vector<bool> failed;
Controller* dc;
int inter_ping_time = 10;

void sig_pipe(int n){fprintf(stderr, "Broken pipe signal");}
int errexit(const char *format, ...);
int listen_socket(int port, int qz);
int connected_socket(int lsd);
void createFlow(string str);
// void addFailure(string str);
// void * pingStats(void * args);
void * pingFaults(void * args);
void storeFailure(int pID, int level, int dID, float sTime);