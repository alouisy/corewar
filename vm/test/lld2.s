.name "zxork"
.comment "I'M ALIIIIVE"

llds: live %16777216 
test2:	lld %0, r1
test3:	lld 193, r1
	lld 666, r2
	lld 66666, r3
	lld -213, r4
	lld -666, r5
	lld -66666, r6
	lld 1, r7
test5:	lld :llds, r8
	lld :test2, r9
	lld :llds2, r10
llds2: live %1 
