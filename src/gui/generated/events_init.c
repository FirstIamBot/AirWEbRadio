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
Data_GUI_Air xReceivedGUItoSI4735;
static uint8_t tempeDataDescription;
static uint8_t tempucucValue;
int slider_vol;
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
		lv_obj_add_flag(guider_ui.pageAirradio_cont_BandWFM, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.pageAirradio_btnm_BandWFM, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.pageAirradio_cont_Mod, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.pageAirradio_btnm_Mob, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.pageAirradio_cont_StepFM, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.pageAirradio_btnm_StepFM, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.pageAirradio_cont_vol, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.pageAirradio_slider_vol, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.pageAirradio_textprogress_vol, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.pageAirradio_cont_BandWAM, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.pageAirradio_btnm_BandWSSB, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.pageAirradio_btnm_BandWAM, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.pageAirradio_cont_StepAM, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.pageAirradio_btnm_StepAM, LV_OBJ_FLAG_HIDDEN);
		xReceivedGUItoSI4735.State = false;
		break;
	}
	default:
		break;
	}
}
static void pageAirradio_spangroup_WB_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		if(tempeDataDescription == ebandIDx && tempucucValue == 3)
	{
		lv_obj_clear_flag(guider_ui.pageAirradio_cont_BandWFM, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.pageAirradio_btnm_BandWFM, LV_OBJ_FLAG_HIDDEN);
	}
	if(tempeDataDescription == ebandIDx && tempucucValue != 3)
	{
		lv_obj_clear_flag(guider_ui.pageAirradio_cont_BandWAM, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.pageAirradio_btnm_BandWAM, LV_OBJ_FLAG_HIDDEN);
	}
	
		break;
	}
	default:
		break;
	}
}
static void pageAirradio_down_step_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		xReceivedGUItoSI4735.eDataDescription = eStepDown;
	xReceivedGUItoSI4735.ucValue = 1;
		break;
	}
	case LV_EVENT_PRESSED:
	{
		lv_obj_set_style_opa(guider_ui.pageAirradio_down_step, 136, LV_PART_MAIN);
		break;
	}
	case LV_EVENT_RELEASED:
	{
		lv_obj_set_style_opa(guider_ui.pageAirradio_down_step, 255, LV_PART_MAIN);
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
			xReceivedGUItoSI4735.eDataDescription = ebandIDx;
		xReceivedGUItoSI4735.ucValue = 0;
		xReceivedGUItoSI4735.State = true;
		tempeDataDescription = ebandIDx;
		tempucucValue = 0;
		
			break;
		}
		case 1:
		{
			xReceivedGUItoSI4735.eDataDescription = ebandIDx;
		xReceivedGUItoSI4735.ucValue = 1;
		xReceivedGUItoSI4735.State = true;
		tempeDataDescription = ebandIDx;
		tempucucValue = 1;
		
			break;
		}
		case 2:
		{
			xReceivedGUItoSI4735.eDataDescription = ebandIDx;
		xReceivedGUItoSI4735.ucValue = 2;
		xReceivedGUItoSI4735.State = true;
		tempeDataDescription = ebandIDx;
		tempucucValue = 2;
		
			break;
		}
		case 3:
		{
			xReceivedGUItoSI4735.eDataDescription = ebandIDx;
		xReceivedGUItoSI4735.ucValue = 3;
		xReceivedGUItoSI4735.State = true;
		tempeDataDescription = ebandIDx;
		tempucucValue = 3;
		
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
			if(tempeDataDescription == ebandIDx && tempucucValue == 3)
		{
			lv_obj_clear_flag(guider_ui.pageAirradio_cont_BandWFM, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.pageAirradio_btnm_BandWFM, LV_OBJ_FLAG_HIDDEN);
		}
		if(tempeDataDescription == ebandIDx && tempucucValue != 3)
		{
			lv_obj_clear_flag(guider_ui.pageAirradio_cont_BandWAM, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.pageAirradio_btnm_BandWAM, LV_OBJ_FLAG_HIDDEN);
		}
		
		
			break;
		}
		case 6:
		{
			if(tempeDataDescription == ebandIDx && tempucucValue == 3)
		{
			lv_obj_clear_flag(guider_ui.pageAirradio_cont_StepFM, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.pageAirradio_btnm_StepFM, LV_OBJ_FLAG_HIDDEN);
		}
		if(tempeDataDescription == ebandIDx && tempucucValue != 3)
		{
			lv_obj_clear_flag(guider_ui.pageAirradio_cont_StepAM, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(guider_ui.pageAirradio_btnm_StepAM, LV_OBJ_FLAG_HIDDEN);
		}
		
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
static void pageAirradio_btnm_StepAM_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_add_flag(guider_ui.pageAirradio_cont_StepAM, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.pageAirradio_btnm_StepAM, LV_OBJ_FLAG_HIDDEN);
		lv_obj_t * obj = lv_event_get_target(e);
		uint32_t id = lv_btnmatrix_get_selected_btn(obj);
		switch(id) {
		case 0:
		{
			xReceivedGUItoSI4735.eDataDescription = eStepAM;
		xReceivedGUItoSI4735.ucValue = 0;
		xReceivedGUItoSI4735.State = true;
			break;
		}
		case 1:
		{
			xReceivedGUItoSI4735.eDataDescription = eStepAM;
		xReceivedGUItoSI4735.ucValue = 1;
		xReceivedGUItoSI4735.State = true;
			break;
		}
		case 2:
		{
			xReceivedGUItoSI4735.eDataDescription = eStepAM;
		xReceivedGUItoSI4735.ucValue = 2;
		xReceivedGUItoSI4735.State = true;
			break;
		}
		case 3:
		{
			xReceivedGUItoSI4735.eDataDescription = eStepAM;
		xReceivedGUItoSI4735.ucValue = 3;
		xReceivedGUItoSI4735.State = true;
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
		lv_obj_add_flag(guider_ui.pageAirradio_cont_StepFM, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.pageAirradio_btnm_StepFM, LV_OBJ_FLAG_HIDDEN);
		lv_obj_t * obj = lv_event_get_target(e);
		uint32_t id = lv_btnmatrix_get_selected_btn(obj);
		switch(id) {
		case 0:
		{
			xReceivedGUItoSI4735.eDataDescription = eStepFM;
		xReceivedGUItoSI4735.ucValue = 0;
		xReceivedGUItoSI4735.State = true;
			break;
		}
		case 1:
		{
			xReceivedGUItoSI4735.eDataDescription = eStepFM;
		xReceivedGUItoSI4735.ucValue = 1;
		xReceivedGUItoSI4735.State = true;
			break;
		}
		case 2:
		{
			xReceivedGUItoSI4735.eDataDescription = eStepFM;
		xReceivedGUItoSI4735.ucValue = 2;
		xReceivedGUItoSI4735.State = true;
			break;
		}
		case 3:
		{
			xReceivedGUItoSI4735.eDataDescription = eStepFM;
		xReceivedGUItoSI4735.ucValue = 3;
		xReceivedGUItoSI4735.State = true;
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
static void pageAirradio_btnm_BandWFM_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_add_flag(guider_ui.pageAirradio_cont_BandWFM, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.pageAirradio_btnm_BandWFM, LV_OBJ_FLAG_HIDDEN);
		lv_obj_t * obj = lv_event_get_target(e);
		uint32_t id = lv_btnmatrix_get_selected_btn(obj);
		switch(id) {
		case 0:
		{
			xReceivedGUItoSI4735.eDataDescription = eBandWFM;
		xReceivedGUItoSI4735.ucValue = 0;
		xReceivedGUItoSI4735.State = true;
			break;
		}
		case 1:
		{
			xReceivedGUItoSI4735.eDataDescription = eBandWFM;
		xReceivedGUItoSI4735.ucValue = 1;
		xReceivedGUItoSI4735.State = true;
			break;
		}
		case 2:
		{
			xReceivedGUItoSI4735.eDataDescription = eBandWFM;
		xReceivedGUItoSI4735.ucValue = 2;
		xReceivedGUItoSI4735.State = true;
			break;
		}
		case 3:
		{
			xReceivedGUItoSI4735.eDataDescription = eBandWFM;
		xReceivedGUItoSI4735.ucValue = 3;
		xReceivedGUItoSI4735.State = true;
			break;
		}
		case 4:
		{
			xReceivedGUItoSI4735.eDataDescription = eBandWFM;
		xReceivedGUItoSI4735.ucValue = 4;
		xReceivedGUItoSI4735.State = true;
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
static void pageAirradio_btnm_BandWSSB_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_add_flag(guider_ui.pageAirradio_cont_BandWSSB, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.pageAirradio_btnm_BandWSSB, LV_OBJ_FLAG_HIDDEN);
		lv_obj_t * obj = lv_event_get_target(e);
		uint32_t id = lv_btnmatrix_get_selected_btn(obj);
		switch(id) {
		case 0:
		{
			xReceivedGUItoSI4735.eDataDescription = eBandWSSB;
		xReceivedGUItoSI4735.ucValue = 0;
		xReceivedGUItoSI4735.State = true;
			break;
		}
		case 1:
		{
			xReceivedGUItoSI4735.eDataDescription = eBandWSSB;
		xReceivedGUItoSI4735.ucValue = 1;
		xReceivedGUItoSI4735.State = true;
			break;
		}
		case 2:
		{
			xReceivedGUItoSI4735.eDataDescription = eBandWSSB;
		xReceivedGUItoSI4735.ucValue = 2;
		xReceivedGUItoSI4735.State = true;
			break;
		}
		case 3:
		{
			xReceivedGUItoSI4735.eDataDescription = eBandWSSB;
		xReceivedGUItoSI4735.ucValue = 3;
		xReceivedGUItoSI4735.State = true;
			break;
		}
		case 4:
		{
			xReceivedGUItoSI4735.eDataDescription = eBandWSSB;
		xReceivedGUItoSI4735.ucValue = 4;
		xReceivedGUItoSI4735.State = true;
			break;
		}
		case 5:
		{
			xReceivedGUItoSI4735.eDataDescription = eBandWSSB;
		xReceivedGUItoSI4735.ucValue = 5;
		xReceivedGUItoSI4735.State = true;
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
static void pageAirradio_btnm_BandWAM_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_add_flag(guider_ui.pageAirradio_cont_BandWAM, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.pageAirradio_btnm_BandWAM, LV_OBJ_FLAG_HIDDEN);
		lv_obj_t * obj = lv_event_get_target(e);
		uint32_t id = lv_btnmatrix_get_selected_btn(obj);
		switch(id) {
		case 0:
		{
			xReceivedGUItoSI4735.eDataDescription = eBandWAM;
		xReceivedGUItoSI4735.ucValue = 0;
		xReceivedGUItoSI4735.State = true;
			break;
		}
		case 1:
		{
			xReceivedGUItoSI4735.eDataDescription = eBandWAM;
		xReceivedGUItoSI4735.ucValue = 1;
		xReceivedGUItoSI4735.State = true;
			break;
		}
		case 2:
		{
			xReceivedGUItoSI4735.eDataDescription = eBandWAM;
		xReceivedGUItoSI4735.ucValue = 2;
		xReceivedGUItoSI4735.State = true;
			break;
		}
		case 3:
		{
			xReceivedGUItoSI4735.eDataDescription = eBandWAM;
		xReceivedGUItoSI4735.ucValue = 3;
		xReceivedGUItoSI4735.State = true;
			break;
		}
		case 4:
		{
			xReceivedGUItoSI4735.eDataDescription = eBandWAM;
		xReceivedGUItoSI4735.ucValue = 4;
		xReceivedGUItoSI4735.State = true;
			break;
		}
		case 5:
		{
			xReceivedGUItoSI4735.eDataDescription = eBandWAM;
		xReceivedGUItoSI4735.ucValue = 5;
		xReceivedGUItoSI4735.State = true;
			break;
		}
		case 6:
		{
			xReceivedGUItoSI4735.eDataDescription = eBandWAM;
		xReceivedGUItoSI4735.ucValue = 6;
		xReceivedGUItoSI4735.State = true;
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
	xReceivedGUItoSI4735.eDataDescription = eslider_vol;
	xReceivedGUItoSI4735.ucValue = slider_vol;
	xReceivedGUItoSI4735.State = true;
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
		lv_obj_add_flag(guider_ui.pageAirradio_cont_Mod, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.pageAirradio_btnm_Mob, LV_OBJ_FLAG_HIDDEN);
		lv_obj_t * obj = lv_event_get_target(e);
		uint32_t id = lv_btnmatrix_get_selected_btn(obj);
		switch(id) {
		case 0:
		{
			xReceivedGUItoSI4735.eDataDescription = eModIdx;
		xReceivedGUItoSI4735.ucValue = 0;
		xReceivedGUItoSI4735.State = true;
			break;
		}
		case 1:
		{
			xReceivedGUItoSI4735.eDataDescription = eModIdx;
		xReceivedGUItoSI4735.ucValue = 1;
		xReceivedGUItoSI4735.State = true;
			break;
		}
		case 2:
		{
			xReceivedGUItoSI4735.eDataDescription = eModIdx;
		xReceivedGUItoSI4735.ucValue = 2;
		xReceivedGUItoSI4735.State = true;
			break;
		}
		case 3:
		{
			xReceivedGUItoSI4735.eDataDescription = eModIdx;
		xReceivedGUItoSI4735.ucValue = 3;
		xReceivedGUItoSI4735.State = true;
			break;
		}
		case 4:
		{
			xReceivedGUItoSI4735.eDataDescription = eModIdx;
		xReceivedGUItoSI4735.ucValue = 4;
		xReceivedGUItoSI4735.State = true;
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
static void pageAirradio_spangroup_Step_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		if(tempeDataDescription == ebandIDx && tempucucValue == 3)
	{
		lv_obj_clear_flag(guider_ui.pageAirradio_cont_StepFM, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.pageAirradio_btnm_StepFM, LV_OBJ_FLAG_HIDDEN);
	}
	if(tempeDataDescription == ebandIDx && tempucucValue != 3)
	{
		lv_obj_clear_flag(guider_ui.pageAirradio_cont_StepAM, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.pageAirradio_btnm_StepAM, LV_OBJ_FLAG_HIDDEN);
	}
		break;
	}
	default:
		break;
	}
}
static void pageAirradio_spangroup_RSSI_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		
		break;
	}
	default:
		break;
	}
}
static void pageAirradio_imgbtn_1_event_handler (lv_event_t *e)
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
static void pageAirradio_up_step_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		xReceivedGUItoSI4735.eDataDescription = eStepUP;
	xReceivedGUItoSI4735.ucValue = 1;
		break;
	}
	case LV_EVENT_PRESSING:
	{
		lv_obj_set_style_opa(guider_ui.pageAirradio_up_step, 115, LV_PART_MAIN);
		break;
	}
	case LV_EVENT_RELEASED:
	{
		lv_obj_set_style_opa(guider_ui.pageAirradio_up_step, 255, LV_PART_MAIN);
		break;
	}
	default:
		break;
	}
}
void events_init_pageAirradio(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->pageAirradio, pageAirradio_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->pageAirradio_spangroup_WB, pageAirradio_spangroup_WB_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->pageAirradio_down_step, pageAirradio_down_step_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->pageAirradio_btnm_Main, pageAirradio_btnm_Main_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->pageAirradio_btnm_StepAM, pageAirradio_btnm_StepAM_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->pageAirradio_btnm_StepFM, pageAirradio_btnm_StepFM_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->pageAirradio_btnm_BandWFM, pageAirradio_btnm_BandWFM_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->pageAirradio_btnm_BandWSSB, pageAirradio_btnm_BandWSSB_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->pageAirradio_btnm_BandWAM, pageAirradio_btnm_BandWAM_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->pageAirradio_slider_vol, pageAirradio_slider_vol_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->pageAirradio_btnm_Mob, pageAirradio_btnm_Mob_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->pageAirradio_spangroup_Step, pageAirradio_spangroup_Step_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->pageAirradio_spangroup_RSSI, pageAirradio_spangroup_RSSI_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->pageAirradio_imgbtn_1, pageAirradio_imgbtn_1_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->pageAirradio_up_step, pageAirradio_up_step_event_handler, LV_EVENT_ALL, NULL);
}

void events_init(lv_ui *ui)
{

}
