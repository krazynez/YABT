TARGET = Button_Tester
OBJS = main.o
EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = YABT

UNAME := $(shell uname)

all:
ifeq ($(UNAME), Linux)
	WINEPREFIX="$(shell pwd)/prefix/" wine bin/prxEncrypter.exe $(TARGET).prx
else
	$(shell pwd)\bin\prxEncrypter $(TARGET).prx
endif
	pack-pbp $(EXTRA_TARGETS) PARAM.SFO icon0.png NULL NULL pic1.png NULL data.psp NULL



BUILD_PRX = 1

PSP_FW_VERSION = 660

LIBS = -lpspctrl -lpspdebug


release: $(TARGET).prx
	@mkdir -p PSP/GAME/YABT/
	@cp EBOOT.PBP PSP/GAME/YABT/
	zip -r YABT.zip PSP/






PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

clean:
	@rm -rf *.o *.SFO PSP/ *.zip *.elf *.prx *.PBP data.psp
	@echo CLEAN
	
