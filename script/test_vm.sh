#!/bin/sh

if [ $# -ne 1 ] && [ $# -ne 2 ]; then
	echo "usage: ./test_vm.sh [-del] [-verb [file.cor]] [-win [file.cor]] [-diff]"
else
	if [ "$1" = "-del" ]; then
		rm -rf ../ressources/example
		rm -rf ../ressources/mine
	fi

	if [ "$1" = "-verb" ] || [ "$1" = "-win" ]; then
		
		if [ "$1" = "-win" ]; then
			rm ../ressources/mine/42.cor
			rm ../ressources/mine/Car.cor
			rm ../ressources/mine/bee_gees.cor
			rm ../ressources/mine/fork.cor
			rm ../ressources/mine/lfork.cor
			rm ../ressources/mine/gg.cor
			rm ../ressources/mine/mandragore.cor
			rm ../ressources/mine/maxi_simple.cor
			rm ../ressources/example/42.cor
			rm ../ressources/example/Car.cor
			rm ../ressources/example/bee_gees.cor
			rm ../ressources/example/fork.cor
			rm ../ressources/example/lfork.cor
			rm ../ressources/example/gg.cor
			rm ../ressources/example/mandragore.cor
			rm ../ressources/example/maxi_simple.cor
		fi
		echo "---------- RESSOURCE VM ------------";

		for filename in ../ressources/example/*.cor; do
			if [ $# -eq 2 ]; then
				test=$2
			else
				test=$filename
			fi
			echo $test VS $filename
			if [ "$1" = "-verb" ]; then
				../ressources/corewar -a -v 31 -d 10000 $test $filename > $filename.txt
			else
				../ressources/corewar $test $filename > $filename.txt
			fi
		done

		echo "------------- MY VM ---------------";

		for filename in ../ressources/mine/*.cor; do
			if [ $# -eq 2 ]; then
				test=$2
			else
				test=$filename
			fi
			echo $test VS $filename
			if [ "$1" = "-verb" ]; then
				../corewar -v 63 -dump 10000 $test $filename > $filename.txt
			else
				../corewar $test $filename > $filename.txt
			fi
		done

	fi

	if [ "$1" = "-diff" ]; then

		for filename in ../ressources/mine/*.txt; do
			diff ../ressources/example/${filename##*/} $filename
		done
	fi
fi
