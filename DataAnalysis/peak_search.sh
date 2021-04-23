#! /bin/bash



#------------------------------------------------------------------------------------------------------------------------------------------ VARIABLES
#         Pb212   Pb214   Pb214   Pb214   Ac228    e+e-    Kr85   Tl208   Bi214   Ac228   Ac228
E_gamma=('238.6' '242.0' '295.2' '352.0' '478.3' '511.0' '514.0' '583.2' '609.3' '911.2' '969.0')

readonly a=0.28 # readonly = constant value
readonly b=0.000583

read -p " What energy value (E0) do you want to study? "  E0 # -p = to assign the input value to the variable E0

x1=`echo "$(( E0-12 ))" | bc`
x2=`echo "$(( E0+12 ))" | bc`
echo " The fit window is given by [x1=$x1;x2=$x2]" 



#------------------------------------------------------------------------------------------------------------------------------------------ PEAK SEARCH 
output=('0' '0' '0' '0' '0' '0' '0' '0' '0' '0' '0') 

for i in {0..10..1}
do	
	# skip i = 0, 1, 5, 6 (i.e. peaks that are far less than 24 keV)
	if [ $i -eq 0 ] || [ $i -eq 1 ] || [ $i -eq 5 ] || [ $i -eq 6 ]
	then 
		continue 
	fi
	
	
	FWHM=`echo "sqrt(8*l(2))*sqrt($a+$b*${E_gamma[i]})" | bc -l`
	
	if [ "$i" -lt 10 ] # suppose i=10: then E_gamma[10+1] does not exist!
	then
		FWHM_plus1=`echo "sqrt(8*l(2))*sqrt($a+$b*${E_gamma[$i+1]})" | bc -l`
	fi
	
	
	#================================================================= OUTSIDE-NEAR + OUTSIDE-NEAR   => es. E0 = 596, 597
	if (  ( (( $(echo "$x1-${E_gamma[i]}<2*$FWHM" | bc -l) )) && (( $(echo "$x1-${E_gamma[i]}>0" | bc -l) )) ) && ( (( $(echo "${E_gamma[i+1]}-$x2<2*$FWHM_plus1" | bc -l) )) && (( $(echo "${E_gamma[i+1]}-$x2>0" | bc -l) )) )  ) && [ "$i" -lt 10 ]
	then
		output[$i]=1
		break
	
	#================================================================= INSIDE-NEAR + OUTSIDE-NEAR   => es. E0 = 594, 595
	elif (  ( (( $(echo "${E_gamma[i]}-$x1<2*$FWHM" | bc -l) )) && (( $(echo "${E_gamma[i]}-$x1>0" | bc -l) )) ) && ( (( $(echo "${E_gamma[i+1]}-$x2<2*$FWHM_plus1" | bc -l) )) && (( $(echo "${E_gamma[i+1]}-$x2>0" | bc -l) )) )  ) && [ "$i" -lt 10 ]
	then
		output[$i]=2
		break
	
	#================================================================= OUTSIDE-NEAR + INSIDE-NEAR   => es. E0 = 598
	elif (  ( (( $(echo "$x1-${E_gamma[i]}<2*$FWHM" | bc -l) )) && (( $(echo "$x1-${E_gamma[i]}>0" | bc -l) )) ) && ( (( $(echo "$x2-${E_gamma[i+1]}<2*$FWHM_plus1" | bc -l) )) && (( $(echo "$x2-${E_gamma[i+1]}>0" | bc -l) )) )  ) && [ "$i" -lt 10 ]
	then
		output[$i]=3
		break
			
	#================================================================= OUTSIDE-NEAR
	elif ( (( $(echo "$x1-${E_gamma[i]}<2*$FWHM" | bc -l) )) && (( $(echo "$x1-${E_gamma[i]}>0" | bc -l) )) ) || ( (( $(echo "${E_gamma[i]}-$x2<2*$FWHM" | bc -l) )) && (( $(echo "${E_gamma[i]}-$x2>0" | bc -l) )) )
	then 
		output[$i]=4
		break
			
			 
	#================================================================= INSIDE-NEAR
	elif ( (( $(echo "${E_gamma[i]}-$x1<2*$FWHM" | bc -l) )) && (( $(echo "${E_gamma[i]}-$x1>0" | bc -l) )) ) || ( (( $(echo "x2-${E_gamma[i]}<2*$FWHM" | bc -l) )) && (( $(echo "x2-${E_gamma[i]}>0" | bc -l) )) )
	then 	
		output[$i]=5
		break
			 
	#================================================================= INSIDE
	elif (( $(echo "${E_gamma[i]}-$x1>2*$FWHM" | bc -l) )) && (( $(echo "$x2-${E_gamma[i]}>2*$FWHM" | bc -l) ))
	then
		output[$i]=6
		break
	
	#================================================================= x1=E V x2=E
	elif (( $(echo "${E_gamma[i]}==$x1" | bc -l) )) || (( $(echo "${E_gamma[i]}==x2" | bc -l) ))
	then
		output[$i]=7
		break
	
	#================================================================= OK
	else
		printf ""
	fi
	

