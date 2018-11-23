#!/bin/sh

if [ $# -ne 1 ]; then
	echo "usage: ./test_asm.sh [-del] [-exec] [-diff]"
fi

if [ "$1" == "-del" ]; then
	rm -rf ../ressources/example
	rm -rf ../ressources/mine
fi

if [ "$1" == "-exec" ]; then
	echo "------------- MY ASM ---------------";

	mkdir ../ressources/mine

	for filename in ../ressources/champs/*.s; do
		../asm $filename
	done

	mv ../ressources/champs/*.cor ../ressources/mine/

	echo "---------- RESSOURCE ASM ------------";

	mkdir ../ressources/example

	for filename in ../ressources/champs/*.s; do
		../ressources/asm $filename
	done

	mv ../ressources/champs/*.cor ../ressources/example/
fi

if [ "$1" == "-diff" ]; then
	for filename in ../ressources/mine/*.cor; do
		diff ../ressources/example/${filename##*/} $filename
	done
fi
