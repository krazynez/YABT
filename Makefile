TARGET = Button_Tester
OBJS = main.o
EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = YABT

UNAME := $(shell uname)

all:
	unpack-pbp $(EXTRA_TARGETS)
	pack-pbp $(EXTRA_TARGETS) PARAM.SFO icon0.png NULL NULL pic1.png res/SND0.AT3 DATA.PSP NULL
	./bin/psptools/pack_ms_game.py --vanity YABT EBOOT.PBP EBOOT.PBP



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
	
