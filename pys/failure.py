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
                downtime=downtime/10
            down_arr.append((downtime))
            arr.append(row)


down_arr.sort()
print down_arr

string=sys.argv[4]
total=float(sum(down_arr))
print max(down_arr)
arr=[0]*(max(down_arr)+1)

print 'hello'

count=len(down_arr)
for i in range(0,len(down_arr)):
    arr[down_arr[i]]+=float(1.0/count)

del down_arr
print 'h2'
print "Total failure time: "+str(total)


print 'here as well'

print 'plotting'


for i in range(1,len(arr)):
    arr[i]+=arr[i-1]

import numpy as np
# a = [ pow(10,i) for i in range(10) ]
# fig = plt.figure()
# ax = fig.add_subplot(2,1,1)

# ax.set_xscale('log')

# line, = ax.plot(a, color='blue', lw=2)
for i in range(0,10):
   arr.insert(0,0)

ax = plt.subplot(111)
ax.set_xscale("log", nonposx='clip')
ax.set_ylim([0,1])
ax.set_xlim([2,7])
plt.plot(arr)
plt.show()
