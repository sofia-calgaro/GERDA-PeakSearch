#! /bin/bash



#------------------------------------------------------------------------------------------------------------------------------------------ VARIABLES
#         Pb212   Pb214   Pb214   Pb214   Ac228    e+e-    Kr85   Tl208   Bi214   Ac228   Ac228
E_gamma=('238.6' '242.0' '295.2' '352.0' '478.3' '511.0' '514.0' '583.2' '609.3' '911.2' '969.0')

readonly a=0.28 # readonly = constant value
readonly b=0.000583

read -p " What energy value (E0) do you want to study? "  E0 # -p = to assign the input value to the variable E0

x1=`echo "$(( E0-12 ))" | bc`
x2=`echo "$(( E0+12 ))" | bc`
echo " The fit window is given by [x1=$x1;x2=$x2] (# of bins = $(( x2-x1 )))" 



#------------------------------------------------------------------------------------------------------------------------------------------ PEAK SEARCH 
output=('0' '0' '0' '0' '0' '0' '0' '0' '0' '0' '0') 

for i in {0..10..1}
do	
	FWHM=`echo "sqrt(8*l(2))*sqrt($a+$b*${E_gamma[i]})" | bc -l`
	
	
	
	if [ "$i" -lt 10 ] # suppose i=10: then E_gamma[10+1] does not exist!
	then
		FWHM_plus1=`echo "sqrt(8*l(2))*sqrt($a+$b*${E_gamma[$i+1]})" | bc -l` 
	fi
	
	
	if [ "$i" -gt 0 ] # suppose i=0: then E_gamma[0-1] does not exist!
	then
		FWHM_minus1=`echo "sqrt(8*l(2))*sqrt($a+$b*${E_gamma[$i-1]})" | bc -l` 
	fi
	
	
	
	# Analysis for i = 2, 3, 4, 7, 8, 9, 10
	if [[ "$i" -ge 2 && "$i" -le 4 ]] || [ "$i" -ge 7 ]
	then
		#================================================================= OUTSIDE-NEAR + OUTSIDE-NEAR   => es. E0 = 596, 597
		if (  ( (( $(echo "$x1-${E_gamma[i]}<2*$FWHM" | bc -l) )) && (( $(echo "$x1-${E_gamma[i]}>0" | bc -l) )) ) && ( (( $(echo "${E_gamma[i+1]}-$x2<2*$FWHM_plus1" | bc -l) )) && (( $(echo "${E_gamma[i+1]}-$x2>0" | bc -l) )) )  ) && (( $(echo "$i<10" | bc -l) ))
		then
			output[$i]=1
			printf " Peaks are: OUTSIDE-NEAR + OUTSIDE-NEAR\n"
			break
		
		#================================================================= INSIDE-NEAR + OUTSIDE-NEAR   => es. E0 = 594, 595
		elif (  ( (( $(echo "${E_gamma[i]}-$x1<2*$FWHM" | bc -l) )) && (( $(echo "${E_gamma[i]}-$x1>0" | bc -l) )) ) && ( (( $(echo "${E_gamma[i+1]}-$x2<2*$FWHM_plus1" | bc -l) )) && (( $(echo "${E_gamma[i+1]}-$x2>0" | bc -l) )) )  ) && (( $(echo "$i<10" | bc -l) ))
		then
			output[$i]=2
			printf " Peaks are: INSIDE-NEAR + OUTSIDE-NEAR\n"
			break
		
		#================================================================= OUTSIDE-NEAR + INSIDE-NEAR   => es. E0 = 598
		elif (  ( (( $(echo "$x1-${E_gamma[i]}<2*$FWHM" | bc -l) )) && (( $(echo "$x1-${E_gamma[i]}>0" | bc -l) )) ) && ( (( $(echo "$x2-${E_gamma[i+1]}<2*$FWHM_plus1" | bc -l) )) && (( $(echo "$x2-${E_gamma[i+1]}>0" | bc -l) )) )  ) && (( $(echo "$i<10" | bc -l) ))
		then
			output[$i]=3
			printf " Peaks are: OUTSIDE-NEAR + INSIDE-NEAR\n"
			break
				
		#================================================================= OUTSIDE-NEAR
		elif ( (( $(echo "$x1-${E_gamma[i]}<2*$FWHM" | bc -l) )) && (( $(echo "$x1-${E_gamma[i]}>0" | bc -l) )) ) || ( (( $(echo "${E_gamma[i]}-$x2<2*$FWHM" | bc -l) )) && (( $(echo "${E_gamma[i]}-$x2>0" | bc -l) )) )
		then 
			output[$i]=4
			printf " Peak is: OUTSIDE-NEAR\n"
			break
				
				 
		#================================================================= INSIDE-NEAR
		elif ( (( $(echo "${E_gamma[i]}-$x1<2*$FWHM" | bc -l) )) && (( $(echo "${E_gamma[i]}-$x1>0" | bc -l) )) ) || ( (( $(echo "x2-${E_gamma[i]}<2*$FWHM" | bc -l) )) && (( $(echo "x2-${E_gamma[i]}>0" | bc -l) )) )
		then 	
			output[$i]=5
			printf " Peak is: INSIDE-NEAR\n"
			break
				 
		#================================================================= INSIDE
		elif (( $(echo "${E_gamma[i]}-$x1>2*$FWHM" | bc -l) )) && (( $(echo "$x2-${E_gamma[i]}>2*$FWHM" | bc -l) ))
		then
			output[$i]=6
			printf " Peak is: INSIDE\n"
			break
		
		#================================================================= x1=E V x2=E
		elif (( $(echo "${E_gamma[i]}==$x1" | bc -l) )) || (( $(echo "${E_gamma[i]}==x2" | bc -l) ))
		then
			output[$i]=7
			printf " Peak is: =x1 or =x2\n"
			break
		
		#================================================================= NO PEAKS
		else
			printf ""
		fi
		
		
		
	# Analysis for i = 0, 1, 5, 6
	else
		#================================================================= INSIDE + INSIDE
		if (( $(echo "${E_gamma[i]}-$x1>2*$FWHM" | bc -l) )) && (( $(echo "$x2-${E_gamma[i+1]}>2*$FWHM_plus1" | bc -l) ))
		then
			output[$i]=8
			printf " Peaks are: INSIDE + INSIDE\n"
			break
			
		#================================================================= INSIDE + INSIDE-NEAR
		elif (( $(echo "${E_gamma[i]}-$x1>2*$FWHM" | bc -l) )) && ( (( $(echo "$x2-${E_gamma[i+1]}<2*$FWHM_plus1" | bc -l) )) && (( $(echo "$x2-${E_gamma[i+1]}>0" | bc -l) )) )
		then
			output[$i]=9
			printf " Peaks are: INSIDE + INSIDE-NEAR\n"
			break
			
		#================================================================= INSIDE-NEAR + INSIDE
		elif ( (( $(echo "${E_gamma[i]}-$x1<2*$FWHM" | bc -l) )) && (( $(echo "${E_gamma[i]}-$x1>0" | bc -l) )) ) && (( $(echo "$x2-${E_gamma[i+1]}>2*$FWHM_plus1" | bc -l) ))
		then
			output[$i]=10
			printf " Peaks are: INSIDE-NEAR + INSIDE\n"
			break
					
		#================================================================= INSIDE-NEAR + INSIDE-NEAR
		elif ( (( $(echo "${E_gamma[i]}-$x1<2*$FWHM" | bc -l) )) && (( $(echo "${E_gamma[i]}-$x1>0" | bc -l) )) ) && ( (( $(echo "$x2-${E_gamma[i+1]}<2*$FWHM_plus1" | bc -l) )) && (( $(echo "$x2-${E_gamma[i+1]}>0" | bc -l) )) )
		then
			output[$i]=11
			printf " Peaks are: INSIDE-NEAR + INSIDE-NEAR\n"
			break
		
		#================================================================= INSIDE + OUTSIDE-NEAR
		elif ( (( $(echo "${E_gamma[i]}-$x1>2*$FWHM" | bc -l) )) && (( $(echo "$x2-${E_gamma[i]}>2*$FWHM" | bc -l) )) ) && ( (( $(echo "${E_gamma[i+1]}-$x2<2*$FWHM_plus1" | bc -l) )) && (( $(echo "${E_gamma[i+1]}-$x2>0" | bc -l) )) )
		then
			output[$i]=12
			printf " Peaks are: INSIDE + OUTSIDE-NEAR\n"
			break
			
		#================================================================= INSIDE-NEAR + OUTSIDE-NEAR
		elif  ( ( (( $(echo "${E_gamma[i]}-$x1<2*$FWHM" | bc -l) )) && (( $(echo "${E_gamma[i]}-$x1>0" | bc -l) )) ) || ( (( $(echo "$x2-${E_gamma[i]}<2*$FWHM" | bc -l) )) && (( $(echo "$x2-${E_gamma[i]}>0" | bc -l) )) ) ) && ( (( $(echo "${E_gamma[i+1]}-$x2<2*$FWHM_plus1" | bc -l) )) && (( $(echo "${E_gamma[i+1]}-$x2>0" | bc -l) )) )
		
		then
			output[$i]=13
			printf " Peaks are: INSIDE-NEAR + OUTSIDE-NEAR\n"
			break
			
		#================================================================= OUTSIDE-NEAR + INSIDE-NEAR
		elif  ( (( $(echo "$x1-${E_gamma[i]}<2*$FWHM" | bc -l) )) && (( $(echo "$x1-${E_gamma[i]}>0" | bc -l) )) && ( (( $(echo "$x2-${E_gamma[i+1]}<2*$FWHM_plus1" | bc -l) )) && (( $(echo "$x2-${E_gamma[i+1]}>0" | bc -l) )) || (( $(echo "${E_gamma[i+1]}-$x1<2*$FWHM_plus1" | bc -l) )) && (( $(echo "${E_gamma[i+1]}-$x1>0" | bc -l) )) ) )
		then
			output[$i]=14
			printf " Peaks are: OUTSIDE-NEAR + INSIDE-NEAR\n"
			break
		
		#================================================================= i=x2 + OUTSIDE-NEAR
		elif (( $(echo "${E_gamma[i]}==$x2" | bc -l) )) && ( (( $(echo "${E_gamma[i+1]}-$x2<2*$FWHM_plus1" | bc -l) )) && (( $(echo "${E_gamma[i+1]}-$x2>0" | bc -l) )) ) 
		then
			output[$i]=15
			printf " Peaks are: =x2 + OUTSIDE-NEAR\n"
			break
					
		#================================================================= INSIDE-NEAR + i+1=x2
		elif ( (( $(echo "$x2-${E_gamma[i]}<2*$FWHM" | bc -l) )) && (( $(echo "$x2-${E_gamma[i]}>0" | bc -l) )) ) && (( $(echo "${E_gamma[i+1]}==$x2" | bc -l) ))
		then
			output[$i]=16
			printf " Peaks are: INSIDE-NEAR + =x2\n"
			break
		
		#================================================================= INSIDE + i+1=x2
		elif ( (( $(echo "$x2-${E_gamma[i]}>2*$FWHM" | bc -l) )) && (( $(echo "${E_gamma[i]}-$x1>2*$FWHM" | bc -l) )) ) && (( $(echo "${E_gamma[i+1]}==$x2" | bc -l) ))
		then
			output[$i]=17
			printf " Peaks are: INSIDE + =x2\n"
			break
		
		#================================================================= OUTSIDE-NEAR + i+1=x1
		elif ( (( $(echo "$x1-${E_gamma[i]}<2*$FWHM" | bc -l) )) && (( $(echo "$x1-${E_gamma[i]}>0" | bc -l) )) ) && (( $(echo "${E_gamma[i+1]}==$x1" | bc -l) ))
		then
			output[$i]=18
			printf " Peaks are: OUTSIDE-NEAR + =x1\n"
			break
			
		#================================================================= i=x1 + INSIDE-NEAR
		elif (( $(echo "${E_gamma[i]}==$x1" | bc -l) )) && ( (( $(echo "${E_gamma[i+1]}-$x1<2*$FWHM_plus1" | bc -l) )) && (( $(echo "${E_gamma[i+1]}-$x1>0" | bc -l) )) ) 
		then
			output[$i]=19
			printf " Peaks are: =x1 + INSIDE-NEAR\n"
			break
				
		#================================================================= OUTSIDE + i=x1
		elif (( $(echo "$i>0" | bc -l) )) && ( (( $(echo "$x1-${E_gamma[i-1]}>2*$FWHM_minus1" | bc -l) )) && (( $(echo "${E_gamma[i]}==$x1" | bc -l) )) )
		then
			output[$i]=20
			printf " Peaks are: OUTSIDE + =x1\n"
			break
			
		#================================================================= OUTSIDE-NEAR	+ OUTSIDE
		elif ( (( $(echo "${E_gamma[i]}-$x2<2*$FWHM" | bc -l) )) && (( $(echo "${E_gamma[i]}-$x2>0" | bc -l) )) ) && (( $(echo "${E_gamma[i+1]}-$x2>2*$FWHM_plus1" | bc -l) ))
		then
			output[$i]=21
			printf " Peaks are: OUTSIDE-NEAR + OUTSIDE\n"
			break
			
		#================================================================= OUTSIDE + OUTSIDE-NEAR
		elif (( $(echo "$i>0" | bc -l) )) && ( ( (( $(echo "$x1-${E_gamma[i-1]}>2*$FWHM_minus1" | bc -l) )) && ( (( $(echo "$x1-${E_gamma[i]}<2*$FWHM" | bc -l) )) ) && (( $(echo "$x1-${E_gamma[i]}>0" | bc -l) )) ) )
		then
			output[$i]=22
			printf " Peaks are: OUTSIDE + OUTSIDE-NEAR\n"
			break
			
		#=================================================================	
		else
			printf ""	
		fi
	fi	

