/* FCE Ultra - NES/Famicom Emulator
 *
 * Copyright notice for this file:
 *  Copyright (C) 2002 Xodnizel
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "mapinc.h"

static uint8 latche, latcheinit;
static uint16 addrreg0, addrreg1;
static void(*WSync)(void);

static DECLFW(LatchWrite)
{
//  FCEU_printf("bs %04x %02x\n",A,V);
  latche=V;
  WSync();
}

static void LatchPower(void)
{
  latche=latcheinit;
  WSync();
  SetReadHandler(0x8000,0xFFFF,CartBR);
  SetWriteHandler(addrreg0,addrreg1,LatchWrite);
}

static void StateRestore(int version)
{
  WSync();
}

static void Latch_Init(CartInfo *info, void (*proc)(void), uint8 init, uint16 adr0, uint16 adr1)
{
  latcheinit=init;
  addrreg0=adr0;
  addrreg1=adr1;
  WSync=proc;
  info->Power=LatchPower;
  GameStateRestore=StateRestore;
  AddExState(&latche, 1, 0, "LATC");
}

//------------------ CPROM ---------------------------

static void CPROMSync(void)
{
  setchr4(0x0000,0);
  setchr4(0x1000,latche&3);
  setprg16(0x8000,0);
  setprg16(0xC000,1);
}

void CPROM_Init(CartInfo *info)
{
  Latch_Init(info, CPROMSync, 0, 0x8000, 0xFFFF);
}

//------------------ Map 184 ---------------------------

static void M184Sync(void)
{
  setchr4(0x0000,latche);
  setchr4(0x1000,latche>>4);
  setprg16(0x8000,0);
  setprg16(0xC000,1);
}

void Mapper184_Init(CartInfo *info)
{
  Latch_Init(info, M184Sync, 0, 0x6000, 0x7FFF);
}

//------------------ CNROM ---------------------------

static void CNROMSync(void)
{
  setchr8(latche&3);
  setprg16(0x8000,0);
  setprg16(0xC000,1);
}

void CNROM_Init(CartInfo *info)
{
  Latch_Init(info, CNROMSync, 0, 0x8000, 0xFFFF);
}

//------------------ ANROM ---------------------------

static void ANROMSync()
{
  setprg32(0x8000,latche&0xf);
  setmirror(MI_0+((latche>>4)&1));
  setchr8(0);
}

void ANROM_Init(CartInfo *info)
{
  Latch_Init(info, ANROMSync, 0, 0x8000, 0xFFFF);
}

//------------------ Map 70 ---------------------------

static void M70Sync()
{
  setprg16(0x8000,latche>>4);
  setprg16(0xc000,~0);
  setchr8(latche&0xf);
}

void Mapper70_Init(CartInfo *info)
{
  Latch_Init(info, M70Sync, 0, 0x8000, 0xFFFF);
}

//------------------ Map 152 ---------------------------

static void M152Sync()
{
  setprg16(0x8000,(latche>>4)&7);
  setprg16(0xc000,~0);
  setchr8(latche&0xf);
  setmirror(MI_0+((latche>>7)&1));         /* Saint Seiya...hmm. */
}

void Mapper152_Init(CartInfo *info)
{
  Latch_Init(info, M152Sync, 0, 0x8000, 0xFFFF);
}

//------------------ Map 78 ---------------------------
/* Should be two separate emulation functions for this "mapper".  Sigh.  URGE TO KILL RISING. */
static void M78Sync()
{
  setprg16(0x8000,(latche&7));
  setprg16(0xc000,~0);
  setchr8(latche>>4);
  setmirror(MI_0+((latche>>3)&1));
}

void Mapper78_Init(CartInfo *info)
{
  Latch_Init(info, M78Sync, 0, 0x8000, 0xFFFF);
}

//------------------ MHROM ---------------------------

static void MHROMSync(void)
{
  setprg32(0x8000,latche>>4);
  setchr8(latche&0xf);
}

void MHROM_Init(CartInfo *info)
{ 
  Latch_Init(info, MHROMSync, 0, 0x8000, 0xFFFF);
}

void Mapper140_Init(CartInfo *info)
{ 
  Latch_Init(info, MHROMSync, 0, 0x6000, 0x7FFF);
}

void Mapper240_Init(CartInfo *info)
{ 
  Latch_Init(info, MHROMSync, 0, 0x4020, 0x5FFF);
  // need SRAM.
}

