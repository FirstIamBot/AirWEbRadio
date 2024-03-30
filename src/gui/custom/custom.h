/*
* Copyright 2023 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef __CUSTOM_H_
#define __CUSTOM_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"
typedef enum
{
    ebandIDx = 1, // Выбор диапазона LW-0,MW-1, Sw-2, FM-3 
    eModIdx = 2,  // Выбор модуляции AM-0, FM-1, LSB-2, USB-3, SSB-4
    eStepFM = 3,  // Шаг перестройки FM
    eStepAM = 4,  // Шаг перестройки AM
    eBandWFM = 5, // Полоса пропускания FM
    eBandWAM = 6, // Полоса пропускания AM
    eBandWSSB = 7,// Полоса пропускания SSB
    eStepUP = 8,  // Перестройка вверх
    eStepDown = 9,// Перестройка вниз
    eRSSI = 10,
    eSNR = 11,
    eslider_vol = 12 // Громкость 
} DataDescription_t;
// Структура данных помещаемых в очередь
typedef struct
{
    bool State;
    int ucValue;
    DataDescription_t eDataDescription;
} Data_GUI_Air;


void custom_init(lv_ui *ui);


#ifdef __cplusplus
}
#endif
#endif /* EVENT_CB_H_ */
