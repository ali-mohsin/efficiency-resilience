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

def extract_dt(device,cat,rms):
    string=sys.argv[1]
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
                downtime=-downtime+70
            else:  
                downtime=downtime/10
            down_arr.append((downtime))

    return down_arr


def plot_cdf(down_arr,labels,markers,colors):
    down_arr.sort()
    arr=[0]*(max(down_arr)+1)
    count=len(down_arr)
    for i in range(0,len(down_arr)):
        arr[down_arr[i]]+=float(1.0/count)
    del down_arr
    for i in range(1,len(arr)):
        arr[i]+=arr[i-1]

    ax = plt.subplot(111)
    ax.set_xscale("log", nonposx='clip')
    ax.set_ylim([0,1])
    plt.plot(arr,label=labels,marker=markers, color=colors)


with open(sys.argv[2],'rb') as fin:
    reader = csv.reader(fin,delimiter=' ')
    rms=[]
    for row in reader:
        if(len(row)<2):
            continue
        rms.append(row)



dev=sys.argv[3]
markers=[]
colors=[]

if(dev=='Link'):
    markers=['o','x']
    colors=['r','k']
    d=extract_dt(dev,'Core',rms)
    plot_cdf(d,"Core "+dev,markers[1],colors[1])

if(dev=='Switch'):
   markers=['D','v']
   colors=['c',(255/255.0,105/255.0,180/255.0)]
 

d1=extract_dt(dev,'Tor',rms)
d2=extract_dt(dev,'Aggr',rms)
plot_cdf(d1,"Tor "+dev,markers[0],colors[0])
plot_cdf(d2,"Aggr "+dev,markers[0],colors[0])
plt.legend(loc=2)
plt.show()