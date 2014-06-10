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

import sys
device=sys.argv[1]
cat=sys.argv[2]
with open(sys.argv[3],'rb') as fin:
    reader = csv.reader(fin,delimiter=' ')
    rms=[]
    code=[]
    for row in reader:
        if(len(row)<2):
            continue
        rms.append(row)

    string=sys.argv[4]
    if(string=='Down'):
        otherS='downFor:'
    else:
        otherS="upFor:"
    arr=[]
    down_arr=[]
    for row in rms:
        d=row[0]
        t=row[1]
        if(device==d and string in row and t==cat):
            downtime=int(find(row,otherS))
            if(string=='Down'):
                downtime=-downtime
            else:  
                downtime=downtime/100
            down_arr.append((downtime))
            arr.append(row)

print down_arr
# import numpy
# a = down_arr # your array of numbers
# num_bins = 40
# counts, bin_edges = numpy.histogram(a, bins=num_bins, normed=True)
# cdf = numpy.cumsum(counts)
# print sum(cdf)
# plt.plot(bin_edges[1:], cdf)
# plt.show()
total=float(sum(down_arr))
print max(down_arr)
arr=[0]*(max(down_arr)+1)

print 'hello'

for i in range(0,len(down_arr)):
    arr[down_arr[i]]+=1


del down_arr
print 'h2'

print "Total failure time: "+str(total)

for i in range(1,len(arr)):
    arr[i]+=arr[i-1]

print 'here as well'
# for i in range(1,len(arr)):
#     arr[i]=float(arr[i])/total


print 'plotting'

import numpy as np
# a = [ pow(10,i) for i in range(10) ]
# fig = plt.figure()
# ax = fig.add_subplot(2,1,1)

# ax.set_xscale('log')

# line, = ax.plot(a, color='blue', lw=2)

ax = plt.subplot(224)
ax.set_xscale("log", nonposx='clip')
plt.plot(arr)
plt.show()
# ten=1
# x=[]
# y=[]
# for i in range(0,len(arr)):
#     if(pow(10,ten)==i):
#         x.append(pow(10,ten))
#         ten+=1
#         y.append(arr[i])

# plt.plot(x,y)
# plt.show()
# print arr
#     num=0
#     for row in rms:
#     	if(row[0]=="Link:"):
#     		id=int(find(row,"LinkID:"))
#     		if(id>num):
#     			num=id

#     num+=1
#     links=[]
#     up=[0]*num
#     down=[0]*num
#     colors=['']*num
#     downArr=[0]*num
#     flow=[]
#     comp=[]
#     for row in rms:
#     	if(row[0]=="Failure:"):
#     		upFail=findAll(row,"Link:")
#     		sTime=float(find(row,"StartTime:"))
#     		eTime=float(find(row,"EndTime:"))
#     		downTime=eTime-sTime
#     		total=float(find(row,"SimTime:"))
#     		downTime=float(downTime)/float(total)
#     		for i in upFail:
#     			downArr[i]+=(downTime*100)

#         if(row[1]=="Flow:"):
#             id=int(find(row,"ID:"))
#             dur=float(find(row,"Duration:"))

#             flow.append(id)
#             comp.append(dur)


#     	if(row[0]=="Link:"):
#     		label=find(row,"Label:")
#     		id=int(find(row,"LinkID:"))
#     		upUtil=int(find(row,"Up_Util:"))
#     		downUtil=int(find(row,"Down_Util:"))
#     		if(id not in links):
#     			links.append(id)
#     			up[id]=upUtil
#     			down[id]=downUtil
#     			if(label=="Aggr"):
# 	    			colors[id]='b'
#     			if(label=="Tor"):
# 	    			colors[id]='r'
#     			if(label=="Core"):
# 	    			colors[id]='g'

# #	    if(row[0]=="Flow"):
# #    		id=int(find(row,"ID:"))
# #    		dur=float(find(row,"Duration:"))
#  #   		flow.append(id)
# #	    		comp.append(dur)
	
# #print "*********************** Simulation Stats *****************************"
# # print float(sum(up))/float(len(up))," %  was the average link Utilization"
# #print float(sum(comp))/float(len(comp))," seconds was the average Flow Completion Time"
# #print len(flow), "flows were successfully completed"

# print "\t\t\t\tPress any key to plot graphs..."
# raw_input()

# width=0.5
# plt.figure(0)
# plt.axis([0,num,0,100])
# torx=[]
# tory=[]
# torydown=[]

# aggrx=[]
# aggry=[]
# aggrydown=[]

# corex=[]
# corey=[]
# coreydown=[]

# for i in range(0,len(links)):
# 	if(colors[i]=='r'):
# 		torx.append(links[i])
# 		tory.append(up[i])
# 		torydown.append(down[i])
# 	if(colors[i]=='g'):
# 		corex.append(links[i])
# 		corey.append(up[i])
# 		coreydown.append(down[i])
# 	if(colors[i]=='b'):
# 		aggrx.append(links[i])
# 		aggry.append(up[i])
# 		aggrydown.append(down[i])
# plt.bar(torx,tory,  width, color='r',label="Tor Links")
# plt.bar(aggrx,aggry,  width, color='b',label="Aggr Links")
# plt.bar(corex,corey,  width, color='g',label="Core Links")
# plt.legend()
# plt.xlabel("Link ID")
# plt.ylabel("Bandwidth Utilization (%)")
# plt.title("Link Utilization")
# # plt.figure(1)
# # plt.bar(torx,torydown,  width, color='r',label="Tor Links")
# # plt.bar(aggrx,aggrydown,  width, color='b',label="Aggr Links")
# # plt.bar(corex,coreydown,  width, color='g',label="Core Links")
# # plt.axis([0,num,0,100])
# # plt.xlabel("Link ID")
# # plt.legend()
# # plt.ylabel("Bandwidth Utilization (%)")
# # plt.title("Down Link Utilization")
# #plt.figure(1)
# #plt.bar(range(0,num),downArr, width, color='r')
# #plt.axis([0,num,0,100])
# #plt.xlabel("Link ID")
# ##plt.legend()
# #plt.ylabel("Down Time (as % of Total Time)")
# #plt.title("Down Times For Links")


# #plt.figure(2)
# #plt.bar(flow,comp ,width, color='r')
# #plt.axis([0,len(flow),0,max(comp)+10])
# #plt.xlabel("Flow Id")
# #plt.legend()
# #plt.ylabel("Completion Time (s)")
# #plt.title("Flow Completion Times")
# #plt.show()
# from subprocess import call
# call(["python", "simu.py"])
# # plt.figure(1)
# # plt.bar(torx,torydown,  width, color='r',label="Tor Links")
# # plt.bar(aggrx,aggrydown,  width, color='b',label="Aggr Links")
# # plt.bar(corex,coreydown,  width, color='g',label="Core Links")
# # plt.axis([0,num,0,100])
# # plt.xlabel("Link ID")
# # plt.legend()
# # plt.ylabel("Bandwidth Utilization (%)")
# # plt.title("Down Link Utilization")
# #plt.figure(1)
# #plt.bar(range(0,num),downArr, width, color='r')
# #plt.axis([0,num,0,100])
# #plt.xlabel("Link ID")
# ##plt.legend()
# #plt.ylabel("Down Time (as % of Total Time)")
# #plt.title("Down Times For Links")


# #plt.figure(2)
# #plt.bar(flow,comp ,width, color='r')
# #plt.axis([0,len(flow),0,max(comp)+10])
# #plt.xlabel("Flow Id")
# #plt.legend()
# #plt.ylabel("Completion Time (s)")
# #plt.title("Flow Completion Times")
