.data   
prompt:     .asciiz "Enter the value of x"
message:    .asciiz "Expression = "
newline:    .asciiz "\n"
space:      .asciiz " "

.text   
            .globl  main

main:       
    #prompt to get the value of the x
    la      $a0,    prompt
    li      $v0,    4
    syscall 
    # get the value of the x
    li      $v0,    5
    syscall 
    # store x in s0
    move    $s0,    $v0
    li      $s3,    1
    move    $s2,    $s0
    mul     $s1,    $s2,    $s2
    
