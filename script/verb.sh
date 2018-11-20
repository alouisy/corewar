#!/bin/bash

./../corewar -v $1 $2 $3 $4 $5 > us.txt ; ./../subject/corewar -v $1 $2 $3 $4 $5 > zaz.txt ; diff us.txt zaz.txt | more
