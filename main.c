#include <stdio.h>
#include <stdbool.h>
#include <pspsdk.h>
#include <psptypes.h>
#include <pspkernel.h>
#include <pspctrl.h>
#include <pspdebug.h>
#include <pspdisplay.h>

PSP_MODULE_INFO("Button Tester", 0, 1, 0);
//PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER);

int isRunning();
int setupExitCallback();

static int exitRequest = 0;

int isRunning()
{
	return !exitRequest;
}

int exitCallback(int arg1, int arg2, void *common) {
	exitRequest = 1;
	return 0;
}

int callbackThread(SceSize args, void *argp) {
	int callbackID;

	callbackID = sceKernelCreateCallback("Exit Callback", exitCallback, NULL);
	sceKernelRegisterExitCallback(callbackID);

	sceKernelSleepThreadCB();

	return 0;
}

int setupExitCallback() {
	int threadID = 0;

	threadID = sceKernelCreateThread("Callback_Thread", callbackThread, 0x11, 0xFA0, THREAD_ATTR_USER, 0);

	if(threadID >= 0)
	{
		sceKernelStartThread(threadID, 0, 0);
	}

	return threadID;
}

int main(int argc, char *args[]) {
	int i = 5;
	bool reverse = false;
	pspDebugScreenInit();
	
	setupExitCallback();

	SceCtrlLatch pad;

	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

	

	while(isRunning()) {
		SceCtrlData analog;
		
		pspDebugScreenSetTextColor(0x0094CC);
		pspDebugScreenSetXY(0, 0);
		pspDebugScreenPrintf("Press a button to test.\n");
		pspDebugScreenSetXY(50, 0);
		pspDebugScreenPrintf("Axis X: %d", analog.Lx);
		pspDebugScreenSetXY(50, 1);
		pspDebugScreenPrintf("Axis Y: %d", analog.Ly);
		pspDebugScreenSetXY(0, 0);
		sceCtrlPeekBufferPositive(&analog, 1);
		sceCtrlReadLatch(&pad);
		if(pad.uiMake & PSP_CTRL_CROSS) {
			pspDebugScreenSetXY(0, 5);
			pspDebugScreenPrintf("Cross pressed.\n");
		}
		if(pad.uiMake & PSP_CTRL_CIRCLE) {
			pspDebugScreenSetXY(0, 5);
			pspDebugScreenPrintf("Circle pressed.\n");
		}
		if(pad.uiMake & PSP_CTRL_TRIANGLE) {
			pspDebugScreenSetXY(0, 5);
			pspDebugScreenPrintf("Triangle pressed.\n");
		}
		if(pad.uiMake & PSP_CTRL_SQUARE) {
			pspDebugScreenSetXY(0, 5);
			pspDebugScreenPrintf("Square pressed.\n");
		}
		if(pad.uiMake & PSP_CTRL_VOLUP) {
			pspDebugScreenSetXY(0, 5);
			pspDebugScreenPrintf("Volume Up pressed.\n");
		}
		if(pad.uiMake & PSP_CTRL_VOLDOWN) {
			pspDebugScreenSetXY(0, 5);
			pspDebugScreenPrintf("Volume Down pressed.\n");
		}
		if(pad.uiMake & PSP_CTRL_SCREEN) {
			pspDebugScreenSetXY(0, 5);
			pspDebugScreenPrintf("Screen button pressed.\n");
		}
		if(pad.uiMake & PSP_CTRL_LTRIGGER) {
			pspDebugScreenSetXY(0, 5);
			pspDebugScreenPrintf("L Trigger pressed.\n");
		}
		if(pad.uiMake & PSP_CTRL_RTRIGGER) {
			pspDebugScreenSetXY(0, 5);
			pspDebugScreenPrintf("R Trigger pressed.\n");
		}
		if(pad.uiMake & PSP_CTRL_UP) {
			pspDebugScreenSetXY(0, 5);
			pspDebugScreenPrintf("D-Pad Up pressed.\n");
		}
		if(pad.uiMake & PSP_CTRL_LEFT) {
			pspDebugScreenSetXY(0, 5);
			pspDebugScreenPrintf("D-Pad Left pressed.\n");
		}
		if(pad.uiMake & PSP_CTRL_DOWN) {
			pspDebugScreenSetXY(0, 5);
			pspDebugScreenPrintf("D-Pad Down pressed.\n");
		}
		if(pad.uiMake & PSP_CTRL_RIGHT) {
			pspDebugScreenSetXY(0, 5);
			pspDebugScreenPrintf("D-Pad Right pressed.\n");
		}
		if(pad.uiMake & PSP_CTRL_SELECT) {
			pspDebugScreenSetXY(0, 5);
			pspDebugScreenPrintf("Select pressed.\n");
		}
		if(pad.uiMake & PSP_CTRL_START) {
			pspDebugScreenSetXY(0, 5);
			pspDebugScreenPrintf("Start pressed.\n");
		}
		if(pad.uiMake & PSP_CTRL_NOTE) {
			pspDebugScreenSetXY(0, 5);
			pspDebugScreenPrintf("Note pressed.\n");
		}
		if(pad.uiMake & PSP_CTRL_HOLD) {
			pspDebugScreenSetXY(0, 5);
			pspDebugScreenPrintf("Hold enabled.\n");
		}

		if (pad.uiBreak & (PSP_CTRL_CROSS | PSP_CTRL_CIRCLE | PSP_CTRL_TRIANGLE | PSP_CTRL_SQUARE | PSP_CTRL_SELECT | PSP_CTRL_START | PSP_CTRL_UP | PSP_CTRL_RIGHT | PSP_CTRL_DOWN | PSP_CTRL_LEFT | PSP_CTRL_LTRIGGER | PSP_CTRL_RTRIGGER | PSP_CTRL_VOLUP | PSP_CTRL_VOLDOWN | PSP_CTRL_NOTE | PSP_CTRL_HOLD)) {
			pspDebugScreenSetXY(0, 5);
			pspDebugScreenPrintf("                    ");
		}

		if(i < 5) {
			i = 4;
			reverse = false;	
		}
		if(i > 45) {
			reverse = true;
		}
		if(reverse)
			i--;
		else
			i++;

		sceKernelDelayThread(200000);
		pspDebugScreenSetXY(i-1, 30);
		pspDebugScreenPrintf("                     ");

		pspDebugScreenSetXY(i, 30);

		pspDebugScreenPrintf("Created by Krazynez");

		
	
		sceDisplayWaitVblankStart();

	}

	sceKernelExitGame();
	return 0;
}

