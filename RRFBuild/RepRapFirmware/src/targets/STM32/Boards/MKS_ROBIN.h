#ifndef MKS_ROBIN_H
#define MKS_ROBIN_H

#include "../Pins_STM32.h"

// MKS Robin Nnao V3 motherboard

constexpr PinEntry PinTable_MKS_ROBIN_NANO_v3_0[] =
{
    //Thermistors
    {PC_1, PinCapability::ainrw, "e0temp,th1"},//TH1
    {PC_0, PinCapability::ainrw, "bedtemp,TB"},//TB
    {PA_2, PinCapability::ainrw, "e1temp,th2"},//TH2

    //Endstops
    {PC_4,  PinCapability::rwpwm, "zstopmax,Z+"},//Z+
    {PC_8,  PinCapability::rwpwm, "zstop,Z-"},//Z-
	{PD_2,  PinCapability::rwpwm, "ystop,Y+"},//Y
    {PD_2,  PinCapability::rwpwm, "ystop,Y-"},//Y
    {PA_15, PinCapability::rwpwm, "xstop,X+"},//X
    {PA_15, PinCapability::rwpwm, "xstop,X-"},//X

    //Heaters and Fans
    {PA_0, PinCapability::rwpwm, "bed"},//H-BED
    {PE_5, PinCapability::rwpwm, "e0heat,e1"},//HE0
    {PB_0, PinCapability::rwpwm, "e1heat,e2"},//HE1
    {PB_1, PinCapability::rwpwm, "fan0,fan"},//FAN1
    {PC_14, PinCapability::rwpwm, "fan1,fan1"},//FAN2
	
	//servo
	{PA_8,  PinCapability::rwpwm, "servo0,Bltouch" },//Bltouch
 
    //Spare pins (also as LEDs)
    {PC_14, PinCapability::rwpwm, "FAN2,fan2"},
    
    //Exp1
    {PC_5,  PinCapability::rwpwm, "PC5"}, //BEEPER
	{PE_13, PinCapability::rwpwm, "PE13"},//BTN_ENC
    {PD_13, PinCapability::rwpwm, "PD13"},//LCD_EN
	{PC_6,  PinCapability::rwpwm, "PC6"}, //LCD_RS
    {PE_14, PinCapability::rwpwm, "PE14"},//LCD_D4
    {PE_15, PinCapability::rwpwm, "PE15"},//LCD_D5
	{PD_11, PinCapability::rwpwm, "PD11"},//LCD_D6
	{PD_10, PinCapability::rwpwm, "PD10"},//LCD_D7
    
    //Exp2
    {PA_6,  PinCapability::rwpwm, "PA6"},
	{PA_5,  PinCapability::rwpwm, "PA5"},
    {PE_8,  PinCapability::rwpwm, "PE8"},
	{PE_10, PinCapability::rwpwm, "PE10"},
    {PE_11, PinCapability::rwpwm, "PE11"},
	{PA_7,  PinCapability::rwpwm, "PA7"},
    {PE_12, PinCapability::rwpwm, "PE12"},
    
    //SD-SPI3
	{PD_12, PinCapability::rwpwm, "SD-DET"},
	{PC_9, PinCapability::rwpwm, "SD-CS"},
	{PC_10, PinCapability::rwpwm, "SD-SCK"},
	{PC_11, PinCapability::rwpwm, "SD-MISO"},
	{PC_12, PinCapability::rwpwm, "SD-MOSI"},

	//TMC-SPI Pins
	{PD_14,  PinCapability::rwpwm, "PD14"},
	{PD_0,  PinCapability::rwpwm, "PD0"},
	{PD_1,  PinCapability::rwpwm, "PD1"},

	//Robin WIFI
	{PA_9, PinCapability::rwpwm, "TX1"},
	{PA_10, PinCapability::rwpwm, "RX1"},
	{PC_15, PinCapability::rwpwm, "CS"},
	{PC_13, PinCapability::rwpwm, "IO0"},
	{PC_7, PinCapability::rwpwm, "IO1"},
	{PE_9, PinCapability::rwpwm, "RST"},
	{PB_13, PinCapability::rwpwm, "SCK"},
	{PC_2, PinCapability::rwpwm, "MISO"},
	{PC_3, PinCapability::rwpwm, "MOSI"},
	
	//Uart3
    {PB_10, PinCapability::rwpwm, "TX3"},
	{PB_11, PinCapability::rwpwm, "RX3"},	
	
	//Udisk
    {PB_14, PinCapability::rwpwm, "DM"},
	{PB_15, PinCapability::rwpwm, "DP"},
	
	//USB
    //{PA_11, PinCapability::rwpwm, "DM"},
	//{PA_12, PinCapability::rwpwm, "DP"},
    
};

constexpr BoardDefaults mks_robin_nano_v3_0_Defaults = {
    5,
    {PE_4,  PE_1, PB_8, PB_3,  PA_3},   //enablePins
    {PE_3,  PE_0,  PB_5,  PD_6,   PD_15},    //stepPins
    {PE_2,  PB_9, PB_4, PD_3,  PA_1},   //dirPins
#if TMC_SOFT_UART
    {PD_5, PD_7, PD_4, PD_9, PD_8},    //uartPins
    5,                                      // Smart drivers
#endif
    0,                                 //digiPot Factor
};

#endif