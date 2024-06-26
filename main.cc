#include "allincludes.h"

/*****************************************************************************
 * static application data
 *****************************************************************************/

Main * mainMod = NULL;

/* Fps */
int last_update_time = 0;
int last_measure = 0;
int update_counter = 0;
int frame_counter = 0;
int measured_ups = 0, measured_fps = 0;

#define FPSARRAYLEN 5
int fpsarray[FPSARRAYLEN];
int fpsarrayptr = 0;
int longtimefps = 0;

/*****************************************************************************
 * Glut Keyboard Callbacks
 *****************************************************************************/
 
void listDisplaySettings() {
    DEVMODE devMode;
    int modeNum = 0;
    while (EnumDisplaySettings(NULL, modeNum, &devMode)) {
        printf("Mode %d: %dx%d, %dbpp, %dHz\n", modeNum, devMode.dmPelsWidth, devMode.dmPelsHeight, devMode.dmBitsPerPel, devMode.dmDisplayFrequency);
        modeNum++;
    }
}

/*****************************************************************************
 * Glut Keyboard Callbacks
 *****************************************************************************/
void keyboardSpecialFunc(int key, int x, int y) {
    /*
    switch (key) {
        case GLUT_KEY_F10:
            mainMod->setPause();
            break;        
    }
    */
    //mainMod->keyboardSpecial(key, 1);
}

void keyboardFunc(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        ChangeDisplaySettingsA(NULL, 0);
        exit (0);
    case 112:
        mainMod->setPause();
        break;
    }
    mainMod->keyboard(key, 1);
}

void keyboardUpFunc(unsigned char key, int x, int y)
{
    mainMod->keyboard(key, 0);
}

/*****************************************************************************
 * Glut Timer Callback (regular update function)
 *****************************************************************************/

void timerFunc(int v)
{
    int time = time_millis();
    
    if (time - last_measure > 1000)
    {
        measured_ups = update_counter * 1000 / (time - last_measure);
        measured_fps = frame_counter * 1000 / (time - last_measure);
        
        update_counter = 0;
        frame_counter = 0;
        last_measure = time;
        
        fpsarray[fpsarrayptr] = measured_fps;
        fpsarrayptr++;
        fpsarrayptr %= FPSARRAYLEN;
        
        longtimefps = 0;
        for (int i = 0; i < FPSARRAYLEN; i++) {
            longtimefps += fpsarray[i];
            longtimefps /= FPSARRAYLEN;
        }
    }
    
    int num_updates = mainMod->updates_per_second * (time-last_update_time) / 1000;
    
    for (int i = 0; i < num_updates; i++)
    {
        update_counter++;
        
        // Game update
        //mainMod->update();        
    }
    
    last_update_time += num_updates * 1000 / mainMod->updates_per_second;
    
    if (num_updates > 0) {
        glutPostRedisplay();
    }
    
    glutTimerFunc(5, timerFunc, 0);
}


/*****************************************************************************
 * Glut Reshape Callback 
 *****************************************************************************/

void reshapeFunc(int w, int h)
{
  glViewport(0, 0, w, h);
  mainMod->screenWidth = w;
  mainMod->screenHeight = h;
  //mainMod->windowSizeChanged();
  glutPostRedisplay();
}

/***************************************** myGlutDisplay() *****************/

void myGlutDisplay( void )
{
    glClearColor( .0f, .0f, .0f, 0.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );        
    
    mainMod->display();
        
    glutSwapBuffers(); 
}


/**************************************** main() ********************/

