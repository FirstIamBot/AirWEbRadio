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
//=================  Структура данных помещаемых в очередь  ====================================
typedef enum
{
    ebandIDx = 1, // Выбор диапазона LW-0,MW-1, Sw-2, FM-3 
    eModIdx = 2,  // Выбор модуляции AM-0, FM-1, LSB-2, USB-3, SSB-4
    eStepFM = 3,  // Шаг перестройки FM
    eStepAM = 4,  // Шаг перестройки AM
    eBandWFM = 5, // Полоса пропускания FM
                                        //  0  Automatically select proper channel filter (Default) |
                                        //  1  Force wide (110 kHz) channel filter |
                                        //  2  Force narrow (84 kHz) channel filter |
                                        //  3  Force narrower (60 kHz) channel filter |
                                        //  4  Force narrowest (40 kHz) channel filter |
    eBandWAM = 6, // Полоса пропускания AM  0 = 6 kHz Bandwidth
                                        //  1 = 4 kHz Bandwidth
                                        //  2 = 3 kHz Bandwidth
                                        //  3 = 2 kHz Bandwidth
                                        //  4 = 1 kHz Bandwidth
                                        // 5 = 1.8 kHz Bandwidth
                                        // 6 = 2.5 kHz Bandwidth, gradual roll off
    eBandWSSB = 7,// Полоса пропускания SSB
    eStepUP = 8,  // Перестройка вверх
    eStepDown = 9,// Перестройка вниз
    eSeekUP = 10,  // Перестройка вверх
    eSeekDown = 11,// Перестройка вниз
    eslider_vol = 12 // Громкость 
} DataDescription_t;
//================  Структура данных помещаемых в очередь ===========================
// 
typedef struct
{
    bool State;             //  Статус Структуры, false-изменений не было, true-изменений не было
    int ucValue;            // Значение Элемента
    DataDescription_t eDataDescription;  // название Элемента
} Data_GUI_Air;

typedef enum
{
    eEmpty = 0,
    eFreq = 1,  // Значение частоты
    eStatussi4735 = 2
} AirWebDescription_t;

typedef struct
{
    bool State;         //  Статус Структуры, false-изменений не было, true-изменений не было
    uint16_t ucFreq;
    uint8_t ucSNR;       //  значение  
    uint8_t ucRSSI;      //  значение  
    uint8_t ucBW;        //  значение
    uint8_t ucStep;      //  значение
    uint8_t ucBand;
    char * vcFreq; // Текстовое значение 
    char * vcFreqRange; // Текстовое значение 
    char * vcStereoMono;// Текстовое значение
    char * vcSNR;       // Текстовое значение  
    char * vcRSSI;      // Текстовое значение  
    char * vcBW;        // Текстовое значение
    char * vcStep;      // Текстовое значение
    AirWebDescription_t eDataDescription;  // название Элемента
} Data_Air_GUI;
//==================================================================================================


void custom_init(lv_ui *ui);


#ifdef __cplusplus
}
#endif
#endif /* EVENT_CB_H_ */
