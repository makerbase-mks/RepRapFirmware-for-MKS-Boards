#ifndef FLY_H
#define FLY_H

#include "../Pins_STM32.h"



constexpr PinEntry PinTable_FLY_F407ZG[] =
{
    //Thermistors
    {PA_0, PinCapability::ainrw, "e0temp,t0"},
    {PC_1, PinCapability::ainrw, "e1temp,t1"},
    {PC_0, PinCapability::ainrw, "e2temp,t2"},
    {PF_10, PinCapability::ainrw, "e3temp,t3"},
    {PF_5, PinCapability::ainrw, "e4temp,t4"},
    {PF_4, PinCapability::ainrw, "e5temp,t5"},
    {PF_3, PinCapability::ainrw, "bedtemp,tb"},

    //Endstops
    {PC_3, PinCapability::rw, "xmin,xstop"},
    {PC_2, PinCapability::rw, "xmax,xstopmax"},
    {PF_2, PinCapability::rw, "ymin,ystop"},
    {PF_3, PinCapability::rw, "ymax,ystopmax"},
    {PF_0, PinCapability::rw, "zmin,zstop"},
    {PC_15, PinCapability::rw, "zmax,zstopmax"},
    {PC_14, PinCapability::rwpwm, "z3"},
    {PA_3, PinCapability::rwpwm, "dljc"},
	
    //Heaters and Fans (Big and Small Mosfets}
    {PE_2,  PinCapability::wpwm, "bed,hbed" },
    {PF_7,  PinCapability::wpwm, "e0heat,he0" },
    {PF_6,  PinCapability::wpwm, "e1heat,he1" },
    {PE_6,  PinCapability::wpwm, "e2heat,he2" },
    {PE_5,  PinCapability::wpwm, "e3heat,he3" },
    {PE_4,  PinCapability::wpwm, "e4heat,he4" },
    {PE_3,  PinCapability::wpwm, "e5heat,he5" },
    
    {PE_8,  PinCapability::wpwm, "fan0,fan" },
    {PF_9,  PinCapability::wpwm, "fan1" },
    {PA_2,  PinCapability::wpwm, "fan2" },
    {PA_1,  PinCapability::wpwm, "fan3" },
    {PE_13,  PinCapability::wpwm, "fan4" },
    {PB_11,  PinCapability::wpwm, "fan5" },

    // Servo
    {PE_11,  PinCapability::wpwm, "servo0" },

    //EXP1
    {PB_10, PinCapability::rwpwm, "PB10"},
    {PE_14, PinCapability::rwpwm, "PE14"},
    {PE_10, PinCapability::rwpwm, "PE10"},
    {PE_8, PinCapability::rwpwm, "PE8"},
    {PE_15, PinCapability::rwpwm, "PE15"},
    {PE_12, PinCapability::rwpwm, "PE12"},
    {PE_9, PinCapability::rwpwm, "PE9"},
    {PE_7, PinCapability::rwpwm, "PE7"},

    //EXP2
    {PB_14, PinCapability::rwpwm, "PB14"},
    {PB_13, PinCapability::rwpwm, "PB13"},
    {PC_5, PinCapability::rwpwm, "PC5"},
    {PC_4, PinCapability::rwpwm, "PC4"},
    {PF_11, PinCapability::rwpwm, "PF11"},
    {PB_15, PinCapability::rwpwm, "PB15"},
    {PB_2, PinCapability::rwpwm, "PB2"},

	//SD
	{PC_13, PinCapability::rwpwm, "SDCD"},
	{PC_9, PinCapability::rwpwm, "SDD1"},
	{PC_8, PinCapability::rwpwm, "SDD0"},
	{PC_12, PinCapability::rwpwm, "SDSCK"},
	{PD_2, PinCapability::rwpwm, "SDCMD"},
	{PC_11, PinCapability::rwpwm, "SDD3"},
	{PC_10, PinCapability::rwpwm, "SDD2"},

	// UART
	{PA_9, PinCapability::rwpwm, "TX1"},
	{PA_10, PinCapability::rwpwm, "RX1"},
};

constexpr BoardDefaults fly_f407zg_Defaults = {
	9,											// Number of drivers
    {PE_1, PG_12,  PD_7, PD_4,  PD_0, PG_8, PG_5, PG_2, PD_9},   	//enablePins
    {PB_9, PB_8, PA_8, PC_7,  PC_6, PD_15, PD_14, PD_13, PD_12},	//stepPins
    {PE_0, PG_11, PD_6, PD_3,  PA_15, PG_7, PG_4, PD_11, PD_8},    	//dirPins
#if TMC_SOFT_UART
    {PG_13, PG_10, PD_5, PD_1,
#if STARTUP_DELAY
    // Avoid clash with jtag pins
    NoPin,
#else
    PA_14,
#endif
     PG_6, PG_3, PD_10, PB_12},                 //uartPins
    9,                                      	// Smart drivers
#endif
    0                                       	//digiPot Factor
};


