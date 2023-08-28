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
                        echo -n "Enter file name: "
                        read fname
                        if [ -e $fname ]
                        then
                                echo "Content of File: "
                                sort -n $fname   #sorts file containing numeric data in ascending order 

                        else
                                echo "File does not exist!"
                        fi
                        ;;
		
		3) 
  			echo -n "Enter file name: "
                        read fname
                        if [ -e $fname ]
                        then
                                echo -n "Enter roll no: "
                                read roll
                                grep -w "$roll" $fname          #output word containing "pattern" as a whole not as a sub-string
                                ans=$?          # $? captures exit status of previous command, 0=success 1=fail
                                if [ $ans -eq 0 ]
                                then
                                        echo "record already exists"
                                else
                                        echo -n "Enter name of student: "
                                        read name
                                        echo $roll $name >> $fname      #entering inputed record data 
                                        echo "Record Inserted successfully"

                                fi
                        else
                                echo "file not exists"
                        fi
                        ;;
			
		4)
			echo -n "Enter the file name: "
                        read fname
                        if [ -e $fname ]
                        then
                                echo -n "Enter the roll no: "
                                read roll
                                grep -w "$roll" $fname
                                ans=$?
                                if [ $ans -eq 0 ]
                                then
                                        echo "Record found"
                                else
                                        echo "Record Not found!"
                                fi
                        else
                                echo "File does Not exist!"
                        fi
                        ;;


		5)	
  			echo -n "Enter file name: "
			read fname
			if [ -e $fname ]
			then 
				echo "Enter Roll No:  "
				read roll
				grep -w "$roll" $fname
			       	flag=$?	
				if [ $flag -eq 0 ]
				then
					echo -n "Enter New Roll no. & New Name: "
					read nroll nname
					grep -w "$nroll" $fname
					flag=$?
					if [ $flag -eq 0 ]
					then
						echo "Newly entered Roll no. already exists"
					else 
						grep -v "$roll" $fname >> temp	#excludes "word and outputs the rest"
						rm $fname	#delete original file data
						cp temp $fname	#why not cp $temp $fname	#copy data with specfied record deleted
						rm temp		#remove variable+data

						echo $nroll $nname >> $fname
					fi
				else
					echo "Record not found"
				fi
			else
				echo "File does Not exist!"
			fi
			;;

		6)
  			echo -n "Enter file name: "
			read fname
			if [ -eq $fname ]
			then
				echo -n "Enter Roll no. to delete: "
				read roll
				grep -w "$roll" $fname
				flag=$?
				if [ $flag -eq 0 ]
				then
					grep -v "$roll" $fname >> temp
					rm $fname
					ls
					cp temp $fname
					ls
					rm temp
				else
					echo "Record Not found"
				fi
			else
				"File does Not exist"
			fi
			;;

		7)
			exit
			;;

		*)	#Default
			echo "Wrong choice please try again!"
			;;

	esac

done
