import csv
import matplotlib.pyplot as plt

def find(arr,num):
    x=0
    for i in arr:
        if(i==num):
            return arr[x+1]
        x+=1
    return -1


def findAll(arr,num):
    x=0
    ans=[]
    for i in arr:
        if(i==num):
            ans.append(int(arr[x+1]))
        x+=1

    return ans

with open('logs.txt','rb') as fin:
    reader = csv.reader(fin,delimiter=' ')
    rms=[]
    code=[]
    for row in reader:
        if(len(row)<2):
            continue
        rms.append(row)

    num=0
    for row in rms:
    	if(row[0]=="Link:"):
    		id=int(find(row,"LinkID:"))
    		if(id>num):
    			num=id

    num+=1
    links=[]
    up=[0]*num
    down=[0]*num
    colors=['']*num
    downArr=[0]*num
    flow=[]
    comp=[]
    for row in rms:
    	if(row[0]=="Failure:"):
    		upFail=findAll(row,"Link:")
    		sTime=float(find(row,"StartTime:"))
    		eTime=float(find(row,"EndTime:"))
    		downTime=eTime-sTime
    		total=float(find(row,"SimTime:"))
    		downTime=float(downTime)/float(total)
    		for i in upFail:
    			downArr[i]+=(downTime*100)

        if(row[1]=="Flow:"):
            id=int(find(row,"ID:"))
            dur=float(find(row,"Duration:"))

            flow.append(id)
            comp.append(dur)


    	if(row[0]=="Link:"):
    		label=find(row,"Label:")
    		id=int(find(row,"LinkID:"))
    		upUtil=int(find(row,"Up_Util:"))
    		downUtil=int(find(row,"Down_Util:"))
    		if(id not in links):
    			links.append(id)
    			up[id]=upUtil
    			down[id]=downUtil
    			if(label=="Aggr"):
	    			colors[id]='b'
    			if(label=="Tor"):
	    			colors[id]='r'
    			if(label=="Core"):
	    			colors[id]='g'

#	    if(row[0]=="Flow"):
#    		id=int(find(row,"ID:"))
#    		dur=float(find(row,"Duration:"))
 #   		flow.append(id)
#	    		comp.append(dur)
	
#print "*********************** Simulation Stats *****************************"
# print float(sum(up))/float(len(up))," %  was the average link Utilization"
#print float(sum(comp))/float(len(comp))," seconds was the average Flow Completion Time"
#print len(flow), "flows were successfully completed"

print "\t\t\t\tPress any key to plot graphs..."
raw_input()

width=0.5
plt.figure(0)
plt.axis([0,num,0,100])
torx=[]
tory=[]
torydown=[]

aggrx=[]
aggry=[]
aggrydown=[]

corex=[]
corey=[]
coreydown=[]

for i in range(0,len(links)):
	if(colors[i]=='r'):
		torx.append(links[i])
		tory.append(up[i])
		torydown.append(down[i])
	if(colors[i]=='g'):
		corex.append(links[i])
		corey.append(up[i])
		coreydown.append(down[i])
	if(colors[i]=='b'):
		aggrx.append(links[i])
		aggry.append(up[i])
		aggrydown.append(down[i])
plt.bar(torx,tory,  width, color='r',label="Tor Links")
plt.bar(aggrx,aggry,  width, color='b',label="Aggr Links")
plt.bar(corex,corey,  width, color='g',label="Core Links")
plt.legend()
plt.xlabel("Link ID")
plt.ylabel("Bandwidth Utilization (%)")
plt.title("Link Utilization")
# plt.figure(1)
# plt.bar(torx,torydown,  width, color='r',label="Tor Links")
# plt.bar(aggrx,aggrydown,  width, color='b',label="Aggr Links")
# plt.bar(corex,coreydown,  width, color='g',label="Core Links")
# plt.axis([0,num,0,100])
# plt.xlabel("Link ID")
# plt.legend()
# plt.ylabel("Bandwidth Utilization (%)")
# plt.title("Down Link Utilization")
#plt.figure(1)
#plt.bar(range(0,num),downArr, width, color='r')
#plt.axis([0,num,0,100])
#plt.xlabel("Link ID")
##plt.legend()
#plt.ylabel("Down Time (as % of Total Time)")
#plt.title("Down Times For Links")


#plt.figure(2)
#plt.bar(flow,comp ,width, color='r')
#plt.axis([0,len(flow),0,max(comp)+10])
#plt.xlabel("Flow Id")
#plt.legend()
#plt.ylabel("Completion Time (s)")
#plt.title("Flow Completion Times")
#plt.show()
from subprocess import call
call(["python", "simu.py"])
# plt.figure(1)
# plt.bar(torx,torydown,  width, color='r',label="Tor Links")
# plt.bar(aggrx,aggrydown,  width, color='b',label="Aggr Links")
# plt.bar(corex,coreydown,  width, color='g',label="Core Links")
# plt.axis([0,num,0,100])
# plt.xlabel("Link ID")
# plt.legend()
# plt.ylabel("Bandwidth Utilization (%)")
# plt.title("Down Link Utilization")
#plt.figure(1)
#plt.bar(range(0,num),downArr, width, color='r')
#plt.axis([0,num,0,100])
#plt.xlabel("Link ID")
##plt.legend()
#plt.ylabel("Down Time (as % of Total Time)")
#plt.title("Down Times For Links")


#plt.figure(2)
#plt.bar(flow,comp ,width, color='r')
#plt.axis([0,len(flow),0,max(comp)+10])
#plt.xlabel("Flow Id")
#plt.legend()
#plt.ylabel("Completion Time (s)")
#plt.title("Flow Completion Times")
