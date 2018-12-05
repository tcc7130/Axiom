PUSHKI 10
DCLVI mat
PUSHKI 10
DCLVI nom
PUSHKI 10
DCLVI cal
DCLI i
PUSHKI 0
POPI i
FOR0:
PUSH i
PUSHKI 10
CLT
JMPC FOR_END0
PUSHKS "Por favor introduzca la matricula numero: "
WRT
PUSH i
WRT
WRTLN
RDI
PUSH i
POPVI mat
PUSHKS "Por favor introduzca el nombre numero: "
WRT
PUSH i
WRT
WRTLN
RDI
PUSH i
POPVI nom
PUSHKS "Por favor introduzca la calificacion numero "
WRT
PUSH i
WRT
WRTLN
RDI
PUSH i
POPVI cal
PUSHKI 1
PUSH i
ADD
POPI i
JMP FOR0
FOR_END0:
EXT
