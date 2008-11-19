#include "share.h"
#include "fceuconfig.h"

static uint8 GunSight[]={
        0,0,0,0,0,0,1,0,0,0,0,0,0,
        0,0,0,0,0,0,2,0,0,0,0,0,0,
        0,0,0,0,0,0,1,0,0,0,0,0,0,
        0,0,0,0,0,0,2,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,3,0,0,0,0,0,0,
        1,2,1,2,0,3,3,3,0,2,1,2,1,
        0,0,0,0,0,0,3,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,2,0,0,0,0,0,0,
        0,0,0,0,0,0,1,0,0,0,0,0,0,
        0,0,0,0,0,0,2,0,0,0,0,0,0,
        0,0,0,0,0,0,1,0,0,0,0,0,0,
};
static uint8 FCEUcursor[11*19]=
{
 1,0,0,0,0,0,0,0,0,0,0,
 1,1,0,0,0,0,0,0,0,0,0,
 1,2,1,0,0,0,0,0,0,0,0,
 1,2,2,1,0,0,0,0,0,0,0,
 1,2,2,2,1,0,0,0,0,0,0,
 1,2,2,2,2,1,0,0,0,0,0,
 1,2,2,2,2,2,1,0,0,0,0,
 1,2,2,2,2,2,2,1,0,0,0,
 1,2,2,2,2,2,2,2,1,0,0,
 1,2,2,2,2,2,2,2,2,1,0,
 1,2,2,2,2,2,1,1,1,1,1,
 1,2,2,1,2,2,1,0,0,0,0,
 1,2,1,0,1,2,2,1,0,0,0,
 1,1,0,0,1,2,2,1,0,0,0,
 1,0,0,0,0,1,2,2,1,0,0,
 0,0,0,0,0,1,2,2,1,0,0,
 0,0,0,0,0,0,1,2,2,1,0,
 0,0,0,0,0,0,1,2,2,1,0,
 0,0,0,0,0,0,0,1,1,0,0,
};

void FCEU_DrawGunSight(uint8 *buf, int xc, int yc) {
	if (GCSettings.crosshair) {
		int x, y;
		int c, d;

		for (y = 0; y < 13; y++)
			for (x = 0; x < 13; x++) {
				uint8 a;
				a = GunSight[y * 13 + x];
				if (a) {
					c = (yc + y - 7);
					d = (xc + x - 7);
					if (c >= 0 && d >= 0 && d < 256 && c < 240) {
						if (a == 3)
							buf[c * 256 + d] = 0xBF - (buf[c * 256 + d] & 0x3F);
						else
							buf[c * 256 + d] = a - 1;
					}
				}
			}
	}
}


void FCEU_DrawCursor(uint8 *buf, int xc, int yc)
{
 int x,y;
 int c,d;

  if(xc<256 && yc<240)
  for(y=0;y<19;y++)
   for(x=0;x<11;x++)
   {
    uint8 a;
    a=FCEUcursor[y*11+x];
    if(a)
    {
     c=(yc+y);
     d=(xc+x);
     if(d<256 && c<240)
      buf[c*256+d]=a+127;
    }
   }
}
