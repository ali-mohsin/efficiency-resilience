import random
f=open('newfile.txt','w')
for i in range(0,500):
    f.write("#define Flow -sourceId "+ str(random.randint(0,60))+" -destId "+str(random.randint(0,60))+" -rate 10M -size "+ str(random.randint(0,1000))+"G -startTime "+str(i*60*60)+"\n")
