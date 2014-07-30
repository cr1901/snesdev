;Macros
;BACKDROP- Set the 0th palette for SNES... used for any pixels not covered by a tile.
;Inputs: \1- Low Color Byte, \2- High Color Byte, \3 (Optional)- Brightness
.MACRO BACKDROP
     lda #%10000000  ; Force VBlank by turning off the screen.
     sta     INIDSP
     lda     #\1  ; Load the low byte of the color.
     sta     CGDATA_W
     lda     #\2  ; Load the high byte of the color.
     sta     CGDATA_W
     .IFNDEFM \3
          lda     #%00001111  ; End VBlank, setting brightness to 15 (100%).
     .ELSE
          lda #\3
     .ENDIF
     sta INIDSP
.ENDM


;SETREGSIZE- Take the guesswork out of setting the register sizes!
;Inputs: desired Size of A, desired Size of X/Y.
;Inputs can take on either 8,16,or 0. '0' means leave size alone
;(value of 0 requirement not enforced in macro)!
.MACRO SETREGSIZE
	.IF NARGS != 2
		.FAIL
	.ELSE
		;A
		.IFEQ \1 8
			sep #$20
			;.PRINTT "sep $20"
		.ELSE
			.IFEQ \1 16
				rep #$20
				;.PRINTT "rep $20"
			.ENDIF
		.ENDIF
		
		;.PRINTT "\n"
		
		;X/Y
		.IFEQ \2 8
			sep #$10
			;.PRINTT "sep $10"
		.ELSE
			.IFEQ \2 16
				rep #$10
				;.PRINTT "rep $10"
			.ENDIF
		.ENDIF
		;.PRINTT "\n"
	.ENDIF
.ENDM

.MACRO PRINTCR
	.printv HEX \1
	.PRINTT "\n"
.ENDM


;TILEDMAXFER- Set up DMA registers for General Purpose DMA transfer to VRAM (does not initiate transfer).
;Inputs:
;\1- DMA Channel Number
;\2- Tile Address
;\3- Number of 16-bit WORDS to transfer!
;\4 (Optional)- DMA parameter register contents (defaults to #%00000001)
;\5 (Not Implemented)- Choose to start on VMDATAL_W or VMDATAH_W
;Requires- VMAINC/VMADDR be set to the correct value.
.MACRO TILEDMAXFER
     .IFNDEFM \4
          lda #%00000001 ;CPU => PPU, Auto-increment of A-bus, word-based transfer to B-bus.
     .ELSE
          lda #\4
     .ENDIF
     sta $4300 + ($10 * \1)
     lda #(VMDATAL_W - $2100)
     sta $4301 + ($10 * \1)
     ldx #\2
     stx $4302 + ($10 * \1) ;Load the address of the colors
     lda #:\2 ;Loads the Bank Number
     sta $4304 + ($10 * \1)
     ldx.w #(\3 * 2)      ;DMA transfers BYTES!... VRAM is 16-bit words.
     stx $4305 + ($10 * \1)
.ENDM

;PALDMAXFER- Set up DMA registers for General Purpose DMA transfer to CGRAM (does not initiate transfer).
;Inputs:
;\1- DMA Channel Number
;\2- Palette Address
;\3- Number of 16-bit WORDS to transfer!
;\4 (Optional)- DMA parameter register contents (defaults to #%00000000)
;Requires- CGADD be set to the correct value.
.MACRO PALDMAXFER
     .IFNDEFM \4
          lda #%00000000 ;CPU => PPU, Auto-increment of A-bus, byte-based transfer to B-bus.
     .ELSE
          lda #\4
     .ENDIF
     sta $4300 + ($10 * \1)
     lda #(CGDATA_W - $2100)
     sta $4301 + ($10 * \1)
     SETREGSIZE 0 16
     ldx #\2
     stx $4302 + ($10 * \1);Load the address of the colors
     lda #:\2 ;Loads the Bank Number
     sta $4304 + ($10 * \1)
     ldx.w #(\3 * 2) 
     stx $4305 + ($10 * \1)
.ENDM

.MACRO SET_CURSOR
	ldx #((\1 * 32) + (\2))
	stx VMADDL
.ENDM

/* .MACRO SET_CURSOR_REL
	SETREGSIZE 16 0
	lda #\1
	clc
	adc VMADDL
	sta VMADDL
	SETREGSIZE 8 0
.ENDM */