done



#------------------------------------------------------------------------------------------------------------------------------------------ xL, xR
k=0
# search the first element output[k] which is different from zero
while  [ "$k" -le 10 ] && [ "${output[$k]}" -eq 0 ]
do
	k=`echo "$(( k+1 ))" | bc`
done

if [ "$k" -eq 11 ] # NO PEAKS
then
	xL=$x1
	xR=$x2
else
	#================================================================= INSIDE || INSIDE + INSIDE
	if [ "${output[$k]}" -eq 6 ] || [ "${output[$k]}" -eq 8 ]
	then
		xL=$x1
		xR=$x2

	#================================================================= OUTSIDE-NEAR + OUTSIDE-NEAR
	elif [ "${output[$k]}" -eq 1 ] && [ "$k" -lt 10 ]
	then
		xL=`echo "$x1+sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
		xR=`echo "$x2-sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`

	#================================================================= INSIDE-NEAR + OUTSIDE-NEAR
	elif [ "${output[$k]}" -eq 2 ] && [ "$k" -lt 10 ] #????
	then
		xL=`echo "$x1-sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
		xR=`echo "$x2-sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`

	#================================================================= OUTSIDE-NEAR + INSIDE-NEAR
	elif [ "${output[$k]}" -eq 3 ] && [ "$k" -lt 10 ] #????
	then
		xL=`echo "$x1+sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
		xR=`echo "$x2+sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
					
	#================================================================= OUTSIDE-NEAR
	elif [ "${output[$k]}" -eq 4 ] 
	then
		xL=`echo "$x1+sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
		xR=`echo "$x2-sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
		
	#================================================================= INSIDE-NEAR
	elif [ "${output[$k]}" -eq 5 ]
	then
		xL=`echo "$x1-sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
		xR=`echo "$x2+sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
		
	#================================================================= x1=E V x2=E
	elif [ "${output[$k]}" -eq 7 ] 
	then
		xL=`echo "$x1+1.5*sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
		xR=`echo "$x2-1.5*sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
			
	#================================================================= INSIDE + INSIDE-NEAR
	elif [ "${output[$k]}" -eq 9 ] && [ "$k" -lt 10 ]
	then
		xL=`echo "$x1-sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
		xR=`echo "$x2+sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
	
	#================================================================= INSIDE-NEAR + INSIDE
	elif [ "${output[$k]}" -eq 10 ] 
	then
		xL=`echo "$x1-sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
		xR=`echo "$x2+sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
	
	#================================================================= INSIDE-NEAR + INSIDE-NEAR
	elif [ "${output[$k]}" -eq 11 ] && [ "$k" -lt 10 ]
	then
		xL=`echo "$x1-sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
		xR=`echo "$x2+sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
	
	#================================================================= INSIDE + OUTSIDE-NEAR
	elif [ "${output[$k]}" -eq 12 ] && [ "$k" -lt 10 ]
	then
		xL=`echo "$x1+sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
		xR=`echo "$x2-sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
	
	#================================================================= INSIDE-NEAR + OUTSIDE-NEAR
	elif [ "${output[$k]}" -eq 13 ] #????
	then
		xL=`echo "$x1-2*sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
		xR=`echo "$x2+2*sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
	
	#================================================================= OUTSIDE-NEAR + INSIDE-NEAR
	elif [ "${output[$k]}" -eq 14 ] && [ "$k" -lt 10 ] #????
	then
		xL=`echo "$x1-2*sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
		xR=`echo "$x2+2*sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
		
	#================================================================= i=x2 + OUTSIDE-NEAR
	elif [ "${output[$k]}" -eq 15 ]
	then
		xL=`echo "$x1+1.5*sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
		xR=`echo "$x2-1.5*sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
		
	#================================================================= INSIDE-NEAR + i+1=x2
	elif [ "${output[$k]}" -eq 16 ] && [ "$k" -lt 10 ]
	then
		xL=`echo "$x1-1.5*sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
		xR=`echo "$x2+1.5*sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
	
	#================================================================= INSIDE + i+1=x2
	elif [ "${output[$k]}" -eq 17 ] && [ "$k" -lt 10 ]
	then
		xL=`echo "$x1-1.5*sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
		xR=`echo "$x2+1.5*sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
	
	#================================================================= OUTSIDE-NEAR + i+1=x1
	elif [ "${output[$k]}" -eq 18 ] && [ "$k" -lt 10 ]
	then
		xL=`echo "$x1+1.5*sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
		xR=`echo "$x2-1.5*sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
	
	#================================================================= i=x1 + INSIDE-NEAR
	elif [ "${output[$k]}" -eq 19 ]
	then
		xL=`echo "$x1-1.5*sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
		xR=`echo "$x2+1.5*sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
	
	#================================================================= OUTSIDE + i=x1
	elif [ "${output[$k]}" -eq 20 ] && [ "$k" -lt 10 ]
	then
		xL=`echo "$x1+1.5*sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
		xR=`echo "$x2-1.5*sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
	
	#================================================================= OUTSIDE-NEAR + OUTSIDE
	elif [ "${output[$k]}" -eq 21 ]
	then
		xL=`echo "$x1+sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
		xR=`echo "$x2-sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
	
	#================================================================= OUTSIDE + OUTSIDE-NEAR
	elif [ "${output[$k]}" -eq 22 ] && [ "$k" -lt 10 ]
	then
		xL=`echo "$x1+sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
		xR=`echo "$x2-sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
	
	#=================================================================
	else
		printf ""
	fi
