  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Edited  2020-02-09 by L Filippeschi
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.


  #
  # Please keep the two macros PUSH and POP unchanged
  #
.global delay
.global time2string 

.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
  #

	.data
	.align 2
mytime:	.word 0x5957 #0x0000 
timstr:	.ascii "text more text lots of text\0"
	.text
main:
	# print timstr
	la	$a0,timstr
	li	$v0,4
	syscall
	nop
	# wait a little
	li	$a0,1000
	jal	delay
	nop
	# call tick
	la	$a0,mytime
	jal	tick
	nop
	# call your function time2string
	la	$a0,timstr
	la	$t0,mytime
	lw	$a1,0($t0)
	jal	time2string
	nop
	# print a newline
	li	$a0,10
	li	$v0,11
	syscall
	nop
	# go back and do it all again
	j	main
	nop
# tick: update time pointed to by $a0
tick:	lw	$t0,0($a0)	# get time
	addiu	$t0,$t0,1	# increase
	andi	$t1,$t0,0xf	# check lowest digit
	sltiu	$t2,$t1,0xa	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x6	# adjust lowest digit
	andi	$t1,$t0,0xf0	# check next digit
	sltiu	$t2,$t1,0x60	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa0	# adjust digit
	andi	$t1,$t0,0xf00	# check minute digit
	sltiu	$t2,$t1,0xa00	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x600	# adjust digit
	andi	$t1,$t0,0xf000	# check last digit
	sltiu	$t2,$t1,0x6000	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa000	# adjust last digit
tiend:	sw	$t0,0($a0)	# save updated result
	jr	$ra		# return
	nop

hexasc:	add 	$v0, $0, $0 	#clears v0
	add 	$t0, $0, $0	#clears t0
	andi 	$t0, $a0, 0x0f	#saves the first 4 bits in t0 rest 0 
	addi 	$t1, $0, 10	#initializes the if control 	
	slt 	$t2, $t0, $t1   #if (a0<10)
	beq 	$t2 , $0, if
	nop 
	addi 	$v0, $t0, 0x30	#number case
	jr 	$ra 
	nop	
if:	addi 	$v0, $t0, 0x37	# letter case 
	jr 	$ra  
	nop
	
	
delay: 	add 	$t0, $a0, $0 	#saves the argument ms
	add 	$t1, $0, $0	#initialize int i 
while: 	slt	$t2, $t0, $0	# t2=1 if ms<0
	beq	$t2, 1, done
	nop
	addi 	$t0, $t0, -1	#ms--
for:	slti 	$t3, $t1, 5252	# i<4711
	addi	$t1, $t1, 1	#i++
	beq	$t3, 1, for
	nop
	add	$t1, $0, $0
	j	while
	nop
done:	jr	$ra
	nop
	
time2string:  			########## $a0 area in memory $a1 time-info
	PUSH $a0
	PUSH $ra
	add 	$t0, $a1, $0 	# $a1 time info is in t0
	add 	$t1, $a0, $0 	# a0 area in memory is in t1
	
	srl   	$t2, $t0, 12 
	add 	$a0, $t2, $0 	#saves the first 4 bits in a0 for hexasc to be excecuted
	jal 	hexasc 
	nop			#will return the ascii code of the first minute

	POP $ra
	POP $a0
	sb 	$v0, 0($a0)	#saves the first minute in the area 
	
	PUSH $a0
	PUSH $ra
	add 	$t0, $a1, $0 	# $a1 time info is in t0
	add 	$t1, $a0, $0 	# a0 area in memory is in t1
	srl   	$t2, $t0, 8 
	add 	$a0, $t2, $0
	jal 	hexasc 
	nop  
	POP $ra
	POP $a0
	sb 	$v0, 1($a0)	#saves the second minute 
	
	add 	$t3, $0, 0x3A
	sb 	$t3, 2($a0)	#saves the colon
	
	PUSH $a0
	PUSH $ra
	add 	$t0, $a1, $0 	# $a1 time info is in t0
	add 	$t1, $a0, $0 	# a0 area in memory is in t1
	srl   	$t2, $t0, 4 
	add 	$a0, $t2, $0
	jal 	hexasc 
	nop  
	POP $ra
	POP $a0
	
	sb 	$v0, 3($a0) 	#saves the first second
	add 	$t6, $0, $v0	#clears t6
	sll	$t6, $t6, 8	# first second in the 2nd byte
	PUSH $a0
	PUSH $ra
	add 	$t0, $a1, $0 	# $a1 time info is in t0
	add 	$t1, $a0, $0 	# a0 area in memory is in t1
	srl   	$t2, $t0, 0 
	add 	$a0, $t2, $0
	jal 	hexasc 
	nop  
	POP $ra
	POP $a0
	add 	$t7, $0, 0x3030
	add 	$t6, $t6, $v0
	bne 	$t6, $t7, normalcase   #if t6!=0 do as normal
	nop
	add	$t6, $0, 0x44
	sb 	$t6, 0($a0)
	add	$t6, $0, 0x49
	sb 	$t6, 1($a0)
	add	$t6, $0, 0x4e
	sb 	$t6, 2($a0)
	add	$t6, $0, 0x47
	sb 	$t6, 3($a0)
	add	$t6, $0, 0x00
	sb 	$t6, 4($a0)
	jr 	$ra
	nop
	
normalcase:
	sb 	$v0, 4($a0) 	#saves the second second
	
	add	$t3, $0, 0x00
	
	sb 	$t3, 5($a0)	#saves the NUL
	jr	$ra
	nop
	