//------------------ Map 87 ---------------------------

static void M87Sync(void)
{
  setprg16(0x8000,0);
  setprg16(0xC000,1);
  setchr8(latche>>1);
}

void Mapper87_Init(CartInfo *info)
{ 
  Latch_Init(info, M87Sync, ~0, 0x6000, 0xFFFF);
}

//------------------ Map 11 ---------------------------

static void M11Sync(void)
{
  setprg32(0x8000,latche&0xf);
  setchr8(latche>>4);
}

void Mapper11_Init(CartInfo *info)
{ 
  Latch_Init(info, M11Sync, 0, 0x8000, 0xFFFF);
}

void Mapper144_Init(CartInfo *info)
{ 
  Latch_Init(info, M11Sync, 0, 0x8001, 0xFFFF);
}

//------------------ UNROM ---------------------------

static void UNROMSync(void)
{
  setprg16(0x8000,latche);
  setprg16(0xc000,~0);
  setchr8(0);
}

void UNROM_Init(CartInfo *info)
{
  Latch_Init(info, UNROMSync, 0, 0x8000, 0xFFFF);
}

//------------------ Map 93 ---------------------------

static void SSUNROMSync(void)
{
  setprg16(0x8000,latche>>4);
  setprg16(0xc000,~0);
  setchr8(0);
}

void SUNSOFT_UNROM_Init(CartInfo *info)
{
  Latch_Init(info, SSUNROMSync, 0, 0x8000, 0xFFFF);
}

//------------------ Map 94 ---------------------------

static void M94Sync(void)
{
  setprg16(0x8000,latche>>2);
  setprg16(0xc000,~0);
  setchr8(0);
}

void Mapper94_Init(CartInfo *info)
{
  Latch_Init(info, M94Sync, 0, 0x8000, 0xFFFF);
}

//------------------ Map 180 ---------------------------

static void M180Sync(void)
{
  setprg16(0x8000,0);
  setprg16(0xc000,latche);
  setchr8(0);
}

void Mapper180_Init(CartInfo *info)
{
  Latch_Init(info, M180Sync, 0, 0x8000, 0xFFFF);
}

//------------------ Map 107 ---------------------------

static void M107Sync(void)
{
  setprg32(0x8000,(latche>>1)&3);
  setchr8(latche&7);
}

void Mapper107_Init(CartInfo *info)
{
  Latch_Init(info, M107Sync, ~0, 0x8000, 0xFFFF);
}

//------------------ Map 113 ---------------------------

static void M113Sync(void)
{
  setprg32(0x8000,(latche>>3)&7);
  setchr8(((latche>>3)&8)|(latche&7));
//  setmirror(latche>>7); // only for HES 6in1
}

void Mapper113_Init(CartInfo *info)
{
  Latch_Init(info, M113Sync, 0, 0x4100, 0x7FFF);
}

//------------------ A65AS ---------------------------

// actually, there is two cart in one... First have extra mirroring
// mode (one screen) and 32K bankswitching, second one have only
// 16 bankswitching mode and normal mirroring... But there is no any 
// correlations between modes and they can be used in one mapper code.

static void BMCA65ASSync(void)
{
  if(latche&0x40)
    setprg32(0x8000,(latche>>1)&0x0F);
  else
  {
    setprg16(0x8000,((latche&0x30)>>1)|(latche&7));
    setprg16(0xC000,((latche&0x30)>>1)|7);
  }
  setchr8(0);
  if(latche&0x80)
    setmirror(MI_0+(((latche>>5)&1)));
  else
    setmirror(((latche>>3)&1)^1);
}

void BMCA65AS_Init(CartInfo *info)
{
  Latch_Init(info, BMCA65ASSync, 0, 0x8000, 0xFFFF);
}

//------------------ NROM ---------------------------

#ifdef DEBUG_MAPPER
static DECLFW(WriteHandler)
{
 FCEU_printf("bs %04x %02x\n",A,V);
}
#endif

static void NROMPower(void)
{
  setprg16(0x8000,0);
  setprg16(0xC000,~0);
  setchr8(0);
  SetReadHandler(0x8000,0xFFFF,CartBR);
  #ifdef DEBUG_MAPPER
  SetWriteHandler(0x4020,0xFFFF,WriteHandler);
  #endif
}

void NROM_Init(CartInfo *info)
{
  info->Power=NROMPower;
}
