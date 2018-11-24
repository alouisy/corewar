.name "zork 2000"
.comment "That's'll folks!"

#init des registres et fork a reset
l1:		live %-5
		ld %218759116, r9 #0D 09 FF CC zjump
		ld %-23, r12
		ld %57674497, r11 #st 03 70 0b 01
		fork %:l2
		ld %190056972, r10 #0B 54 0A 0C sti
		ld %-23, r13
		fork %:boum
		ld %218759116, r10 #0D 09 FF CC zjump
		ld %-21, r12
		ld %-21, r13
		add r16, r16, r16
		live %-5
		zjmp %-491
boum:   live %-5
		add r16, r16, r16
		st r10, 65035
		st r09, 65034
		zjmp %-511

l2:		live %-5
		sti r1, %:live, %2
		st r16, -7
		st r16, -11
		fork %:pivot
		fork %:ifav
		ld %656, r2 #00 00 02 90: ld
		ld %16842752, r3 #01 01 00 00: param de ld
		ld %-2, r5 #i pour boucle while
		ld %-1, r6 #operations sur les negs pour eviter les 00 00 00 XX

#boucle de fork
ifar:	live %-5
		sub r5, r6, r5 #i--
		add r1, r1, r1 #(if (r1 != 0) : carry = 0)
		zjmp %:elsear
		fork %:ifar
		add r16, r16, r16 #(if (r16 == 0) : carry = 1)
		zjmp %:ifar
elsear:	live %-5
		ld %-3, r5
		add r1, r1, r1 #(if (r16 == 0) : carry = 1)
		fork %:ifar

#bouclier arriere en boucle
l3:		live %-5
		st r4, 65032
		st r2, 65031
		st r1, 65030
		st r3, 65029
		st r4, 65062
		st r2, 65061
		st r1, 65060
		st r3, 65059
		st r4, -350
		st r2, -351
		st r1, -352
		st r3, -353
l4:		live %-5
		and r16, r16, r16
		zjmp %:l3

#ecriture des bnnes valeurs de live
pivot:	live %-5
live:	ld %-5, r15
		sti r15, %:l1, %1
		sti r15, %:l2, %1
		sti r15, %:boum, %1
		sti r15, %:ifar, %1
		sti r15, %:elsear, %1
		sti r15, %:ifav, %1
		sti r15, %:av, %1
		sti r15, %:pivot, %1
		sti r15, %:l3,%1
		sti r15, %:l4, %1
		sti r15, %:p1, %1
		sti r15, %:end, %1
		lfork %-2048 

#boucle de fork
ifav:	live %-5
erase:	sti r1, %:live, %2
		st r16, -7
		st r16, -11
		ld %100, r3
		ld %1, r8
		ld %57674497, r11 #st 03 70 0b 01
av:		live %-5
		fork %:pivot

#bouclier avant
p1:		live %-5
		and r16, r16, r16
		fork %:end
		st r11, :tar1 #st
		st r11, 100 #st
		st r11, 150 #st
		st r11, 200 #st
		st r11, 250 #st
		st r11, 300 #st
		st r11, 400 #st
		st r11, 450 #st
		st r11, 500 #st
		st r8, 511 #live
		and r16, r16, r16
end:	live %1
		zjmp %:p1
tar1: aff r1

