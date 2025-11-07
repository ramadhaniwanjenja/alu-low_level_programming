section .data
    balance dd 1000
    
    menu db 10,'====== ATM MENU ======',10
         db '1. Deposit',10
         db '2. Withdraw',10
         db '3. Check Balance',10
         db '4. Exit',10
         db 'Enter your choice: ',0
    menu_len equ $ - menu
    
    deposit_prompt db 'Enter deposit amount: ',0
    deposit_len equ $ - deposit_prompt
    
    withdraw_prompt db 'Enter withdraw amount: ',0
    withdraw_len equ $ - withdraw_prompt
    
    balance_msg db 'Current Balance: $',0
    balance_len equ $ - balance_msg
    
    insufficient db 'Error: Insufficient funds!',10,0
    insufficient_len equ $ - insufficient
    
    success_deposit db 'Deposit successful!',10,0
    success_deposit_len equ $ - success_deposit
    
    success_withdraw db 'Withdraw successful!',10,0
    success_withdraw_len equ $ - success_withdraw
    
    goodbye db 'Thank you for using our ATM!',10,0
    goodbye_len equ $ - goodbye
    
    newline db 10,0

section .bss
    choice resb 2
    amount resb 10
    display_buffer resb 20

section .text
    global _start

_start:
    call main_loop
    jmp exit_atm

main_loop:
    call print_menu
    call read_choice
    
    mov al, [choice]
    sub al, '0'
    
    cmp al, 1
    je do_deposit
    
    cmp al, 2
    je do_withdraw
    
    cmp al, 3
    je do_check_balance
    
    cmp al, 4
    je exit_atm
    
    jmp main_loop

print_menu:
    mov eax, 4
    mov ebx, 1
    mov ecx, menu
    mov edx, menu_len
    int 0x80
    ret

read_choice:
    mov eax, 3
    mov ebx, 0
    mov ecx, choice
    mov edx, 2
    int 0x80
    ret

do_deposit:
    mov eax, 4
    mov ebx, 1
    mov ecx, deposit_prompt
    mov edx, deposit_len
    int 0x80
    
    call read_amount
    call convert_string_to_number
    
    add [balance], eax
    
    mov eax, 4
    mov ebx, 1
    mov ecx, success_deposit
    mov edx, success_deposit_len
    int 0x80
    
    jmp main_loop

do_withdraw:
    mov eax, 4
    mov ebx, 1
    mov ecx, withdraw_prompt
    mov edx, withdraw_len
    int 0x80
    
    call read_amount
    call convert_string_to_number
    
    mov ebx, [balance]
    cmp eax, ebx
    jg show_insufficient
    
    sub [balance], eax
    
    mov eax, 4
    mov ebx, 1
    mov ecx, success_withdraw
    mov edx, success_withdraw_len
    int 0x80
    
    jmp main_loop

show_insufficient:
    mov eax, 4
    mov ebx, 1
    mov ecx, insufficient
    mov edx, insufficient_len
    int 0x80
    jmp main_loop

do_check_balance:
    mov eax, 4
    mov ebx, 1
    mov ecx, balance_msg
    mov edx, balance_len
    int 0x80
    
    mov eax, [balance]
    call convert_number_to_string
    
    mov eax, 4
    mov ebx, 1
    mov ecx, display_buffer
    mov edx, 20
    int 0x80
    
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    int 0x80
    
    jmp main_loop

read_amount:
    mov eax, 3
    mov ebx, 0
    mov ecx, amount
    mov edx, 10
    int 0x80
    ret

convert_string_to_number:
    xor eax, eax
    xor ecx, ecx
    mov esi, amount
.convert_loop:
    movzx ebx, byte [esi + ecx]
    cmp ebx, 10
    je .convert_done
    cmp ebx, 0
    je .convert_done
    sub ebx, '0'
    imul eax, 10
    add eax, ebx
    inc ecx
    jmp .convert_loop
.convert_done:
    ret

convert_number_to_string:
    mov edi, display_buffer
    add edi, 19
    mov byte [edi], 0
    dec edi
    mov ebx, 10
.number_loop:
    xor edx, edx
    div ebx
    add dl, '0'
    mov [edi], dl
    dec edi
    test eax, eax
    jnz .number_loop
    inc edi
    mov ecx, edi
    ret

exit_atm:
    mov eax, 4
    mov ebx, 1
    mov ecx, goodbye
    mov edx, goodbye_len
    int 0x80
    
    mov eax, 1
    xor ebx, ebx
    int 0x80