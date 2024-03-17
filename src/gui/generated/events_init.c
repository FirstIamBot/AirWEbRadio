/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"

#if LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif


#include "custom.h"
static lv_timer_t  * task_tprogress;
static void pageStatic_btn_next_page_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.pageActive, guider_ui.pageActive_del, &guider_ui.pageStatic_del, setup_scr_pageActive, LV_SCR_LOAD_ANIM_NONE, 100, 200, false, true);
		break;
	}
	default:
		break;
	}
}
static void pageStatic_slider_all_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_VALUE_CHANGED:
	{
		int slider_value = lv_slider_get_value(guider_ui.pageStatic_slider_all);
	lv_textprogress_set_value(guider_ui.pageStatic_tp_step_1, slider_value);
	lv_textprogress_set_value(guider_ui.pageStatic_tp_step_5, slider_value);
	lv_textprogress_set_value(guider_ui.pageStatic_tp_step_20, slider_value);
	lv_bar_set_value(guider_ui.pageStatic_bar_1, slider_value, LV_ANIM_OFF);
		break;
	}
	default:
		break;
	}
}
void events_init_pageStatic(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->pageStatic_btn_next_page, pageStatic_btn_next_page_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->pageStatic_slider_all, pageStatic_slider_all_event_handler, LV_EVENT_ALL, NULL);
}
static void pageActive_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_SCREEN_LOADED:
	{
		task_tprogress = lv_timer_create(pageActive_tprogress_img_1_timer_cb, 100, NULL);
		break;
	}
	case LV_EVENT_SCREEN_UNLOAD_START:
	{
		lv_timer_del(task_tprogress);
		break;
	}
	default:
		break;
	}
}
static void pageActive_btn_pre_btn_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.pageStatic, guider_ui.pageStatic_del, &guider_ui.pageActive_del, setup_scr_pageStatic, LV_SCR_LOAD_ANIM_NONE, 100, 200, false, true);
		break;
	}
	default:
		break;
	}
}
static void pageActive_btn_1_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.main, guider_ui.main_del, &guider_ui.pageActive_del, setup_scr_main, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
		break;
	}
	default:
		break;
	}
}
void events_init_pageActive(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->pageActive, pageActive_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->pageActive_btn_pre_btn, pageActive_btn_pre_btn_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->pageActive_btn_1, pageActive_btn_1_event_handler, LV_EVENT_ALL, NULL);
}
static void main_btnm_1_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_t * obj = lv_event_get_target(e);
		uint32_t id = lv_btnmatrix_get_selected_btn(obj);
		switch(id) {
		case 15:
		{
			ui_load_scr_animation(&guider_ui, &guider_ui.pageStatic, guider_ui.pageStatic_del, &guider_ui.main_del, setup_scr_pageStatic, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
			break;
		}
		case 16:
		{
			ui_load_scr_animation(&guider_ui, &guider_ui.Band, guider_ui.Band_del, &guider_ui.main_del, setup_scr_Band, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
			break;
		}
		case 17:
		{
			ui_load_scr_animation(&guider_ui, &guider_ui.screen_1, guider_ui.screen_1_del, &guider_ui.main_del, setup_scr_screen_1, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
			break;
		}
		default:
			break;
		}
		break;
	}
	default:
		break;
	}
}
void events_init_main(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->main_btnm_1, main_btnm_1_event_handler, LV_EVENT_ALL, NULL);
}
static void Band_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.main, guider_ui.main_del, &guider_ui.Band_del, setup_scr_main, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
		break;
	}
	default:
		break;
	}
}
void events_init_Band(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->Band, Band_event_handler, LV_EVENT_ALL, NULL);
}
static void screen_1_btn_1_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.main, guider_ui.main_del, &guider_ui.screen_1_del, setup_scr_main, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
		break;
	}
	default:
		break;
	}
}
void events_init_screen_1(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_1_btn_1, screen_1_btn_1_event_handler, LV_EVENT_ALL, NULL);
}

void events_init(lv_ui *ui)
{

}
