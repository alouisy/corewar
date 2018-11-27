.name "zork 2000"
.comment "That's'll folks!"

#init des registres et fork a reset
l1:		live %-5
		and r16, %0, r16
erase:	sti r1, %:live, %2
		st r16, -7
		st r16, -11
live:	ld %-5, r15
		ld %57674497, r11 #st 03 70 0b 01
		ld %-1, r6 #operations sur les negs pour eviter les 00 00 00 XX
		fork %:l8
l7:		live %-5
		fork %:twin2
twin1:	ld %218758878, r10 #0D 09 FF 01 zjump
		ld %-281, r13
		add r16, r16, r16
l2:		live %-5
		st r10, 65067
		zjmp %-479
twin2:  ld %190056972, r10 #0B 54 0A 0C sti
		ld %-285, r13
		add r16, r16, r16
l3:		live %-5
		st r10, 65031
		zjmp %-511

l8:		live %-5
		ld %-10, r5
		fork %:ifav
		ld %656, r2 #00 00 02 90: ld
		ld %16842752, r3 #01 01 00 00: param de ld

#boucle de fork
ifar:	live %-5
		sub r5, r6, r5 #i--
		zjmp %:l5
		fork %:l5
		add r16, r16, r16 #(if (r16 == 0) : carry = 1)
		zjmp %:ifar

#bouclier arriere en boucle
l5:		live %-5
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
l6:		live %-5
		and r16, r16, r16
		zjmp %:l5

#ecriture des bnnes valeurs de live
pivot:	live %-5
		sti r15, %:l5, %1
		st r16, -5
		sti r15, %:l6, %1
		st r16, -5
		sti r15, %:p1, %1
		st r16, -5
		sti r15, %:p2, %1
		st r16, -5
		sti r15, %:l1, %1
		st r16, -5
		sti r15, %:l2, %1
		st r16, -5
		sti r15, %:end, %1
		st r16, -5
		sti r15, %:ifav, %1
		st r16, -5
		sti r15, %:l3, %1
		st r16, -5
		sti r15, %:l7, %1
		st r16, -5
		sti r15, %:l8, %1
		st r16, -5
		sti r15, %:ifar, %1
		st r16, -5
		sti r15, %:pivot, %1
		st r16, -5

#boucle de fork
ifav:	live %-5
		fork %:pivot

#bouclier avant
p1:		live %-5
		sub r5, r6, r5 #i--
		zjmp %:p2
		add r16, r16, r16 #(if (r16 == 0) : carry = 1)
		zjmp %:tar1
p2:		st r11, :tar1 #st
		st r11, 100 #st
		st r11, 150 #st
		st r11, 200 #st
		st r11, 250 #st
		st r11, 300 #st
		st r11, 400 #st
		st r11, 450 #st
		st r11, 500 #st
		ld %1, r8
		st r8, 511 #live
		and r16, r16, r16
end:	live %1
		zjmp %:p1
tar1: aff r1
