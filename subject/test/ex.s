.name "gg"
.comment "testing"

l2:		sti r1, %:live, %1
		and %1, %1, r6
		and r1, r1, r0
		and r1, r1, r2
		and r1, r1, r3
		and r1, r1, r4
		and r1, %0, r5

live:	live %1
		fork %:write
		zjmp %:live
write:	sti r6, %20, %0
		sti r1, %17, %0
