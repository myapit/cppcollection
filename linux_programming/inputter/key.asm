SpeedFactorKey equ 0xFFFF

; This code gets a key
; Output: AX = key
;         BX = next value for CurrentPtr
PeekKey:
	mov bx, KeyData
CurrentPtr equ $-2
.speedfactorloop:
	mov ax, [cs:bx]
	cmp ax, SpeedFactorKey
	jne .notspeedfactor
	mov al, [cs:bx+2]
	mov [cs:SpeedFactor], al
	add bx, 3
	jmp .speedfactorloop
.notspeedfactor:	
	inc bx
	inc bx
	or al, al
	jz .zero
	xor ah,ah
	dec bx
.zero:	cmp al, 01Dh
	je .JainputToggle
	ret
.JainputToggle:
	mov ax, 1B1Dh ; ctrl+] on US keyboard
	ret

GoNextKey:
	; Input: BX
	mov byte [cs:KbPrev], 0 ; Prev := Cur
	KbCur equ $ - 1
	mov word [cs:CurrentPtr], bx
	ret

; This code decides upon a delay

DecideDelay_Done:
	; Note: The largest defined delay, 2024, multiplied by 16 makes 7E80.
	; Still in limits for AX.
	mov bx, 16
	SpeedFactor equ $ - 2
	mul bx
	shr ax, 4
	xchg bx, ax
	pop edx
	pop eax
	pop ds
	ret
DecideDelay:
	; For the current key (AX), decide upon the delay before giving that key
	; Output: BX
	push ds
	push eax
	push edx
	 push cs
	 pop ds
	 or al, al
	 jnz .NotZero
	 xchg al,ah
	 or al, 80h
.NotZero:
	 mov [KbCur], al
	 cmp al, 0h
	KbPrev equ $ - 1
	 jz Delay_IsRepeat
.NotRepeat:
	 mov byte[KbRepeats], 0
	 mov bx, Delay_CharClassTable
	 shr al, 1
	 xlatb  ; = mov al, [bx+al]
	 jc .LookupEven
.LookupOdd:
	 shr al, 4
.LookupEven:
	 and ax, 15
	 xchg bx, ax
	 push DecideDelay_Done
	 jmp [Delay_CharClassPointer+bx]

Delay_IsRepeat:
	 mov al, 0
	KbRepeats equ $ - 1
	 cmp al, 2
	 mov ax, 15
	 jae DecideDelay_Done
	 mov ax, 70
	 inc byte[KbRepeats]
	 jmp DecideDelay_Done

Delay_KeyIsSpecialKey:
	 ; Special keys (F1 etc.) are quite fast, 14 cps
	 mov ax, 70
	 ret
Delay_KeyIsCtrlK:
	 ; About 10..44 ms
	 mov ax, 35
	 call Random
	 add ax, 10
	 ret
Delay_KeyIsFastCtrl:
	; cmp byte [KbPrev], 0xC3
	; jne Delay_KeyIsFastCtrl
	; mov ax, 0
	;KbF9count equ $ - 2
	; inc word [KbF9count]
	; cmp ax, 2
	; jne Delay_KeyIsFastCtrl
	; mov ax, 1500
	; ret
	 ; some 40 cps for certain editing keys
	 mov ax, 25
	 ret
Delay_KeyIsSlowKey:
	 ; Random 10..60 cps
	 mov ax, 51
	 call Random
	 add ax, 10
	 jmp Div1000by
Delay_KeyIsAlnum:
	 mov ax, 3
	 call Random
	 dec ax
	 xchg bx, ax
	 mov ax, 3
	 call Random
	 dec ax
	 imul ax, bx
	 add ax, byte 5
	KbModifier equ $-1
	 mov bx, 1
	 cmp ax, bx
	 jg .ModifierMinskip
	 xchg bx, ax
.ModifierMinskip:
	 mov bx, 18
	 cmp ax, bx
	 jl .ModifierMaxskip
	 xchg bx, ax
