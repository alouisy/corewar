#!/bin/bash

./corewar -dump 10000 -v 3 $@ > us.txt && ./../subject/corewar -d 10000 -v 22 $@ > zaz.txt && diff us.txt zaz.txt
