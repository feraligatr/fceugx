#include "types.h"
#include "fceu.h"
#include "drawing.h"
#include "video.h"
#include "movie.h"
#include "driver.h"

static uint8 Font6x7[792] =
{
	6,  0,  0,  0,  0,  0,  0,  0,
	3, 64, 64, 64, 64, 64,  0, 64,
	5, 80, 80, 80,  0,  0,  0,  0,
	6, 80, 80,248, 80,248, 80, 80,
	6, 32,120,160,112, 40,240, 32,
	6, 64,168, 80, 32, 80,168, 16,
	6, 96,144,160, 64,168,144,104,
	3, 64, 64,  0,  0,  0,  0,  0,
	4, 32, 64, 64, 64, 64, 64, 32,
	4, 64, 32, 32, 32, 32, 32, 64,
	6,  0, 80, 32,248, 32, 80,  0,
	6,  0, 32, 32,248, 32, 32,  0,
	3,  0,  0,  0,  0,  0, 64,128,
	5,  0,  0,  0,240,  0,  0,  0,
	3,  0,  0,  0,  0,  0,  0, 64,
	5, 16, 16, 32, 32, 32, 64, 64,
	6,112,136,136,136,136,136,112, //0
	6, 32, 96, 32, 32, 32, 32, 32,
	6,112,136,  8, 48, 64,128,248,
	6,112,136,  8, 48,  8,136,112,
	6, 16, 48, 80,144,248, 16, 16,
	6,248,128,128,240,  8,  8,240,
	6, 48, 64,128,240,136,136,112,
	6,248,  8, 16, 16, 32, 32, 32,
	6,112,136,136,112,136,136,112,
	6,112,136,136,120,  8, 16, 96,
	3,  0,  0, 64,  0,  0, 64,  0,
	3,  0,  0, 64,  0,  0, 64,128,
	4,  0, 32, 64,128, 64, 32,  0,
	5,  0,  0,240,  0,240,  0,  0,
	4,  0,128, 64, 32, 64,128,  0,
	5,112,136,  8, 16, 32,  0, 32,
	6,112,136,136,184,176,128,112,
	6,112,136,136,248,136,136,136, //A
	6,240,136,136,240,136,136,240,
	6,112,136,128,128,128,136,112,
	6,224,144,136,136,136,144,224,
	6,248,128,128,240,128,128,248,
	6,248,128,128,240,128,128,128,
	6,112,136,128,184,136,136,120,
	6,136,136,136,248,136,136,136,
	4,224, 64, 64, 64, 64, 64,224,
	6,  8,  8,  8,  8,  8,136,112,
	6,136,144,160,192,160,144,136,
	6,128,128,128,128,128,128,248,
	6,136,216,168,168,136,136,136,
	6,136,136,200,168,152,136,136,
	7, 48, 72,132,132,132, 72, 48,
	6,240,136,136,240,128,128,128,
	6,112,136,136,136,168,144,104,
	6,240,136,136,240,144,136,136,
	6,112,136,128,112,  8,136,112,
	6,248, 32, 32, 32, 32, 32, 32,
	6,136,136,136,136,136,136,112,
	6,136,136,136, 80, 80, 32, 32,
	6,136,136,136,136,168,168, 80,
	6,136,136, 80, 32, 80,136,136,
	6,136,136, 80, 32, 32, 32, 32,
	6,248,  8, 16, 32, 64,128,248,
	3,192,128,128,128,128,128,192,
	5, 64, 64, 32, 32, 32, 16, 16,
	3,192, 64, 64, 64, 64, 64,192,
	4, 64,160,  0,  0,  0,  0,  0,
	6,  0,  0,  0,  0,  0,  0,248,
	3,128, 64,  0,  0,  0,  0,  0,
	5,  0,  0, 96, 16,112,144,112, //a
	5,128,128,224,144,144,144,224,
	5,  0,  0,112,128,128,128,112,
	5, 16, 16,112,144,144,144,112,
	5,  0,  0, 96,144,240,128,112,
	5, 48, 64,224, 64, 64, 64, 64,
	5,  0,112,144,144,112, 16,224,
	5,128,128,224,144,144,144,144,
	2,128,  0,128,128,128,128,128,
	4, 32,  0, 32, 32, 32, 32,192,
	5,128,128,144,160,192,160,144,
	2,128,128,128,128,128,128,128,
	6,  0,  0,208,168,168,168,168,
	5,  0,  0,224,144,144,144,144,
	5,  0,  0, 96,144,144,144, 96,
	5,  0,  0,224,144,144,224,128,
	5,  0,  0,112,144,144,112, 16,
	5,  0,  0,176,192,128,128,128,
	5,  0,  0,112,128, 96, 16,224,
	4, 64, 64,224, 64, 64, 64, 32,
	5,  0,  0,144,144,144,144,112,
	5,  0,  0,144,144,144,160,192,
	6,  0,  0,136,136,168,168, 80,
	5,  0,  0,144,144, 96,144,144,
	5,  0,144,144,144,112, 16, 96,
	5,  0,  0,240, 32, 64,128,240,
	4, 32, 64, 64,128, 64, 64, 32,
	3, 64, 64, 64, 64, 64, 64, 64,
	4,128, 64, 64, 32, 64, 64,128,
	6,  0,104,176,  0,  0,  0,  0
};

