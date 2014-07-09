import sys
import random
vms=[]
bws=[]

with open('script.ns','w') as fout:
	randValue = random.random()
	randValue = 1000000 * randValue
	ranValue = int(randValue)
	randValue = float(ranValue)/1000000
	fout.write("#define FatTree -k 40 -reduncancy none -sharing no -oct yes -repeatForAll -algo default -torLinks 1G -aggrLinks 1G -coreLinks 1G -failures enable -runFor 30000000 -seed " + str(randValue) +"\n")

	vm_mean = float(sys.argv[1])
	bw_mean = float(sys.argv[2])

	# print vm_mean
	# print bw_mean

	for i in range(0,2500):
		while True:
			num=int(random.expovariate(1/vm_mean))
			bw=int(random.expovariate(1/bw_mean))
			
			if bw<1000:
				break

		if(num<2):
			num=2
		if(bw<1):
			bw=1
		
		if(num > 150 or bw > 500):
			continue

		vms.append(num)
		bws.append(bw)
		mystr="#define Tenant -vm "+str(num)+" -bw "+str(bw)+"\n"
		fout.write(mystr)

# sum_vms = sum(vms)
# num_vms = len(vms)
# mean_vm = float(sum_vms)/float(num_vms)

# sum_bws = sum(bws)
# num_bws = len(bws)
# mean_bw = float(sum_bws)/float(num_bws)

# print mean_vm
# print mean_bw
