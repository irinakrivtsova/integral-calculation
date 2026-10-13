section .data
    c1 dq 0.7
    c2 dq 0.95
    c3 dq 3.0
    c4 dq 2.0
    c5 dq 1.0


section .text
global der1
global der2
global der3

der1:
    push ebp
    mov ebp, esp

    finit
    fld qword [ebp + 8]
    fmul qword [c1] ; 0.7x               

    fsub qword [c2] ; 0.7x - 0.95 

    mov esp, ebp
    pop ebp
    ret

der2:
    push ebp
    mov ebp, esp

    finit
    fld qword [c3] ;3

    mov esp, ebp
    pop ebp
    ret

der3:
    push ebp
    mov ebp, esp

    finit
    fld qword [ebp + 8]
    fadd qword [c4] ; x + 2
    fmul st0, st0   ; (x + 2)^2

    fld qword [c5]  ; 1
    fdivrp    

    fchs            ; - 1 / (x + 2)

    mov esp, ebp
    pop ebp
    ret
    