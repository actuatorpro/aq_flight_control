/*
    This file is part of AutoQuad.

    AutoQuad is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    AutoQuad is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with AutoQuad.  If not, see <http://www.gnu.org/licenses/>.

    Copyright © 2011, 2012, 2013  Bill Nesbitt
*/

#ifndef _spi_h
#define _spi_h

#include "digital.h"

#define SPI_BAUD_MASK		    (~((int16_t)0b111<<3))

#define SPI_SLOTS		    5

typedef void spiCallback_t(int);

typedef struct {
    digitalPin *cs;
    uint16_t baud;
    spiCallback_t *callback;
    volatile uint32_t *flag;
    uint8_t interface;
} spiClient_t;

typedef struct {
    uint16_t size;
    uint32_t rxBuf;
    uint32_t txBuf;
    spiClient_t *client;
} spiSlot_t;

typedef struct {
    SPI_TypeDef *spi;
    DMA_Stream_TypeDef *rxDMAStream;
    DMA_Stream_TypeDef *txDMAStream;
    spiSlot_t slots[SPI_SLOTS];
    volatile uint8_t head, tail;
    volatile uint8_t txRunning;
    uint8_t initialized;
} spiStruct_t;

extern spiStruct_t spiData[];

extern uint8_t spiWriteByte(spiClient_t *spi, uint8_t val);
extern spiClient_t *spiClientInit(SPI_TypeDef *spi, uint16_t baud, GPIO_TypeDef *csPort, uint16_t csPin, volatile uint32_t *flag, spiCallback_t *callback);
extern void spiChangeBaud(spiClient_t *spi, uint16_t baud);
extern void spiChangeCallback(spiClient_t *client, spiCallback_t *callback);
extern void spiTransaction(spiClient_t *client, void *rxBuf, void *txBuf, uint16_t size);

#endif