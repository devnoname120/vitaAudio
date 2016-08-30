/*
 * 		
 *			-vitaAudio Engine-
 *
 *
 *
 */

// INCLUDE REQUIRED HEADERS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <psp2/touch.h>
#include <psp2/kernel/processmgr.h>
#include <vita2d.h>
#include "vitaAudio/vitaAudio.h"


// DEFINE HELPFUL MATH FUNCTIONS
#define lerp(value, from_max, to_max) ((((value *10) *(to_max *10)) /(from_max *10)) /10)
#define point_in_rectangle(px, py, x1, y1, x2, y2) ((px) > (x1) && (px) < (x2) && (py) > (y1) && (py) < (y2) ? 1 : 0)


// CREATE IMAGE BUFFERS
extern unsigned char _binary_resources_sprites_img_bg_png_start;
extern unsigned char _binary_resources_sprites_img_btn_png_start;
extern unsigned char _binary_resources_sprites_img_btnp_png_start;


// INITIALIZE VARIABLES
SceTouchData    touch;
int touch_check;
int touch_x;
int touch_y;
int touch_check_pressed_prev	= 0;
int touch_check_pressed			= 0;
int touch_check_released_prev	= 0;
int touch_check_released		= 0;

int btnstate_btn1				= 0;
int btnstate_btn2				= 0;
int btnstate_btn3				= 0;


// CREATE AUDIO HANDLERS
AudioHandler snd_button1;



// MAIN LOOP
int main()
	{
	// INITIALIZE VITA2D
	vita2d_init();
	vita2d_set_clear_color( RGBA8(0x40, 0x40, 0x40, 0xFF) );
	
	// LOAD TEXTURES
	vita2d_texture *img_bg 		= vita2d_load_PNG_buffer( &_binary_resources_sprites_img_bg_png_start 	); // Background image
	vita2d_texture *img_btn 	= vita2d_load_PNG_buffer( &_binary_resources_sprites_img_btn_png_start 	); // button image
	vita2d_texture *img_btnp 	= vita2d_load_PNG_buffer( &_binary_resources_sprites_img_btnp_png_start 	); // button pressed image
	
	// SET TOUCH SAMPLING
	sceTouchSetSamplingState( SCE_TOUCH_PORT_FRONT, 1 );
	sceTouchSetSamplingState( SCE_TOUCH_PORT_BACK,  1 );
	
	// INITIALIZE AUDIO
	InitializeAudio( &snd_button1 );
	
	// LOAD AUDIO FILES
	LoadWav( &snd_button1, "ux0:/app/VITAUDIO/files/snd_button1.wav", AUDIO_OUT_MAIN, 0 );
	
	while (1)
		{
		// KEEP BACK-LIGHT ON
		sceKernelPowerTick( 0 );
		
		// INCLUDE EXAMPLES LOGIC
		#include "logic.h"
		
		// START DRAW AND CLEAR SCREEN BUFFER OF ANY EXISTING ARTIFACTS
		vita2d_start_drawing();
		vita2d_clear_screen();
		
		// DRAW BACKGROUND
		vita2d_draw_texture( img_bg, 0, 0 );
		
		// DRAW BUTTONS
		if ( btnstate_btn1 ) 	{ vita2d_draw_texture( img_btn,   44,   61 ); }
		else					{ vita2d_draw_texture( img_btnp,  44,   61 ); }
		
		if ( btnstate_btn2 ) 	{ vita2d_draw_texture( img_btn,   44,  246 ); }
		else					{ vita2d_draw_texture( img_btnp,  44,  246 ); }
		
		if ( btnstate_btn3 ) 	{ vita2d_draw_texture( img_btn,   44,  425 ); }
		else					{ vita2d_draw_texture( img_btnp,  44,  425 ); }
		
		// FINISH DRAW CALL
		vita2d_end_drawing();
		vita2d_swap_buffers();
		}
	// FREE RESOURCES FROM MEMORY
	vita2d_fini();
	vita2d_free_texture( img_btn );
	vita2d_free_texture( img_btnp );
	
	// CALL EXIT PROCCESS
	sceKernelExitProcess(0);
	return 0;
	}
