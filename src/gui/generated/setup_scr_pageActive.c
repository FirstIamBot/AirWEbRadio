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



void setup_scr_pageActive(lv_ui *ui)
{
	//Write codes pageActive
	ui->pageActive = lv_obj_create(NULL);
	lv_obj_set_size(ui->pageActive, 320, 240);
	lv_obj_set_scrollbar_mode(ui->pageActive, LV_SCROLLBAR_MODE_OFF);

	//Write style for pageActive, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->pageActive, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->pageActive, lv_color_hex(0x85e9cf), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->pageActive, LV_GRAD_DIR_VER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->pageActive, lv_color_hex(0x99cffb), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_main_stop(ui->pageActive, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_stop(ui->pageActive, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes pageActive_btn_pre_btn
	ui->pageActive_btn_pre_btn = lv_btn_create(ui->pageActive);
	ui->pageActive_btn_pre_btn_label = lv_label_create(ui->pageActive_btn_pre_btn);
	lv_label_set_text(ui->pageActive_btn_pre_btn_label, "<");
	lv_label_set_long_mode(ui->pageActive_btn_pre_btn_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->pageActive_btn_pre_btn_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->pageActive_btn_pre_btn, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->pageActive_btn_pre_btn, 8, 12);
	lv_obj_set_size(ui->pageActive_btn_pre_btn, 35, 24);

	//Write style for pageActive_btn_pre_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->pageActive_btn_pre_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->pageActive_btn_pre_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->pageActive_btn_pre_btn, 44, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->pageActive_btn_pre_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->pageActive_btn_pre_btn, lv_color_hex(0x005a4d), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->pageActive_btn_pre_btn, &lv_font_Antonio_Regular_19, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->pageActive_btn_pre_btn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->pageActive_btn_pre_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes pageActive_label_title_acticity
	ui->pageActive_label_title_acticity = lv_label_create(ui->pageActive);
	lv_label_set_text(ui->pageActive_label_title_acticity, "Progress-Activity");
	lv_label_set_long_mode(ui->pageActive_label_title_acticity, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->pageActive_label_title_acticity, 82, 9);
	lv_obj_set_size(ui->pageActive_label_title_acticity, 156, 30);

	//Write style for pageActive_label_title_acticity, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->pageActive_label_title_acticity, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->pageActive_label_title_acticity, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->pageActive_label_title_acticity, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->pageActive_label_title_acticity, &lv_font_Antonio_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->pageActive_label_title_acticity, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->pageActive_label_title_acticity, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->pageActive_label_title_acticity, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->pageActive_label_title_acticity, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->pageActive_label_title_acticity, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->pageActive_label_title_acticity, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->pageActive_label_title_acticity, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->pageActive_label_title_acticity, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->pageActive_label_title_acticity, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->pageActive_label_title_acticity, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes pageActive_textprogress_img_1
	ui->pageActive_textprogress_img_1 = lv_textprogress_create(ui->pageActive);
	lv_textprogress_set_range_value(ui->pageActive_textprogress_img_1, 0, 100, 80, 0);
	lv_textprogress_set_decimal(ui->pageActive_textprogress_img_1, 2);
	lv_textprogress_set_value(ui->pageActive_textprogress_img_1, 0);
	lv_obj_set_pos(ui->pageActive_textprogress_img_1, 118, 183);
	lv_obj_set_size(ui->pageActive_textprogress_img_1, 82, 30);

	//Write style for pageActive_textprogress_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_radius(ui->pageActive_textprogress_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->pageActive_textprogress_img_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->pageActive_textprogress_img_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->pageActive_textprogress_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->pageActive_textprogress_img_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->pageActive_textprogress_img_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->pageActive_textprogress_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->pageActive_textprogress_img_1, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->pageActive_textprogress_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->pageActive_textprogress_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->pageActive_textprogress_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes pageActive_img_1
	ui->pageActive_img_1 = lv_img_create(ui->pageActive);
	lv_obj_add_flag(ui->pageActive_img_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->pageActive_img_1, &_nxp200_alpha_133x94);
	lv_img_set_pivot(ui->pageActive_img_1, 50,50);
	lv_img_set_angle(ui->pageActive_img_1, 0);
	lv_obj_set_pos(ui->pageActive_img_1, 99, 73);
	lv_obj_set_size(ui->pageActive_img_1, 133, 94);

	//Write style for pageActive_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->pageActive_img_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes pageActive_btn_1
	ui->pageActive_btn_1 = lv_btn_create(ui->pageActive);
	ui->pageActive_btn_1_label = lv_label_create(ui->pageActive_btn_1);
	lv_label_set_text(ui->pageActive_btn_1_label, ">");
	lv_label_set_long_mode(ui->pageActive_btn_1_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->pageActive_btn_1_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->pageActive_btn_1, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->pageActive_btn_1, 267, 12);
	lv_obj_set_size(ui->pageActive_btn_1, 35, 24);

	//Write style for pageActive_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->pageActive_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->pageActive_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->pageActive_btn_1, 44, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->pageActive_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->pageActive_btn_1, lv_color_hex(0x005a4d), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->pageActive_btn_1, &lv_font_Antonio_Regular_19, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->pageActive_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->pageActive_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//The custom code of pageActive.
	

	//Update current screen layout.
	lv_obj_update_layout(ui->pageActive);

	//Init events for screen.
	events_init_pageActive(ui);
}
