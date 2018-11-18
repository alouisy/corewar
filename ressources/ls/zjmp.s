.name "zjmp"
.comment "I'M ALIIIIVE"

l1:		sti r1, %:live2, %1

live1:	live %1
		zjmp %:live
l2:		sti r1, %:live2, %1
		and r1, %0, r1
live2:	live %1
		zjmp %-600
live:	zjmp %513
		zjmp %800
