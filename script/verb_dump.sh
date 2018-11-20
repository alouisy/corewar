#!/bin/bash

./../corewar -dump $1 -v 31 $2 $3 $4 $5 > us.txt ; ./../subject/corewar -d $1 -v 31 $2 $3 $4 $5 > zaz.txt ; diff us.txt zaz.txt | more
