
;.EXPORT needed? This assembler waits until link time to check whether labels are
;valid, it appears. I.e. the assembler has no concept of "extern" for address labels.

;Only definitions may need to be exported, since they are local to a file
;unless the .EXPORT directive is used.

;Entries commented with an ending '*' have their official register names
;as containing a leading asterisk. Since asterisks are a comment in this assembler,
;the full name cannot be used, but is noted.
.ENUM $2100 ASC
INIDSP db ;00
OBJSEL db ;01
OAMADD .dw ;02-03
OAMADDL db ;02
OAMADDH db ;03
OAM_DATA db ;04
BGMODE db ;05
MOSAIC db ;06
BG1SC db ;07
BG2SC db ;08
BG3SC db ;09
BG4SC db ;0A
BG12NBA db ;0B
BG34NBA db ;0C
BG1HOFS db ;0D- All HOFS/VOFS can be written twice to set low/high (10/13 bits)
BG1VOFS db ;0E
BG2HOFS db ;0F
BG2VOFS db ;10
BG3HOFS db ;11
BG3VOFS db ;12
BG4HOFS db ;13
BG4VOFS db ;14
VMAINC db ;15
VMADD .dw ;16-17
VMADDL db ;16
VMADDH db ;17

;Not official name, but due to leading asterisks, these register names alias their
;read counterparts.
VMDATA_W .dw ;18-19
VMDATAL_W db ;18
VMDATAH_W db ;19

M7SEL db ;1A
M7A db ;1B
M7B db ;1C
M7C db ;1D
M7D db ;1E
M7X db ;1F
M7Y db ;20
CGADD db ;21

;Not official name, but due to leading asterisks, this register name aliases its
;read counterpart.
CGDATA_W db ;22- Write-twice (15-bits)

W12SEL db ;23
W34SEL db ;24
WOBJSEL db ;25
WH0 db ;26
WH1 db ;27
WH2 db ;28
WH3 db ;29
WBGLOG db ;2A
WOBJLOG db ;2B
TM db ;2C
TS db ;2D
TMW db ;2E
TSW db ;2F
CGSWSEL db ;30
CGADSUB db ;31
COLDATA db ;32
SETINI db ;33
MPYL db ;34 *
MPYM db ;35 *
MPYH db ;36 *
SLVH db ;37 *
OAMDATA db ;38 *

;Not official name, but due to leading asterisks, these register names alias their
;write counterparts. '_R' is appended to official name (minus asterisk) to distinguish.
VMDATA_R .dw ;39-3a *
VMDATAL_R db ;39 *
VMDATAH_R db ;3A *

;Not official name, but due to leading asterisks, this register name aliases its
;write counterpart. '_R' is appended to official name (minus asterisk) to distinguish.
CGDATA_R db ;3B *- Write-twice (15-bits)

OPHCT db ;3C *
OPVCT db ;3D *
STAT77 db ;3E *
STAT78 db ;3F *
APU100 db ;40
APU101 db ;41
APU102 db ;42
APU103 db ;43

.ENDE
