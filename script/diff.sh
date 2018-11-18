#!/bin/bash

./corewar -dump 6002 -v $@ > us.txt && ./../subject/corewar -d 6002 -v 22 $@ > zaz.txt && diff us.txt zaz.txt
