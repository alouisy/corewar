.name "zxork"
.comment "I'M ALIIIIVE"

lds: live %1 
test2:	ld %2, r1
	ld %0, r2
	ld %10, r3
	ld %260, r4
test1:	ld %499, r5
	ld %816, r6
	ld %666, r7
	ld %66666, r8
	ld %666666666, r9
	ld %:lds2, r10
	ld %:lds, r11
	ld %:test2, r12
	ld %:test1, r13
	ld %:lds, r11
	ld %65400, r14
test3:	ld 193, r0
	ld 514, r1
	ld 66666, r2
	ld -213, r3
	ld -666, r4
	ld -66666, r5
test4: add r1, r2, r15 
	add r10, r4, r2
	add r11, r4, r3
	add r12, r4, r4
	add r13, r4, r5
	add r8, r4, r6
	add r9, r4, r7
	add r9, r1, r8
lds2: live %1 
