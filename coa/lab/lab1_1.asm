.data   
prompt: .asciiz "Enter a positive Number"
true:   .asciiz "Number is positive"
false:  .asciiz "Number is negative"

.text   
        .globl  main

main:   
    # Prompt for number
    la      $a0,    prompt
    li      $v0,    4
    syscall 
    # Take the input
    li      $v0,    5
    syscall 
    move    $s0,    $v0
    move    $a0,    $s0
    li      $v0,    1
    syscall 
    # check if the number is positive
    ble     $s0,    $zero,  label
    la      $a0,    true
    li      $v0,    4
    syscall 
label:  
    la      $a0,    false
    li      $v0,    4
    syscall 


