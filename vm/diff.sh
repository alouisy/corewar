#!/bin/bash

./corewar -dump 3000 -v $@ > us.txt && ./../subject/corewar -d 3000 -v 4 $@ > zaz.txt && diff us.txt zaz.txt
