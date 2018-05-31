# MPLAB IDE generated this makefile for use with GNU make.
# Project: MD.mcp
# Date: Wed Feb 29 13:08:09 2012

AS = pic30-as.exe
CC = pic30-gcc.exe
LD = pic30-ld.exe
AR = pic30-ar.exe
HX = pic30-bin2hex.exe
RM = rm

./Release/MD.hex : ./Release/MD.cof
	$(HX) ".\Release\MD.cof"

./Release/MD.cof : Obj/main.o Obj/pwm.o Obj/tmr.o Obj/md_coding.o Obj/ecan.o Obj/spi.o Obj/adc506a.o Obj/mem.o
	$(CC) -mcpu=24HJ128GP506A "Obj\main.o" "Obj\pwm.o" "Obj\tmr.o" "Obj\md_coding.o" "Obj\ecan.o" "Obj\spi.o" "Obj\adc506a.o" "Obj\mem.o" -o".\Release\MD.cof" -Wl,-L"C:\Program Files (x86)\Microchip\mplabc30\v3.25\support\PIC24H\gld",-L"C:\Program Files (x86)\Microchip\mplabc30\v3.25\lib",-Tp24HJ128GP506A.gld,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,--defsym=__ICD2RAM=1,-Map=".\Release\MD.map",--report-mem

Obj/main.o : ../../Program\ Files\ (x86)/Microchip/mplabc30/v3.25/support/PIC24H/h/p24HJ128GP506A.h Header/md_coding.h ../../Program\ Files\ (x86)/Microchip/mplabc30/v3.25/support/PIC24H/h/p24HJ128GP506A.h Header/adc506a.h Header/pwm.h ../../Program\ Files\ (x86)/Microchip/mplabc30/v3.25/support/PIC24H/h/p24HJ128GP506A.h Header/mem.h ../../Program\ Files\ (x86)/Microchip/mplabc30/v3.25/support/PIC24H/h/p24HJ128GP506A.h Header/spi.h ../../Program\ Files\ (x86)/Microchip/mplabc30/v3.25/support/PIC24H/h/p24HJ128GP506A.h Header/tmr.h Header/ecan.h ../../Program\ Files\ (x86)/Microchip/mplabc30/v3.25/support/PIC24H/h/p24HJ128GP506A.h Header/pwm.h ../../Program\ Files\ (x86)/Microchip/mplabc30/v3.25/support/PIC24H/h/p24HJ128GP506A.h Header/main.h ../../Program\ Files\ (x86)/Microchip/mplabc30/v3.25/support/PIC24H/h/p24HJ128GP506A.h Source/main.c
	$(CC) -mcpu=24HJ128GP506A -x c -c "Source\main.c" -o".\Obj\main.o" -I".\Header" -I".\Source" -I"C:\Program Files (x86)\Microchip\mplabc30\v3.25\include" -I"C:\Program Files (x86)\Microchip\mplabc30\v3.25\support\peripheral_30F_24H_33F" -I"C:\Program Files (x86)\Microchip\mplabc30\v3.25\support\PIC24H\h" -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -g -Wall

Obj/pwm.o : ../../Program\ Files\ (x86)/Microchip/mplabc30/v3.25/support/PIC24H/h/p24HJ128GP506A.h Header/pwm.h ../../Program\ Files\ (x86)/Microchip/mplabc30/v3.25/support/PIC24H/h/p24HJ128GP506A.h Source/pwm.c
	$(CC) -mcpu=24HJ128GP506A -x c -c "Source\pwm.c" -o".\Obj\pwm.o" -I".\Header" -I".\Source" -I"C:\Program Files (x86)\Microchip\mplabc30\v3.25\include" -I"C:\Program Files (x86)\Microchip\mplabc30\v3.25\support\peripheral_30F_24H_33F" -I"C:\Program Files (x86)\Microchip\mplabc30\v3.25\support\PIC24H\h" -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -g -Wall

Obj/tmr.o : ../../Program\ Files\ (x86)/Microchip/mplabc30/v3.25/support/PIC24H/h/p24HJ128GP506A.h Header/tmr.h ../../Program\ Files\ (x86)/Microchip/mplabc30/v3.25/support/PIC24H/h/p24HJ128GP506A.h Source/tmr.c
	$(CC) -mcpu=24HJ128GP506A -x c -c "Source\tmr.c" -o".\Obj\tmr.o" -I".\Header" -I".\Source" -I"C:\Program Files (x86)\Microchip\mplabc30\v3.25\include" -I"C:\Program Files (x86)\Microchip\mplabc30\v3.25\support\peripheral_30F_24H_33F" -I"C:\Program Files (x86)\Microchip\mplabc30\v3.25\support\PIC24H\h" -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -g -Wall

