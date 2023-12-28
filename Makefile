TARGET = Button_Tester
OBJS = main.o
EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = YABT 

BUILD_PRX = 1

PSP_FW_VERSION = 660

LIBS = -lpspctrl -lpspdebug


all: $(TARGET).prx
	@mkdir -p PSP/GAME/YABT/
	@cp EBOOT.PBP PSP/GAME/YABT/
	zip -r YABT.zip PSP/






PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

clean:
	@rm -rf *.o *.SFO PSP/ *.zip *.elf *.prx *.PBP
	@echo CLEAN
	
