#!/bin/sh

path_to_test="./"
path_to_testok="./srcsok/"
path_to_testko="./srcsko/"
path_to_ft_asm="../"
path_to_asm="./"
#tester=$path_to_test"/test"
ft_asm=$path_to_ft_asm"asm"
asm=$path_to_asm"asm"
launcher_log=$path_to_test"launcher.log"

let "koTest = 0"
let "okTest = 0"
let "success = 0"
let "fail = 0"
let "invalid_dump = 0"
let "discarded = 0"
let "total = 0"

rm -f $launcher_log
#rm -f "$path_to_test/"*.s
rm -f "$path_to_testok"*.cor
rm -f "$path_to_testok"*.diff
rm -f "$path_to_testok"*.txt
rm -f "$path_to_testok"*.log
rm -f "$path_to_testko"*.log
rm -f "$path_to_testko"*.txt
rm -f "$path_to_testko"*.cor
rm -f "$path_to_testko"*.diff

#echo "\033[0;32m==Building $tester==\033[0m"	| tee	-a	$launcher_log
#make -C $path_to_test							>>			$launcher_log
echo "\n\033[0;32m==Building $ft_asm==\033[0m"	| tee	-a	$launcher_log
make -C $path_to_ft_asm							>>			$launcher_log
#if [ -x $tester ]
#then
	if [ -x $asm ]
	then
		if [ -x $ft_asm ]
		then
		echo "\033[0;34mProducing testing .s file\033[0m"
		#$tester >> $launcher_log
		allKo=`ls "$path_to_testko" | grep ".s"`
		let "total = `ls $path_to_testko | grep ".s" |  wc -l`"
		for file in $allKo # Starting test with invalid syntax source files
		do
			let "koTest = $koTest + 1"
			$asm "$path_to_testko$file" >> $launcher_log
			cor=`echo $file | cut -d'.' -f1`
			if [ -f "$path_to_testko$cor.cor" ]
			then
				#mv $path_to_testko$file $path_to_testok$file
				let "discarded = $discarded + 1"
			else
				$asm "$path_to_testko$file" > "$path_to_testko$cor.log"
				$ft_asm "$path_to_testko$file" >> $launcher_log
				if [ -f "$path_to_testko$cor.cor" ]
				then
					let "fail = $fail + 1"
				else
					$ft_asm "$path_to_testko$file" > "$path_to_testko$cor.my.log"
					let "success = $success + 1"
				fi
			fi
			echo "\033[A\033[2K\033[0;36mkoTests: $koTest tests, $discarded discarded, $success success, $fail fails\033[0m"

		done
		echo "\n\n"
		let "success = 0"
		let "fail = 0"
		let "discarded = 0"
		allOk=`ls "$path_to_testok" | grep ".s"`
		let "total = `ls $path_to_testok | grep ".s" | wc -l`"
		for file in $allOk # Starting test with valid syntax source files
		do
			let "okTest = $okTest + 1"
			$asm "$path_to_testok$file" >> $launcher_log
			cor=`echo $file | cut -d'.' -f1`
			if [ -f "$path_to_testok$cor.cor" ]
			then
				hexdump -vC "$path_to_testok$cor.cor" > "$path_to_testok$cor.txt"
				rm -f "$path_to_testok$cor.cor"
				$ft_asm "$path_to_testok$file" >> $launcher_log
				if [ -f "$path_to_testok$cor.cor" ]
				then
					hexdump -vC "$path_to_testok$cor.cor" > "$path_to_testok$cor.my.txt"
					diff "$path_to_testok$cor.txt" "$path_to_testok$cor.my.txt" > "$path_to_testok$cor.diff"
					if [ -s "$path_to_testok$cor.diff" ]
					then
						let "invalid_dump = $invalid_dump + 1"
					else
						let "success = $success + 1"
					fi
				else
					$ft_asm "$path_to_testok$file" > "$path_to_testok$cor.log"
					let "fail = $fail + 1"
				fi
			else
				#mv $path_to_testok$file $path_to_testko$file
				let "discarded = $discarded + 1"
			fi
			echo "\033[A\033[2K\033[0;36mokTests: $okTest tests, $discarded discarded, $success success, $fail fails, $invalid_dump invalid dumps\033[0m"
		done
		else
			echo "$ft_asm is not executable"
		fi
		echo "$total\n"
	else
		echo "$asm is not executable"
	fi
#else
	#echo "$test is not executable"
#fi
