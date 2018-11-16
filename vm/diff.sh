#!/bin/bash

./corewar -dump 5000 -v 3 $@ > us.txt && ./../subject/corewar -d 5000 -v 30 $@ > zaz.txt && diff us.txt zaz.txt
