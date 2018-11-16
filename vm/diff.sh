#!/bin/bash

./corewar -dump 110 -v 3 $@ > us.txt && ./../subject/corewar -d 110 -v 30 $@ > zaz.txt && diff us.txt zaz.txt
