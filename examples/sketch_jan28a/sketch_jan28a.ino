extern "C" 
{
#include "eagle_soc.h"
#include "uart_register.h"
}
#include <Arduino.h>
#define UART_INV_MASK  (0x3f<<19)  
#define UART 1

void setup() {
    uint32_t baud = 3200000; // 800 Support
#ifdef INCLUDE_NEO_KHZ400_SUPPORT

    if ((_flagsPixels & NEO_SPDMASK) == NEO_KHZ400)
    {
        // 400 Support
        baud = 1600000;
    }

#endif

    Serial1.begin(baud, SERIAL_6N1, SERIAL_TX_ONLY);

    CLEAR_PERI_REG_MASK(UART_CONF0(UART), UART_INV_MASK);
    //SET_PERI_REG_MASK(UART_CONF0(UART), UART_TXD_INV);
    SET_PERI_REG_MASK(UART_CONF0(UART), (BIT(22)));

}

void loop() {
  // put your main code here, to run repeatedly:

}
