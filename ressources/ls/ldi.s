.name "ldi"
.comment "I'M ALIIIIVE"

ldis: live %1 
#test dir dir
test2:
	ldi %-66666, %178520066, r9
	st r9, 0
	ldi %-66666, %43648261, r10
	ldi %-66666, r9, r11
	ldi %-666666666, r10, r12
	ldi %0, %0, r1
	ldi %2, %0, r2
	ldi %4, %3, r3
	ldi %3, %-4, r4
	ldi %-4, %3, r5
	ldi %-5, %-5, r6
	ldi %666, %-666, r7
	ldi %66666, %10, r8
	ldi %66666, %666, r9
	ldi %66666, %-10, r10
	ldi %66666, %-666, r11
	ldi %666666666, %10, r12
	ldi %666666666, %666, r13
	ldi %666666666, %-10, r14
	ldi %666666666, %-666, r15
	ldi %:ldis, %-666, r1
	ldi %:test3, %-666, r2
	ldi %193, %-20, r3
	ldi %193, %-900, r4
	ldi %-666, %193, r5
	ldi %-666, %-193, r6
	ldi %-666, %-666, r7
	ldi %-66666, %10, r8
	ldi %-66666, %666, r9
	ldi %-66666, %-10, r10
	ldi %-66666, %-666, r11
	ldi %-666666666, %10, r12
#test dir reg
test3:
	ldi %0, r1, r1
	ldi %193, r2, r2
	ldi %193, r3, r3
	ldi %193, r4, r4
	ldi %666, r5, r5
	ldi %666, r6, r6
	ldi %666, r7, r7
	ldi %66666, r8, r8
	ldi %66666, r9, r9
	ldi %66666, r10, r10
	ldi %66666, r11, r11
	ldi %666666666, r12, r12
	ldi %666666666, r13, r13
	ldi %666666666, r14, r14
	ldi %666666666, r15, r15
	ldi %:ldis, r2, r1
	ldi %:test3, r3, r2
	ldi %193, r1, r3
	ldi %193, r2, r4
	ldi %-666, r3, r5
	ldi %-666, r4, r6
	ldi %-666, r5, r7
	ldi %-66666, r6, r8
	ldi %-65538, r7, r9
	ldi %-66666, r8, r10
	ldi %-66666, r9, r11
	ldi %-666666666, r10, r12
#test ind dir
#test ind reg
#test reg dir
##test reg reg
