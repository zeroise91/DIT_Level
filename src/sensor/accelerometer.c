/*
 * accelerometer.c
 *
 *  Created on: Aug 10, 2015
 *      Author: parkbeomchan
 */


#include "Device/Sensor.h"
#include "level.h"
#include <Elementary.h>

#define ACCELEROMETER_PERIOD 100

static Accelerometer accelerometer_get_instance(){
	static Accelerometer  pacc=NULL;
	if(pacc == NULL)
		pacc= NewAccelerometer();
	return pacc;
}
static void acccallback(sensor_h sensor, sensor_event_s * event, void * user_data){

	appdata_s* ad = (appdata_s*)user_data;

	int ball_default_point_x = DISPLAY_WIDTH/2-LEVEL_CIIRLE_BALL_RADIUS/2;
	int ball_default_point_y = DISPLAY_HEIGHT/2-LEVEL_CIIRLE_BALL_RADIUS/2;


	float dx = event->values[0] ;
	if(dx>9.8)dx = 9.8;
	if(dx<-9.8) dx=-9.8;
	float dy = event->values[1] ;
	if(dy>9.8)dy = 9.8;
	if(dy<-9.8) dy=-9.8;

	dx*=13;
	dy*=-13;

	evas_object_hide(ad->guide);
	evas_object_hide(ad->ball);

	evas_object_move(ad->ball,ball_default_point_x+dx,ball_default_point_y+dy);

	evas_object_show(ad->ball);
	evas_object_show(ad->guide);

}

void accelrometer_activate(appdata_s* ad){

	Accelerometer accelerometer = accelerometer_get_instance();

	if(accelerometer->isSupported(accelerometer))
	{
		accelerometer->addCallback(accelerometer,acccallback,ACCELEROMETER_PERIOD,ad);
		accelerometer->On(accelerometer);
	}

}



