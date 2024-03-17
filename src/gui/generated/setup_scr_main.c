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



void setup_scr_main(lv_ui *ui)
{
	//Write codes main
	ui->main = lv_obj_create(NULL);
	lv_obj_set_size(ui->main, 320, 240);
	lv_obj_set_scrollbar_mode(ui->main, LV_SCROLLBAR_MODE_OFF);

	//Write style for main, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->main, 242, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->main, lv_color_hex(0x0b082e), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->main, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes main_btnm_1
	ui->main_btnm_1 = lv_btnmatrix_create(ui->main);
	static const char *main_btnm_1_text_map[] = {"1", "2", "3", "0", "0", "0", "\n", "4", "5", "6", "0", "0", "\n", "7", "8", "9", "0", "\n", "Prev", "Band", "Next", "",};
	lv_btnmatrix_set_map(ui->main_btnm_1, main_btnm_1_text_map);
	lv_obj_set_pos(ui->main_btnm_1, 8, 80);
	lv_obj_set_size(ui->main_btnm_1, 305, 154);

	//Write style for main_btnm_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->main_btnm_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->main_btnm_1, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->main_btnm_1, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->main_btnm_1, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->main_btnm_1, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_row(ui->main_btnm_1, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_column(ui->main_btnm_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->main_btnm_1, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->main_btnm_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->main_btnm_1, lv_color_hex(0x111010), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->main_btnm_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for main_btnm_1, Part: LV_PART_ITEMS, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->main_btnm_1, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->main_btnm_1, lv_color_hex(0x0c2b49), LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->main_btnm_1, &lv_font_Abel_regular_20, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->main_btnm_1, 255, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->main_btnm_1, 4, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->main_btnm_1, 255, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->main_btnm_1, lv_color_hex(0x93e3ff), LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->main_btnm_1, LV_GRAD_DIR_NONE, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->main_btnm_1, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);

	//Write style for main_btnm_1, Part: LV_PART_ITEMS, State: LV_STATE_PRESSED.
	lv_obj_set_style_border_width(ui->main_btnm_1, 0, LV_PART_ITEMS|LV_STATE_PRESSED);
	lv_obj_set_style_text_color(ui->main_btnm_1, lv_color_hex(0xffffff), LV_PART_ITEMS|LV_STATE_PRESSED);
	lv_obj_set_style_text_font(ui->main_btnm_1, &lv_font_Abel_regular_20, LV_PART_ITEMS|LV_STATE_PRESSED);
	lv_obj_set_style_text_opa(ui->main_btnm_1, 255, LV_PART_ITEMS|LV_STATE_PRESSED);
	lv_obj_set_style_radius(ui->main_btnm_1, 4, LV_PART_ITEMS|LV_STATE_PRESSED);
	lv_obj_set_style_bg_opa(ui->main_btnm_1, 255, LV_PART_ITEMS|LV_STATE_PRESSED);
	lv_obj_set_style_bg_color(ui->main_btnm_1, lv_color_hex(0x93e3ff), LV_PART_ITEMS|LV_STATE_PRESSED);
	lv_obj_set_style_bg_grad_dir(ui->main_btnm_1, LV_GRAD_DIR_NONE, LV_PART_ITEMS|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_width(ui->main_btnm_1, 2, LV_PART_ITEMS|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_color(ui->main_btnm_1, lv_color_hex(0x93e3ff), LV_PART_ITEMS|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_opa(ui->main_btnm_1, 255, LV_PART_ITEMS|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_spread(ui->main_btnm_1, 2, LV_PART_ITEMS|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_ofs_x(ui->main_btnm_1, 0, LV_PART_ITEMS|LV_STATE_PRESSED);
	lv_obj_set_style_shadow_ofs_y(ui->main_btnm_1, 1, LV_PART_ITEMS|LV_STATE_PRESSED);

	//Write codes main_label_2
	ui->main_label_2 = lv_label_create(ui->main);
	lv_label_set_text(ui->main_label_2, "Label");
	lv_label_set_long_mode(ui->main_label_2, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->main_label_2, 24, 18);
	lv_obj_set_size(ui->main_label_2, 194, 52);

	//Write style for main_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->main_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->main_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->main_label_2, lv_color_hex(0x04b2ee), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->main_label_2, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->main_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->main_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->main_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->main_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->main_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->main_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->main_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->main_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->main_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->main_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//The custom code of main.
	

	//Update current screen layout.
	lv_obj_update_layout(ui->main);

	//Init events for screen.
	events_init_main(ui);
}
