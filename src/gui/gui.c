#include "gui.h"

#include "test/gui_meter.h"
#include "test/lv_test.h"
#include "test/gui_scrol.h"


lv_ui guider_ui;

void awgui(void)
{
    setup_ui(&guider_ui);
    events_init(&guider_ui);
    custom_init(&guider_ui);
}