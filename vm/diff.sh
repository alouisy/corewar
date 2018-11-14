#!/bin/bash

./corewar -dump 3000 -v 30 $@ > us.txt && ./../subject/corewar -d 3000 -v 30 $@ > zaz.txt && diff us.txt zaz.txt