Obj/md_coding.o : ../../Program\ Files\ (x86)/Microchip/mplabc30/v3.25/support/PIC24H/h/p24HJ128GP506A.h Header/md_coding.h ../../Program\ Files\ (x86)/Microchip/mplabc30/v3.25/support/PIC24H/h/p24HJ128GP506A.h Source/md_coding.c
	$(CC) -mcpu=24HJ128GP506A -x c -c "Source\md_coding.c" -o".\Obj\md_coding.o" -I".\Header" -I".\Source" -I"C:\Program Files (x86)\Microchip\mplabc30\v3.25\include" -I"C:\Program Files (x86)\Microchip\mplabc30\v3.25\support\peripheral_30F_24H_33F" -I"C:\Program Files (x86)\Microchip\mplabc30\v3.25\support\PIC24H\h" -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -g -Wall

Obj/ecan.o : Header/ecan.h ../../Program\ Files\ (x86)/Microchip/mplabc30/v3.25/support/PIC24H/h/p24HJ128GP506A.h ../../Program\ Files\ (x86)/Microchip/mplabc30/v3.25/support/PIC24H/h/p24hxxxx.h Source/ecan.c
	$(CC) -mcpu=24HJ128GP506A -x c -c "Source\ecan.c" -o".\Obj\ecan.o" -I".\Header" -I".\Source" -I"C:\Program Files (x86)\Microchip\mplabc30\v3.25\include" -I"C:\Program Files (x86)\Microchip\mplabc30\v3.25\support\peripheral_30F_24H_33F" -I"C:\Program Files (x86)\Microchip\mplabc30\v3.25\support\PIC24H\h" -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -g -Wall

Obj/spi.o : ../../Program\ Files\ (x86)/Microchip/mplabc30/v3.25/support/PIC24H/h/p24HJ128GP506A.h Source/spi.c
	$(CC) -mcpu=24HJ128GP506A -x c -c "Source\spi.c" -o".\Obj\spi.o" -I".\Header" -I".\Source" -I"C:\Program Files (x86)\Microchip\mplabc30\v3.25\include" -I"C:\Program Files (x86)\Microchip\mplabc30\v3.25\support\peripheral_30F_24H_33F" -I"C:\Program Files (x86)\Microchip\mplabc30\v3.25\support\PIC24H\h" -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -g -Wall

Obj/adc506a.o : ../../Program\ Files\ (x86)/Microchip/mplabc30/v3.25/support/PIC24H/h/p24HJ128GP506A.h Header/adc506a.h ../../Program\ Files\ (x86)/Microchip/mplabc30/v3.25/support/PIC24H/h/p24HJ128GP506A.h Source/adc506a.c
	$(CC) -mcpu=24HJ128GP506A -x c -c "Source\adc506a.c" -o".\Obj\adc506a.o" -I".\Header" -I".\Source" -I"C:\Program Files (x86)\Microchip\mplabc30\v3.25\include" -I"C:\Program Files (x86)\Microchip\mplabc30\v3.25\support\peripheral_30F_24H_33F" -I"C:\Program Files (x86)\Microchip\mplabc30\v3.25\support\PIC24H\h" -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -g -Wall

Obj/mem.o : ../../Program\ Files\ (x86)/Microchip/mplabc30/v3.25/support/PIC24H/h/p24HJ128GP506A.h Header/mem.h Source/mem.c
	$(CC) -mcpu=24HJ128GP506A -x c -c "Source\mem.c" -o".\Obj\mem.o" -I".\Header" -I".\Source" -I"C:\Program Files (x86)\Microchip\mplabc30\v3.25\include" -I"C:\Program Files (x86)\Microchip\mplabc30\v3.25\support\peripheral_30F_24H_33F" -I"C:\Program Files (x86)\Microchip\mplabc30\v3.25\support\PIC24H\h" -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -g -Wall

clean : 
	$(RM) "Obj\main.o" "Obj\pwm.o" "Obj\tmr.o" "Obj\md_coding.o" "Obj\ecan.o" "Obj\spi.o" "Obj\adc506a.o" "Obj\mem.o" ".\Release\MD.cof" ".\Release\MD.hex"

