global H5

H5:
    push rbx

    mov edx, 32
    xor rax, rax
    xor rbx, rbx
lop:
    cmp edx, 0
    je end
    rol eax, 1

    mov bl, [rdi]
    add eax, ebx

    inc rdi
    dec edx
    jmp lop
end:
    div rsi
    mov rax, rdx

    pop rbx
    ret