void DrawTextLineBG(uint8 *dest)
{
	int x,y;
	static int otable[7]={81,49,30,17,8,3,0};
	//100,40,15,10,7,5,2};
	for(y=0;y<14;y++)
	{
		int offs;

		if(y>=7) offs=otable[13-y];
		else offs=otable[y];

		for(x=offs;x<(256-offs);x++)
		{
			// Choose the dimmest set of colours and then dim that
			dest[y*256+x]=(dest[y*256+x]&0x0F)|0xC0;
		}
	}
}


void DrawMessage(bool beforeMovie)
{
	if(guiMessage.howlong)
	{
		//don't display movie messages if we're not before the movie
		if(beforeMovie && !guiMessage.isMovieMessage)
			return;

		uint8 *t;
		guiMessage.howlong--;

		if (guiMessage.linesFromBottom > 0)
			t=XBuf+FCEU_TextScanlineOffsetFromBottom(guiMessage.linesFromBottom)+1;
		else
			t=XBuf+FCEU_TextScanlineOffsetFromBottom(20)+1;

		/*
		FCEU palette:
		$00: [8] unvpalette found in palettes/palettes.h
		black, white, black, greyish, redish, bright green, bluish
		$80:
		nes palette
		$C0:
		dim version of nes palette

		*/

		if(t>=XBuf)
		{
			int color = 0x20;
			if(guiMessage.howlong <= 40) color = 0x3C;
			if(guiMessage.howlong <= 32) color = 0x31;
			if(guiMessage.howlong <= 24) color = 0x21;
			if(guiMessage.howlong <= 16) color = 0x51;
			if(guiMessage.howlong <=  8) color = 0x41;
			DrawTextTrans(ClipSidesOffset+t, 256, (uint8 *)guiMessage.errmsg, color+0x80);
		}
	}

	if(subtitleMessage.howlong)
	{
		//don't display movie messages if we're not before the movie
		if(beforeMovie && !subtitleMessage.isMovieMessage)
			return;

		uint8 *tt;
		subtitleMessage.howlong--;
		tt=XBuf+FCEU_TextScanlineOffsetFromBottom(216);

		if(tt>=XBuf)
		{
			int color = 0x20;
			if(subtitleMessage.howlong == 39) color = 0x38;
			if(subtitleMessage.howlong <= 30) color = 0x2C;
			if(subtitleMessage.howlong <= 20) color = 0x1C;
			if(subtitleMessage.howlong <= 10) color = 0x11;
			if(subtitleMessage.howlong <= 5) color = 0x1;
			DrawTextTrans(ClipSidesOffset+tt, 256, (uint8 *)subtitleMessage.errmsg, color+0x80);
		}
	}
}




static uint8 sstat[2541] =
{
	0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
	0x80,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,
	0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x83,0x83,0x83,0x83,
	0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x81,0x80,0x83,
	0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,
	0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x81,0x81,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x80,0x80,0x80,
	0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x81,0x81,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x83,0x80,0x80,0x81,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x83,0x83,0x81,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x83,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x83,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x83,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x83,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x81,0x81,0x81,0x81,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x80,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
	0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x81,0x81,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x83,0x80,0x80,0x81,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x83,0x83,0x81,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x81,0x83,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x81,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x83,0x83,0x83,0x81,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x81,0x81,0x83,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
	0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x81,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x83,0x81,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x83,0x80,0x81,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x81,0x81,0x81,0x81,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x81,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
	0x80,0x80,0x80,0x80,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x81,0x81,0x81,0x81,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x80,0x80,0x80,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x81,0x81,0x81,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x80,0x81,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x83,0x83,0x83,0x81,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x81,0x81,0x83,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
	0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x81,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x83,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x81,0x81,0x81,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x80,0x80,0x80,0x81,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x80,0x83,0x83,0x81,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x80,0x83,0x83,0x81,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x81,0x81,0x83,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x83,0x83,
	0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x81,0x81,0x81,0x81,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x80,0x81,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x83,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x83,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x83,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,
	0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x81,0x81,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x83,0x80,0x80,0x81,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x80,0x83,0x83,0x81,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x81,0x81,0x83,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x83,0x80,0x80,0x81,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x80,0x83,0x83,0x81,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x80,0x83,0x83,0x81,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x81,0x81,0x83,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,
	0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x81,0x81,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x80,0x80,0x80,0x81,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x80,0x83,0x83,0x81,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x80,0x83,0x83,0x81,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x81,0x81,0x81,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x81,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x83,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x81,0x83,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,
	0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x81,0x81,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x83,0x80,0x80,0x81,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x80,0x83,0x83,0x81,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x80,0x83,0x83,0x81,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x80,0x83,0x83,0x81,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x80,0x83,0x83,0x81,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x80,0x83,0x83,0x81,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x81,0x81,0x81,0x83,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x83,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80
};





