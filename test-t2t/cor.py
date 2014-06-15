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

def extract_dt(device,rms):
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
        if(device==d and string in row):
            r=row[9]
            if(r!='2'):
                continue
            downtime=int(find(row,otherS))
            if(string=='Down'):
                downtime=-downtime  
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



d=extract_dt('Link',rms)
single=0
double=0
triple=0
buff=0
for i in range(0,len(d)-3):
    print d[i],'on ',i,' th index'
    if(buff!=0):
        buff-=1
        continue
    if(d[i]==d[i+1]):
        if(d[i+1]==d[i+2]):
            triple+=1
            print 'got triple'
            buff=2
            continue
        else:
            double+=1
            print 'got double'
            buff=1
            continue
    else:
        print 'got single'
        single+=1


total=float(len(d))
print single/total
print 2*double/total
print 3*triple/total

