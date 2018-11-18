.name "or"
.comment "I'M ALIIIIVE"

ors: live %1 
#test dir dir
test2:
	or %-66666, %178520066, r9
	or %-66666, %43648261, r10
	or %-66666, r9, r11
	or %-666666666, r10, r12
	or %0, %0, r1
	or %2, %0, r2
	or %4, %3, r3
	or %3, %-4, r4
	or %-4, %3, r5
	or %-5, %-5, r6
	or %666, %-666, r7
	or %66666, %10, r8
	or %66666, %666, r9
	or %66666, %-10, r10
	or %66666, %-666, r11
	or %666666666, %10, r12
	or %666666666, %666, r13
	or %666666666, %-10, r14
	or %666666666, %-666, r15
	or %:ors, %-666, r1
	or %:test3, %-666, r2
	or %193, %-20, r3
	or %193, %-900, r4
	or %-666, %193, r5
	or %-666, %-193, r6
	or %-666, %-666, r7
	or %-66666, %10, r8
	or %-66666, %666, r9
	or %-66666, %-10, r10
	or %-66666, %-666, r11
	or %-666666666, %10, r12
#test dir reg
test3:
	or %0, r1, r1
	or %193, r2, r2
	or %193, r3, r3
	or %193, r4, r4
	or %666, r5, r5
	or %666, r6, r6
	or %666, r7, r7
	or %66666, r8, r8
	or %66666, r9, r9
	or %66666, r10, r10
	or %66666, r11, r11
	or %666666666, r12, r12
	or %666666666, r13, r13
	or %666666666, r14, r14
	or %666666666, r15, r15
	or %:ors, r2, r1
	or %:test3, r3, r2
	or %193, r1, r3
	or %193, r2, r4
	or %-666, r3, r5
	or %-666, r4, r6
	or %-666, r5, r7
	or %-66666, r6, r8
	or %-65538, r7, r9
	or %-66666, r8, r10
	or %-66666, r9, r11
	or %-666666666, r10, r12
#test ind dir
#test ind reg
#test reg dir
##test reg reg
