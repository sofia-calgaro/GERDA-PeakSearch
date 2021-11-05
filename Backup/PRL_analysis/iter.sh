#! /bin/bash

make clean
make -s

sum_array=()
sum_array2=()
for (( i=0; i<2; i++ ))
do
	./peak_search.sh 1500 1 && 
	
	#=======================================================
	declare -a txt_content # array of the .txt content
	txt_content=(`cat "output.txt"`) &&

	sum=0
	for j in ${txt_content[@]}
	do
		let sum+=$j
	done &&
	
	sum_array[i]=$sum &&
	
	#printf "%s\n" "${sum_array[$i]}" > p0_warnings.txt &&
	
	> "output.txt" &&
	
	#=======================================================
	declare -a txt_content2 # array of the .txt content
	txt_content2=(`cat "output2.txt"`) &&

	sum_2=0
	for j in ${txt_content2[@]}
	do
		let sum_2+=$j
	done &&
	
	sum_array2[i]=$sum_2 &&
	
	#printf "%s\n" "${sum_array2[$i]}" > p1_warnings.txt
	
	> "output2.txt"
done 


printf "%s\n" "${sum_array[@]}" > p0_warnings.txt
printf "%s\n" "${sum_array2[@]}" > p1_warnings.txt
