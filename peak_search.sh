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
		printf "\n\tE_gamma[$i]=${E_gamma[i]}; FWHM[$i]=$FWHM\n\tE_gamma[$i+1]=${E_gamma[i+1]}; FWHM[$i+1]=$FWHM_plus1\n"
		printf "\n\tTwo gamma peaks are OUTSIDE but NEAR x1 and x2:
			\r\t  o x1-E_gamma[$i] = `echo "$x1-${E_gamma[i]}" | bc -l | awk '{printf "%f", $0}'` 
			\r\t  o E_gamma[$i+1]-x2 = `echo "${E_gamma[i+1]}-$x2" | bc -l | awk '{printf "%f", $0}'`"
		printf "\n\tTherefore: output[$i] = ${output[i]} -> "	
		output[$i]=1
		printf "${output[i]}"
		break
	
	#================================================================= INSIDE-NEAR + OUTSIDE-NEAR   => es. E0 = 594, 595
	elif (  ( (( $(echo "${E_gamma[i]}-$x1<2*$FWHM" | bc -l) )) && (( $(echo "${E_gamma[i]}-$x1>0" | bc -l) )) ) && ( (( $(echo "${E_gamma[i+1]}-$x2<2*$FWHM_plus1" | bc -l) )) && (( $(echo "${E_gamma[i+1]}-$x2>0" | bc -l) )) )  ) && [ "$i" -lt 10 ]
	then
		printf "\n\tE_gamma[$i]=${E_gamma[i]}; FWHM[$i]=$FWHM\n\tE_gamma[$i+1]=${E_gamma[i+1]}; FWHM[$i+1]=$FWHM_plus1\n"
		printf "\n\tThe left peak is INSIDE but NEAR x1,
			\r\tthe right peak is OUTSIDE but NEAR x2:
			\r\t  o E_gamma[$i]-x1 = `echo "${E_gamma[i]}-$x1" | bc -l | awk '{printf "%f", $0}'`
			\r\t  o E_gamma[$i+1]-x2 = `echo "${E_gamma[i+1]}-$x2" | bc -l | awk '{printf "%f", $0}'`"
		printf "\n\tTherefore: output[$i] = ${output[i]} -> "	
		output[$i]=2
		printf "${output[i]}"
		break
	
	#================================================================= OUTSIDE-NEAR + INSIDE-NEAR   => es. E0 = 598
	elif (  ( (( $(echo "$x1-${E_gamma[i]}<2*$FWHM" | bc -l) )) && (( $(echo "$x1-${E_gamma[i]}>0" | bc -l) )) ) && ( (( $(echo "$x2-${E_gamma[i+1]}<2*$FWHM_plus1" | bc -l) )) && (( $(echo "$x2-${E_gamma[i+1]}>0" | bc -l) )) )  ) && [ "$i" -lt 10 ]
	then
		printf "\n\tE_gamma[$i]=${E_gamma[i]}; FWHM[$i]=$FWHM\n\tE_gamma[$i+1]=${E_gamma[i+1]}; FWHM[$i+1]=$FWHM_plus1\n"
		printf "\n\tThe left peak is OUTSIDE but NEAR x1,
			\r\tthe right peak is INSIDE but NEAR x2:
			\r\t  o E_gamma[$i]-x1 = `echo "$x1-${E_gamma[i]}" | bc -l | awk '{printf "%f", $0}'`
			\r\t  o x2-E_gamma[$i+1] = `echo "$x2-${E_gamma[i+1]}" | bc -l | awk '{printf "%f", $0}'`"
		printf "\n\tTherefore: output[$i] = ${output[i]} -> "	
		output[$i]=3
		printf "${output[i]}"
		break
			
	#================================================================= OUTSIDE-NEAR
	elif ( (( $(echo "$x1-${E_gamma[i]}<2*$FWHM" | bc -l) )) && (( $(echo "$x1-${E_gamma[i]}>0" | bc -l) )) ) || ( (( $(echo "${E_gamma[i]}-$x2<2*$FWHM" | bc -l) )) && (( $(echo "${E_gamma[i]}-$x2>0" | bc -l) )) )
	then 
		printf "\n\tE_gamma[$i]=${E_gamma[i]}; FWHM[$i]=$FWHM\n"
		printf "\n\tThe gamma peak is OUTSIDE but NEAR x1 or x2:
			\r\t  o x1-E_gamma[$i] = `echo "$x1-${E_gamma[i]}" | bc -l | awk '{printf "%f", $0}'`
			\r\t  o E_gamma[$i]-x2 = `echo "${E_gamma[i]}-$x2" | bc -l | awk '{printf "%f", $0}'`"
		printf "\n\tTherefore: output[$i] = ${output[i]} -> "	
		output[$i]=4
		printf "${output[i]}"
		break
			
			 
	#================================================================= INSIDE-NEAR
	elif ( (( $(echo "${E_gamma[i]}-$x1<2*$FWHM" | bc -l) )) && (( $(echo "${E_gamma[i]}-$x1>0" | bc -l) )) ) || ( (( $(echo "x2-${E_gamma[i]}<2*$FWHM" | bc -l) )) && (( $(echo "x2-${E_gamma[i]}>0" | bc -l) )) )
	then 
		printf "\n\tE_gamma[$i]=${E_gamma[i]}; FWHM[$i]=$FWHM\n"
		printf "\n\tThe gamma peak is INSIDE but NEAR x1 or x2:
			\r\t o E_gamma[$i]-x1 = `echo "${E_gamma[i]}-$x1" | bc -l | awk '{printf "%f", $0}'`
			\r\t o x2-E_gamma[$i] = `echo "$x2-${E_gamma[i]}" | bc -l | awk '{printf "%f", $0}'`"
		printf "\n\tTherefore: output[$i] = ${output[i]} -> "	
		output[$i]=5
		printf "${output[i]}"
		break
			 
	#================================================================= INSIDE
	elif (( $(echo "${E_gamma[i]}-$x1>2*$FWHM" | bc -l) )) && (( $(echo "$x2-${E_gamma[i]}>2*$FWHM" | bc -l) ))
	then
		printf "\n\tE_gamma[$i]=${E_gamma[i]}; FWHM[$i]=$FWHM\n"
		printf "\n\tThe gamma peak is INSIDE [$x1;$x2]:
			\r\t o E_gamma[$i]-x1 = `echo "${E_gamma[i]}-$x1" | bc -l | awk '{printf "%f", $0}'`
			\r\t o E_gamma[$i]-x2 = `echo "${E_gamma[i]}-$x2" | bc -l | awk '{printf "%f", $0}'`"
		printf "\n\tTherefore: output[$i] = ${output[i]} -> "	
		output[$i]=6
		printf "${output[i]}"
		break
	
	#================================================================= x1=E V x2=E
	elif (( $(echo "${E_gamma[i]}==$x1" | bc -l) )) || (( $(echo "${E_gamma[i]}==x2" | bc -l) ))
	then
		printf "\n\tE_gamma[$i]=${E_gamma[i]}; FWHM[$i]=$FWHM\n"
		printf "\n\tThe gamma peak coincides with x1 or x2:
			\r\t o E_gamma[$i]-x1 = `echo "${E_gamma[i]}-$x1" | bc -l | awk '{printf "%f", $0}'`
			\r\t o E_gamma[$i]-x2 = `echo "${E_gamma[i]}-$x2" | bc -l | awk '{printf "%f", $0}'`"
		printf "\n\tTherefore: output[$i] = ${output[i]} -> "	
		output[$i]=7
		printf "${output[i]}"
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
	printf " x1=$x1 -> xL=$xL; x2=$x2 -> xR=$xR"

