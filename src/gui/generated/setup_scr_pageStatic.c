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



void setup_scr_pageStatic(lv_ui *ui)
{
	//Write codes pageStatic
	ui->pageStatic = lv_obj_create(NULL);
	lv_obj_set_size(ui->pageStatic, 320, 240);
	lv_obj_set_scrollbar_mode(ui->pageStatic, LV_SCROLLBAR_MODE_OFF);

	//Write style for pageStatic, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->pageStatic, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->pageStatic, lv_color_hex(0x7dcdb7), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->pageStatic, LV_GRAD_DIR_VER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->pageStatic, lv_color_hex(0x99edd7), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_main_stop(ui->pageStatic, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_stop(ui->pageStatic, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes pageStatic_btn_next_page
	ui->pageStatic_btn_next_page = lv_btn_create(ui->pageStatic);
	ui->pageStatic_btn_next_page_label = lv_label_create(ui->pageStatic_btn_next_page);
	lv_label_set_text(ui->pageStatic_btn_next_page_label, ">");
	lv_label_set_long_mode(ui->pageStatic_btn_next_page_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->pageStatic_btn_next_page_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->pageStatic_btn_next_page, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->pageStatic_btn_next_page, 272, 13);
	lv_obj_set_size(ui->pageStatic_btn_next_page, 38, 26);

	//Write style for pageStatic_btn_next_page, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->pageStatic_btn_next_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->pageStatic_btn_next_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->pageStatic_btn_next_page, 44, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->pageStatic_btn_next_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->pageStatic_btn_next_page, lv_color_hex(0x1b614f), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->pageStatic_btn_next_page, &lv_font_Antonio_Regular_19, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->pageStatic_btn_next_page, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->pageStatic_btn_next_page, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes pageStatic_label_title_static
	ui->pageStatic_label_title_static = lv_label_create(ui->pageStatic);
	lv_label_set_text(ui->pageStatic_label_title_static, "Progress-Static");
	lv_label_set_long_mode(ui->pageStatic_label_title_static, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->pageStatic_label_title_static, 80, 12);
	lv_obj_set_size(ui->pageStatic_label_title_static, 156, 30);

	//Write style for pageStatic_label_title_static, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->pageStatic_label_title_static, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->pageStatic_label_title_static, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->pageStatic_label_title_static, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->pageStatic_label_title_static, &lv_font_Antonio_Regular_10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->pageStatic_label_title_static, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->pageStatic_label_title_static, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->pageStatic_label_title_static, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->pageStatic_label_title_static, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->pageStatic_label_title_static, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->pageStatic_label_title_static, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->pageStatic_label_title_static, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->pageStatic_label_title_static, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->pageStatic_label_title_static, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->pageStatic_label_title_static, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes pageStatic_bar_1
	ui->pageStatic_bar_1 = lv_bar_create(ui->pageStatic);
	lv_obj_set_style_anim_time(ui->pageStatic_bar_1, 1000, 0);
	lv_bar_set_mode(ui->pageStatic_bar_1, LV_BAR_MODE_NORMAL);
	lv_bar_set_range(ui->pageStatic_bar_1, 0, 100);
	lv_bar_set_value(ui->pageStatic_bar_1, 0, LV_ANIM_OFF);
	lv_obj_set_pos(ui->pageStatic_bar_1, 80, 66);
	lv_obj_set_size(ui->pageStatic_bar_1, 158, 45);

	//Write style for pageStatic_bar_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->pageStatic_bar_1, 72, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->pageStatic_bar_1, lv_color_hex(0x58c100), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->pageStatic_bar_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->pageStatic_bar_1, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->pageStatic_bar_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for pageStatic_bar_1, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->pageStatic_bar_1, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->pageStatic_bar_1, lv_color_hex(0x26a000), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->pageStatic_bar_1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->pageStatic_bar_1, 8, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write codes pageStatic_tp_step_20
	ui->pageStatic_tp_step_20 = lv_textprogress_create(ui->pageStatic);
	lv_textprogress_set_range_value(ui->pageStatic_tp_step_20, 0, 100, 5, 0);
	lv_textprogress_set_decimal(ui->pageStatic_tp_step_20, 0);
	lv_textprogress_set_value(ui->pageStatic_tp_step_20, 0);
	lv_obj_set_pos(ui->pageStatic_tp_step_20, 47, 131);
	lv_obj_set_size(ui->pageStatic_tp_step_20, 66, 27);

	//Write style for pageStatic_tp_step_20, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_radius(ui->pageStatic_tp_step_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->pageStatic_tp_step_20, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->pageStatic_tp_step_20, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->pageStatic_tp_step_20, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->pageStatic_tp_step_20, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->pageStatic_tp_step_20, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->pageStatic_tp_step_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->pageStatic_tp_step_20, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->pageStatic_tp_step_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->pageStatic_tp_step_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->pageStatic_tp_step_20, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes pageStatic_slider_all
	ui->pageStatic_slider_all = lv_slider_create(ui->pageStatic);
	lv_slider_set_range(ui->pageStatic_slider_all, 0, 100);
	lv_slider_set_mode(ui->pageStatic_slider_all, LV_SLIDER_MODE_NORMAL);
	lv_slider_set_value(ui->pageStatic_slider_all, 0, LV_ANIM_OFF);
	lv_obj_set_pos(ui->pageStatic_slider_all, 80, 186);
	lv_obj_set_size(ui->pageStatic_slider_all, 162, 6);

	//Write style for pageStatic_slider_all, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->pageStatic_slider_all, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->pageStatic_slider_all, lv_color_hex(0x161616), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->pageStatic_slider_all, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->pageStatic_slider_all, 44, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->pageStatic_slider_all, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->pageStatic_slider_all, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for pageStatic_slider_all, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->pageStatic_slider_all, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->pageStatic_slider_all, lv_color_hex(0x04b100), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->pageStatic_slider_all, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->pageStatic_slider_all, 44, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style for pageStatic_slider_all, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->pageStatic_slider_all, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->pageStatic_slider_all, lv_color_hex(0x089d00), LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->pageStatic_slider_all, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->pageStatic_slider_all, 44, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Write codes pageStatic_tp_step_5
	ui->pageStatic_tp_step_5 = lv_textprogress_create(ui->pageStatic);
	lv_textprogress_set_range_value(ui->pageStatic_tp_step_5, 0, 100, 20, 0);
	lv_textprogress_set_decimal(ui->pageStatic_tp_step_5, 0);
	lv_textprogress_set_value(ui->pageStatic_tp_step_5, 0);
	lv_obj_set_pos(ui->pageStatic_tp_step_5, 126, 131);
	lv_obj_set_size(ui->pageStatic_tp_step_5, 66, 27);

	//Write style for pageStatic_tp_step_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_radius(ui->pageStatic_tp_step_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->pageStatic_tp_step_5, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->pageStatic_tp_step_5, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->pageStatic_tp_step_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->pageStatic_tp_step_5, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->pageStatic_tp_step_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->pageStatic_tp_step_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->pageStatic_tp_step_5, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->pageStatic_tp_step_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->pageStatic_tp_step_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->pageStatic_tp_step_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes pageStatic_tp_step_1
	ui->pageStatic_tp_step_1 = lv_textprogress_create(ui->pageStatic);
	lv_textprogress_set_range_value(ui->pageStatic_tp_step_1, 0, 100, 0, 0);
	lv_textprogress_set_decimal(ui->pageStatic_tp_step_1, 0);
	lv_textprogress_set_value(ui->pageStatic_tp_step_1, 0);
	lv_obj_set_pos(ui->pageStatic_tp_step_1, 206, 131);
	lv_obj_set_size(ui->pageStatic_tp_step_1, 66, 27);

	//Write style for pageStatic_tp_step_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_radius(ui->pageStatic_tp_step_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->pageStatic_tp_step_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->pageStatic_tp_step_1, &lv_font_montserratMedium_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->pageStatic_tp_step_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->pageStatic_tp_step_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->pageStatic_tp_step_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->pageStatic_tp_step_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->pageStatic_tp_step_1, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->pageStatic_tp_step_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->pageStatic_tp_step_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->pageStatic_tp_step_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes pageStatic_img_1
	ui->pageStatic_img_1 = lv_img_create(ui->pageStatic);
	lv_obj_add_flag(ui->pageStatic_img_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->pageStatic_img_1, &_nxp60_alpha_40x28);
	lv_img_set_pivot(ui->pageStatic_img_1, 50,50);
	lv_img_set_angle(ui->pageStatic_img_1, 0);
	lv_obj_set_pos(ui->pageStatic_img_1, 140, 75);
	lv_obj_set_size(ui->pageStatic_img_1, 40, 28);

	//Write style for pageStatic_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->pageStatic_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//The custom code of pageStatic.
	

	//Update current screen layout.
	lv_obj_update_layout(ui->pageStatic);

	//Init events for screen.
	events_init_pageStatic(ui);
}
