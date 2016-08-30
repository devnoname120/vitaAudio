






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
	int btnstate_btn1				= 0;
	int btnstate_btn2				= 0;
	int btnstate_btn3				= 0;
	
	
	// BUTTONS
	if ( point_in_rectangle( touch_x, touch_y, 44,  61, 362, 115 ) )	{   } 	// BUTTON 1
	if ( point_in_rectangle( touch_x, touch_y, 44, 246, 362, 299 ) )	{   }	// BUTTON 2
	if ( point_in_rectangle( touch_x, touch_y, 44, 425, 362, 478 ) )	{   }	// BUTTON 3
	}