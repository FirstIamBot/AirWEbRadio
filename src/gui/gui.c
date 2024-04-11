#include "gui.h"
#include "test/gui_meter.h"
#include "test/lv_test.h"
#include "test/gui_scrol.h"

#include "Arduino.h"



lv_ui guider_ui;

/**
 * @ingroup group18 Covert numbers to char array
 * @brief Converts a number to a char array
 * @details It is useful to mitigate memory space used by functions like sprintf or other generic similar functions
 * @details You can use it to format frequency using decimal or thousand separator and also to convert small numbers.
 *
 * @param value  value to be converted
 * @param strValue char array that will be receive the converted value
 * @param len final string size (in bytes)
 * @param dot the decimal or thousand separator position
 * @param separator symbol "." or ","
 * @param remove_leading_zeros if true removes up to two leading zeros (default is true)
 */
void convertToChar(uint16_t value, char *strValue, uint8_t len, uint8_t dot, uint8_t separator, bool remove_leading_zeros)
{
    char d;
    for (int i = (len - 1); i >= 0; i--)
    {
        d = value % 10;
        value = value / 10;
        strValue[i] = d + 48;
    }
    strValue[len] = '\0';
    if (dot > 0)
    {
        for (int i = len; i >= dot; i--)
        {
            strValue[i + 1] = strValue[i];
        }
        strValue[dot] = separator;
    }

    if (remove_leading_zeros)
    {
        if (strValue[0] == '0')
        {
            strValue[0] = ' ';
            if (strValue[1] == '0')
                strValue[1] = ' ';
        }
    }
}


void awgui(void)
{
    setup_ui(&guider_ui);
    events_init(&guider_ui);
    custom_init(&guider_ui);

}
void awgui_reload(Data_Air_GUI data){

    char valFreq[10];

    switch (data.eDataDescription)
    {
        case eFreq:
            lv_label_set_text(guider_ui.pageAirradio_label_Freq, data.vcFreq);
            lv_label_set_text(guider_ui.pageAirradio_label_FreqRange, data.vcFreqRange);
            lv_label_set_text(guider_ui.pageAirradio_label_mono, data.vcStereoMono);
            
            lv_label_set_text(guider_ui.pageAirradio_label_rssi_val, data.vcRSSI);
            lv_label_set_text(guider_ui.pageAirradio_label_snr_val, data.vcSNR);
            break;
        case eStatussi4735:
            lv_label_set_text(guider_ui.pageAirradio_label_rssi_val, data.vcRSSI);
            lv_label_set_text(guider_ui.pageAirradio_label_snr_val, data.vcSNR);
            //lv_label_set_text(guider_ui.pageAirradio_label_wb_val, data.vcBW);
            //lv_label_set_text(guider_ui.pageAirradio_label_step_val, data.vcStep);
            break;
        default:
            break;
    }
}