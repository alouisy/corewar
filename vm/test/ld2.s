.name "zxork"
.comment "I'M ALIIIIVE"

lds: live %1 
test3:	ld 19, r1
	ld 666, r2
	ld 65600, r3
	ld -21, r4
	ld -666, r5
	ld -65600, r6
	ld 1, r7
test5:	ld :lds, r8
	ld :test3, r9
	ld :lds2, r10
lds2: live %1 
