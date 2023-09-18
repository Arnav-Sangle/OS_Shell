echo "Enter a no. "
read n

m=`expr $n / 2`
i=2
#flag=0

while [ $i -lt $m ]	#if n=4 then m=2, so use -le instead of -lt
do
	if [ `expr $n % $i` -eq 0 ]
	then
		#flag=1
		echo "Not Prime"
		break
	else
		i=`expr $i + 1`
		#OR
		#((i++))
	fi
done

#echo $i $m

if [ $m -eq 0 ] #1/2=0
then
	echo "Neither Prime nor Composite"
elif [ $m -eq 1 -o `expr $i - 1` -eq $m ] #2/2=1 OR i=m-1 i.e. loop complete
then
	echo "Prime"
fi
