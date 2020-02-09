.text 
 
	add	$a0, $0, 1 	# a0 = n 
	beq 	$a0, 1, zero
	beq	$a0, $0, zero
	nop
	add 	$a1, $0, $a0	# sets a1 for the loop j=n
	addi	$a1, $a1, -1	# j=n-1
	add 	$v0, $a0, $0	# initialize the result to the first n,  rtrn = n
for1:
	beq	$a1, 1, stop	# checks when we are at j == 1
	nop
	add 	$a2, $0, $0	# clears the temporary sum (x)
	add 	$a3, $a1, $0	# i=j
for2:
	beq	$a3, 0, done2	# i==0
	nop
	add 	$a2, $a2, $v0 	# x += rtrn
	add 	$a3, $a3, -1 	# i-- 
	beq	$0, $0, for2
	nop
done2:
	add	$v0, $a2, $0	# rtrn = x
	addi 	$a1, $a1, -1	# j--
	beq	$0, $0, for1
	nop

zero:	
	addi 	$v0, $0, 1
	beq	$0, $0, stop
	nop 

stop:
	beq	$0, $0, stop
	nop



