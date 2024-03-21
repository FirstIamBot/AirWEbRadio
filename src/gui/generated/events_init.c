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
uint8_t GUI_bandIdx;
#include "custom.h"
int slider_vol;
uint8_t GUI_BandWFMIdx;
uint8_t GUI_ModIdx;
uint8_t GUI_StepFMIdx;
static void pageStatic_btn_next_page_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.pageAirradio, guider_ui.pageAirradio_del, &guider_ui.pageStatic_del, setup_scr_pageAirradio, LV_SCR_LOAD_ANIM_NONE, 100, 100, false, true);
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
static void pageAirradio_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_add_flag(guider_ui.pageAirradio_cont_BandFM, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.pageAirradio_btnm_BandFM, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.pageAirradio_cont_Mod, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.pageAirradio_btnm_Mob, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.pageAirradio_cont_StepFM, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.pageAirradio_btnm_StepFM, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.pageAirradio_cont_vol, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.pageAirradio_slider_vol, LV_OBJ_FLAG_HIDDEN);
		break;
	}
	default:
		break;
	}
}
static void pageAirradio_btn_vol_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_clear_flag(guider_ui.pageAirradio_cont_vol, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.pageAirradio_slider_vol, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.pageAirradio_textprogress_vol, LV_OBJ_FLAG_HIDDEN);
		break;
	}
	default:
		break;
	}
}
static void pageAirradio_btnm_Main_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_t * obj = lv_event_get_target(e);
		uint32_t id = lv_btnmatrix_get_selected_btn(obj);
		switch(id) {
		case 0:
		{
			GUI_bandIdx = 0;
			break;
		}
		case 1:
		{
			GUI_bandIdx = 1;
			break;
		}
		case 2:
		{
			GUI_bandIdx = 2;
			break;
		}
		case 3:
		{
			GUI_bandIdx = 3;
		
			break;
		}
		case 4:
		{
			lv_obj_clear_flag(guider_ui.pageAirradio_cont_Mod, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.pageAirradio_btnm_Mob, LV_OBJ_FLAG_HIDDEN);
			break;
		}
		case 5:
		{
			lv_obj_clear_flag(guider_ui.pageAirradio_cont_BandFM, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.pageAirradio_btnm_BandFM, LV_OBJ_FLAG_HIDDEN);
			break;
		}
		case 6:
		{
			lv_obj_clear_flag(guider_ui.pageAirradio_cont_StepFM, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.pageAirradio_btnm_StepFM, LV_OBJ_FLAG_HIDDEN);
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
static void pageAirradio_slider_vol_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_VALUE_CHANGED:
	{
		slider_vol = lv_slider_get_value(guider_ui.pageAirradio_slider_vol);
	lv_textprogress_set_value(guider_ui.pageAirradio_textprogress_vol, slider_vol);
		break;
	}
	default:
		break;
	}
}
static void pageAirradio_btn_1_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		ui_load_scr_animation(&guider_ui, &guider_ui.pageStatic, guider_ui.pageStatic_del, &guider_ui.pageAirradio_del, setup_scr_pageStatic, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
		break;
	}
	default:
		break;
	}
}
static void pageAirradio_btnm_BandFM_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_t * obj = lv_event_get_target(e);
		uint32_t id = lv_btnmatrix_get_selected_btn(obj);
		switch(id) {
		case 0:
		{
			GUI_BandWFMIdx = 0;
			break;
		}
		case 1:
		{
			GUI_BandWFMIdx = 1;
			break;
		}
		case 2:
		{
			GUI_BandWFMIdx = 2;
			break;
		}
		case 3:
		{
			GUI_BandWFMIdx = 3;
			break;
		}
		case 4:
		{
			GUI_BandWFMIdx = 4;
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
static void pageAirradio_btnm_Mob_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_t * obj = lv_event_get_target(e);
		uint32_t id = lv_btnmatrix_get_selected_btn(obj);
		switch(id) {
		case 0:
		{
			GUI_ModIdx = 0;
			break;
		}
		case 1:
		{
			GUI_ModIdx = 1;
			break;
		}
		case 2:
		{
			GUI_ModIdx = 2;
			break;
		}
		case 3:
		{
			GUI_ModIdx = 3;
			break;
		}
		case 4:
		{
			GUI_ModIdx = 4;
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
static void pageAirradio_btnm_StepFM_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_t * obj = lv_event_get_target(e);
		uint32_t id = lv_btnmatrix_get_selected_btn(obj);
		switch(id) {
		case 0:
		{
			GUI_StepFMIdx = 0;
			break;
		}
		case 1:
		{
			GUI_StepFMIdx = 1;
			break;
		}
		case 2:
		{
			GUI_StepFMIdx = 2;
			break;
		}
		case 3:
		{
			GUI_StepFMIdx = 3;
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
void events_init_pageAirradio(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->pageAirradio, pageAirradio_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->pageAirradio_btn_vol, pageAirradio_btn_vol_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->pageAirradio_btnm_Main, pageAirradio_btnm_Main_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->pageAirradio_slider_vol, pageAirradio_slider_vol_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->pageAirradio_btn_1, pageAirradio_btn_1_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->pageAirradio_btnm_BandFM, pageAirradio_btnm_BandFM_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->pageAirradio_btnm_Mob, pageAirradio_btnm_Mob_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->pageAirradio_btnm_StepFM, pageAirradio_btnm_StepFM_event_handler, LV_EVENT_ALL, NULL);
}

void events_init(lv_ui *ui)
{

}
