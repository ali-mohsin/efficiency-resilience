import random


with open('script.ns','w') as fout:
	fout.write("#define FatTree -k 20 -reduncancy e2e -sharing yes -oct yes -repeatForAll  -algo default -torLinks 1G -aggrLinks 1G -coreLinks 1G -failures enable -runFor 30000000\n")

	for i in range(0,10000):
		num=int(random.expovariate(1/49.0))
		bw=int(random.expovariate(1/100.0))
		if(num<2):
			num=2
		if(bw<1):
			bw=1
		mystr="#define Tenant -vm "+str(num)+" -bw "+str(bw)+"\n"
		fout.write(mystr)
