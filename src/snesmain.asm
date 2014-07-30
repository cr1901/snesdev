.incdir ".\include"

.include "header.inc"
.include "ppu_reg.inc"


EmptyHandler:
VBlank:
	rti
	
Start:
	sei         ; Disabled interrupts
	clc         ; clear carry to switch to native mode
	xce         ; Xchange carry & emulation bit. native mode
	rep #$18    ; Binary mode (decimal mode off), X/Y 16 bit
	ldx #$1FFF  ; set stack to $1FFF
	txs
	jsr Init    ;Init registers

	lda #%10000000  ; Force VBlank by turning off the screen.
	sta INIDSP
	lda #%11100000  ; Load the low byte of the color.
	sta CGDATA_W
	lda #%00000000 ; Load the high byte of the color.
	sta CGDATA_W
	lda #%00001111  ; End VBlank, setting brightness to 15 (100%).
	sta INIDSP
	
Loop:
	jmp Loop
