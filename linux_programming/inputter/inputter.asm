bits 16
org 100h

_main:	jmp NonTSRmain

ActivationKey equ 29  ; ACTIVATION KEY ( CTRL-9, which makes CTRL+']' )

;BlankLength equ 320
	; The above number is arbitrary.
	; It has two functions:
	;   It decreases the chances that a file read error
	;   overwrites the uninstallation routine that is
	;   called after said error.
	;   And it enables UPX to compress the .com file.
	;   It happens to make the file smaller than it
	;   would be without it, despite the fact that it
	;   refuses to compress without the above part.

;;;;;;;;;;;;;;;;;;;;; DOS Interrupt
;; INT 21 function 0B must be hooked because under DOSBox,
;; it just looks up keyboard buffer...
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

GotoOldI21:
	db 0EAh ; jmp far
OldI21: dw 0,0
INT21:	cmp ah, 0x0B ; Get STDIN status
	jne GotoOldI21

	; Check if STDIN is CON
	push bx
	push dx
	push ax
	 mov ax, 4400h
	 xor bx, bx
	 pushf
	 call far [cs:OldI21] ; Get device information
	 mov al, 0x81
	 and dl, al
	 cmp dl, al
	pop ax
	pop dx
	pop bx
	jne GotoOldI21 ; Jump to standard 0B function if wasn't CON
	; Get key status using our INT 16h
	mov ah, 11h
	 pushf
	 push cs
	 call I16_Func1
	mov ax, 0x0BFF
	jnz .I21gotchar
	xor al, al
.I21gotchar:
	iret

;;;;;;;;;;;;;;;;;;;;; Keyboard Interrupt
I16testEOF:
	; Test whether we're in-stream or out-stream.
	; out-stream (not streaming) is indicated by "AE" flag condition.
	; in-stream (streaming) is indicated by "B" flag condition.
	cmp word [cs:CurrentPtr], word KeyData
	EndPointer equ $-2
	ret
GotoOldI16:
	db 0EAh ; jmp far
OldI16: dw 0,0
INT16:	
	cmp ah, 01h
	je short I16_Func1
	cmp ah, 10h
	je short I16_Func0
	cmp ah, 11h
	je short I16_Func1
	cmp ah, 00h
	je short I16_Func0
	cmp ah, 21h
	je short I16_Func1
	cmp ah, 20h
	jne GotoOldI16
I16_Func0:
	call I16testEOF
	jae CheckActivationKey0
	; Function 0: Get and wait for key
	; Step 1. Wait until any pending delay is resolved.
	call WaitDelay
	; Step 2. Check what is the next key we're about to give.
	;         Increment the pointer as necessary.
	push bx
	 call PeekKey
	 ;call CAVESTORY_ReportKey
	 call GoNextKey
	 call DecideDelay
	 call EnactDelay
	pop bx
	jmp PlainIret

CheckActivationKey0:
	pushf
	call far [cs:OldI16]
	cmp al, ActivationKey
	jne PlainIret
	; Activate
	push word I16_Func0
Activate:
	mov word [cs:CurrentPtr], KeyData
	; Reset all variables that affect timing
	call ResetVariables
	ret

CheckActivationKey1:
	pushf
	call far [cs:OldI16]
	jz Func1Idle
	cmp al, ActivationKey
	jne I16noZFreturn
	; Activate
	call Activate
	; Pop the activation key from keyboard queue
	xor ax,ax
	pushf
	call far [cs:OldI16]
	;jmp I16_Func1
I16_Func1:
	call I16testEOF
	jae CheckActivationKey1
	; Function 1: Check if key is available. ZF=1 if NO key. Does not remove key from buffer.
	; Step 1. Check whether we are currently in process of waiting before next key is given
        call CheckDelay
        jc Func1Idle
        ; Step 2. Check what is the next key we're about to give.
	push bx
	 call PeekKey
	pop bx
I16noZFreturn:
	and [esp+4], byte 0xBF
	iret
