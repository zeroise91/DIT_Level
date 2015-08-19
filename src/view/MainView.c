
#include "level.h"
#include <Elementary.h>
#include <Evas.h>

static void
win_delete_request_cb(void *data , Evas_Object *obj , void *event_info)
{
	ui_app_exit();
}

static void
win_back_cb(void *data, Evas_Object *obj, void *event_info)
{
	appdata_s *ad = data;
	/* Let window go to hide state. */
	elm_win_lower(ad->win);
}

static void
app_get_resource(const char *res_file_in, char *res_path_out, int res_path_max)
{
	char *res_path = app_get_resource_path();
	if (res_path) {
		snprintf(res_path_out, res_path_max, "%s%s", res_path, res_file_in);
		free(res_path);
	}
}

static void
create_base_gui(appdata_s *ad)
{
	/* Window */
	ad->win = elm_win_util_standard_add(PACKAGE, PACKAGE);
	elm_win_autodel_set(ad->win, EINA_TRUE);

	evas_object_smart_callback_add(ad->win, "delete,request", win_delete_request_cb, NULL);
	eext_object_event_callback_add(ad->win, EEXT_CALLBACK_BACK, win_back_cb, ad);

	/* Conformant */
	ad->conform = elm_conformant_add(ad->win);
	elm_win_indicator_mode_set(ad->win, ELM_WIN_INDICATOR_SHOW);
	elm_win_indicator_opacity_set(ad->win, ELM_WIN_INDICATOR_BG_TRANSPARENT);
	evas_object_size_hint_weight_set(ad->conform, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_win_resize_object_add(ad->win, ad->conform);
	evas_object_show(ad->conform);


	/* Image */
	char img_path[PATH_MAX] = { 0, };
	app_get_resource("Back_black.png", img_path, PATH_MAX);

	Evas* canvas = evas_object_evas_get(ad->conform);
	ad->backgroundimage = evas_object_image_filled_add(canvas);		// Add an image to the given evas
	evas_object_image_file_set(ad->backgroundimage, img_path, NULL);//Set the source file from where an image object must fetch the real image data
	evas_object_move(ad->backgroundimage, 0, 0);					// Move the given Evas object to the given location inside its canvas�� viewport
	evas_object_resize(ad->backgroundimage, DISPLAY_WIDTH, DISPLAY_HEIGHT);				// Change the size of the given Evas object
	evas_object_show(ad->backgroundimage);							// Make the given Evas object visible

	/* Image */
	char mfimg_path[PATH_MAX] = { 0, };
	app_get_resource("back_circle.png", mfimg_path, PATH_MAX);

	ad->mainrame = evas_object_image_filled_add(canvas);		// Add an image to the given evas
	evas_object_image_file_set(ad->mainrame, mfimg_path, NULL);//Set the source file from where an image object must fetch the real image data
	evas_object_move(ad->mainrame, DISPLAY_WIDTH/2-LEVEL_CIIRLE_MAINFRAME_RADIUS/2, DISPLAY_HEIGHT/2-LEVEL_CIIRLE_MAINFRAME_RADIUS/2);					// Move the given Evas object to the given location inside its canvas�� viewport
	evas_object_resize(ad->mainrame, LEVEL_CIIRLE_MAINFRAME_RADIUS, LEVEL_CIIRLE_MAINFRAME_RADIUS);				// Change the size of the given Evas object
	evas_object_show(ad->mainrame);							// Make the given Evas object visible


	char img_path2[PATH_MAX] = { 0, };
	app_get_resource("center.png", img_path2, PATH_MAX);
	ad->ball = evas_object_image_filled_add(canvas);		// Add an image to the given evas
	evas_object_image_file_set(ad->ball, img_path2, NULL);//Set the source file from where an image object must fetch the real image data
	evas_object_move(ad->ball, DISPLAY_WIDTH/2-LEVEL_CIIRLE_BALL_RADIUS/2, DISPLAY_HEIGHT/2-LEVEL_CIIRLE_BALL_RADIUS/2);					// Move the given Evas object to the given location inside its canvas�� viewport
	evas_object_resize(ad->ball, LEVEL_CIIRLE_BALL_RADIUS, LEVEL_CIIRLE_BALL_RADIUS);				// Change the size of the given Evas object
	evas_object_show(ad->ball);							// Make the given Evas object visible


		char img_path3[PATH_MAX] = { 0, };
		app_get_resource("guide.png", img_path3, PATH_MAX);
		ad->guide = evas_object_image_filled_add(canvas);		// Add an image to the given evas
		evas_object_image_file_set(ad->guide, img_path3, NULL);//Set the source file from where an image object must fetch the real image data
		evas_object_move(ad->guide, DISPLAY_WIDTH/2-LEVEL_CIIRLE_MAINFRAME_RADIUS/2, DISPLAY_HEIGHT/2-LEVEL_CIIRLE_MAINFRAME_RADIUS/2);					// Move the given Evas object to the given location inside its canvas�� viewport
		evas_object_resize(ad->guide, LEVEL_CIIRLE_MAINFRAME_RADIUS, LEVEL_CIIRLE_MAINFRAME_RADIUS);				// Change the size of the given Evas object
		evas_object_show(ad->guide);							// Make the given Evas object visible
	/* Show window after base gui is set up */
	evas_object_show(ad->win);

	accelrometer_activate(ad);
}

static bool
app_create(void *data)
{
	/* Hook to take necessary actions before main event loop starts
		Initialize UI resources and application's data
		If this function returns true, the main loop of application starts
		If this function returns false, the application is terminated */
	appdata_s *ad = data;

	create_base_gui(ad);

	return true;
}

static void
app_control(app_control_h app_control, void *data)
{
	/* Handle the launch request. */
}

static void
app_pause(void *data)
{


	/* Take necessary actions when application becomes invisible. */

	appdata_s* ad =(appdata_s* )data;
	ad->acc->Off(ad->acc);

}

static void
app_resume(void *data)
{
	/* Take necessary actions when application becomes visible. */
	appdata_s * ad = (appdata_s*)data;
	ad->acc->On(ad->acc);


}

static void
app_terminate(void *data)
{
	/* Release all resources. */
}

static void
ui_app_lang_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LANGUAGE_CHANGED*/
	char *locale = NULL;
	system_settings_get_value_string(SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE, &locale);
	elm_language_set(locale);
	free(locale);
	return;
}

