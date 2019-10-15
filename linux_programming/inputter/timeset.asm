xor ax,ax
mov ds,ax
mov eax, (16*3600)*0x1234DC/65536 - 900 ; set time to about 15:59:30
mov [ds:46Ch], eax
mov ax, 4C00h
int 21h
