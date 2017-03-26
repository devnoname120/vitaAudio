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
#include <psp2/io/stat.h>
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
vaudio snd_button1;
vaudio snd_button2;
vaudio snd_button3;



// MAIN LOOP
int main()
	{
	sceIoMkdir( "ux0:/data/vitaAudio/", 0777 );
	// INITIALIZE VITA2D
	vita2d_init();
	vita2d_set_clear_color( RGBA8(0x40, 0x40, 0x40, 0xFF) );
	
	// LOAD TEXTURES
	vita2d_texture *img_bg 		= vita2d_load_PNG_buffer( &_binary_resources_sprites_img_bg_png_start 	); // Background image
	vita2d_texture *img_btn 	= vita2d_load_PNG_buffer( &_binary_resources_sprites_img_btn_png_start 	); // button image
	vita2d_texture *img_btnp 	= vita2d_load_PNG_buffer( &_binary_resources_sprites_img_btnp_png_start ); // button pressed image
	
	// LOAD FONT
	vita2d_font *font_24 			= vita2d_load_font_file( "ux0:/app/VITAUDIO1/files/MyriadPro.otf" );
	vita2d_font *font_30 			= vita2d_load_font_file( "ux0:/app/VITAUDIO1/files/MyriadPro.otf" );
	
	// SET TOUCH SAMPLING
	sceTouchSetSamplingState( SCE_TOUCH_PORT_FRONT, 1 );
	sceTouchSetSamplingState( SCE_TOUCH_PORT_BACK,  1 );
	
	
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
		if ( btnstate_btn1 ) 	{ vita2d_draw_texture( img_btnp, 44,  61 ); }
		else					{ vita2d_draw_texture( img_btn,  44,  61 ); }
		vita2d_font_draw_text( font_24, 123, 92, RGBA8( 255, 255, 255, 255 ), 24, "Play Wav Sound" );
		
		if ( btnstate_btn2 ) 	{ vita2d_draw_texture( img_btnp, 44, 246 ); }
		else					{ vita2d_draw_texture( img_btn,  44, 246 ); }
		vita2d_font_draw_text( font_24, 123, 278, RGBA8( 255, 255, 255, 255 ), 24, "Play Ogg Sound" );
		
		if ( btnstate_btn3 ) 	{ vita2d_draw_texture( img_btnp, 44, 425 ); }
		else					{ vita2d_draw_texture( img_btn,  44, 425 ); }
		vita2d_font_draw_text( font_24, 89, 458, RGBA8( 255, 255, 255, 255 ), 24, "Play Background Music" );
		
		// DRAW DEBUG
		vita2d_font_draw_textf( font_24, 430, 140, RGBA8( 255, 255, 255, 255 ), 24, "%s%d%s%s%d%s%s%d%s%s%s%d%s%s%d",
																									"touch_check              = ", touch_check, "\n",
																									"touch_check_pressed      = ", touch_check_pressed,"\n",
																									"touch_check_pressed_prev = ", touch_check_pressed_prev,"\n",
																									"\n",
																									"touch_check_released     = ", touch_check_released,"\n",
																									"touch_check_released_prev= ", touch_check_released_prev
																									);
		
		
		// FINISH DRAW CALL
		vita2d_end_drawing();
		vita2d_swap_buffers();
		}
	// FREE RESOURCES FROM MEMORY
	vita2d_fini();
	vita2d_free_texture( img_btn );
	vita2d_free_texture( img_btnp );
	vaudio_stop	( &snd_button1 );
	vaudio_free	( &snd_button1 );
	vaudio_stop	( &snd_button2 );
	vaudio_free	( &snd_button2 );
	
	// CALL EXIT PROCCESS
	sceKernelExitProcess(0);
	return 0;
	}