#include "spi.h"

void SPI_initMaster(void)
{
    /*Description: Ports directions
    SS(PB4)     = 1 (Output)    slave select line
    MOSI(PB5)   = 1 (Output)    Master output slave input
    MISO(PB6)   = 0 (Input)     Master input slave output
    Sck(PB7)    = 1 (Output)    Serial Clock line
     */
    DDRB |= (1 << PB4) | (1 << PB5) | (1 << PB7);
    DDRB &= ~((1 << PB6));
    /*
    Description: SPCR (SPI Control REG.)
    SPE      = 1 Enable SPI
    MSTR     = 1 Enable AS SPI Master Mode
    SPR1:0   = 00 Use FCPU/4 clock speed
    */
    SPCR = (1 << SPE) | (1 << MSTR);
}
void SPI_initSlave(void)
{
    /*Description: Ports directions
    SS(PB4)     = 0 (Input)    slave select line
    MOSI(PB5)   = 0 (Input)    Master Output slave input
    MISO(PB6)   = 1 (Output)     Master input slave Output
    Sck(PB7)    = 0 (Input)    Serial Clock line
     */
    DDRB |= (1 << PB6);
    DDRB &= ~((1 << PB4) | (1 << PB5) | (1 << PB7));
    /*
    Description: SPCR (SPI Control REG.)
    SPE      = 1 Enable SPI
    MSTR     = 0 Enable AS SPI Slave Mode
    */
    SPCR = (1 << SPE);
}
void SPI_sendByte(uint8 data)
{
    /*
    Description: SPdR (SPI Data REG.)
    Write data in data register
   */
    SPDR = data;
    /*
    Description: SPSR (SPI Status REG.)
    wait untill last serial transfer is complete
   */
    while (BIT_IS_CLEAR(SPSR, SPIF))
        ;
}
void SPI_sendString(const uint8 *str)
{
    /*Send bytes untill null terminator is found*/
    while (*str != '\0')
    {
        SPI_sendByte(*str);
        str++;
    }
}
uint8 SPI_recieveByte(void)
{
    /*
    Description: SPSR (SPI Status REG.)
    wait untill Data is fully recieved
   */
    while (BIT_IS_CLEAR(SPSR, SPIF))
        ;
    /*return data from SPI Data REG.*/
    return SPDR;
}
void SPI_recieveString(uint8 * const str)
{
    uint16 i = 0;
    /*put first recieved byte in string*/
    str[i] = SPI_recieveByte();
    /*loop untill a hash is found*/
    while (str[i] != '#')
    {
        i++;
        str[i] = SPI_recieveByte();
    }
    /*insert null terminator instaed of last hash*/
    str[i] = '\0';
}
