/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

typedef struct
{
  
	lv_obj_t *pageStatic;
	bool pageStatic_del;
	lv_obj_t *pageStatic_btn_next_page;
	lv_obj_t *pageStatic_btn_next_page_label;
	lv_obj_t *pageStatic_label_title_static;
	lv_obj_t *pageStatic_bar_1;
	lv_obj_t *pageStatic_tp_step_20;
	lv_obj_t *pageStatic_slider_all;
	lv_obj_t *pageStatic_tp_step_5;
	lv_obj_t *pageStatic_tp_step_1;
	lv_obj_t *pageStatic_img_1;
	lv_obj_t *pageAirradio;
	bool pageAirradio_del;
	lv_obj_t *pageAirradio_RDS;
	lv_obj_t *pageAirradio_btnm_Main;
	lv_obj_t *pageAirradio_up_step;
	lv_obj_t *pageAirradio_up_step_label;
	lv_obj_t *pageAirradio_down_step;
	lv_obj_t *pageAirradio_down_step_label;
	lv_obj_t *pageAirradio_label_mono;
	lv_obj_t *pageAirradio_label_FreqRange;
	lv_obj_t *pageAirradio_label_Freq;
	lv_obj_t *pageAirradio_label_step_val;
	lv_obj_t *pageAirradio_label_step_range;
	lv_obj_t *pageAirradio_label_step_name;
	lv_obj_t *pageAirradio_label_wb_name;
	lv_obj_t *pageAirradio_label_wb_range;
	lv_obj_t *pageAirradio_label_wb_val;
	lv_obj_t *pageAirradio_imgbtn_1;
	lv_obj_t *pageAirradio_imgbtn_1_label;
	lv_obj_t *pageAirradio_cont_StepAM;
	lv_obj_t *pageAirradio_btnm_StepAM;
	lv_obj_t *pageAirradio_cont_StepFM;
	lv_obj_t *pageAirradio_btnm_StepFM;
	lv_obj_t *pageAirradio_cont_BandWFM;
	lv_obj_t *pageAirradio_btnm_BandWFM;
	lv_obj_t *pageAirradio_cont_BandWSSB;
	lv_obj_t *pageAirradio_btnm_BandWSSB;
	lv_obj_t *pageAirradio_cont_BandWAM;
	lv_obj_t *pageAirradio_btnm_BandWAM;
	lv_obj_t *pageAirradio_cont_vol;
	lv_obj_t *pageAirradio_textprogress_vol;
	lv_obj_t *pageAirradio_slider_vol;
	lv_obj_t *pageAirradio_cont_Mod;
	lv_obj_t *pageAirradio_btnm_Mod;
	lv_obj_t *pageAirradio_label_rssi_val;
	lv_obj_t *pageAirradio_label_rrsi_name;
	lv_obj_t *pageAirradio_label_rssi_range;
	lv_obj_t *pageAirradio_label_snr_val;
	lv_obj_t *pageAirradio_label_snr_name;
	lv_obj_t *pageAirradio_label_snr_range;
	lv_obj_t *pageAirradio_cont_AGC;
	lv_obj_t *pageAirradio_textprogress_AGC;
	lv_obj_t *pageAirradio_slider_AGC;
	lv_obj_t *pageAirradio_cb_AGC;
  int global_language;
}lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui * ui);

void ui_init_style(lv_style_t * style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t ** new_scr, bool new_scr_del, bool * old_scr_del, ui_setup_scr_t setup_scr,
                           lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

void ui_move_animation(void * var, int32_t duration, int32_t delay, int32_t x_end, int32_t y_end, lv_anim_path_cb_t path_cb,
                       uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                       lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);

void ui_scale_animation(void * var, int32_t duration, int32_t delay, int32_t width, int32_t height, lv_anim_path_cb_t path_cb,
                        uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                        lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);

void ui_img_zoom_animation(void * var, int32_t duration, int32_t delay, int32_t zoom, lv_anim_path_cb_t path_cb,
                           uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                           lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);

void ui_img_rotate_animation(void * var, int32_t duration, int32_t delay, lv_coord_t x, lv_coord_t y, int32_t rotate,
                   lv_anim_path_cb_t path_cb, uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time,
                   uint32_t playback_delay, lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);

void init_scr_del_flag(lv_ui *ui);

void setup_ui(lv_ui *ui);


extern lv_ui guider_ui;
extern int global_language;


void setup_scr_pageStatic(lv_ui *ui);
void setup_scr_pageAirradio(lv_ui *ui);
LV_IMG_DECLARE(_nxp60_alpha_40x28);
LV_IMG_DECLARE(_vol_alpha_43x46);

LV_FONT_DECLARE(lv_font_Antonio_Regular_19)
LV_FONT_DECLARE(lv_font_montserratMedium_10)
LV_FONT_DECLARE(lv_font_Antonio_Regular_10)
LV_FONT_DECLARE(lv_font_montserratMedium_12)
LV_FONT_DECLARE(lv_font_montserratMedium_16)
LV_FONT_DECLARE(lv_font_montserratMedium_24)
LV_FONT_DECLARE(lv_font_montserratMedium_19)
LV_FONT_DECLARE(lv_font_montserratMedium_20)
LV_FONT_DECLARE(lv_font_montserratMedium_26)
LV_FONT_DECLARE(lv_font_montserratMedium_14)
LV_FONT_DECLARE(lv_font_montserratMedium_11)


#ifdef __cplusplus
}
#endif
#endif