static uint8 play_slines[]=
{
	0, 0, 1,
	1, 0, 2,
	2, 0, 3,
	3, 0, 4,
	4, 0, 5,
	5, 0, 6,
	6, 0, 7,
	7, 0, 8,
	8, 0, 7,
	9, 0, 6,
	10, 0, 5,
	11, 0, 4,
	12, 0, 3,
	13, 0, 2,
	14, 0, 1,
	99,
};

static uint8 record_slines[]=
{
	0, 5, 9,
	1, 3, 11,
	2, 2, 12,
	3, 1, 13,
	4, 1, 13,
	5, 0, 14,
	6, 0, 14,
	7, 0, 14,
	8, 0, 14,
	9, 0, 14,
	10, 1, 13,
	11, 1, 13,
	12, 2, 12,
	13, 3, 11,
	14, 5, 9,
	99,
};

static uint8 pause_slines[]=
{
	0, 2, 6,
	1, 2, 6,
	2, 2, 6,
	3, 2, 6,
	4, 2, 6,
	5, 2, 6,
	6, 2, 6,
	7, 2, 6,
	8, 2, 6,
	9, 2, 6,
	10, 2, 6,
	11, 2, 6,
	12, 2, 6,
	13, 2, 6,
	14, 2, 6,

	0, 9, 13,
	1, 9, 13,
	2, 9, 13,
	3, 9, 13,
	4, 9, 13,
	5, 9, 13,
	6, 9, 13,
	7, 9, 13,
	8, 9, 13,
	9, 9, 13,
	10, 9, 13,
	11, 9, 13,
	12, 9, 13,
	13, 9, 13,
	14, 9, 13,
	99,
};

static uint8 no_slines[]=
{
	99
};

static uint8* sline_icons[4]=
{
	no_slines,
	play_slines,
	record_slines,
	pause_slines
};

static void drawstatus(uint8* XBuf, int n, int y, int xofs)
{
	uint8* slines=sline_icons[n];
	int i;


	XBuf += FCEU_TextScanlineOffsetFromBottom(y) + 240 + 255 + xofs;
	for(i=0; slines[i]!=99; i+=3)
	{
		int y=slines[i];
		uint8* dest=XBuf+(y*256);
		int x;
		for(x=slines[i+1]; x!=slines[i+2]; ++x)
			dest[x]=0;
	}

	XBuf -= 255;
	for(i=0; slines[i]!=99; i+=3)
	{
		int y=slines[i];
		uint8* dest=XBuf+(y*256);
		int x;
		for(x=slines[i+1]; x!=slines[i+2]; ++x)
			dest[x]=4;
	}
}

/// this draws the recording icon (play/pause/record)
void FCEU_DrawRecordingStatus(uint8* XBuf)
{
	if(FCEUD_ShowStatusIcon())
	{
		bool hasPlayRecIcon = false;
		if(FCEUMOV_Mode(MOVIEMODE_RECORD))
		{
			drawstatus(XBuf-ClipSidesOffset,2,28,0);
			hasPlayRecIcon = true;
		}
		else if(FCEUMOV_Mode(MOVIEMODE_PLAY|MOVIEMODE_FINISHED))
		{
			drawstatus(XBuf-ClipSidesOffset,1,28,0);
			hasPlayRecIcon = true;
		}

		if(FCEUI_EmulationPaused())
			drawstatus(XBuf-ClipSidesOffset,3,28,hasPlayRecIcon?-16:0);
	}
}


