/****************************************************************************
 * FCE Ultra 0.98.12
 * Nintendo Wii/Gamecube Port
 *
 * Tantric September 2008
 *
 * fceugc.c
 *
 * This file controls overall program flow. Most things start and end here!
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <gctypes.h>
#include <ogc/system.h>
#include <fat.h>
#include <wiiuse/wpad.h>

#include "types.h"

#include "gcvideo.h"
#include "pad.h"
#include "fceuload.h"
#include "common.h"
#include "menudraw.h"
#include "menu.h"
#include "fceuconfig.h"
#include "preferences.h"

#ifdef WII_DVD
#include <di/di.h>
#endif

extern bool romLoaded;
bool isWii;

/* Some timing-related variables. */
static int fullscreen=0;
static int genie=0;
static int palyo=0;

static volatile int nofocus=0;
static volatile int userpause=0;

#define SO_FORCE8BIT  1
#define SO_SECONDARY  2
#define SO_GFOCUS     4
#define SO_D16VOL     8

#define GOO_DISABLESS   1       /* Disable screen saver when game is loaded. */
#define GOO_CONFIRMEXIT 2       /* Confirmation before exiting. */
#define GOO_POWERRESET  4       /* Confirm on power/reset. */

static int soundvolume=100;
static int soundquality=0;
static int soundo;

uint8 *xbsave=NULL;
int eoptions=EO_BGRUN | EO_FORCEISCALE;

extern int cleanSFMDATA();
extern void ResetNES(void);
extern void InitialiseSound();
extern void PlaySound( void *Buf, int samples );
long long basetime;

void FCEUD_Update(uint8 *XBuf, int32 *Buffer, int Count);

int main(int argc, char *argv[])
{

#ifdef WII_DVD
	DI_Init();	// first
#endif

	int selectedMenu = -1;

#ifdef HW_RVL
	WPAD_Init();
	// read wiimote accelerometer and IR data
	WPAD_SetDataFormat(WPAD_CHAN_ALL,WPAD_FMT_BTNS_ACC_IR);
	WPAD_SetVRes(WPAD_CHAN_ALL,640,480);
#endif

    initDisplay();

    /*** Initialise freetype ***/
	if (FT_Init ())
	{
		printf ("Cannot initialise font subsystem!\n");
		while (1);
	}

    InitialiseSound();
    fatInitDefault();
#ifndef HW_RVL
    DVD_Init();
#endif

    /*** Minimal Emulation Loop ***/
    if ( !FCEUI_Initialize() ) {
        printf("Unable to initialize system\n");
        return 1;
    }

    palyo=0;
    FCEUI_SetVidSystem(palyo);
    genie&=1;
    FCEUI_SetGameGenie(genie);
    fullscreen&=1;
    soundo&=1;
    FCEUI_SetSoundVolume(soundvolume);
    FCEUI_SetSoundQuality(soundquality);

    cleanSFMDATA();
    GCMemROM();
    romLoaded = false; // we start off with only the color test rom

    // Set Defaults
	DefaultSettings();

	// Load preferences
	if(!LoadPrefs(GCSettings.SaveMethod, SILENT))
	{
		WaitPrompt((char*) "Preferences reset - check settings!");
		selectedMenu = 3; // change to preferences menu
	}

	// Go to main menu
    MainMenu (selectedMenu);

    while (1)
    {
        uint8 *gfx;
        int32 *sound;
        int32 ssize;

        FCEUI_Emulate(&gfx, &sound, &ssize, 0);
        xbsave = gfx;
        FCEUD_Update(gfx, sound, ssize);
    }

    return 0;
}

/****************************************************************************
 * FCEU Support Functions to be written
 ****************************************************************************/
/*** File Control ***/


FILE *FCEUD_UTF8fopen(const char *n, const char *m)
{
    return(fopen(n,m));
}

/*** General Logging ***/
void FCEUD_PrintError(char *s)
{
}

void FCEUD_Message(char *text)
{
}

/*** VIDEO ***/
void FCEUD_Update(uint8 *XBuf, int32 *Buffer, int Count)
{
    PlaySound(Buffer, Count);
    RenderFrame( (char *)XBuf, GCSettings.screenscaler );
    GetJoy();
}

/*** Netplay ***/
int FCEUD_SendData(void *data, uint32 len)
{
    return 1;
}

int FCEUD_RecvData(void *data, uint32 len)
{
    return 0;
}

void FCEUD_NetworkClose(void)
{
}

void FCEUD_NetplayText(uint8 *text)
{
}

