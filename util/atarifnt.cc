#include "allincludes.h"

/* Scroller */
char * text = "IN THE FUTURE THE ALIENS ARE ABOUT TO CONQUER THE EARTH. YOU ARE A SKILLED SPACESHIP PILOT AND THE LAST HOPE OF MANKIND. EXPLORE THE ASTEROIDBELT BETWEEN MARS AND JUPITER AND DESTROY ALL THE ALIENS. TRY TO AVOID THE ASTEROIDS THEY CAN DESTROY YOUR SPACESHIP. YOU HAVE ONLY ONE MINUTE. GOOD LUCK!              ************** COPYRIGHT BY CHI HOANG *******************            LETS WRAAAAAAAAAAAAAAP ......................";
int textArray[4096];
int textMax = 27;
int textPos = 0;
static int startPos = 0;
static int doubleBuf = 0;
static float sinPos = 0;
static float sinCounter = 0;

/* characters included in the font (31) */
const char* af_transTab_32="ABCDEFGHIJKLMNOPQRSTUVWXYZ*?!. ";
int af_trans_table_32[256];

/* the bitmaps -- font is read from file and extracted to this array */
unsigned char af_bitmap_32[95][4][32];

/* load TLB_FNT.neo (32x32), and extract charset into the bitmap array */
void afInit32()
{
  File * file = new File("data/TLB_FNT.NEO");
  unsigned char * buf = new unsigned char[file->size()];
  file->read(buf);
  delete file;

  for (int i=0;i<31;i++)
    {
      int py=i/10,px=i%10; // (row, col) of character in font
      for (int l=0;l<32;l++)
	{            
            unsigned char pix8=buf[128+px*16+(py*32+l)*160];
            unsigned char pix9=buf[128+px*16+(py*32+l)*160+1];
            unsigned char pix10=buf[128+px*16+(py*32+l)*160+8];
            unsigned char pix11=buf[128+px*16+(py*32+l)*160+9];
            
            af_bitmap_32[i][0][31-l] = pix8;
            af_bitmap_32[i][1][31-l] = pix9;
            af_bitmap_32[i][2][31-l] = pix10;
            af_bitmap_32[i][3][31-l] = pix11;
	}
    }

  delete buf;

  for (unsigned char c = 0; c < 255; c++)
    {
      af_trans_table_32[c] = 0;
      for (int j = 0; j < (int) strlen(af_transTab_32); j++)
	if (af_transTab_32[j]==c)
	  {
	    af_trans_table_32[c] = j;
	    break;
	  }
    }
    
    printf("afInit: TLB font ready\n");
    
    // init scroller
    int startText = 40;
    for (int i=startText;i<(int)strlen(text)+startText;i++)
    {
        textArray[i] = (char) text[i-startText];
    }
}

void scroller(int screenWidth, int screenHeight) {
    
     // Scroller
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();  
    gluOrtho2D(0, screenWidth, 0, screenHeight);
    glViewport(-32, 0, screenWidth+32, screenHeight); 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();    
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_BLEND);  
    glColor4f(.9,.9,.9,1.0);  
    
    char buf[256];
   
    doubleBuf++;
    if (doubleBuf == 2) {
        doubleBuf = 0;
        sinPos += 0.1; 
        if (sinPos > 0.1 * 62) {
            sinPos = 0.0;
        }          
        startPos -=4;        
        if (startPos == -32) {                
            startPos = 0;
            sinPos += 0.1*4;
            if (sinPos > 0.1 * 62) {
                sinPos = 0.1;
            }            
            textPos++;
            if (textPos > (int)strlen(text)+40) {
                textPos = 0;
            }
        }
    }

    sinCounter = sinPos;
    
    for (int i=0;i<textMax;i++) {
        sinCounter+= 0.1;
        sprintf(buf, "%c", textArray[(int) i + (int)textPos]);
        afPrintAt32(startPos+32*i, screenHeight-450+(int) roundf(fmcos(sinCounter)*32), buf,(float) sinCounter);        
        sinCounter+= 0.4;
    }    
}

void resetScroller() {
    textPos = 0;
}


void afPrintAt32(int x, int y, char * text, float sinCounter)
{
  glRasterPos2i(x, y);
  int l = strlen(text);
  for (int i = 0; i < l; i++) {
      sinCounter+= 0.1;
      glBitmap(8, 32, 0, 0, 8, (int) roundf(fmcos(sinCounter)), af_bitmap_32[af_trans_table_32[(int)text[i]]][0]);
      sinCounter+= 0.1;
      glBitmap(8, 32, 0, 0, 8, (int) roundf(fmcos(sinCounter)), af_bitmap_32[af_trans_table_32[(int)text[i]]][1]);     
      sinCounter+= 0.1;
      glBitmap(8, 32, 0, 0, 8, (int) roundf(fmcos(sinCounter)), af_bitmap_32[af_trans_table_32[(int)text[i]]][2]);    
      sinCounter+= 0.1;
      glBitmap(8, 32, 0, 0, 8, (int) roundf(fmcos(sinCounter)), af_bitmap_32[af_trans_table_32[(int)text[i]]][3]);  
  }  
}

/* Atari Font  */

#include "allincludes.h"

/* characters included in the font (95) */
const char* af_transTab="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_-=+]{[`'\"~;:.>/?}\\|,< ";
int af_trans_table[256];

/* the bitmaps -- font is read from file and extracted to this array */
unsigned char af_bitmap[95][8];

/* load font.pi1, and extract charset into the bitmap array */
void afInit()
{
  File * file = new File("data/font.pi1");
  unsigned char * buf = new unsigned char[file->size()];
  file->read(buf);
  delete file;

  for (int i=0;i<95;i++)
    {
      int py=i/40,px=i%40; // (row, col) of character in font.pi1
      for (int l=0;l<8;l++)
	{
	  unsigned char pix8=buf[34+(px/2)*8+(px%2==1?1:0)+(py*8+l)*160+4];
	  af_bitmap[i][7-l] = pix8;
	}
    }

  delete buf;

  for (unsigned char c = 0; c < 255; c++)
    {
      af_trans_table[c] = 0;
      for (int j = 0; j < 95; j++)
	if (af_transTab[j]==c)
	  {
	    af_trans_table[c] = j;
	    break;
	  }
    }
  printf("afInit: Atari font ready\n");
}

/* print string at given position */
void afPrintAt(int x, int y, char * text)
{
  glRasterPos2i(x, y);
  int l = strlen(text);
  for (int i = 0; i < l; i++)
    glBitmap(8, 8, 0, 0, 8, 0, af_bitmap[af_trans_table[(int)text[i]]]);
}
