/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



void setup_scr_pageAirradio(lv_ui *ui)
{
	//Write codes pageAirradio
	ui->pageAirradio = lv_obj_create(NULL);
	lv_obj_set_size(ui->pageAirradio, 320, 240);
	lv_obj_set_scrollbar_mode(ui->pageAirradio, LV_SCROLLBAR_MODE_OFF);

	//Write style for pageAirradio, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->pageAirradio, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->pageAirradio, lv_color_hex(0x37d5f7), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->pageAirradio, LV_GRAD_DIR_HOR, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->pageAirradio, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_main_stop(ui->pageAirradio, 63, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_stop(ui->pageAirradio, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes pageAirradio_RDS
	ui->pageAirradio_RDS = lv_label_create(ui->pageAirradio);
	lv_label_set_text(ui->pageAirradio_RDS, "Radio Rok's Live  15:00 20.03.2024");
	lv_label_set_long_mode(ui->pageAirradio_RDS, LV_LABEL_LONG_SCROLL_CIRCULAR);
	lv_obj_set_pos(ui->pageAirradio_RDS, 75, 59);
	lv_obj_set_size(ui->pageAirradio_RDS, 176, 14);

	//Write style for pageAirradio_RDS, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->pageAirradio_RDS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->pageAirradio_RDS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->pageAirradio_RDS, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->pageAirradio_RDS, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->pageAirradio_RDS, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->pageAirradio_RDS, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->pageAirradio_RDS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->pageAirradio_RDS, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->pageAirradio_RDS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->pageAirradio_RDS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->pageAirradio_RDS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->pageAirradio_RDS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->pageAirradio_RDS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->pageAirradio_RDS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes pageAirradio_spangroup_1
	ui->pageAirradio_spangroup_1 = lv_spangroup_create(ui->pageAirradio);
	lv_spangroup_set_align(ui->pageAirradio_spangroup_1, LV_TEXT_ALIGN_LEFT);
	lv_spangroup_set_overflow(ui->pageAirradio_spangroup_1, LV_SPAN_OVERFLOW_CLIP);
	lv_spangroup_set_mode(ui->pageAirradio_spangroup_1, LV_SPAN_MODE_BREAK);
	//create spans
	lv_span_t *pageAirradio_spangroup_1_span;
	pageAirradio_spangroup_1_span = lv_spangroup_new_span(ui->pageAirradio_spangroup_1);
	lv_span_set_text(pageAirradio_spangroup_1_span, "101.6");
	lv_style_set_text_color(&pageAirradio_spangroup_1_span->style, lv_color_hex(0x000000));
	lv_style_set_text_decor(&pageAirradio_spangroup_1_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&pageAirradio_spangroup_1_span->style, &lv_font_montserratMedium_36);
	pageAirradio_spangroup_1_span = lv_spangroup_new_span(ui->pageAirradio_spangroup_1);
	lv_span_set_text(pageAirradio_spangroup_1_span, "MHz");
	lv_style_set_text_color(&pageAirradio_spangroup_1_span->style, lv_color_hex(0x000000));
	lv_style_set_text_decor(&pageAirradio_spangroup_1_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&pageAirradio_spangroup_1_span->style, &lv_font_montserratMedium_20);
	lv_obj_set_pos(ui->pageAirradio_spangroup_1, 91, 17);
	lv_obj_set_size(ui->pageAirradio_spangroup_1, 154, 46);

	//Write style state: LV_STATE_DEFAULT for &style_pageAirradio_spangroup_1_main_main_default
	static lv_style_t style_pageAirradio_spangroup_1_main_main_default;
	ui_init_style(&style_pageAirradio_spangroup_1_main_main_default);
	
	lv_style_set_border_width(&style_pageAirradio_spangroup_1_main_main_default, 0);
	lv_style_set_radius(&style_pageAirradio_spangroup_1_main_main_default, 0);
	lv_style_set_bg_opa(&style_pageAirradio_spangroup_1_main_main_default, 0);
	lv_style_set_pad_top(&style_pageAirradio_spangroup_1_main_main_default, 0);
	lv_style_set_pad_right(&style_pageAirradio_spangroup_1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_pageAirradio_spangroup_1_main_main_default, 0);
	lv_style_set_pad_left(&style_pageAirradio_spangroup_1_main_main_default, 0);
	lv_style_set_shadow_width(&style_pageAirradio_spangroup_1_main_main_default, 0);
	lv_obj_add_style(ui->pageAirradio_spangroup_1, &style_pageAirradio_spangroup_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_spangroup_refr_mode(ui->pageAirradio_spangroup_1);

	//Write codes pageAirradio_spangroup_2
	ui->pageAirradio_spangroup_2 = lv_spangroup_create(ui->pageAirradio);
	lv_spangroup_set_align(ui->pageAirradio_spangroup_2, LV_TEXT_ALIGN_LEFT);
	lv_spangroup_set_overflow(ui->pageAirradio_spangroup_2, LV_SPAN_OVERFLOW_CLIP);
	lv_spangroup_set_mode(ui->pageAirradio_spangroup_2, LV_SPAN_MODE_BREAK);
	//create spans
	lv_span_t *pageAirradio_spangroup_2_span;
	pageAirradio_spangroup_2_span = lv_spangroup_new_span(ui->pageAirradio_spangroup_2);
	lv_span_set_text(pageAirradio_spangroup_2_span, "Band");
	lv_style_set_text_color(&pageAirradio_spangroup_2_span->style, lv_color_hex(0x000000));
	lv_style_set_text_decor(&pageAirradio_spangroup_2_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&pageAirradio_spangroup_2_span->style, &lv_font_montserratMedium_12);
	pageAirradio_spangroup_2_span = lv_spangroup_new_span(ui->pageAirradio_spangroup_2);
	lv_span_set_text(pageAirradio_spangroup_2_span, "Mod");
	lv_style_set_text_color(&pageAirradio_spangroup_2_span->style, lv_color_hex(0x000000));
	lv_style_set_text_decor(&pageAirradio_spangroup_2_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&pageAirradio_spangroup_2_span->style, &lv_font_montserratMedium_12);
	pageAirradio_spangroup_2_span = lv_spangroup_new_span(ui->pageAirradio_spangroup_2);
	lv_span_set_text(pageAirradio_spangroup_2_span, "Bw");
	lv_style_set_text_color(&pageAirradio_spangroup_2_span->style, lv_color_hex(0x000000));
	lv_style_set_text_decor(&pageAirradio_spangroup_2_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&pageAirradio_spangroup_2_span->style, &lv_font_montserratMedium_12);
	pageAirradio_spangroup_2_span = lv_spangroup_new_span(ui->pageAirradio_spangroup_2);
	lv_span_set_text(pageAirradio_spangroup_2_span, "Mono");
	lv_style_set_text_color(&pageAirradio_spangroup_2_span->style, lv_color_hex(0x000000));
	lv_style_set_text_decor(&pageAirradio_spangroup_2_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&pageAirradio_spangroup_2_span->style, &lv_font_montserratMedium_12);
	lv_obj_set_pos(ui->pageAirradio_spangroup_2, 13, 62);
	lv_obj_set_size(ui->pageAirradio_spangroup_2, 39, 71);

	//Write style state: LV_STATE_DEFAULT for &style_pageAirradio_spangroup_2_main_main_default
	static lv_style_t style_pageAirradio_spangroup_2_main_main_default;
	ui_init_style(&style_pageAirradio_spangroup_2_main_main_default);
	
	lv_style_set_border_width(&style_pageAirradio_spangroup_2_main_main_default, 0);
	lv_style_set_radius(&style_pageAirradio_spangroup_2_main_main_default, 0);
	lv_style_set_bg_opa(&style_pageAirradio_spangroup_2_main_main_default, 0);
	lv_style_set_pad_top(&style_pageAirradio_spangroup_2_main_main_default, 5);
	lv_style_set_pad_right(&style_pageAirradio_spangroup_2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_pageAirradio_spangroup_2_main_main_default, 0);
	lv_style_set_pad_left(&style_pageAirradio_spangroup_2_main_main_default, 0);
	lv_style_set_shadow_width(&style_pageAirradio_spangroup_2_main_main_default, 0);
	lv_obj_add_style(ui->pageAirradio_spangroup_2, &style_pageAirradio_spangroup_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_spangroup_refr_mode(ui->pageAirradio_spangroup_2);

	//Write codes pageAirradio_up_step
	ui->pageAirradio_up_step = lv_btn_create(ui->pageAirradio);
	ui->pageAirradio_up_step_label = lv_label_create(ui->pageAirradio_up_step);
	lv_label_set_text(ui->pageAirradio_up_step_label, ">");
	lv_label_set_long_mode(ui->pageAirradio_up_step_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->pageAirradio_up_step_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->pageAirradio_up_step, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->pageAirradio_up_step, 248, 27);
	lv_obj_set_size(ui->pageAirradio_up_step, 38, 26);

	//Write style for pageAirradio_up_step, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->pageAirradio_up_step, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->pageAirradio_up_step, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->pageAirradio_up_step, 44, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->pageAirradio_up_step, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->pageAirradio_up_step, lv_color_hex(0x1b614f), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->pageAirradio_up_step, &lv_font_Antonio_Regular_19, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->pageAirradio_up_step, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->pageAirradio_up_step, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes pageAirradio_down_step
	ui->pageAirradio_down_step = lv_btn_create(ui->pageAirradio);
	ui->pageAirradio_down_step_label = lv_label_create(ui->pageAirradio_down_step);
	lv_label_set_text(ui->pageAirradio_down_step_label, "<");
	lv_label_set_long_mode(ui->pageAirradio_down_step_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->pageAirradio_down_step_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->pageAirradio_down_step, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->pageAirradio_down_step, 54, 27);
	lv_obj_set_size(ui->pageAirradio_down_step, 38, 26);

	//Write style for pageAirradio_down_step, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->pageAirradio_down_step, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->pageAirradio_down_step, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->pageAirradio_down_step, 44, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->pageAirradio_down_step, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->pageAirradio_down_step, lv_color_hex(0x1b614f), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->pageAirradio_down_step, &lv_font_Antonio_Regular_19, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->pageAirradio_down_step, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->pageAirradio_down_step, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes pageAirradio_btn_vol
	ui->pageAirradio_btn_vol = lv_btn_create(ui->pageAirradio);
	ui->pageAirradio_btn_vol_label = lv_label_create(ui->pageAirradio_btn_vol);
	lv_label_set_text(ui->pageAirradio_btn_vol_label, "Vol");
	lv_label_set_long_mode(ui->pageAirradio_btn_vol_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->pageAirradio_btn_vol_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->pageAirradio_btn_vol, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->pageAirradio_btn_vol, 268, 98);
	lv_obj_set_size(ui->pageAirradio_btn_vol, 40, 30);

	//Write style for pageAirradio_btn_vol, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->pageAirradio_btn_vol, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->pageAirradio_btn_vol, lv_color_hex(0x186bb1), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->pageAirradio_btn_vol, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->pageAirradio_btn_vol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->pageAirradio_btn_vol, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->pageAirradio_btn_vol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->pageAirradio_btn_vol, lv_color_hex(0x060606), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->pageAirradio_btn_vol, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->pageAirradio_btn_vol, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->pageAirradio_btn_vol, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes pageAirradio_btnm_Main
	ui->pageAirradio_btnm_Main = lv_btnmatrix_create(ui->pageAirradio);
	static const char *pageAirradio_btnm_Main_text_map[] = {"LW", "MW", "SW", "FM", "\n", "Mod", "BW", "Step", "AGC", "",};
	lv_btnmatrix_set_map(ui->pageAirradio_btnm_Main, pageAirradio_btnm_Main_text_map);
	lv_obj_set_pos(ui->pageAirradio_btnm_Main, 7, 145);
	lv_obj_set_size(ui->pageAirradio_btnm_Main, 306, 94);

	//Write style for pageAirradio_btnm_Main, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->pageAirradio_btnm_Main, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->pageAirradio_btnm_Main, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->pageAirradio_btnm_Main, lv_color_hex(0xc9c9c9), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->pageAirradio_btnm_Main, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->pageAirradio_btnm_Main, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->pageAirradio_btnm_Main, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->pageAirradio_btnm_Main, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->pageAirradio_btnm_Main, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_row(ui->pageAirradio_btnm_Main, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_column(ui->pageAirradio_btnm_Main, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->pageAirradio_btnm_Main, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->pageAirradio_btnm_Main, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->pageAirradio_btnm_Main, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->pageAirradio_btnm_Main, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for pageAirradio_btnm_Main, Part: LV_PART_ITEMS, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->pageAirradio_btnm_Main, 1, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->pageAirradio_btnm_Main, 255, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->pageAirradio_btnm_Main, lv_color_hex(0xc9c9c9), LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->pageAirradio_btnm_Main, LV_BORDER_SIDE_FULL, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->pageAirradio_btnm_Main, lv_color_hex(0xffffff), LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->pageAirradio_btnm_Main, &lv_font_montserratMedium_16, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->pageAirradio_btnm_Main, 255, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->pageAirradio_btnm_Main, 4, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->pageAirradio_btnm_Main, 255, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->pageAirradio_btnm_Main, lv_color_hex(0x2195f6), LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->pageAirradio_btnm_Main, LV_GRAD_DIR_NONE, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->pageAirradio_btnm_Main, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);

	//Write codes pageAirradio_cont_vol
	ui->pageAirradio_cont_vol = lv_obj_create(ui->pageAirradio);
	lv_obj_set_pos(ui->pageAirradio_cont_vol, 200, 4);
	lv_obj_set_size(ui->pageAirradio_cont_vol, 68, 233);
	lv_obj_set_scrollbar_mode(ui->pageAirradio_cont_vol, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->pageAirradio_cont_vol, LV_OBJ_FLAG_HIDDEN);

	//Write style for pageAirradio_cont_vol, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->pageAirradio_cont_vol, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->pageAirradio_cont_vol, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->pageAirradio_cont_vol, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->pageAirradio_cont_vol, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->pageAirradio_cont_vol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->pageAirradio_cont_vol, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->pageAirradio_cont_vol, lv_color_hex(0x245793), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->pageAirradio_cont_vol, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->pageAirradio_cont_vol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->pageAirradio_cont_vol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->pageAirradio_cont_vol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->pageAirradio_cont_vol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->pageAirradio_cont_vol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes pageAirradio_textprogress_vol
	ui->pageAirradio_textprogress_vol = lv_textprogress_create(ui->pageAirradio_cont_vol);
	lv_textprogress_set_range_value(ui->pageAirradio_textprogress_vol, 0, 100, 20, 0);
	lv_textprogress_set_decimal(ui->pageAirradio_textprogress_vol, 0);
	lv_textprogress_set_value(ui->pageAirradio_textprogress_vol, 0);
	lv_obj_set_pos(ui->pageAirradio_textprogress_vol, 10, 8);
	lv_obj_set_size(ui->pageAirradio_textprogress_vol, 45, 27);

	//Write style for pageAirradio_textprogress_vol, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_radius(ui->pageAirradio_textprogress_vol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->pageAirradio_textprogress_vol, lv_color_hex(0xdcf30c), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->pageAirradio_textprogress_vol, &lv_font_montserratMedium_14, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->pageAirradio_textprogress_vol, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->pageAirradio_textprogress_vol, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->pageAirradio_textprogress_vol, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->pageAirradio_textprogress_vol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->pageAirradio_textprogress_vol, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->pageAirradio_textprogress_vol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->pageAirradio_textprogress_vol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->pageAirradio_textprogress_vol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes pageAirradio_slider_vol
	ui->pageAirradio_slider_vol = lv_slider_create(ui->pageAirradio_cont_vol);
	lv_slider_set_range(ui->pageAirradio_slider_vol, 0, 100);
	lv_slider_set_mode(ui->pageAirradio_slider_vol, LV_SLIDER_MODE_NORMAL);
	lv_slider_set_value(ui->pageAirradio_slider_vol, 0, LV_ANIM_OFF);
	lv_obj_set_pos(ui->pageAirradio_slider_vol, 26, 41);
	lv_obj_set_size(ui->pageAirradio_slider_vol, 11, 177);

	//Write style for pageAirradio_slider_vol, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->pageAirradio_slider_vol, 170, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->pageAirradio_slider_vol, lv_color_hex(0x050706), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->pageAirradio_slider_vol, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->pageAirradio_slider_vol, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->pageAirradio_slider_vol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->pageAirradio_slider_vol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for pageAirradio_slider_vol, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->pageAirradio_slider_vol, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->pageAirradio_slider_vol, lv_color_hex(0x34ff98), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->pageAirradio_slider_vol, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->pageAirradio_slider_vol, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style for pageAirradio_slider_vol, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->pageAirradio_slider_vol, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->pageAirradio_slider_vol, lv_color_hex(0x00ed5c), LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->pageAirradio_slider_vol, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->pageAirradio_slider_vol, 50, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Write codes pageAirradio_btn_1
	ui->pageAirradio_btn_1 = lv_btn_create(ui->pageAirradio_cont_vol);
	ui->pageAirradio_btn_1_label = lv_label_create(ui->pageAirradio_btn_1);
	lv_label_set_text(ui->pageAirradio_btn_1_label, "<");
	lv_label_set_long_mode(ui->pageAirradio_btn_1_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->pageAirradio_btn_1_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->pageAirradio_btn_1, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->pageAirradio_btn_1, 5, 5);
	lv_obj_set_size(ui->pageAirradio_btn_1, 54, 44);

	//Write style for pageAirradio_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->pageAirradio_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->pageAirradio_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->pageAirradio_btn_1, 44, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->pageAirradio_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->pageAirradio_btn_1, lv_color_hex(0x1b614f), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->pageAirradio_btn_1, &lv_font_Antonio_Regular_19, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->pageAirradio_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->pageAirradio_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes pageAirradio_cont_BandFM
	ui->pageAirradio_cont_BandFM = lv_obj_create(ui->pageAirradio);
	lv_obj_set_pos(ui->pageAirradio_cont_BandFM, 3, 3);
	lv_obj_set_size(ui->pageAirradio_cont_BandFM, 66, 188);
	lv_obj_set_scrollbar_mode(ui->pageAirradio_cont_BandFM, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->pageAirradio_cont_BandFM, LV_OBJ_FLAG_HIDDEN);

	//Write style for pageAirradio_cont_BandFM, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->pageAirradio_cont_BandFM, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->pageAirradio_cont_BandFM, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->pageAirradio_cont_BandFM, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->pageAirradio_cont_BandFM, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->pageAirradio_cont_BandFM, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->pageAirradio_cont_BandFM, 152, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->pageAirradio_cont_BandFM, lv_color_hex(0x2a4052), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->pageAirradio_cont_BandFM, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->pageAirradio_cont_BandFM, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->pageAirradio_cont_BandFM, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->pageAirradio_cont_BandFM, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->pageAirradio_cont_BandFM, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->pageAirradio_cont_BandFM, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes pageAirradio_btnm_BandFM
	ui->pageAirradio_btnm_BandFM = lv_btnmatrix_create(ui->pageAirradio_cont_BandFM);
	static const char *pageAirradio_btnm_BandFM_text_map[] = {"AUT", "\n", "110", "\n", "84", "\n", "60", "\n", "40", "",};
	lv_btnmatrix_set_map(ui->pageAirradio_btnm_BandFM, pageAirradio_btnm_BandFM_text_map);
	lv_obj_set_pos(ui->pageAirradio_btnm_BandFM, 6, 8);
	lv_obj_set_size(ui->pageAirradio_btnm_BandFM, 48, 167);

	//Write style for pageAirradio_btnm_BandFM, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->pageAirradio_btnm_BandFM, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->pageAirradio_btnm_BandFM, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->pageAirradio_btnm_BandFM, lv_color_hex(0xc9c9c9), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->pageAirradio_btnm_BandFM, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->pageAirradio_btnm_BandFM, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->pageAirradio_btnm_BandFM, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->pageAirradio_btnm_BandFM, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->pageAirradio_btnm_BandFM, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_row(ui->pageAirradio_btnm_BandFM, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_column(ui->pageAirradio_btnm_BandFM, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->pageAirradio_btnm_BandFM, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->pageAirradio_btnm_BandFM, 151, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->pageAirradio_btnm_BandFM, lv_color_hex(0x0b4f72), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->pageAirradio_btnm_BandFM, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for pageAirradio_btnm_BandFM, Part: LV_PART_ITEMS, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->pageAirradio_btnm_BandFM, 1, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->pageAirradio_btnm_BandFM, 255, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->pageAirradio_btnm_BandFM, lv_color_hex(0xc9c9c9), LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->pageAirradio_btnm_BandFM, LV_BORDER_SIDE_FULL, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->pageAirradio_btnm_BandFM, lv_color_hex(0xffffff), LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->pageAirradio_btnm_BandFM, &lv_font_montserratMedium_16, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->pageAirradio_btnm_BandFM, 255, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->pageAirradio_btnm_BandFM, 4, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->pageAirradio_btnm_BandFM, 255, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->pageAirradio_btnm_BandFM, lv_color_hex(0x2195f6), LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->pageAirradio_btnm_BandFM, LV_GRAD_DIR_NONE, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->pageAirradio_btnm_BandFM, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);

	//Write codes pageAirradio_cont_Mod
	ui->pageAirradio_cont_Mod = lv_obj_create(ui->pageAirradio);
	lv_obj_set_pos(ui->pageAirradio_cont_Mod, 1, 17);
	lv_obj_set_size(ui->pageAirradio_cont_Mod, 62, 168);
	lv_obj_set_scrollbar_mode(ui->pageAirradio_cont_Mod, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->pageAirradio_cont_Mod, LV_OBJ_FLAG_HIDDEN);

	//Write style for pageAirradio_cont_Mod, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->pageAirradio_cont_Mod, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->pageAirradio_cont_Mod, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->pageAirradio_cont_Mod, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->pageAirradio_cont_Mod, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->pageAirradio_cont_Mod, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->pageAirradio_cont_Mod, 149, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->pageAirradio_cont_Mod, lv_color_hex(0x2a4052), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->pageAirradio_cont_Mod, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->pageAirradio_cont_Mod, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->pageAirradio_cont_Mod, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->pageAirradio_cont_Mod, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->pageAirradio_cont_Mod, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->pageAirradio_cont_Mod, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes pageAirradio_btnm_Mob
	ui->pageAirradio_btnm_Mob = lv_btnmatrix_create(ui->pageAirradio_cont_Mod);
	static const char *pageAirradio_btnm_Mob_text_map[] = {"AM", "\n", "FM", "\n", "LSB", "\n", "USB", "\n", "SSB", "",};
	lv_btnmatrix_set_map(ui->pageAirradio_btnm_Mob, pageAirradio_btnm_Mob_text_map);
	lv_obj_set_pos(ui->pageAirradio_btnm_Mob, 4, 2);
	lv_obj_set_size(ui->pageAirradio_btnm_Mob, 50, 160);

	//Write style for pageAirradio_btnm_Mob, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->pageAirradio_btnm_Mob, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->pageAirradio_btnm_Mob, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->pageAirradio_btnm_Mob, lv_color_hex(0xc9c9c9), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->pageAirradio_btnm_Mob, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->pageAirradio_btnm_Mob, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->pageAirradio_btnm_Mob, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->pageAirradio_btnm_Mob, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->pageAirradio_btnm_Mob, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_row(ui->pageAirradio_btnm_Mob, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_column(ui->pageAirradio_btnm_Mob, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->pageAirradio_btnm_Mob, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->pageAirradio_btnm_Mob, 151, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->pageAirradio_btnm_Mob, lv_color_hex(0x0b4f72), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->pageAirradio_btnm_Mob, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for pageAirradio_btnm_Mob, Part: LV_PART_ITEMS, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->pageAirradio_btnm_Mob, 1, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->pageAirradio_btnm_Mob, 255, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->pageAirradio_btnm_Mob, lv_color_hex(0xc9c9c9), LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->pageAirradio_btnm_Mob, LV_BORDER_SIDE_FULL, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->pageAirradio_btnm_Mob, lv_color_hex(0xffffff), LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->pageAirradio_btnm_Mob, &lv_font_montserratMedium_16, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->pageAirradio_btnm_Mob, 255, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->pageAirradio_btnm_Mob, 4, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->pageAirradio_btnm_Mob, 255, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->pageAirradio_btnm_Mob, lv_color_hex(0x2195f6), LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->pageAirradio_btnm_Mob, LV_GRAD_DIR_NONE, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->pageAirradio_btnm_Mob, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);

	//Write codes pageAirradio_cont_StepFM
	ui->pageAirradio_cont_StepFM = lv_obj_create(ui->pageAirradio);
	lv_obj_set_pos(ui->pageAirradio_cont_StepFM, 4, 14);
	lv_obj_set_size(ui->pageAirradio_cont_StepFM, 77, 182);
	lv_obj_set_scrollbar_mode(ui->pageAirradio_cont_StepFM, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->pageAirradio_cont_StepFM, LV_OBJ_FLAG_HIDDEN);

	//Write style for pageAirradio_cont_StepFM, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->pageAirradio_cont_StepFM, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->pageAirradio_cont_StepFM, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->pageAirradio_cont_StepFM, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->pageAirradio_cont_StepFM, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->pageAirradio_cont_StepFM, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->pageAirradio_cont_StepFM, 197, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->pageAirradio_cont_StepFM, lv_color_hex(0x314760), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->pageAirradio_cont_StepFM, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->pageAirradio_cont_StepFM, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->pageAirradio_cont_StepFM, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->pageAirradio_cont_StepFM, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->pageAirradio_cont_StepFM, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->pageAirradio_cont_StepFM, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes pageAirradio_btnm_StepFM
	ui->pageAirradio_btnm_StepFM = lv_btnmatrix_create(ui->pageAirradio_cont_StepFM);
	static const char *pageAirradio_btnm_StepFM_text_map[] = {"10", "\n", "50", "\n", "100", "\n", "200", "",};
	lv_btnmatrix_set_map(ui->pageAirradio_btnm_StepFM, pageAirradio_btnm_StepFM_text_map);
	lv_obj_set_pos(ui->pageAirradio_btnm_StepFM, 7, 9);
	lv_obj_set_size(ui->pageAirradio_btnm_StepFM, 59, 159);
	lv_obj_add_flag(ui->pageAirradio_btnm_StepFM, LV_OBJ_FLAG_HIDDEN);

	//Write style for pageAirradio_btnm_StepFM, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->pageAirradio_btnm_StepFM, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->pageAirradio_btnm_StepFM, 31, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->pageAirradio_btnm_StepFM, lv_color_hex(0xc9c9c9), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->pageAirradio_btnm_StepFM, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->pageAirradio_btnm_StepFM, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->pageAirradio_btnm_StepFM, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->pageAirradio_btnm_StepFM, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->pageAirradio_btnm_StepFM, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_row(ui->pageAirradio_btnm_StepFM, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_column(ui->pageAirradio_btnm_StepFM, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->pageAirradio_btnm_StepFM, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->pageAirradio_btnm_StepFM, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for pageAirradio_btnm_StepFM, Part: LV_PART_ITEMS, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->pageAirradio_btnm_StepFM, 1, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->pageAirradio_btnm_StepFM, 255, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->pageAirradio_btnm_StepFM, lv_color_hex(0xc9c9c9), LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->pageAirradio_btnm_StepFM, LV_BORDER_SIDE_FULL, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->pageAirradio_btnm_StepFM, lv_color_hex(0xffffff), LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->pageAirradio_btnm_StepFM, &lv_font_montserratMedium_16, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->pageAirradio_btnm_StepFM, 255, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->pageAirradio_btnm_StepFM, 4, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->pageAirradio_btnm_StepFM, 255, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->pageAirradio_btnm_StepFM, lv_color_hex(0x2195f6), LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->pageAirradio_btnm_StepFM, LV_GRAD_DIR_NONE, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->pageAirradio_btnm_StepFM, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);

	//The custom code of pageAirradio.
	

	//Update current screen layout.
	lv_obj_update_layout(ui->pageAirradio);

	//Init events for screen.
	events_init_pageAirradio(ui);
}
