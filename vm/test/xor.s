.name "xor"
.comment "I'M ALIIIIVE"

xors: live %1 
#test dir dir
test2:
	xor %-66666, %178520066, r9
	xor %-66666, %43648261, r10
	xor %-66666, r9, r11
	xor %-666666666, r10, r12
	xor %0, %0, r1
	xor %2, %0, r2
	xor %4, %3, r3
	xor %3, %-4, r4
	xor %-4, %3, r5
	xor %-5, %-5, r6
	xor %666, %-666, r7
	xor %66666, %10, r8
	xor %66666, %666, r9
	xor %66666, %-10, r10
	xor %66666, %-666, r11
	xor %666666666, %10, r12
	xor %666666666, %666, r13
	xor %666666666, %-10, r14
	xor %666666666, %-666, r15
	xor %:xors, %-666, r1
	xor %:test3, %-666, r2
	xor %193, %-20, r3
	xor %193, %-900, r4
	xor %-666, %193, r5
	xor %-666, %-193, r6
	xor %-666, %-666, r7
	xor %-66666, %10, r8
	xor %-66666, %666, r9
	xor %-66666, %-10, r10
	xor %-66666, %-666, r11
	xor %-666666666, %10, r12
#test dir reg
test3:
	xor %0, r1, r1
	xor %193, r2, r2
	xor %193, r3, r3
	xor %193, r4, r4
	xor %666, r5, r5
	xor %666, r6, r6
	xor %666, r7, r7
	xor %66666, r8, r8
	xor %66666, r9, r9
	xor %66666, r10, r10
	xor %66666, r11, r11
	xor %666666666, r12, r12
	xor %666666666, r13, r13
	xor %666666666, r14, r14
	xor %666666666, r15, r15
	xor %:xors, r2, r1
	xor %:test3, r3, r2
	xor %193, r1, r3
	xor %193, r2, r4
	xor %-666, r3, r5
	xor %-666, r4, r6
	xor %-666, r5, r7
	xor %-66666, r6, r8
	xor %-65538, r7, r9
	xor %-66666, r8, r10
	xor %-66666, r9, r11
	xor %-666666666, r10, r12
#test ind dir
#test ind reg
#test reg dir
##test reg reg
