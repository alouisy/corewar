.name "carry"
.comment "I'M ALIIIIVE"

live1:	live %1
		zjmp %399
and:	#and %1, %2, r1
		#and %4, %3, r2
		zjmp %:and
add:	#add r2, r3, r4 
		zjmp %:add
sub:	#sub r2, r3, r5 
		zjmp %:sub
ld:		ld %100, r6 #carry?
		zjmp %:ld
lld:	lld %100, r7 #carry?
		zjmp %:lld
lldi:	lldi %100, r9, r8 #carry?
		zjmp %:lldi
