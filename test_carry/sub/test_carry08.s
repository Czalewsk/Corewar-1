.name "test8"
.comment "olo"

ld %-1 ,r2
ld %1, r3
lol: sub r2, r3, r4
zjmp %:lol
