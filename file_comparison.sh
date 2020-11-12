#!/bin/bash

# cmp_dir - program to compare two directories

# Check for required arguments
if [ $# -ne 2 ]; then
	  echo "usage: $0 directory_1 directory_2" 1>&2
	    exit 1
fi

# Make sure both arguments are directories
if [ ! -d "$1" ]; then
	  echo "$1 is not a directory!" 1>&2
	    exit 1
fi

if [ ! -d "$2" ]; then
	  echo "$2 is not a directory!" 1>&2
	    exit 1
fi

# Process each file in directory_1, comparing it to directory_2
in1_notin2=0
file_diff=0
while IFS= read -r -d $'\0' filename
do
	fn=${filename#$1}
	if [[ "$fn" == ".git/"* ]]; then
		continue
	fi
	if [ ! -f "$2/$fn" ]; then
		echo "$fn exists in $1 but is missing from $2"
		in1_notin2=$((in1_notin2 + 1))
	else
		line_diff=`diff -b -B "$filename" "$2/$fn" | grep "^[<>]" | wc -l`
		if [ $line_diff  -ne 0 ]; then
			echo "$filename and $2/$fn differ by $line_diff lines"
			file_diff=$((file_diff + 1))
		fi
	fi
done < <(find "$1" -type f -print0)

# Already accounted for different files, just need to find files in $2 not in $1
in2_notin1=0
while IFS= read -r -d $'\0' filename
do
	fn=${filename#$2}
	if [[ "$fn" == ".git/"* ]]; then
		continue
	fi
	if [ ! -f "$1/$fn" ]; then
		echo "$fn exists in $1 but is missing from $2"
		in2_notin1=$((in2_notin1 + 1))
	fi
done < <(find "$2" -type f -print0)

echo "*** SUMMARY ***"
echo "Files in $1 not in $2 = $in1_notin2"
echo "Files in $2 not in $1 = $in2_notin1"
echo "Files in both $1 and $2 but have diff = $file_diff"