done



#------------------------------------------------------------------------------------------------------------------------------------------ xL, xR
printf "\n\n output[i] = "
echo "${output[@]}"


k=0
# search the first element output[k] which is different from zero
while  [ "$k" -le 10 ] && [ "${output[$k]}" -eq 0 ]
do
	k=`echo "$(( k+1 ))" | bc`
done

# if k=11 -> k=10 (it means that output[i]=0 for every i)
if [ "$k" -eq 11 ]
then
	k=`echo "$(( k-1 ))" | bc`
fi


#================================================================= OK or INSIDE
if [ "${output[$k]}" -eq 0 ] || [ "${output[$k]}" -eq 6 ]
then
	xL=$x1
	xR=$x2

#================================================================= OUTSIDE-NEAR + OUTSIDE-NEAR
elif [ "${output[$k]}" -eq 1 ]
then
	FWHM=`echo "sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
	FWHM_plus1=`echo "sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
	xL=`echo "$x1+$FWHM" | bc -l | awk '{printf "%f", $0}'`
	xR=`echo "$x2-$FWHM_plus1" | bc -l | awk '{printf "%f", $0}'`
	printf " x1 = $x1 -> xL = $xL\n x2 = $x2 -> xR = $xR\n"

#================================================================= INSIDE-NEAR + OUTSIDE-NEAR
elif [ "${output[$k]}" -eq 2 ]
then
	FWHM=`echo "sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
	FWHM_plus1=`echo "sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
	xL=`echo "$x1-$FWHM" | bc -l | awk '{printf "%f", $0}'`
	xR=`echo "$x2-$FWHM_plus1" | bc -l | awk '{printf "%f", $0}'`
	printf " x1 = $x1 -> xL = $xL\n x2 = $x2 -> xR = $xR\n"

#================================================================= OUTSIDE-NEAR + INSIDE-NEAR
elif [ "${output[$k]}" -eq 3 ]
then
	FWHM=`echo "sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
	FWHM_plus1=`echo "sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
	xL=`echo "$x1+$FWHM" | bc -l | awk '{printf "%f", $0}'`
	xR=`echo "$x2+$FWHM_plus1" | bc -l | awk '{printf "%f", $0}'`
	printf " x1 = $x1 -> xL = $xL\n x2 = $x2 -> xR = $xR\n"
				
#================================================================= OUTSIDE-NEAR or x1=E V x2=E
elif [ "${output[$k]}" -eq 4 ] || [ "${output[$k]}" -eq 7 ]
then
	FWHM=`echo "sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
	xL=`echo "$x1+$FWHM" | bc -l | awk '{printf "%f", $0}'`
	xR=`echo "$x2-$FWHM" | bc -l | awk '{printf "%f", $0}'`
	printf " x1 = $x1 -> xL = $xL\n x2 = $x2 -> xR = $xR\n"
	
#================================================================= INSIDE-NEAR
elif [ "${output[$k]}" -eq 5 ]
then
	FWHM=`echo "sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
	xL=`echo "$x1-$FWHM" | bc -l | awk '{printf "%f", $0}'`
	xR=`echo "$x2+$FWHM" | bc -l | awk '{printf "%f", $0}'`
	printf " x1 = $x1 -> xL = $xL\n x2 = $x2 -> xR = $xR\n"
	
fi


# calculation of bins
delta=`echo "$xR-$xL" | bc -l`
echo " New number of bins = $delta"
bins=`echo $delta | bc -l | awk '{print ($0-int($0)<0.499)?int($0):int($0)+1}'`
echo " New number of bins (rounded) = $bins"


# it is necessary to round xL, xR before sending them to the main()
xL=`echo $xL | bc -l | awk '{print ($0-int($0)<0.499)?int($0):int($0)+1}'`
xR=`echo $xR | bc -l | awk '{print ($0-int($0)<0.499)?int($0):int($0)+1}'`



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



#------------------------------------------------------------------------------------------------------------------------------------------ ANALYSIS
make clean
make -s
./runDataAnalysis --nums 6 "$E0" "$pol_degree" "$xL" "$xR" "$k" "${output[$k]}"
printf "\n"