void FCEU_DrawNumberRow(uint8 *XBuf, int *nstatus, int cur)
{
	uint8 *XBaf;
	int z,x,y;

	XBaf=XBuf - 4 + (FSettings.LastSLine-34)*256;
	if(XBaf>=XBuf)
		for(z=1;z<11;z++)
		{
			if(nstatus[z%10])
			{
				for(y=0;y<13;y++)
					for(x=0;x<21;x++)
						XBaf[y*256+x+z*21+z]=sstat[y*21+x+(z-1)*21*12]^0x80;
			} else {
				for(y=0;y<13;y++)
					for(x=0;x<21;x++)
						if(sstat[y*21+x+(z-1)*21*12]!=0x83)
							XBaf[y*256+x+z*21+z]=sstat[y*21+x+(z-1)*21*12]^0x80;

						else
							XBaf[y*256+x+z*21+z]=(XBaf[y*256+x+z*21+z]&0xF)|0xC0;
			}
			if(cur==z%10)
			{
				for(x=0;x<21;x++)
					XBaf[x+z*21+z*1]=4;
				for(x=1;x<12;x++)
				{
					XBaf[256*x+z*21+z*1]=
						XBaf[256*x+z*21+z*1+20]=4;
				}
				for(x=0;x<21;x++)
					XBaf[12*256+x+z*21+z*1]=4;
			}
		}
}

static int FixJoedChar(uint8 ch)
{
	int c = ch - 32;
	return (c < 0 || c > 98) ? 0 : c;
}
static int JoedCharWidth(uint8 ch)
{
	return Font6x7[FixJoedChar(ch)*8];
}

char target[64][256];

void DrawTextTransWH(uint8 *dest, uint32 width, uint8 *textmsg, uint8 fgcolor, int max_w, int max_h, int border)
{
	unsigned int beginx=2, x=beginx;
	unsigned int y=2;

	memset(target, 0, 64 * 256);

	assert(width==256);
	if (max_w > 256) max_w = 256;
	if (max_h >  64) max_h =  64;

	int ch = 0, wid = 0, nx = 0, ny = 0, max_x = x, offs = 0;
	int pixel_color;
	for(; *textmsg; ++textmsg)
	{
		if(*textmsg == '\n')
		{
			// new line
			x = beginx;
			y += 8;
			continue;
		}
		ch  = FixJoedChar(*textmsg);
		wid = Font6x7[ch * 8];

		if ((x + wid) >= (int)width)
		{
			// wrap to new line
			x = beginx;
			y += 8;
		}

		for(ny = 0; ny < 7; ++ny)
		{
			uint8 d = Font6x7[ch * 8 + 1 + ny];
			for(nx = 0; nx < wid; ++nx)
			{
				pixel_color = (d >> (7 - nx)) & 1;
				if (pixel_color)
				{
					if (y + ny >= 62)
					{
						// Max border is 2, so the max safe y is 62 (since 64 is the max for the target array
						goto textoverflow;
					}
					target[y + ny][x + nx] = 2;
				} else
				{
					target[y + ny][x + nx] = 1;
				}
			}
		}
		// proceed to next char
		x += wid;
		if (max_x < x)
			max_x = x;

	}
textoverflow:

	max_x += 2;
	if (max_x > width)
		max_x = width;
	int max_y = y + ny + 2;
	if (max_y > 62)
		max_y = 62;

	// draw target buffer to screen buffer
	for (y = 0; y < max_y; ++y)
	{
		for (x = 0; x < max_x; ++x)
		{
			offs = y * width + x;
			pixel_color = target[y][x] * 100;

			if(border>=1)
			{
				x>=(     1) && (pixel_color += target[y][x-1]);
				x<(width-1) && (pixel_color += target[y][x+1]);
				y>=(     1) && (pixel_color += target[y-1][x]);
				y<(16   -1) && (pixel_color += target[y+1][x]);
			}
			if(border>=2)
			{
				x>=(     1) && (pixel_color += target[y][x-1]*10);
				x<(width-1) && (pixel_color += target[y][x+1]*10);
				y>=(     1) && (pixel_color += target[y-1][x]*10);
				y<(16   -1) && (pixel_color += target[y+1][x]*10);

				x>=(     1) && y>=(  1) && (pixel_color += target[y-1][x-1]);
				x<(width-1) && y>=(  1) && (pixel_color += target[y-1][x+1]);
				x>=(     1) && y<(16-1) && (pixel_color += target[y+1][x-1]);
				x<(width-1) && y<(16-1) && (pixel_color += target[y+1][x+1]);

				x>=(     2) && (pixel_color += target[y][x-2]);
				x<(width-2) && (pixel_color += target[y][x+2]);
				y>=(     2) && (pixel_color += target[y-2][x]);
				y<(16   -2) && (pixel_color += target[y+2][x]);
			}

			if(pixel_color >= 200)
				dest[offs] = fgcolor;
			else if(pixel_color >= 10)
			{
				if(dest[offs] < 0xA0)
					dest[offs] = 0xC1;
				else
					dest[offs] = 0xD1;
			}
			else if(pixel_color > 0)
			{
				dest[offs] = 0xCF;
			}
		}
	}
}

void DrawTextTrans(uint8 *dest, uint32 width, uint8 *textmsg, uint8 fgcolor)
{
	DrawTextTransWH(dest, width, textmsg, fgcolor, 256, 16, 2);
}
