clear
rm flows.txt
rm logs.txt
rm ./admin
python parser.py
cat admin_side.cpp >> main.cpp
g++ -ggdb -w -o admin main.cpp controller.cpp flow.cpp host.cpp link.cpp path.cpp switch.cpp topology.cpp -pthread
gdb ./admin 5025
rm *.txt