#================================================================= OUTSIDE-NEAR + OUTSIDE-NEAR
elif [ "${output[$k]}" -eq 1 ]
then
	FWHM=`echo "sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
	FWHM_plus1=`echo "sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
	xL=`echo "$x1+$FWHM" | bc -l | awk '{printf "%f", $0}'`
	xR=`echo "$x2-$FWHM_plus1" | bc -l | awk '{printf "%f", $0}'`
	printf " x1 = $x1 -> xL = $xL\n x2 = $x2 -> xR = $xR\n"
	delta=`echo "$xR-$xL" | bc -l`
	echo " New number of bins = $delta"

#================================================================= INSIDE-NEAR + OUTSIDE-NEAR
elif [ "${output[$k]}" -eq 2 ]
then
	FWHM=`echo "sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
	FWHM_plus1=`echo "sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
	xL=`echo "$x1-$FWHM" | bc -l | awk '{printf "%f", $0}'`
	xR=`echo "$x2-$FWHM_plus1" | bc -l | awk '{printf "%f", $0}'`
	printf " x1 = $x1 -> xL = $xL\n x2 = $x2 -> xR = $xR\n"
	delta=`echo "$xR-$xL" | bc -l`
	echo " New number of bins = $delta"

#================================================================= OUTSIDE-NEAR + INSIDE-NEAR
elif [ "${output[$k]}" -eq 3 ]
then
	FWHM=`echo "sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
	FWHM_plus1=`echo "sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k+1]})" | bc -l | awk '{printf "%f", $0}'`
	xL=`echo "$x1+$FWHM" | bc -l | awk '{printf "%f", $0}'`
	xR=`echo "$x2+$FWHM_plus1" | bc -l | awk '{printf "%f", $0}'`
	printf " x1 = $x1 -> xL = $xL\n x2 = $x2 -> xR = $xR\n"
	delta=`echo "$xR-$xL" | bc -l`
	echo " New number of bins = $delta"
				
#================================================================= OUTSIDE-NEAR or x1=E V x2=E
elif [ "${output[$k]}" -eq 4 ] || [ "${output[$k]}" -eq 7 ]
then
	FWHM=`echo "sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
	xL=`echo "$x1+$FWHM" | bc -l | awk '{printf "%f", $0}'`
	xR=`echo "$x2-$FWHM" | bc -l | awk '{printf "%f", $0}'`
	printf " x1 = $x1 -> xL = $xL\n x2 = $x2 -> xR = $xR\n"
	delta=`echo "$xR-$xL" | bc -l`
	echo " New number of bins = $delta"
	
#================================================================= INSIDE-NEAR
elif [ "${output[$k]}" -eq 5 ]
then
	FWHM=`echo "sqrt(8*l(2))*sqrt($a+$b*${E_gamma[k]})" | bc -l | awk '{printf "%f", $0}'`
	xL=`echo "$x1-$FWHM" | bc -l | awk '{printf "%f", $0}'`
	xR=`echo "$x2+$FWHM" | bc -l | awk '{printf "%f", $0}'`
	printf " x1 = $x1 -> xL = $xL\n x2 = $x2 -> xR = $xR\n"
	delta=`echo "$xR-$xL" | bc -l`
	echo " New number of bins = $delta"
fi

printf "\n\n"
