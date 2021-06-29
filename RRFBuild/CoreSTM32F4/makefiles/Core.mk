CORE_DIR = $(CORESTM_DIR)


#Core
CORE_SRC_DIRS  = cores cores/arduino cores/arduino/avr cores/arduino/stm32 cores/arduino/stm32/LL cores/arduino/stm32/usb cores/arduino/stm32/usb/cdc 
CORE_SRC_DIRS += system system/STM32F4xx system/Middlewares/ST/STM32_USB_Device_Library/Core/Inc system/Middlewares/ST/STM32_USB_Device_Library/Core/Src 
CORE_SRC_DIRS += system/Drivers/CMSIS/Device/ST/STM32F4xx/Include system/Drivers/CMSIS/Device/ST/STM32F4xx/Source
CORE_SRC_DIRS += system/Drivers/STM32F4xx_HAL_Driver/Inc system/Drivers/STM32F4xx_HAL_Driver/Src
CORE_SRC_DIRS += CMSIS/CMSIS/Core/Include system/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc
CORE_SRC_DIRS += variants/BIGTREE_SKR_PRO_1v1 libraries/ConfigurableUART libraries/SharedSPI libraries/PWM libraries/SDIO libraries/CRC32
#Core libraries
CORE_SRC_DIRS += libraries/Wire 
# libraries/SDCard libraries/SharedSPI libraries/SoftwarePWM libraries/ConfigurableUART
#mbed
#CORE_SRC_DIRS += cores/mbed/usb/hal cores/mbed/usb/TARGET_NXP cores/mbed/usb/USBDevice cores/mbed/usb/USBPhy
#CORE_SRC_DIRS += cores/mbed/usb/USBSerial cores/mbed/usb/utilities cores/mbed/platform

#CORE_SRC_DIRS += cores/smoothie

CORE_SRC = $(CORE_DIR) $(addprefix $(CORE_DIR)/, $(CORE_SRC_DIRS))
CORE_INCLUDES = $(addprefix -I, $(CORE_SRC))


#Additional Core Includes
#CORE_INCLUDES	+= -I$(CORE_DIR)/system/ExploreM3_lib/
#CORE_INCLUDES   += -I$(CORE_DIR)/system/CMSIS/CMSIS/Include/

#openlpc 
#CORE_INCLUDES  += -I$(CORE_DIR)/cores/lpcopen/inc

#Find all c and c++ files for Core
CORE_OBJ_SRC_C    += $(foreach src, $(CORE_SRC), $(wildcard $(src)/*.c))
CORE_OBJ_SRC_CXX   += $(foreach src, $(CORE_SRC), $(wildcard $(src)/*.cpp))
CORE_OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(CORE_OBJ_SRC_C)) $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(CORE_OBJ_SRC_CXX))
CORE_OBJS += $(BUILD_DIR)/CoreSTM32F4/cores/arduino/stm32/startup_stm32yyxx.o
