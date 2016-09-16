; a very simple assembly program for RISKY
; this program computes fibonacci values up to 100
; it outputs them on data channel 1
; return jump address expected at register 4
setup:
    set 0 100 ; store 100 for comparison
    set 1 1 ; operand a
    set 2 1 ; operand b
    set 3 0 ; operand c
    ; setup data channel
    cdc 1 DC_WRITE DC_ACTIVE
    ; write out first two 1s
    wri 1 1
    wri 1 2
    jmp 4

; one round of fibonacci
; return jump address expected at register 4
fibonacci:
    ; c = a + b
    add 3 1 2
    ; a = b
    cop 1 2
    ; b = c
    cop 2 3
    jmp 4

; main program
main:
    set 4 main#1
    jmp setup

main#1:
    set 4 main#2
    jmp fibonacci

main#2:
    ; only write out if less than 100
    gtn 5 0 3
    bra end 5
    ; write out c
    wri 1 3
    ; set return location
    set 4 main#1
    ; jump back to fibonacci
    jmp fibonacci

end:
    ; program end
    hlt
