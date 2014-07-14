

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

	// cout<<"Number of run: "<<runs<<"\n";
	if(failures)
	{
		for(int i=0; i<runs; i++)
		{
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


	int downTime=0;
	int one=0;
	int two=0;
	int three=0;
	int vms;
	// for(int i=0;i<dc->tenant_flows.size();i++)
	// {
	// 	cout<<"links: "<<dc->tenant_flows[i]->links_pairs.size()<<" dt: "<<dc->tenant_flows[i]->downTime<<endl;
	// }

	// cout<<"Total Dt: "<<dc->downTime<<endl;
	// cout<<"Total flows: "<<dc->tenant_flows.size()<<endl;

	// cout<<dc->all_tenants.size()<<" was the number of accomodated tenants"<<endl;
	cout<<"Availability: "<<100-100*(dc->downTime/(float(dc->tenant_flows.size())*runs))<<"\n";
	// cout<<"Downtime due to level 1: "<<one<<endl;
	// cout<<"Downtime due to level 2: "<<two<<endl;
	// cout<<"Downtime due to level 3: "<<three<<endl;

	// cout<<"Total accepted: "<<dc->totalAccepted<<endl;
		// cout<<100-100*(dc->downTime/(float(dc->all_flows.size())*runs))<<" Was the Availability"<<endl;


	// ********************************** USEFUL CODE ENDS HERE *********************

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