.ModifierMaxskip:
	 mov [KbModifier], al
	 mov bx, ax
	 shl ax, 2   ; ax = ax*4
	 add ax, bx  ;        *5
	 call Random
	 add ax, 20 ; bx = rand(modifier*6) + 20
	 xchg bx, ax
	 mov ax, 46
	 call Random
	 add bx, ax  ; bx = rand(modifier*6) + 20 + rand(46)
	 mov ax, 93
	 call Random
	 add ax, bx  ; ax = rand(modifier*6) + 20 + rand(46) + rand(93)
	 mov bx, 43691 ; 2^17 / 3
	 mul bx
	 shr dx, 1     ; x * (2^17 / 3) / 2^17
	 xchg dx, ax ; ax = ( rand(modifier*6) + 20 + rand(46) + rand(93) ) / 3
	 ret
Delay_KeyIsPondering:
	 mov ax, 524
Delay_FastReturn:
	 ret
Delay_KeyIsArrow:
	 ; Arrows, however, are slow
	 cmp byte[KbPrev], 'Z'-64
	 mov ax, 20
	 je Delay_FastReturn ; fast scrolling when alternating with ^Z
	 ; Random 8..73 cps
	 mov ax, 66
	 call Random
	 add ax, 8
	 ;jmp Div1000by
Div1000by: ; calculate 1000 / (ax)
	 xchg bx, ax
	 mov ax, 1000
	 cwd
	 div bx
	 ret

Random:
	; calculate value 0..(ax-1)
	; input, output: ax
	; uses: ebx
	push ebx
	 movzx ebx, ax
	 mov eax, 1
	KbRandSeed equ $ - 4
	 imul eax, eax,  214013
	 add eax, 2531011
	 mov [KbRandSeed], eax
	 xor edx, edx
	 div ebx
	 mov bx, dx
	xchg bx, ax
	pop ebx
	ret

Delay_CharClassPointer:
	dw Delay_KeyIsSpecialKey   ; 0
	dw Delay_KeyIsFastCtrl     ; 2
	dw Delay_KeyIsCtrlK        ; 4
	dw Delay_KeyIsAlnum        ; 6
	dw Delay_KeyIsSlowKey      ; 8
	dw Delay_KeyIsPondering    ; A
	dw Delay_KeyIsArrow        ; C

Delay_CharClassTable:
	; D, H, I, J, M are fast ctrls
	; K is CtrlK
	; A,B,E,F,W,Y, Z are other ctrls

	; Ctrl keys:
	;  @A   BC   DE   FG   HI   JK   LM   NO   PQ   RS   TU   VW   XY   Z[   \]   ^_
	;   !   "#   $%   &'   ()   *+   ,-   ./   01   23   45   67   89   :;   <=   >?
	;  @A   BC   DE   FG   HI   JK   LM   NO   PQ   RS   TU   VW   XY   Z[   \]   ^_
	;  `a   bc   de   fg   hi   jk   lm   no   pq   rs   tu   vw   xy   z{   |}   ~<del>
	db 0Ch,0C0h, 2Ch,0C0h, 22h, 24h, 02h, 00h, 00h, 00h, 00h, 02h, 02h, 28h, 88h, 88h
	db 88h, 88h, 88h, 88h, 88h, 88h, 88h, 88h, 66h, 66h, 66h, 66h, 66h, 88h, 88h, 88h
	db 86h, 66h, 66h, 66h, 66h, 66h, 66h, 66h, 66h, 66h, 66h, 66h, 66h, 68h, 88h, 88h
	db 86h, 66h, 66h, 66h, 66h, 66h, 66h, 66h, 66h, 66h, 66h, 66h, 66h, 68h, 88h,0A8h
	db 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h
	db 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h
	db 00h, 00h, 00h, 00h,0C0h, 0Ch, 0Ch, 00h,0C0h, 00h, 00h, 00h, 00h, 00h, 00h, 00h
	db 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 00h, 0Ch,0C0h, 00h, 00h, 00h, 00h, 00h

