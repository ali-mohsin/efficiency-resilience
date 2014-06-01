import csv

def find(arr,num):
    x=0
    for i in arr:
        if(i==num):
            return arr[x+1]
        x+=1
    return -1

def bw2int(rate):
    if(rate==-1):
        return -1
    rUnit=rate[len(rate)-1]
    rate=int(rate[0:len(rate)-1])
    rdiv=1
    if(rUnit=="K"):
        rdiv=1.0/1024.0
    if(rUnit=="G"):
        rdiv=1024
    return str(rate*rdiv)

with open('script.ns','rb') as fin:
    reader = csv.reader(fin,delimiter=' ')
    script=[]
    code=[]
    for row in reader:
        if(len(row)<2):
            continue
        script.append(row)


#    code.append("#include <sys/types.h>\n#include <sys/socket.h>\n#include <netinet/in.h>\n#include <arpa/inet.h>\n#include <netdb.h>\n#include <stdio.h>\n#include <unistd.h>\n\n#include <stdlib.h>\n#include <string.h>\n#include <signal.h>\n#include <errno.h>\n#include <stdarg.h>\n#include <iostream>\n#include <sstream>\n#include <fstream>\n#include <string>\n#include <pthread.h>\n#include <time.h>\n#include \"path.h\"\n#include \"link.h\"\n#include \"switch.h\"\n#include \"topology.h\"\n#include \"controller.h\"\nusing namespace std;\n#define PROTOPORT 1532\n#define QLEN 6\nextern int errno;\nfloat end_delay = 10.0;\nfloat stats_delay = 0.3;\nfloat fault_delay = 0.5;\nchar recvBuf[1024];\nbool finishThis = false;\nfloat run_time = 0.0;\nfloat run_stats = 0.0;\nfloat run_faults = 0.0;\nbool busy = false;\nController* dc;\nvoid sig_pipe(int n){fprintf(stderr, \"Broken pipe signal\");}\nint errexit(const char *format, ...);\nint listen_socket(int port, int qz);\nint connected_socket(int lsd);\nvoid createFlow(string str);\nvoid addFailure(string str);\nvoid * pingStats(void * args);\nvoid * pingFaults(void * args);\nint main (int argc, char *argv[])\n{\n")
    code.append("#include \"starter.h\"\n")
    code.append("int main (int argc, char *argv[])\n{\n")
    for row in script:
        header=row[0]
        if(header=="#define"):
            identifier=row[1]
            if(identifier=="Failure"):
                pod=int(find(row,"-pod"))
                level=int(find(row,"-level"))
                seq=int(find(row,"-seq"))
                sTime=int(find(row,"-startTime"))
                code.append("storeFailure("+str(pod)+","+str(level)+","+str(seq)+","+str(sTime)+ ");\n")
            if(identifier=="FatTree"):
                k=find(row,"-k")
                auto=find(row,'-auto')
                algo=find(row,"-algo")
                runFor=find(row,"-runFor")
                torCap=bw2int(find(row,"-torLinks"))
                aggrCap=bw2int(find(row,"-aggrLinks"))
                coreCap=bw2int(find(row,"-coreLinks"))
                fail=find(row,"-failures")
                red=find(row,"-reduncancy")
                if(fail=="enable"):
                    code.append("\tint failures=1;\n")
                else:
                    code.append("\tint failures=0;\n")


                if(red=="1:1"):
                    code.append("\tint oneToOne=1;\n")
                else:
                    code.append("\tint oneToOne=0;\n")


                if(algo=="default" and auto=='yes'):
                    line= "\tdc= new Controller("+k+","+torCap+","+aggrCap+","+coreCap+",oneToOne,"+runFor+",1);"
                    code.append(line)
                    auto=1
                elif(algo=='default'):
                    line= "\tdc= new Controller("+k+","+torCap+","+aggrCap+","+coreCap+",oneToOne,"+runFor+",0);"
                    code.append(line)
                    auto=0
                    
                alpha="int runFor="+str(runFor)+";"
                code.append(alpha)

            if(identifier=="flow" or identifier=="Flow" and auto==0):
                srcId=find(row,"-sourceId")
                dstId=find(row,"-destId")
                rate=bw2int(find(row,"-rate"))
                size=bw2int(find(row,"-size"))
                sTime=float(find(row,"-startTime"))

                line= "\tdc->instantiateFlow(dc->all_hosts["+srcId+"],dc->all_hosts["+ dstId +"],"+str(rate)+","+str(size)+","+str(sTime)+");"
                code.append(line)

    with open('main.cpp','w') as fout:
        for row in code:
            fout.write(row+'\n')

    fin.close()
    fout.close()