Func1Idle:
	or [esp+4], byte 0x40
PlainIret:
	iret

ResetVariables:
	push eax
	 call ReadBIOStimer
	 mov [cs:KbDelayEndStamp], eax
	 xor ax, ax
	 mov dword [cs:KbRandSeed], 1
	 mov byte [cs:KbPrev],      al
	 mov byte [cs:KbCur],       al
	 mov byte [cs:KbModifier],  5
	 mov byte [cs:KbRepeats],   al
	 mov word [cs:SpeedFactor], 16
	pop eax
	ret
;KbPrev		db ?
;KbCur		db ?
;KbModifier	db ?
;KbRepeats	db ?
;SpeedFactor	dw ?
;KbRandSeed	dd ?

;CAVESTORY_ReportKey:
;	; ax = key
;	push bx
;	push ax
;	 xchg bx, ax
;	 mov ax, 0x537E ; Report forced key (Bisqwit's CAVE STORY -related hack in Dosbox)
;	 int 21h
;	pop ax
;	pop bx
;	ret

%include "key.asm"

EnactDelay:
	; Input: bx = Number of milliseconds to delay
	add [cs:KbDelayEndStamp], bx
	adc [cs:KbDelayEndStamp+2], word 0
	
	; THE FOLLOWING CODE IS DISABLED FOR BISQWIT'S DOSBOX
;	push eax
;	push edx
;	 mov [cs:KbDelayEndStamp], eax
;	 xchg bx, ax
;	 ; With carry calculation:
;	 ;       timer = [0x46C]
;	 ;       input *= 59659
;	 ;       input += carry
;	 ;       timer += input / 3276800 ; i.e. timer += input * ~18.2e-3
;	 ;       carry  = input % 3276800
;	 movzx eax, ax
;	 imul eax, eax, 59659 ; 0x1234DC/2/2/5
;	 add eax, 59659
;	KbDelayCarry equ $ - 4
;	 push eax
;	  mov edx, 1374389535  ; round( 2^52 / (65536000/2/2/5) )
;	  mul edx
;	  shr edx, 20
;	  mov [cs:KbDelayEndStamp], edx
;	  imul edx, edx, 3276800  ; 65536000/2/2/5
;	 pop eax
;	 sub eax, edx
;	 mov [cs:KbDelayCarry], eax
;	 call ReadBIOStimer
;	 add [cs:KbDelayEndStamp], eax
;	pop edx
;	pop eax
	; END CODE DISABLEMENT
	ret

ReadBIOStimer:
	push ds
	 xor ax, ax
	 mov ds, ax
	 ;mov eax, [0x46C]
	 mov eax, [0x47C] ; BISQWIT MILLISECOND TIMER (DOSBOX)
	pop ds
	ret

CheckDelay:
	; Can use: AX. Return: CF = 1 if delaying, 0 if not
	push eax
	 call ReadBIOStimer
	 cmp eax, 1000 ; arbitrary value equal to about 55 seconds after midnight
	 KbDelayEndStamp equ $ - 4
	pop eax
	ret

WaitDelay_Loop:
	sti
	hlt
WaitDelay:
	; Wait until current delay is exhausted. Can use: AX
	call CheckDelay
	jc WaitDelay_Loop
	ret

KeyData:
;;;;;;;;;;;;;;;;;;;;;;
	times BlankLength db 0x00
TSRend:

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;; MAIN (NON-RESIDENT) ;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
RelocatedStackRoom   equ 0x80
RelocatedDataLength  equ (RelocatedDataEnd - RelocatedSource)
RelocatedTarget      equ (0x10000 - RelocatedDataLength - RelocatedStackRoom)-1
			; -1 just in case rep movsw copied one byte too many
RelocationDifference equ RelocatedTarget - (RelocatedSource - (_main - 0x100))

MaxInputDataLength equ RelocatedTarget - (KeyData - _main + 0x100)

NonTSRmain:
	mov di, RelocatedTarget
	mov si, RelocatedSource
	mov cx, (RelocatedDataLength+1) / 2
	cld
	rep movsw

	mov es, [2Ch]
	mov ah, 49h
	int 21h ; Free the environment segment.

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
GoUninstaller:

	mov bp,cs
	shl ebp,16

	cli
	mov fs, [UninstalledSegment] ; zero

	mov bx, 16h*4
	mov bp, INT16
	call CheckVector

	mov bx, 21h*4
	mov bp, INT21
	call CheckVector

	sti

	mov ax, word 0
UninstalledSegment equ $-2
	or ax,ax
	jz RelocatedSourceCodeBegin + RelocationDifference
	mov es, ax
	mov ah, 49h ; Free the code segment
	int 21h
	mov dx,UninstalledText
	call TextOut
	mov ax, 4C00h ; Exit
	int 21h

CheckVector:
	; INPUT:
	;  fs:bx -- pointer to interrupt vector
	;  ds:bp -- pointer to new interrupt handler (in cs)
	; TEMPS:
	;  es:di -- pointer to current interrupt handler
	;  edx   -- previous vector (assuming inputter was installed)
	;  si    -- copy of bx (used while string-searching)
	;  eax   -- old handler address, if installing
	; UNUSED:
	;  ecx,esp,fs,gs, Hsi,Hdi,Hbp
	les di, [fs:bx] ; current handler
	;lea si, [bp]
	mov si, bp
	cmpsd
	jne .VecNotSame
	cmpsd
	jne .VecNotSame
.VecIsSame:
	; Uninstall the current vector occupant
	mov eax, [es:di-4-(4+4)] ; Load previous vector
	mov [UninstalledSegment], es
	;mov [fs:bx],eax  ; store previous handler
	;ret
	; Below: almost the same, the redundant store to [bp-4] does not matter
	jmp short .VecIdenticalCode
.VecNotSame:
	; Store new handler address
	mov eax, ebp
.VecIdenticalCode:
	xchg [fs:bx], eax ; store new handler, get old handler
	mov [bp-4], eax   ; store old handler
	ret



; These text strings are in the un-relocated part.
; The relocated part is as short as possible so
; that the key-data can be as long as possible.
DOSerrorTable: dw DOSerror2,DOSerror3,DOSerror4,DOSerror5
Error_TooLongFile: db 'Given input script is too long.$'
Error_Unprintable: db 'Unprintable error$'
DOSerror2: db 'File not found$'
DOSerror3: db 'Path not found$'
DOSerror4: db 'Too many open files$'
DOSerror5: db 'Access denied$'
DataFileLoadErrorMessage:
	db 'INPUTTER could not load data file: "'
DataFileName:
	db 'inputter.dat', 0
DataFileNameEnds equ $-1
	db ': $'
DataFileLoadErrorMessageContinues:
	db 13,10
	db ' INPUTTER uses this file as the stream of data to input.',13,10
	db ' Please create it. It is a text file. For example, if it contains "hello",',13,10
	db ' then INPUTTER will type "hello" when you hit the activation key (ctrl-9).',13,10
	db ' The data file can be up to about 64 kilobytes in length.',13,10
	db 'Trying to unload INPUTTER.',13,10,'$'
UninstalledText:
	db 'INPUTTER unloaded.',13,10,'$'


DoDataFileLoadError: ; ax = dos error code
	push ax
	 mov [DataFileNameEnds], byte '"'
	 mov dx, DataFileLoadErrorMessage ;Display text
	 call TextOut
	pop ax
	dec ax ;sub ax,2
	dec ax
	cmp ax,5-2
	mov dx, Error_Unprintable
	ja HadDOSerror
	mov bx,ax
	xchg si,ax
	mov dx,[bx+si + DOSerrorTable]
HadDOSerror:
	call TextOut
	mov dx,DataFileLoadErrorMessageContinues
	push GoUninstaller
	jmp TextOut
	;call TextOut
	;jmp GoUninstaller ; Hope it still exists there!

;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;; RELOCATED PART ;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;
RelocatedSource:

RelocatedSourceCodeBegin:
	mov ax, 0x3D00 ; open file in read-only mode
	mov dx, DataFileName
	int 21h
	jc DataFileLoadError_DOS
	xchg bx,ax ; ax = file handle -> bx
	mov ax, 4202h ; seek to file end
	cwd
	xor cx,cx
	;xor dx,dx
	int 21h
	jc DataFileLoadError_DOS
	or dx, dx
	jnz DataFileLoadError_TooLongFile
	cmp ax, MaxInputDataLength
	ja DataFileLoadError_TooLongFile
	mov ax, 4200h ; seek to file beginning
	;xor cx,cx - already set as such
	;xor dx,dx
	int 21h
	jc DataFileLoadError_DOS
	mov dx, KeyData
	;xor ax, ax - already set as such
.DataLoadingLoop:
	 add dx, ax
	 mov ah, 3Fh ; read from file
	 mov cx, MaxInputDataLength
	 int 21h
	 jc DataFileLoadError_DOS
	 or ax, ax
	 jnz .DataLoadingLoop ; Loop until EOF
	mov si,dx
	add si,ax
	mov [EndPointer], si
	mov [CurrentPtr], si
	mov ah, 3Eh ;close file
	int 21h
	
	mov dx,InstalledText + RelocationDifference; Display text
	call TextOut

	; Measure the length of the input
	cli
	 call Activate - RelocationDifference
	 xor ax, ax
	 mov [cs:KbDelayEndStamp+0], ax
	 mov [cs:KbDelayEndStamp+2], ax
.LengthLoop:
	 call I16testEOF - RelocationDifference
	 jae .LengthLoopDone
	 call PeekKey - RelocationDifference     ; output: ax = key, bx = next key ptr
	 call GoNextKey - RelocationDifference
	 call DecideDelay - RelocationDifference ; output: bx = delay
	 call EnactDelay  - RelocationDifference
	 jmp .LengthLoop
.LengthLoopDone:
	sti
	mov ax, -1
	push ax
	 mov eax, [cs:KbDelayEndStamp] ; ebp = number of milliseconds the input lasts (limit: 49 days)
	 mov cx, 3
.DoMoreLengthMeasuring:
	 xor edx, edx
	 mov ebx, 10
	 div ebx
	 add dl, '0'
	 push dx
	  dec cx
	  js .TestDecimalZero
	  jnz .DoMoreLengthMeasuring
	  mov dl, '.'
	  push dx
.TestDecimalZero:
	  test eax, eax
	  jnz .DoMoreLengthMeasuring
	  mov dx,InputLengthTextPart1 + RelocationDifference
	  call TextOut
.LengthReportingLoop:
	 pop dx
	 or dx, dx
	 js .DoneLengthReporting
	 mov ah, 2
	 int 21h
	 jmp .LengthReportingLoop
.DoneLengthReporting	:
	mov dx,InputLengthTextPart2 + RelocationDifference
	call TextOut

	;mov dx, (((TSRend - _main) + 15) >> 4) + 10h
	lea dx, [si + 15]
	shr dx, 4

	mov ax, 3100h ; Calculate TSR size and do TSR.
	int 21h
TextOut:
	mov ah,9
	int 21h
	ret

DataFileLoadError_TooLongFile:
	mov dx, Error_TooLongFile
	jmp HadDOSerror - RelocationDifference ; Hope it still exists there
DataFileLoadError_DOS:
	jmp DoDataFileLoadError - RelocationDifference ; Hope it still exists there

InputLengthTextPart1:
	db 'Estimated longevity $'
InputLengthTextPart2:
	db ' s.',13,10,'$'
InstalledText:
	db 'Long, difficult text block input helper installed',13,10
	db 'Copyright (C) 2011-11-24 Joel Yliluoma, http://iki.fi/bisqwit/',13,10
	db '$'

RelocatedDataEnd equ $

End:
