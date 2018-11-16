#!/bin/bash

./corewar -dump 1500 -v 3 $@ > us.txt && ./../subject/corewar -d 1500 -v 30 $@ > zaz.txt && diff us.txt zaz.txt