constexpr PinEntry PinTable_FLY_E3[] =
{


    //Thermistors
    {PA_4, PinCapability::ainrw, "e0temp,t0"},
    {PA_3, PinCapability::ainrw, "bedtemp,tb"},

    //Endstops
    {PA_2, PinCapability::rw, "xmin,xstop"},
    {PA_1, PinCapability::rw, "ymin,ystop"},
    {PC_5, PinCapability::rw, "zmin,zstop"},

	// Servo
    {PB_0,  PinCapability::wpwm, "servo0" },

   // Porbe
    {PC_4, PinCapability::rwpwm, "probe"},
	
    //Heaters and Fans (Big and Small Mosfets}
    {PA_0,  PinCapability::wpwm, "bed,hbed" },
    {PA_5,  PinCapability::wpwm, "e0heat,he0" },
    {PA_7,  PinCapability::wpwm, "fan0,fan" },
    {PA_6,  PinCapability::wpwm, "fan1" },



    //EXP1
    {PE_12, PinCapability::rwpwm, "beep"},
    {PE_11, PinCapability::rwpwm, "btnenc"},
    {PE_10, PinCapability::rwpwm, "btnen1"},
    {PE_9, PinCapability::rwpwm, "btnen2"},
    {PE_8, PinCapability::rwpwm, "lcdd4"},
    {PE_7, PinCapability::rwpwm, "lcdrs"},
    {PB_1, PinCapability::rwpwm, "lcden"},

	//SD
	{PA_15, PinCapability::rwpwm, "SDCD"},
	{PC_9, PinCapability::rwpwm, "SDD1"},
	{PC_8, PinCapability::rwpwm, "SDD0"},
	{PC_12, PinCapability::rwpwm, "SDSCK"},
	{PD_2, PinCapability::rwpwm, "SDCMD"},
	{PC_11, PinCapability::rwpwm, "SDD3"},
	{PC_10, PinCapability::rwpwm, "SDD2"},

	// UART
	{PA_9, PinCapability::rwpwm, "TX1"},
	{PA_10, PinCapability::rwpwm, "RX1"},

    // WIFI UART	
	{PD_8, PinCapability::rwpwm, "PD8"},
	{PD_9, PinCapability::rwpwm, "PD9"},	
	
    //WIFI
    {PE_13, PinCapability::rwpwm, "PE13"},
    {PE_14, PinCapability::rwpwm, "PE14"},
    {PE_15, PinCapability::rwpwm, "PE15"},

    //soft spi 
    {PC_0, PinCapability::rwpwm, "PC0"},
    {PC_1, PinCapability::rwpwm, "PC1"},
    {PC_2, PinCapability::rwpwm, "PC2"},
    {PC_3, PinCapability::rwpwm, "PC3"},
    {PC_7, PinCapability::rwpwm, "PC7"},

    //Signal light
     {PA_8, PinCapability::rwpwm, "PA8"},

    //FPC
    {PB_10, PinCapability::rwpwm, "FPC1"},
    {PB_11, PinCapability::rwpwm, "FPC2"},
    {PD_10, PinCapability::rwpwm, "FPC3"},
    {PD_11, PinCapability::rwpwm, "FPC4"},
    {PD_12, PinCapability::rwpwm, "FPC5"},
    {PD_13, PinCapability::rwpwm, "FPC6"},
    {PD_14, PinCapability::rwpwm, "FPC7"},
    {PD_15, PinCapability::rwpwm, "FPC8"},
    {PC_6, PinCapability::rwpwm, "FPC9"},
    {PD_0, PinCapability::rwpwm, "FPC10"},
    {PD_1, PinCapability::rwpwm, "FPC11"},


};

constexpr BoardDefaults fly_e3_Defaults = {
	4,											// Number of drivers
    {PC_15, PE_5, PE_1, PB_5},   	//enablePins
    {PC_13, PE_3, PB_9, PB_3},	    //stepPins
    {PC_14, PE_4, PE_0, PB_4},    	//dirPins
#if TMC_SOFT_UART
    {PE_6, PE_2, PB_8, PD_7},             
	 4, 			                         //uartPins                                          	// Smart drivers
#endif
    0  

};