int main(int argc, char* argv[])
{  
    
    /****************************************/
    /*   Initialize GLUT and create window  */
    /****************************************/
    
    glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowPosition(0, 0 );
    glutInitWindowSize( 800, 600 );
    glutCreateWindow(argv[0]);
    printf("OpenGL Version %s, %s, %s.\n", glGetString(GL_VERSION), glGetString(GL_VENDOR), glGetString(GL_RENDERER));    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);        
    glutKeyboardFunc(keyboardFunc);
    glutKeyboardUpFunc(keyboardUpFunc);
    glutSpecialFunc(keyboardSpecialFunc);    
    glutTimerFunc(10, timerFunc, 0);    
    glutDisplayFunc( myGlutDisplay );
    //glutReshapeFunc(reshapeFunc); 
    
    glutIgnoreKeyRepeat(1);


    // Change Screen Resolution to 800x600
 		/*
    DEVMODE s1;
    DEVMODE* sp = &s1;
    s1.dmFields = DM_BITSPERPEL + DM_PELSWIDTH + DM_PELSHEIGHT + DM_DISPLAYFLAGS + DM_DISPLAYFREQUENCY;
    s1.dmSize = 124; 
    s1.dmBitsPerPel = 16; 
    s1.dmPelsWidth = 800; 
    s1.dmPelsHeight = 600; 
    s1.dmDisplayFlags = 0; 
    s1.dmDisplayFrequency = 75;
    
    int errornr;
    
    // list all avaible display settings
	  errornr = EnumDisplaySettings (NULL, 108 , sp);
	    
		// change display setting
		errornr = ChangeDisplaySettingsA(sp, 0);
	    
	       
	    printf("Erronr:%d\n", errornr);
	    printf("dmFields:%d\ndmSize:%d\ndmBitsPerPel:%d\ndmPelsWidth:%d\ndmPelsHeight:%d\ndmDisplayFlags:%d\ndmDisplayFrequency:%d\n", 
	        s1.dmFields,
	        s1.dmSize,
	        s1.dmBitsPerPel, 
	        s1.dmPelsWidth,
	        s1.dmPelsHeight, 
	        s1.dmDisplayFlags,
	        s1.dmDisplayFrequency
	    );    
    
		*/

    // List all available display settings
    // printf("Available display settings:\n");
    // listDisplaySettings();
    
    // Change Screen Resolution to 800x600x32
    DEVMODE s1;
    ZeroMemory(&s1, sizeof(s1));
    s1.dmSize = sizeof(DEVMODE);
    s1.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFLAGS | DM_DISPLAYFREQUENCY;
    s1.dmBitsPerPel = 32;
    s1.dmPelsWidth = 800;
    s1.dmPelsHeight = 600;
    s1.dmDisplayFlags = 0;
    s1.dmDisplayFrequency = 60;    
    
    int errornr = ChangeDisplaySettingsA(&s1, CDS_FULLSCREEN);
    
    if (errornr != DISP_CHANGE_SUCCESSFUL) {
        printf("ChangeDisplaySettingsA failed: %d\n", errornr);
        //return -1;
        exit (0);
    }
    
    /*
    if (errornr < 0) {
        printf("Sorry, can not change the display resolution to 800x600x16bit... Goodbye!");
        exit (0);
    }
    */
	
    glutFullScreen();    
    
    srand(985);
    
    // init module    
    mainMod = new Game();
    
    // init math module
    fmInit();
    
    // init atari font  8x8 and 32x32   
    afInit();   
    afInit32();      
    
    // init logo
    mainMod->image[0] = new TargaFile("data/spaceship.tga");
    
    // init Wobbler
    for (int i=0;i<mainMod->image[0]->height;i++) {
        mainMod->wobblerImg[i] = new Logo(mainMod->image[0]->width, i, mainMod->image[0]->img);
    }          

    // init farbbalken
    mainMod->farbbalken = new Farbbalken;

    // init farbpfeile
    mainMod->farbpfeile = new Farbpfeile(mainMod->farbbalken->farbverlauf);
    
    mainMod->farbpfeile->registerPfeile(mainMod->screenWidth,mainMod->screenHeight);
    printf("Farbpfeile:%d\n",mainMod->farbpfeile->currentPfeile);

    initStars(mainMod->screenWidth,mainMod->screenHeight);
    
    glutMainLoop();
    return 0;
}

/*****************************************************************************
 * Main member functions
 *****************************************************************************/


Main::Main()
{
  updates_per_second = 50;
  screenWidth = 800;
  screenHeight = 600;
  intro = true;
}

/* empty bodies: to be overridden by subclass */

void Main::update() {}
void Main::display() {}
void Main::keyboard(unsigned char key, int state) {}
void Main::keyboardSpecial(int key, int state) {}
void Main::resetGame() {}
void Main::skipIntro() {}
void Main::setPause() {}



