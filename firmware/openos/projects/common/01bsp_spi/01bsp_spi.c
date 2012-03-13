/**
\brief This program shows the use of the "spi" bsp module.

Since the bsp modules for different platforms have the same declaration, you
can use this project with any platform.

\author Thomas Watteyne <watteyne@eecs.berkeley.edu>, February 2012
*/

#include "stdint.h"
#include "board.h"
#include "spi.h"

/**
\brief The program starts executing here.
*/
int main(void)
{
   uint8_t              spi_tx_buffer[3];
   uint8_t              spi_rx_buffer[3];

   // initialize
   board_init();

   // prepare buffer to send over SPI
   spi_tx_buffer[0]     =  (0x40 | 0x1E);        // [b7]    RAM/Register : 0    (register)
                                                 // [b6]    Read/Write:    1    (read)
                                                 // [b5-0]  address:       0x1E (Manufacturer ID, Lower 16 Bit)
   spi_tx_buffer[1]     =  0x00;                 // send a SNOP strobe just to get the reg value
   spi_tx_buffer[2]     =  0x00;                 // send a SNOP strobe just to get the reg value

   printf("command %u,%u,%u \n",spi_tx_buffer[0],spi_tx_buffer[1],spi_tx_buffer[2] );
   // retrieve radio manufacturer ID over SPI
   spi_txrx(spi_tx_buffer,
            sizeof(spi_tx_buffer),
            SPI_BUFFER,
            spi_rx_buffer,
            sizeof(spi_rx_buffer),
            SPI_FIRST,
            SPI_LAST);
   printf("manufacturer id %u,%u,%u \n",spi_rx_buffer[0],spi_rx_buffer[1],spi_rx_buffer[2] );
   // sleep
   while(1) {
      board_sleep();
   }
}