constexpr PinEntry PinTable_FLY_CDYV2[] =
{


    //Thermistors
    {PA_3, PinCapability::ainrw, "e0temp,t0"},
    {PC_4, PinCapability::ainrw, "e1temp,t1"},
    {PC_5, PinCapability::ainrw, "e2temp,t2"},
    {PB_1, PinCapability::ainrw, "bedtemp,tb"},

    //Endstops
    {PC_7, PinCapability::rw, "xmin,xstop"},
    {PC_6, PinCapability::rw, "xmax,xstopmax"},
    {PD_11, PinCapability::rw, "ymin,ystop"},
    {PD_10, PinCapability::rw, "ymax,ystopmax"},
    {PB_10, PinCapability::rw, "zmin,zstop"},
    {PB_11, PinCapability::rw, "zmax,zstopmax"},

	// Servo
    {PE_6,  PinCapability::wpwm, "servo0" },

   // Probe
    {PC_2, PinCapability::rwpwm, "probe"},
	
    //Heaters and Fans (Big and Small Mosfets}
    {PB_0,  PinCapability::wpwm, "bed,hbed" },
    {PD_12,  PinCapability::wpwm, "e0heat,he0" },
    {PD_13,  PinCapability::wpwm, "e1heat,he1" },
    {PD_14,  PinCapability::wpwm, "e2heat,he2" },
    {PA_0,  PinCapability::wpwm, "fan0,fan" },
    {PA_1,  PinCapability::wpwm, "fan1" },
    {PA_2,  PinCapability::wpwm, "fan2" },


    //EXP1
    // {PE_12, PinCapability::rwpwm, "beep"},
    // {PE_11, PinCapability::rwpwm, "btnenc"},
    // {PE_10, PinCapability::rwpwm, "btnen1"},
    // {PE_9, PinCapability::rwpwm, "btnen2"},
    // {PE_8, PinCapability::rwpwm, "lcdd4"},
    // {PE_7, PinCapability::rwpwm, "lcdrs"},
    // {PB_1, PinCapability::rwpwm, "lcden"},

	//SD
	{PC_9, PinCapability::rwpwm, "SDD1"},
	{PC_8, PinCapability::rwpwm, "SDD0"},
	{PC_12, PinCapability::rwpwm, "SDSCK"},
	{PD_2, PinCapability::rwpwm, "SDCMD"},
	{PC_11, PinCapability::rwpwm, "SDD3"},
	{PC_10, PinCapability::rwpwm, "SDD2"},

	// UART
	{PA_9, PinCapability::rwpwm, "TX1"},
	{PA_10, PinCapability::rwpwm, "RX1"},

    // WIFI UART	
	{PD_8, PinCapability::rwpwm, "PD8"},
	{PD_9, PinCapability::rwpwm, "PD9"},	
	
    //WIFI
    {PE_10, PinCapability::rwpwm, "PE10"},
    {PE_11, PinCapability::rwpwm, "PE11"},
    {PE_12, PinCapability::rwpwm, "PE12"},

    //spi 1  (SD,MAX311865,MAX6675)
    {PA_4, PinCapability::rwpwm, "SDCS"},
    {PA_5, PinCapability::rwpwm, "PA5"},
    {PA_6, PinCapability::rwpwm, "PA6"},
    {PA_7, PinCapability::rwpwm, "PA7"},
    {PE_7, PinCapability::rwpwm, "PE7,SPI1CS1"},  
    {PE_8, PinCapability::rwpwm, "PE8,SPI1CS2"},

    //spi 3  (MOT TMC2130 TMC5160)
    {PB_3, PinCapability::rwpwm, "PB3"},
    {PB_4, PinCapability::rwpwm, "PB4"},
    {PB_5, PinCapability::rwpwm, "PB5"},

    //Signal light   Neopixel
    {PD_15, PinCapability::rwpwm, "PD15"},

    //Laser 
    {PB_9, PinCapability::rwpwm, "PB9,Laser"},



};

constexpr BoardDefaults fly_cdyv2_Defaults = {
	6,											// Number of drivers
    {PC_1, PC_14, PB_8, PD_7, PD_4, PD_0},   	//enablePins
    {PE_5, PE_4, PE_3, PE_2, PE_1, PE_0},	    //stepPins
    {PC_0, PC_13, PB_7, PD_6, PD_3, PA_15},    	//dirPins
#if TMC_SOFT_UART
    {PC_15, PA_8, PB_6, PD_5, PD_1, PE_9},             
	 6, 			                         //uartPins                                          	// Smart drivers
#endif
    0  

};

#endif