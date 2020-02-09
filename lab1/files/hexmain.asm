  # hexmain.asm
  # Written 2015-09-04 by F Lundevall
  # Edited  2020-02-09 by L Filippeschi
  # Copyright abandonded - this file is in the public domain.

	.text
main:
	li	$a0,10		# change this to test different values

	jal	hexasc		# call hexasc
	nop			# delay slot filler (just in case)	
back:
	move	$a0,$v0		# copy return value to argument register

	li	$v0,11		# syscall with v0 = 11 will print out
	syscall			# one byte from a0 to the Run I/O window
	
stop:	j	stop		# stop after one run
	nop			# delay slot filler (just in case)


hexasc:	add 	$v0, $0, $0 	#clears v0
	add 	$t0, $0, $0	#clears t0
	andi 	$t0, $a0, 0x0f	#saves the first 4 bits in t0 rest 0 
	addi 	$t1, $0, 10	#initializes the if control 	

	slt 	$t2, $t0, $t1   #if (a0<10)
	beq 	$t2 , $0, if
	nop 
	
	addi 	$v0, $t0, 0x30	
	jr 	$ra 
	nop
		
if:	addi 	$v0, $t0, 0x37	#bigger letter case 
	jr 	$ra  
	nop
	  
