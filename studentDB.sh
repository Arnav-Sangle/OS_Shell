clear
while [ 1 ]
do
	#for \n,\t to work put string in quotes
	echo "\nMENU
	1. Create
	2. Display
	3. Insert
	4. Search
	5. Modify
	6. Delete
	7. Exit\n"

	echo  "Enter choice: \c" # \c is used to take input on same line
	read ch

	case $ch in
		1)
		       	echo -n "Enter file name: " # -n is also used for taking input on same line
			read fname
   			if [ -e fname ] #compares all existing files with fname
			then 
				echo "File already exists"
			else
				 >> $fname	#piping/writing out empty fname
				echo "File created successfully"
			fi	
			;;

		2)
			
			;;
		
		3) 
			;;
			
		4)
			;;

		5)	
			;;

		6)
			;;

		7)
			exit
			;;

		*)	#Default
			echo "Wrong choice please try again!"
			;;

	esac

done
