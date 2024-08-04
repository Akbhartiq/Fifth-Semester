.data   
prompt:     .asciiz "Enter the value of n"
message:    .asciiz "Sum of number from 1 to "
is:         .asciiz "is: "
newline:    .asciiz "\n"
space:      .asciiz " "

.text   
            .globl  main

main:       
    # Prompt for the value of n
    la      $a0,    prompt
    li      $v0,    4
    syscall 
    # Take the input
    li      $v0,    5
    syscall 
    move    $s0,    $v0
    li      $s1,    0                           #store the sum
    li      $s2,    1                           #kind of counter

loop:       
    bgt     $s2,    $s0,        label
    add     $s1,    $s1,        $s2
    addi    $s2,    $s2,        1

label:      
    la      $a0,    message
    li      $v0,    4
    syscall 
    move    $a0,    $s0
    li      $v0,    1
    syscall 
    la      $a0,    is
    li      $v0,    4
    syscall 
    move    $a0,    $s1
    li      $v0,    1
    syscall 
    la      $a0,    newline
    li      $v0,    4
    syscall 

exit:       
    li      $v0,    10
    syscall 


