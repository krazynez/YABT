TARGET = Button_Tester
OBJS = main.o
EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = YABT 

BUILD_PRX = 1

PSP_FW_VERSION = 660

LIBS = -lpspctrl -lpspdebug

all: $(TARGET).prx


PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
