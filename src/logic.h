






// TOUCH CONTROLS -----------------------------------
sceTouchPeek( SCE_TOUCH_PORT_FRONT, &touch, 1 );
if ( touch.reportNum > 0 )
	{
	touch_check 				= 1;
	touch_x 					= (lerp(touch.report[0].x, 1919, 960));
	touch_y 					= (lerp(touch.report[0].y, 1087, 544));
	touch_check_released_prev 	= 0;
	touch_check_released 		= 0;
	if ( touch_check_pressed_prev == 0 ) { touch_check_pressed_prev = 1; touch_check_pressed = 1; }
	else 								 { touch_check_pressed = 0; }
	}
else
	{
	touch_check 				= 0;
	touch_check_pressed 		= 0;
	touch_check_pressed_prev 	= 0;
	if ( touch_check_released_prev == 0 ) { touch_check_released_prev = 1; touch_check_released = 1; }
	else 								  { touch_check_released = 0; }
	}


if ( touch_check_pressed )
	{
	// BUTTONS
	if ( point_in_rectangle( touch_x, touch_y, 44,  61, 362, 115 ) )	{ btnstate_btn1 = 1; } 	// BUTTON 1
	if ( point_in_rectangle( touch_x, touch_y, 44, 246, 362, 299 ) )	{ btnstate_btn2 = 1; }	// BUTTON 2
	if ( point_in_rectangle( touch_x, touch_y, 44, 425, 362, 478 ) )	{ btnstate_btn3 = 1; }	// BUTTON 3
	}


if ( touch_check )
	{
	
	}

if ( touch_check_released )
	{
	// RESET BUTTON STATES
	btnstate_btn1				= 0;
	btnstate_btn2				= 0;
	btnstate_btn3				= 0;
	
	// BUTTONS
	// BUTTON 1
	if ( point_in_rectangle( touch_x, touch_y, 44,  61, 362, 115 ) )
		{
		vaudio_play_sound_wav( &snd_button1, "ux0:/app/VITAUDIO1/files/snd_button1.wav" );
		}
		
	// BUTTON 2
	if ( point_in_rectangle( touch_x, touch_y, 44, 246, 362, 299 ) )
		{
		vaudio_play_sound_wav( &snd_button2, "ux0:/app/VITAUDIO1/files/snd_button2.wav" );
		}
		
	// BUTTON 3
	if ( point_in_rectangle( touch_x, touch_y, 44, 425, 362, 478 ) )
		{
		vaudio_play_music_ogg( &snd_button3, "ux0:/app/VITAUDIO1/files/snd_button3.ogg" );
		}
	}