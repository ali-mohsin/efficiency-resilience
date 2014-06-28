import random
vms=[]

with open('script.ns','w') as fout:
	fout.write("#define FatTree -k 30 -reduncancy none -sharing no -oct yes -repeatForAll  -algo default -torLinks 1G -aggrLinks 1G -coreLinks 1G -failures enable -runFor 30000000\n")

	for i in range(0,500):
		num=int(random.expovariate(1/49.0))
		bw=int(random.expovariate(1/100.0))
		vms.append(num)
		if(num<2):
			num=2
		if(bw<1):
			bw=1
		mystr="#define Tenant -vm "+str(num)+" -bw "+str(bw)+"\n"
		fout.write(mystr)


import numpy as np
print np.mean(vms)