static void
ui_app_orient_changed(app_event_info_h event_info, void *user_data)
{

	/*APP_EVENT_DEVICE_ORIENTATION_CHANGED*/
	return;
}

static void
ui_app_region_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_REGION_FORMAT_CHANGED*/
}

static void
ui_app_low_battery(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LOW_BATTERY*/
}

static void
ui_app_low_memory(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LOW_MEMORY*/
}

int
main(int argc, char *argv[])
{
	appdata_s ad = {0,};
	int ret = 0;

	ui_app_lifecycle_callback_s event_callback = {0,};
	app_event_handler_h handlers[5] = {NULL, };

	event_callback.create = app_create;
	event_callback.terminate = app_terminate;
	event_callback.pause = app_pause;
	event_callback.resume = app_resume;
	event_callback.app_control = app_control;

	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_BATTERY], APP_EVENT_LOW_BATTERY, ui_app_low_battery, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_MEMORY], APP_EVENT_LOW_MEMORY, ui_app_low_memory, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_DEVICE_ORIENTATION_CHANGED], APP_EVENT_DEVICE_ORIENTATION_CHANGED, ui_app_orient_changed, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_LANGUAGE_CHANGED], APP_EVENT_LANGUAGE_CHANGED, ui_app_lang_changed, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_REGION_FORMAT_CHANGED], APP_EVENT_REGION_FORMAT_CHANGED, ui_app_region_changed, &ad);
	ui_app_remove_event_handler(handlers[APP_EVENT_LOW_MEMORY]);

	ret = ui_app_main(argc, argv, &event_callback, &ad);
	if (ret != APP_ERROR_NONE) {
		dlog_print(DLOG_ERROR, LOG_TAG, "ui_app_main() is failed. err = %d", ret);
	}

	return ret;
}
