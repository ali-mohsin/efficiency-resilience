

	//Main tasks that this code does is that iterate for run number of times and after every ping interval which represents 1 sec, dump the data, 

	pthread_t t1,t2;//, t3;
//	pthread_create(&t1, NULL, pingFaults, NULL);

	int flowsNum = dc->all_flows.size();
	end_delay = 1000000 + 5.0;
	struct timespec time1, time2;
	time1.tv_sec = 0;
	time1.tv_nsec = 10; // interval of 100 nano sec, 

	//TODO (ali-mohsin), verify this 100 nsec is the optimal, if not then it can be optimized

	int runs = (runFor);
	int num_fails = failTimes.size(); // would compute to 0

	cout<<"Number of run: "<<runs<<"\n";
	if(failures)
	{
		for(int i=0; i<runs; i++)
		{
			if (i%10000==0)
				cout<<i<<"th run"<<endl;
			

			dc->autofail(i);
			// seconds_run++;
			// if( (seconds_run % inter_ping_time) == 0 )
			// {
			// 	if( (seconds_run % 31536000) == 0 )
			// 	{
			// 		years_run++;
			// 		seconds_run = seconds_run - 31536000;
			// 	}
			// 	long time_so_far = years_run*31536000 + seconds_run;
			// }

			// if(nanosleep(&time1, &time2) < 0)
			// {
			// 	cout<<"Nanosleep() failed\n";
			// 	return -1;
			// }

			// for(int j=0; j<flowsNum; j++)
			// {
			// 	if( ((dc->all_flows[j]->getActive() + dc->all_flows[j]->getStart()) < run_time ) && (!(dc->all_flows[j]->getDone())))
			// 	{
			// 		dc->all_flows[j]->setDone(true);
			// 		cout<<"Flow has completed!\n";
			// 	}
			// }
		}
	}
	else
	{

		cout<<"You are running simulation with out failures, You are not in Sproj 1 anymore! Please add -failure flag "<<endl;
	}

	finishThis = true;


	// ********************************** USEFUL CODE ENDS HERE *********************


	if(failures)
	{
		cout<<"fail"<<endl;
		cout<<100-100*(dc->downTime/(float(dc->all_flows.size())*runs))<<" Was the Availability"<<endl;
		ofstream fout;
		fout.open("failures.txt");
		string failStr = "";
		int len_cores = dc->all_cores.size();
		int len_switches = dc->all_switches.size();
		bool shouldBreak = false;

		for(int i=0; i<num_fails; i++)
		{
			if( failTimes[i] < end_delay)
			{
				shouldBreak = false;
				stringstream pI, le, dI, start, end, simTime;
				pI << failPID[i];
				le << failLevel[i];
				dI << failDID[i];
				start << failTimes[i];
				if( failComplete[i]+failTimes[i] < end_delay )
				{
					end << (failComplete[i]+failTimes[i]);
				}
				else
				{
					end << end_delay;
				}
				simTime << end_delay;

				failStr = failStr + "Failure: PodID: " + pI.str() + " Level: " + le.str() + " DeviceID: " + dI.str() + " ";
				for(int j=0; j<len_cores; j++)
				{
					if( (dc->all_cores[j]->getPodID() == failPID[i]) && (dc->all_cores[j]->getLevel() == failLevel[i]) && (dc->all_cores[j]->getDeviceID() ==failDID[i]) )
					{
						int num_up = dc->all_cores[j]->up_links.size();
						for(int l=0; l<num_up; l++)
						{
							stringstream index;
							stringstream upLink;
							index << l;
							upLink << dc->all_cores[j]->up_links[l]->getID();
							failStr = failStr + "Link: " + upLink.str() + " ";
						}
						int num_down = dc->all_cores[j]->down_links.size();
						for(int l=0; l<num_down; l++)
						{
							stringstream index;
							stringstream downLink;
							index << l;
							downLink << dc->all_cores[j]->down_links[l]->getID();
							failStr = failStr + "Link: " + downLink.str() + " ";
						}
						shouldBreak = true;
						break;
					}
				}
				if(!shouldBreak)
				{
					for(int j=0; j<len_switches; j++)
					{
						if( (dc->all_switches[j]->getPodID() == failPID[i]) && (dc->all_switches[j]->getLevel() == failLevel[i]) && (dc->all_switches[j]->getDeviceID() ==failDID[i]) )
						{
							int num_up = dc->all_switches[j]->up_links.size();
							for(int l=0; l<num_up; l++)
							{
								stringstream index;
								stringstream upLink;
								index << l;
								upLink << dc->all_switches[j]->up_links[l]->getID();
								failStr = failStr + "Link: " + upLink.str() + " ";
							}
							int num_down = dc->all_switches[j]->down_links.size();
							for(int l=0; l<num_down; l++)
							{
								stringstream index;
								stringstream downLink;
								index << l;
								downLink << dc->all_switches[j]->down_links[l]->getID();
								failStr = failStr + "Link: " + downLink.str() + " ";
							}
							shouldBreak = true;
							break;
						}
					}
				}
				failStr = failStr + "StartTime: " + start.str() + " EndTime: " + end.str() + " SimTime: " + simTime.str() + "\n";
			}
		}
		fout<<failStr;
		fout.close();
	}

	ofstream flowOut;
	flowOut.open("flows.txt");
	int num_flows = dc->all_flows.size();
	string flowStr = "";
	for(int i=0; i<num_flows; i++)
	{
		stringstream id, duration;
		id << dc->all_flows[i]->getID();
		duration << dc->all_flows[i]->getActive();
		flowStr = flowStr + " Flow: ID: " + id.str() + " Duration: " + duration.str() + "\n";
	}
	flowOut << flowStr;
	flowOut.close();

	pthread_exit(NULL);

	return 0;
}

void storeFailure(int pid, int level, int did, float fTime)
{
	failTimes.push_back(fTime);
	failPID.push_back(pid);
	failLevel.push_back(level);
	failDID.push_back(did);
	failed.push_back(false);
	failComplete.push_back(0.0);
}

void * pingFaults(void * args)
{
	struct timespec time1, time2;
	time1.tv_sec = 0;
	time1.tv_nsec = 1000000;	//this is 1 usec == 0.001 msec == 0.000001 sec
	int fault_runs = (fault_delay*1000000000)/time1.tv_nsec;	//calculating num runs to achieve the delay

	while(1)
	{
		// cout<<"here"<<endl;
		for(int i=0; i<fault_runs; i++)
		{
			if(nanosleep(&time1, &time2) < 0)
			{
				cout<<"Nanosleep() failed\n";
				exit(-1);
			}
			if(finishThis)
			{
				pthread_exit(NULL);
			}
		}
		//call the detect fault function

		// while(busy)
		// {
		// 	if(nanosleep(&time1, &time2) < 0)
		// 	{
		// 		cout<<"Nanosleep() failed\n";
		// 		exit(-1);
		// 	}
		// }
		// busy = true;
		run_faults = run_time;
//		cout<<"About to find faults!\n";
		dc->findFaults();
//		cout<<"Done finding faults!\n";
		// busy = false;

		if(finishThis)
		{
			pthread_exit(NULL);
		}
	}

}
