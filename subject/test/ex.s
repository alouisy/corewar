.name "gg"
.comment "testing"

l2:		sti r1, %:live, %1
		and %1, %1, r5
		and r1, r1, r0
		and r1, r1, r2
		and r1, r1, r3
		and r1, r1, r4
		and %4294967295, %4294967295, r5
#copy de live
		and r5, %191367934, r6
		and r5, %67108875, r7
		and r5, %1744961025, r8
#fin copie
		and %4294967295, %1, r10
		and r1, %0, r5
#copie la fonction wlive dans la mémoire
cpylive:	sti r6, %-505, %0
		sti r7, %-508, %0
		sti r8, %-511, %0
#copie live dans la mémoire
wlive:	sti r10, %-500, %0
		sti r1, %-503, %0
		lfork %-700
live:	live %1
		zjmp %:live
