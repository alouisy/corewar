#!/bin/sh

for filename in ../ressources/champs/not_valid/*.s; do
	../asm $filename
done
