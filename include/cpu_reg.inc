;Entries commented with an ending '*' have their official register names
;as containing a leading asterisk. Since asterisks are a comment in this assembler,
;the full name cannot be used, but is noted.

.ENUM $4200 ASC
NMITIMEN db ;00
WRIO db ;01
WRMPYA db ;02
WRMPYB db ;03
WRDIVL db ;04
WRDIVH db ;05
WRDIVB db ;06
HTIME .dw ;07-08
HTIMEL db ;07
HTIMEH db ;08
VTIME .dw ;09-0a
VTIMEL db ;09
VTIMEH db ;0A
MDMAEN db ;0B
HDMAEN db ;0C
MEMSEL db ;0D
.ENDE

;0E and 0F not in development manual?
.ENUM $4210 ASC
RDNMI db ;10 *
TIMEUP db ;11 *
HBVJOY db ;12 *
RDIO db ;13 *
RDDIV .dw ;14-15
RDDIVL db ;14
RDDIVH db ;15
RDMPY .dw ;16-17
RDMPYL db ;16
RDMPYH db ;17
JOY1 .dw ;18-19
JOY1L db ;18
JOY1H db ;19
JOY2 .dw ;1A-1B
JOY2L db ;1A
JOY2H db ;1B
JOY3 .dw ;1C-1D
JOY3L db ;1C
JOY3H db ;1D
JOY4 .dw ;1E-1F
JOY4L db ;1E
JOY4H db ;1F
.ENDE

;DMA Registers- No official names exist
.STRUCT DMA
PARAM db ;00
ADDRB db ;01
ADDRA1 .dw ;02-04
ADDRA1L db ;02
ADDRA1H db ;03
ADDRA1K db ;04- banK address- Named as such to prevent confustion with ADDRB.

NUMBYTES .dw ;05-06
H_INDADDR .dw ;05-07
NUMBYTESL .db ;05
H_INDADDRL db ;05
NUMBYTESH .db ;06
H_INDADDRH db ;06
H_INDADDRK db ;07

ADDRA2 .dw ;08-09
ADDRA2L db ;08
ADDRA2H db ;09
H_NUMLINES db ;0A
.ENDST

;DMA0
;I've had problems with these personally... I do not suggest using these!
.ENUM $4300 ASC
DMA0 INSTANCEOF DMA
DMA1 INSTANCEOF DMA
DMA2 INSTANCEOF DMA
DMA3 INSTANCEOF DMA
DMA4 INSTANCEOF DMA
DMA5 INSTANCEOF DMA
DMA6 INSTANCEOF DMA
DMA7 INSTANCEOF DMA
.ENDE
