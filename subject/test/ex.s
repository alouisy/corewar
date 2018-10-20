.name "gg"
.comment "testing"

l2:		sti r1, %:live, %1
		and r1, %0, r1

live:	live %1
		fork %-513
		zjmp %:live
