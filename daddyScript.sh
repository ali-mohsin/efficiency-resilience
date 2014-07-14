#!/bin/bash

runs=5

for vm in 49
do
	for bw in 100
	do
		echo "Settings"
		echo "VM = "$vm", BW = "$bw

		outFile="./output/out_"$vm"_"$bw".txt"
		echo "Settings" > $outFile
		echo "VM = "$vm", BW = "$bw >> $outFile

		for run in $(seq 1 $runs)
		do
			echo "Run Number: "$run

			python tenant.py $vm $bw

			echo "" >> $outFile
			rm ./admin
			python parser.py
			cat admin_side.cpp >> main.cpp
			g++ -w -o admin main.cpp controller.cpp flow.cpp host.cpp link.cpp path.cpp switch.cpp topology.cpp -pthread
			echo "Started simulation - without replication...please wait..."
			echo $run" ================================" >> $outFile
			echo "Without Replication" >> $outFile
			./admin 5025 >> $outFile

			mv new_script.ns script.ns

			echo "" >> $outFile
			rm ./admin
			python parser.py
			cat admin_side.cpp >> main.cpp
			g++ -w -o admin main.cpp controller.cpp flow.cpp host.cpp link.cpp path.cpp switch.cpp topology.cpp -pthread
			echo "Started simulation - with 1:1 replication...please wait..."
			echo "With 1:1 Replication" >> $outFile
			./admin 5025 >> $outFile
		done

		echo "Results in: "$outFile
		echo ""

	done
done