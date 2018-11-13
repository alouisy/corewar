.name "zxork"
.comment "I'M ALIIIIVE"

ldis: live %1 
#test dir dir
test2:
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
test3: #eg+reg
	sti r1, r1, r1
	sti r1, r2, r1
	sti r1, r3, r1
	sti r1, r4, r1
	sti r1, r5, r1
	sti r1, r6, r1
	sti r1, r7, r1
	sti r1, r8, r1
	sti r1, r9, r1
	sti r1, r10, r1
	sti r1, r11, r1
test4: #dir+reg
	sti r1, %10, r1
	sti r1, %666, r1
	sti r1, %66666, r1
	sti r1, %65400, r1
	sti r1, %-10, r1
	sti r1, %-666, r1
	sti r1, %-66666, r1
	sti r1, %-65400, r1
	sti r1, %0, r1
	sti r1, %:test5, r1
	sti r1, %:ldis, r1
test5: #ind+reg
	sti r1, 10, r1
	sti r1, 666, r1
	sti r1, 66666, r1
	sti r1, 65400, r1
	sti r1, -10, r1
	sti r1, -666, r1
	sti r1, -66666, r1
	sti r1, -65400, r1
	sti r1, 0, r1
	sti r1, :test4, r1
sti r1, :ldis, r1
