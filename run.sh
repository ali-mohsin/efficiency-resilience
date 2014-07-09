#!/bin/bash

echo "Generated tenant request pattern"
python tenant.py 49 100

echo "Preparing simulation - without replication"
rm *.txt
rm ./admin
python parser.py
cat admin_side.cpp >> main.cpp
g++ -w -o admin main.cpp controller.cpp flow.cpp host.cpp link.cpp path.cpp switch.cpp topology.cpp -pthread
echo "Started simulation...please wait..."
echo "Without Replication" > ./output/output.txt
./admin 5025 >> ./output/output.txt

echo "" >> ./output/output.txt
mv new_script.ns script.ns

echo "Preparing simulation - with 1:1 replication"
rm *.txt
rm ./admin
python parser.py
cat admin_side.cpp >> main.cpp
g++ -ggdb -w -o admin main.cpp controller.cpp flow.cpp host.cpp link.cpp path.cpp switch.cpp topology.cpp -pthread
echo "Started simulation...please wait..."
echo "With 1:1 Replication" >> ./output/output.txt
./admin 5025 >> ./output/output.txt
