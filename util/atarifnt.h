/* $Id: atarifnt.h,v 1.1 2005/02/09 03:19:43 dude Exp $ */

#ifndef ATARIFNT_H
#define ATARIFNT_H

void afInit32();
void afPrintAt32(int x, int y, char * text, float sinCounter);
void scroller(int screenWidth, int screenHeight);
void resetScroller();

void afInit();
void afPrintAt(int x, int y, char * text);

#endif
