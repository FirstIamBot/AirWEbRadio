#ifndef GUI_H
#define GUI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "custom.h"
#include "gui_guider.h"
#include "events_init.h"

//extern Data_GUI_Air xReceivedGUItoSI4735;

void gui_meter(void);
void gui_bar(void);
void lv_test(void);
void awgui(void); 

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif