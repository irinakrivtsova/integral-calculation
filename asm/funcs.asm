section .data
    c1 dq 0.35
    c2 dq 0.95
    c3 dq 2.7
    c4 dq 3.0
    c5 dq 1.0
    c6 dq 2.0

section .text
global func1
global func2
global func3

func1:
    push ebp
    mov ebp, esp

    finit
    fld qword [ebp + 8]  
    fmul st0, st0   ; x^2
    fmul qword [c1] ; 0.35x^2

    fld qword [ebp + 8]   
    fmul qword [c2] ; 0.95x

    fsubp st1, st0  ; 0.35x^2 - 0.95x
    fadd qword [c3] ; + 2.7

    mov esp, ebp
    pop ebp
    ret

func2:
    push ebp
    mov ebp, esp

    finit
    fld qword [ebp + 8] 
    fmul qword [c4] ; 3x        
    fadd qword [c5] ; 3x + 1

    mov esp, ebp
    pop ebp
    ret

func3:
    push ebp
    mov ebp, esp

    finit
    fld qword [c5]     
    fld qword [ebp + 8]     
    fadd qword [c6]         
    fdivp st1, st0 

    mov esp, ebp
    pop ebp
    ret
    