fi



# calculation of bins
delta=`echo "$xR-$xL" | bc -l`
bins=`echo $delta | bc -l | awk '{print ($0-int($0)<0.499)?int($0):int($0)+1}'` 


# it is necessary to round xL, xR before sending them to the main()
xL=`echo $xL | bc -l | awk '{print ($0-int($0)<0.499)?int($0):int($0)+1}'`
xR=`echo $xR | bc -l | awk '{print ($0-int($0)<0.499)?int($0):int($0)+1}'`


# we must change k=11 otherwise we cannot pass output[k] to runDataAnalysis (it would be out of range)
if [ "$k" -eq 11 ]
then
	k=`echo "$(( k-1 ))" | bc`
	# we define a different value for output[10] from the one it could assume when there is a peak
	output[$k]=50;
	printf " => no peaks were found!\n\n$"
else
	printf " => the fit window becomes [xL=$xL;xR=$xR] (# of bins = $bins)\n\n" 
fi



#------------------------------------------------------------------------------------------------------------------------------------------ POL-DEGREE
#if [ "$E0" -lt 120 ]
#then
#	pol_degree=2
#elif [ "$E0" -ge 120 ] && [ "$E0" -lt 1700 ]
#then
#	pol_degree=1
#else
#	pol_degree=0
#fi

read -p " What degree do you want to use for the BKG? "  pol_degree



#------------------------------------------------------------------------------------------------------------------------------------------ ANALYSIS
make clean
make -s
./runDataAnalysis --nums 6 "$E0" "$pol_degree" "$xL" "$xR" "$k" "${output[$k]}"
printf "\n"
