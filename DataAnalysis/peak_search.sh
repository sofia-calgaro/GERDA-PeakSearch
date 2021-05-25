#! /bin/bash

#------------------------------------------------------------------------------------------------------------------------------------------ VARIABLES
#         Pb212  Pb214  Pb214  Pb214  Ac228   e+e-  Kr85  Tl208   Bi214   Ac228  Ac228    K40      K42
E_gamma=('238.6' '242' '295.2' '352' '478.3' '511' '514' '583.2' '609.3' '911.2' '969' '1460.8' '1524.6')
numGamma=${#E_gamma[@]}

readonly a=0.28 # readonly = constant value
readonly b=0.000583

#------------------------------------------------------------------------------------------------------------------------------------------ 

thr=165 # BEGe
#thr=195 # coax

E0=$1
num_E0=$2

#read -p " What energy (E0>=40) do you want to study? "  E0 # -p = to assign the input value to the variable E0

#if [ "$E0" -lt 40 ]
#then
#	while [ "$E0" -lt 40 ]
#	do
#		echo " E0 IS TOO LOW! "
#		read -p " What energy (E0>=40) do you want to study? "  E0
#	done
#fi

#read -p " How many energies do you want to study? " num_E0
#read -p " Which threshold: 165 (BEGe) or 195 (coax)? " thr
#echo " You will study energies inside [$E0;$(( num_E0+E0-1  ))]"

make clean
make -s

# to remove already existing root files
#find MarginalizedROOT/ -type f -delete

#=============================================== WHILE LOOP over E0
max_E0=`echo "$(( E0+num_E0 ))" | bc`
while [ "$E0" -lt "$max_E0" ]
do

	x1=`echo "$(( E0-12 ))" | bc`
	x2=`echo "$(( E0+12 ))" | bc`
	printf "\n\n----------------------------------------------------------------------------------\n"
	printf " For E0=$E0 the fit window is [x1=$x1;x2=$x2] (# of bins = $(( x2-x1 )))\n" 

	#------------------------------------------------------------------------------------------------------------------------------------------ PEAK SEARCH 
	# let's define a variable array depending on the number of gamma peaks
	output=()
	for (( j=0; j<$numGamma; j++ ))
	do
		output+=(0)
	done


	for (( i=0; i<$numGamma; i++ ))
	do	
		FWHM=`echo "sqrt(8*l(2))*sqrt($a+$b*${E_gamma[i]})" | bc -l`
		
		
		if (( $(echo "$i<$numGamma-1" | bc -l) )) # suppose i=numGamma-1: then E_gamma[numGamma] does not exist!
		then
			FWHM_plus1=`echo "sqrt(8*l(2))*sqrt($a+$b*${E_gamma[$i+1]})" | bc -l` 
		fi
		
		
		if [ "$i" -gt 0 ] # suppose i=0: then E_gamma[0-1] does not exist!
		then
			FWHM_minus1=`echo "sqrt(8*l(2))*sqrt($a+$b*${E_gamma[$i-1]})" | bc -l` 
		fi
		
		
		
		# Analysis for peaks that differ more than 24 keV
		#if ( ( (( $(echo "${E_gamma[i]}-${E_gamma[i-1]}>24" | bc -l) )) && (( $(echo "$i>0" | bc -l) )) ) && ( (( $(echo "${E_gamma[i+1]}-${E_gamma[i]}>24" | bc -l) )) && (( $(echo "$i<10" | bc -l) )) ) )
		if [[ "$i" -ge 2 && "$i" -le 4 ]] || [ "$i" -ge 7 ]
		then
			#================================================================= OUTSIDE-NEAR + OUTSIDE-NEAR   => es. E0 = 596, 597
			if (  ( (( $(echo "$x1-${E_gamma[i]}<2*$FWHM" | bc -l) )) && (( $(echo "$x1-${E_gamma[i]}>0" | bc -l) )) ) && ( (( $(echo "${E_gamma[i+1]}-$x2<2*$FWHM_plus1" | bc -l) )) && (( $(echo "${E_gamma[i+1]}-$x2>0" | bc -l) )) )  ) && (( $(echo "$i<$numGamma-1" | bc -l) ))
			then
				output[$i]=1
				printf " Peaks are: OUTSIDE-NEAR (${E_gamma[i]}) + OUTSIDE-NEAR (${E_gamma[i+1]})\n"
				break
			
			#================================================================= INSIDE-NEAR + OUTSIDE-NEAR   => es. E0 = 594, 595
			elif (  ( (( $(echo "${E_gamma[i]}-$x1<2*$FWHM" | bc -l) )) && (( $(echo "${E_gamma[i]}-$x1>0" | bc -l) )) ) && ( (( $(echo "${E_gamma[i+1]}-$x2<2*$FWHM_plus1" | bc -l) )) && (( $(echo "${E_gamma[i+1]}-$x2>0" | bc -l) )) )  ) && (( $(echo "$i<$numGamma-1" | bc -l) ))
			then
				output[$i]=2
				printf " Peaks are: INSIDE-NEAR (${E_gamma[i]}) + OUTSIDE-NEAR (${E_gamma[i+1]})\n"
				break
			
			#================================================================= OUTSIDE-NEAR + INSIDE-NEAR   => es. E0 = 598
			elif (  ( (( $(echo "$x1-${E_gamma[i]}<2*$FWHM" | bc -l) )) && (( $(echo "$x1-${E_gamma[i]}>0" | bc -l) )) ) && ( (( $(echo "$x2-${E_gamma[i+1]}<2*$FWHM_plus1" | bc -l) )) && (( $(echo "$x2-${E_gamma[i+1]}>0" | bc -l) )) )  ) && (( $(echo "$i<$numGamma-1" | bc -l) ))
			then
				output[$i]=3
				printf " Peaks are: OUTSIDE-NEAR (${E_gamma[i]}) + INSIDE-NEAR (${E_gamma[i+1]})\n"
				break
					
			#================================================================= OUTSIDE-NEAR
			elif ( (( $(echo "$x1-${E_gamma[i]}<2*$FWHM" | bc -l) )) && (( $(echo "$x1-${E_gamma[i]}>0" | bc -l) )) ) || ( (( $(echo "${E_gamma[i]}-$x2<2*$FWHM" | bc -l) )) && (( $(echo "${E_gamma[i]}-$x2>0" | bc -l) )) )
			then 
				output[$i]=4
				printf " Peak is: OUTSIDE-NEAR (${E_gamma[i]})\n"
				break
					
					 
			#================================================================= INSIDE-NEAR
			elif ( (( $(echo "${E_gamma[i]}-$x1<2*$FWHM" | bc -l) )) && (( $(echo "${E_gamma[i]}-$x1>0" | bc -l) )) ) || ( (( $(echo "$x2-${E_gamma[i]}<2*$FWHM" | bc -l) )) && (( $(echo "$x2-${E_gamma[i]}>0" | bc -l) )) )
			then 	
				output[$i]=5
				printf " Peak is: INSIDE-NEAR (${E_gamma[i]})\n"
				break
					 
			#================================================================= INSIDE
			elif (( $(echo "${E_gamma[i]}-$x1>2*$FWHM" | bc -l) )) && (( $(echo "$x2-${E_gamma[i]}>2*$FWHM" | bc -l) ))
			then
				output[$i]=6
				printf " Peak is: INSIDE (${E_gamma[i]})\n"
				break
			
			#================================================================= x1=E V x2=E
			elif (( $(echo "${E_gamma[i]}==$x1" | bc -l) )) || (( $(echo "${E_gamma[i]}==x2" | bc -l) ))
			then
				output[$i]=7
				printf " Peak is: =x1 or =x2 (${E_gamma[i]})\n"
				break
			
			#================================================================= NO PEAKS
			else
				printf ""
			fi
			
			
			
		# Analysis for peaks that differ less than 24 keV 
		else
			#================================================================= INSIDE + INSIDE
			if (( $(echo "${E_gamma[i]}-$x1>2*$FWHM" | bc -l) )) && (( $(echo "$x2-${E_gamma[i+1]}>2*$FWHM_plus1" | bc -l) ))
			then
				output[$i]=8
				printf " Peaks are: INSIDE (${E_gamma[i]}) + INSIDE (${E_gamma[i+1]})\n"
				break
				
			#================================================================= INSIDE + INSIDE-NEAR
			elif (( $(echo "${E_gamma[i]}-$x1>2*$FWHM" | bc -l) )) && ( (( $(echo "$x2-${E_gamma[i+1]}<2*$FWHM_plus1" | bc -l) )) && (( $(echo "$x2-${E_gamma[i+1]}>0" | bc -l) )) )
			then
				output[$i]=9
				printf " Peaks are: INSIDE (${E_gamma[i]}) + INSIDE-NEAR (${E_gamma[i+1]})\n"
				break
				
			#================================================================= INSIDE-NEAR + INSIDE
			elif ( (( $(echo "${E_gamma[i]}-$x1<2*$FWHM" | bc -l) )) && (( $(echo "${E_gamma[i]}-$x1>0" | bc -l) )) ) && (( $(echo "$x2-${E_gamma[i+1]}>2*$FWHM_plus1" | bc -l) ))
			then
				output[$i]=10
				printf " Peaks are: INSIDE-NEAR (${E_gamma[i]}) + INSIDE (${E_gamma[i+1]})\n"
				break
						
			#================================================================= INSIDE-NEAR + INSIDE-NEAR
			elif ( (( $(echo "${E_gamma[i]}-$x1<2*$FWHM" | bc -l) )) && (( $(echo "${E_gamma[i]}-$x1>0" | bc -l) )) ) && ( (( $(echo "$x2-${E_gamma[i+1]}<2*$FWHM_plus1" | bc -l) )) && (( $(echo "$x2-${E_gamma[i+1]}>0" | bc -l) )) )
			then
				output[$i]=11
				printf " Peaks are: INSIDE-NEAR (${E_gamma[i]}) + INSIDE-NEAR (${E_gamma[i+1]})\n"
				break
			
			#================================================================= INSIDE + OUTSIDE-NEAR
			elif ( (( $(echo "${E_gamma[i]}-$x1>2*$FWHM" | bc -l) )) && (( $(echo "$x2-${E_gamma[i]}>2*$FWHM" | bc -l) )) ) && ( (( $(echo "${E_gamma[i+1]}-$x2<2*$FWHM_plus1" | bc -l) )) && (( $(echo "${E_gamma[i+1]}-$x2>0" | bc -l) )) )
			then
				output[$i]=12
				printf " Peaks are: INSIDE (${E_gamma[i]}) + OUTSIDE-NEAR (${E_gamma[i+1]})\n"
				break
				
			#================================================================= INSIDE-NEAR + OUTSIDE-NEAR
			elif  ( ( (( $(echo "${E_gamma[i]}-$x1<2*$FWHM" | bc -l) )) && (( $(echo "${E_gamma[i]}-$x1>0" | bc -l) )) ) || ( (( $(echo "$x2-${E_gamma[i]}<2*$FWHM" | bc -l) )) && (( $(echo "$x2-${E_gamma[i]}>0" | bc -l) )) ) ) && ( (( $(echo "${E_gamma[i+1]}-$x2<2*$FWHM_plus1" | bc -l) )) && (( $(echo "${E_gamma[i+1]}-$x2>0" | bc -l) )) )
			
			then
				output[$i]=13
				printf " Peaks are: INSIDE-NEAR (${E_gamma[i]}) + OUTSIDE-NEAR (${E_gamma[i+1]})\n"
				break
				
			#================================================================= OUTSIDE-NEAR + INSIDE-NEAR
			elif  ( (( $(echo "$x1-${E_gamma[i]}<2*$FWHM" | bc -l) )) && (( $(echo "$x1-${E_gamma[i]}>0" | bc -l) )) && ( (( $(echo "$x2-${E_gamma[i+1]}<2*$FWHM_plus1" | bc -l) )) && (( $(echo "$x2-${E_gamma[i+1]}>0" | bc -l) )) || (( $(echo "${E_gamma[i+1]}-$x1<2*$FWHM_plus1" | bc -l) )) && (( $(echo "${E_gamma[i+1]}-$x1>0" | bc -l) )) ) )
			then
				output[$i]=14
				printf " Peaks are: OUTSIDE-NEAR (${E_gamma[i]}) + INSIDE-NEAR (${E_gamma[i+1]})\n"
				break
			
			#================================================================= i=x2 + OUTSIDE-NEAR
			elif (( $(echo "${E_gamma[i]}==$x2" | bc -l) )) && ( (( $(echo "${E_gamma[i+1]}-$x2<2*$FWHM_plus1" | bc -l) )) && (( $(echo "${E_gamma[i+1]}-$x2>0" | bc -l) )) ) 
			then
				output[$i]=15
				printf " Peaks are: =x2 (${E_gamma[i]}) + OUTSIDE-NEAR (${E_gamma[i+1]})\n"
				break
						
			#================================================================= INSIDE-NEAR + i+1=x2
			elif ( (( $(echo "$x2-${E_gamma[i]}<2*$FWHM" | bc -l) )) && (( $(echo "$x2-${E_gamma[i]}>0" | bc -l) )) ) && (( $(echo "${E_gamma[i+1]}==$x2" | bc -l) ))
			then
				output[$i]=16
				printf " Peaks are: INSIDE-NEAR (${E_gamma[i]}) + =x2 (${E_gamma[i+1]})\n"
				break
			
			#================================================================= INSIDE + i+1=x2
			elif ( (( $(echo "$x2-${E_gamma[i]}>2*$FWHM" | bc -l) )) && (( $(echo "${E_gamma[i]}-$x1>2*$FWHM" | bc -l) )) ) && (( $(echo "${E_gamma[i+1]}==$x2" | bc -l) ))
			then
				output[$i]=17
				printf " Peaks are: INSIDE (${E_gamma[i]}) + =x2 (${E_gamma[i+1]})\n"
				break
			
			#================================================================= OUTSIDE-NEAR + i+1=x1
			elif ( (( $(echo "$x1-${E_gamma[i]}<2*$FWHM" | bc -l) )) && (( $(echo "$x1-${E_gamma[i]}>0" | bc -l) )) ) && (( $(echo "${E_gamma[i+1]}==$x1" | bc -l) ))
			then
				output[$i]=18
				printf " Peaks are: OUTSIDE-NEAR (${E_gamma[i]}) + =x1 (${E_gamma[i+1]})\n"
				break
				
			#================================================================= i=x1 + INSIDE-NEAR
			elif (( $(echo "${E_gamma[i]}==$x1" | bc -l) )) && ( (( $(echo "${E_gamma[i+1]}-$x1<2*$FWHM_plus1" | bc -l) )) && (( $(echo "${E_gamma[i+1]}-$x1>0" | bc -l) )) ) 
			then
				output[$i]=19
				printf " Peaks are: =x1 (${E_gamma[i]}) + INSIDE-NEAR (${E_gamma[i+1]})\n"
				break
					
			#================================================================= OUTSIDE + i=x1
			elif (( $(echo "$i>0" | bc -l) )) && ( (( $(echo "$x1-${E_gamma[i-1]}>2*$FWHM_minus1" | bc -l) )) && (( $(echo "${E_gamma[i]}==$x1" | bc -l) )) )
			then
				output[$i]=20
				printf " Peaks are: OUTSIDE (${E_gamma[i]}) + =x1 (${E_gamma[i+1]})\n"
				break
				
			#================================================================= OUTSIDE-NEAR	+ OUTSIDE
			elif ( (( $(echo "${E_gamma[i]}-$x2<2*$FWHM" | bc -l) )) && (( $(echo "${E_gamma[i]}-$x2>0" | bc -l) )) ) && (( $(echo "${E_gamma[i+1]}-$x2>2*$FWHM_plus1" | bc -l) ))
			then
				output[$i]=21
				printf " Peaks are: OUTSIDE-NEAR (${E_gamma[i]}) + OUTSIDE (${E_gamma[i+1]})\n"
				break
				
			#================================================================= OUTSIDE + OUTSIDE-NEAR
			elif (( $(echo "$i>0" | bc -l) )) && ( ( (( $(echo "$x1-${E_gamma[i-1]}>2*$FWHM_minus1" | bc -l) )) && ( (( $(echo "$x1-${E_gamma[i]}<2*$FWHM" | bc -l) )) ) && (( $(echo "$x1-${E_gamma[i]}>0" | bc -l) )) ) )
			then
				output[$i]=22
				printf " Peaks are: OUTSIDE (${E_gamma[i]}) + OUTSIDE-NEAR (${E_gamma[i+1]})\n"
				break
				
			#=================================================================	
			else
				printf ""	
			fi
		fi	

	done



	#------------------------------------------------------------------------------------------------------------------------------------------ xL, xR
	k=0
	NumGPeaks=0
	# search the first element output[k] which is different from zero
	while  (( $(echo "$k<=$numGamma-1" | bc -l) )) && [ "${output[$k]}" -eq 0 ]
	do
		k=`echo "$(( k+1 ))" | bc`
	done

	outputK=${output[$k]}

	if [ "$k" -eq "$numGamma" ] # NO PEAKS
	then
		xL=$x1
		xR=$x2
	else
		#================================================================= INSIDE
		if [ "$outputK" -eq 6 ]
		then
			xL=$x1
			xR=$x2
			NumGPeaks=1
		
		#================================================================= INSIDE + INSIDE
		elif [ "$outputK" -eq 8 ]
		then 
			xL=$x1
			xR=$x2
			NumGPeaks=2
			
		#================================================================= OUTSIDE-NEAR + OUTSIDE-NEAR
		elif [ "$outputK" -eq 1 ] && (( $(echo "$k<$numGamma-1" | bc -l) ))
		then
			xL=`echo "$x1+sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
			xR=`echo "$x2-sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`

		#================================================================= INSIDE-NEAR + OUTSIDE-NEAR
		elif [ "$outputK" -eq 2 ] && (( $(echo "$k<$numGamma-1" | bc -l) ))
		then
			xL=`echo "$x1-sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
			xR=`echo "$x2-sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
			NumGPeaks=1

		#================================================================= OUTSIDE-NEAR + INSIDE-NEAR
		elif [ "$outputK" -eq 3 ] && (( $(echo "$k<$numGamma-1" | bc -l) ))
		then
			xL=`echo "$x1+sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
			xR=`echo "$x2+sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
			NumGPeaks=1
						
		#================================================================= OUTSIDE-NEAR
		elif [ "$outputK" -eq 4 ] 
		then
			xL=`echo "$x1+sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
			xR=`echo "$x2-sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
			
		#================================================================= INSIDE-NEAR
		elif [ "$outputK" -eq 5 ]
		then
			xL=`echo "$x1-sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
			xR=`echo "$x2+sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
			NumGPeaks=1
			
		#================================================================= x1=E V x2=E
		elif [ "$outputK" -eq 7 ] 
		then
			xL=`echo "$x1+1.5*sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
			xR=`echo "$x2-1.5*sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
				
		#================================================================= INSIDE + INSIDE-NEAR
		elif [ "$outputK" -eq 9 ] && (( $(echo "$k<$numGamma-1" | bc -l) ))
		then
			xL=`echo "$x1-sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
			xR=`echo "$x2+sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
			NumGPeaks=2
		
		#================================================================= INSIDE-NEAR + INSIDE
		elif [ "$outputK" -eq 10 ] 
		then
			xL=`echo "$x1-sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
			xR=`echo "$x2+sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
			NumGPeaks=2
		
		#================================================================= INSIDE-NEAR + INSIDE-NEAR
		elif [ "$outputK" -eq 11 ] && (( $(echo "$k<$numGamma-1" | bc -l) ))
		then
			xL=`echo "$x1-sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
			xR=`echo "$x2+sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
			NumGPeaks=2
		
		#================================================================= INSIDE + OUTSIDE-NEAR
		elif [ "$outputK" -eq 12 ] && (( $(echo "$k<$numGamma-1" | bc -l) ))
		then
			xL=`echo "$x1+sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
			xR=`echo "$x2-sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
			NumGPeaks=1
		
		#================================================================= INSIDE-NEAR + OUTSIDE-NEAR
		elif [ "$outputK" -eq 13 ]
		then
			xL=`echo "$x1+1*sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
			xR=`echo "$x2-3*sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
		
		#================================================================= OUTSIDE-NEAR + INSIDE-NEAR
		elif [ "$outputK" -eq 14 ] && (( $(echo "$k<$numGamma-1" | bc -l) ))
		then
			xL=`echo "$x1+3*sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
			xR=`echo "$x2-1*sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
			
		#================================================================= i=x2 + OUTSIDE-NEAR
		elif [ "$outputK" -eq 15 ]
		then
			xL=`echo "$x1+1.5*sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
			xR=`echo "$x2-1.5*sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
			
		#================================================================= INSIDE-NEAR + i+1=x2
		elif [ "$outputK" -eq 16 ] && (( $(echo "$k<$numGamma-1" | bc -l) ))
		then
			xL=`echo "$x1-1.5*sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
			xR=`echo "$x2+1.5*sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
			NumGPeaks=2
		
		#================================================================= INSIDE + i+1=x2
		elif [ "$outputK" -eq 17 ] && (( $(echo "$k<$numGamma-1" | bc -l) ))
		then
			xL=`echo "$x1-1.5*sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
			xR=`echo "$x2+1.5*sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
			NumGPeaks=2
		
		#================================================================= OUTSIDE-NEAR + i+1=x1
		elif [ "$outputK" -eq 18 ] && (( $(echo "$k<$numGamma-1" | bc -l) ))
		then
			xL=`echo "$x1+1.5*sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
			xR=`echo "$x2-1.5*sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
		
		#================================================================= i=x1 + INSIDE-NEAR
		elif [ "$outputK" -eq 19 ]
		then
			xL=`echo "$x1-1.5*sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
			xR=`echo "$x2+1.5*sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
			NumGPeaks=2
		
		#================================================================= OUTSIDE + i=x1
		elif [ "$outputK" -eq 20 ] && (( $(echo "$k<$numGamma-1" | bc -l) ))
		then
			xL=`echo "$x1+1.5*sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
			xR=`echo "$x2-1.5*sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
		
		#================================================================= OUTSIDE-NEAR + OUTSIDE
		elif [ "$outputK" -eq 21 ]
		then
			xL=`echo "$x1+sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
			xR=`echo "$x2-sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
		
		#================================================================= OUTSIDE + OUTSIDE-NEAR
		elif [ "$outputK" -eq 22 ] && (( $(echo "$k<$numGamma-1" | bc -l) ))
		then
			xL=`echo "$x1+sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
			xR=`echo "$x2-sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
		
		#=================================================================
		else
			printf ""
		fi
	fi
	
	
	if (( $(echo "$E0>$thr-20" | bc -l) )) && (( $(echo "$E0<$thr" | bc -l) ))
	then
		xR=`echo "$thr-1+0.1" | bc -l | awk '{printf "%f", $0}'`
	else
		printf ""
	fi
	if (( $(echo "$E0>=$thr" | bc -l) )) && (( $(echo "$E0<$thr+20" | bc -l) ))
	then
		xL=`echo "$thr+0.1" | bc -l | awk '{printf "%f", $0}'`
	else
		printf ""
	fi
	

	# calculation of bins
	delta=`echo "$xR-$xL" | bc -l`
	bins=`echo $delta | bc -l | awk '{print ($0-int($0)<0.499)?int($0):int($0)+1}'` 


	# it is necessary to round xL, xR before sending them to the main()
	xL=`echo $xL | bc -l | awk '{print ($0-int($0)<0.499)?int($0):int($0)+1}'`
	xR=`echo $xR | bc -l | awk '{print ($0-int($0)<0.499)?int($0):int($0)+1}'`


	# we must change k=numGamma otherwise we cannot pass output[k] to runDataAnalysis (it would be out of range)
	if [ "$k" -eq "$numGamma" ]
	then
		outputK=0
		printf "\n NO peaks were found!\n"
	else
		printf "\n The fit window becomes [xL=$xL;xR=$xR] (# of bins = $bins)\n" 
	fi

	printf " k = $k -> outputK = $outputK\n\n"



	#------------------------------------------------------------------------------------------------------------------------------------------ POL-DEGREE
	if [ "$E0" -lt 120 ]
	then
		pol_degree=2
	elif [ "$E0" -ge 120 ] && [ "$E0" -lt 1700 ]
	then
		pol_degree=1
	else
		pol_degree=0
	fi

	#read -p " What degree (0, 1, 2) do you want for the BKG? "  pol_degree
	printf "\n"


	#------------------------------------------------------------------------------------------------------------------------------------------ ANALYSIS
	#make clean
	#time make -s

	ck0=1 # check for p0 range
	ck1=1 # check for p1 range
	ck2=1 # check for p2 range
	
	rng0=0 # range for p0 range
	rng1=0 # range for p1 range
	rng2=0 # range for p2 range
	# NOTA: if rngX=0, the range in models will be x+-10*sigma
	#	if rngX=1, the range in models will be x+-15*sigma
	#	if rngX=2, the range in models will be x+-20*sigma
	#	if rng2=3, the range in models will be x+-25*sigma
	
	while [[ "$ck0" != 0 || "$ck1" != 0 || "$ck2" != 0 ]] && [[ "$rng0" < 3 && "$rng1" < 3 && "$rng2" < 4 ]]
	do
		./runDataAnalysis --nums 9 "$E0" "$pol_degree" "$xL" "$xR" "$k" "$outputK" "$rng0" "$rng1" "$rng2" &&
		
		name_model=""
		# 0 gamma peaks
		if [ "$NumGPeaks" -eq 0 ] 
		then
			name_model="GausPol${pol_degree}"
		# 1 gamma peak 
		elif [ "$NumGPeaks" -eq 1 ]
		then
			name_model="GausPol${pol_degree}_1Gamma"
		# 2 gamma peaks
		elif [ "$NumGPeaks" -eq 2 ]
		then
		name_model="GausPol${pol_degree}_2Gamma"
		fi
		
		root_file="\"${name_model}\"" &&
		
		# posterior analysis
		root -l <<-EOF
		.L PosteriorCheck.C
		PosteriorCheck($E0, $pol_degree, $root_file);
		EOF
		
		# read the output of the posterior analysis
		declare -a txt_content # array of the .txt content
		txt_content=(`cat "check_posterior.txt"`) &&
					
		# p0 check (0=ok, 1=problems)
		if [ "${txt_content[0]}" -eq 1 ]
		then
			ck0=1
		else
			ck0=0
		fi
		# p1 check (0=ok, 1=problems)
		if [ "${txt_content[1]}" -eq 1 ]
		then
			ck1=1
		else
			ck1=0
		fi
		# p2 check (0=ok, 1=problems)
		if [ "${txt_content[2]}" -eq 1 ]
		then
			ck2=1
		else
			ck2=0
		fi
			
		rm check_posterior.txt
		
		# chose another option of range for p0
		if [ "$ck0" -eq 1 ]
		then 
			rng0=`echo "$(( rng0+1 ))" | bc`
		fi
		# chose another option of range for p1
		if [ "$ck1" -eq 1 ]
		then 
			rng1=`echo "$(( rng1+1 ))" | bc`
		fi
		# chose another option of range for p2
		if [ "$ck2" -eq 1 ]
		then 
			rng2=`echo "$(( rng2+1 ))" | bc`
		fi	
		
	done

	E0=`echo "$(( E0+1 ))" | bc`
done


