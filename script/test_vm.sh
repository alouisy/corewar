#!/bin/sh

if [ $# -ne 1 ]; then
	echo "usage: ./test_vm.sh [-del] [-exec] [-diff]"
fi

if [ "$1" == "-del" ]; then
	rm -rf ../ressources/example
	rm -rf ../ressources/mine
	rm -rf ./vm_diff
fi

if [ "$1" == "-exec" ]; then

	echo "---------- RESSOURCE vm ------------";

	for filename in ../ressources/example/*.cor; do
		echo $filename VS $filename
		../ressources/corewar -a -v 31 -d 12000 $filename $filename > $filename.txt
	done

	echo "------------- MY VM ---------------";

	for filename in ../ressources/mine/*.cor; do
		echo $filename VS $filename
		../corewar -v 31 -dump 12000 $filename $filename > $filename.txt
	done

fi

if [ "$1" == "-diff" ]; then

	for filename in ../ressources/mine/*.txt; do
		diff ../ressources/example/${filename##*/} $filename
	done
fi
