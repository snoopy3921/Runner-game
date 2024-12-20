##############################################################################
# @author: GaoKong
# @date:   05/2/2017
##############################################################################
#NOTE:
# Learn Makefiles at https://makefiletutorial.com/
# using find PATH -type d -print to list subdirectories recursively

# Utilitis define
Print = @echo "~"

# Name of build target ex: ak-base-kit-stm32l151-application.bin
NAME_MODULE = Runner-game
PROJECT = $(NAME_MODULE)

GCC_PATH		= $(HOME)/tools/gcc-arm-none-eabi-10.3-2021.10
PROGRAMER_PATH		= $(HOME)/tools/STM32CubeProgrammer/bin
OPENOCD_CFG_PATH	= /usr/local/share/openocd/scripts/board/stm32ldiscovery.cfg

ST_FLASH	= /usr/bin/st-flash
ST_UTIL		= /usr/bin/st-util
ST_INFO		= /usr/bin/st-info

# App start address, that need sync with declare in linker file and interrupt vector table.
APP_START_ADDR_VAL = 0x08000000
APP_ADDR_OPTION = -DAPP_START_ADDR=$(APP_START_ADDR_VAL)

# Define console baudrate, that is used to configure UART.
SYS_CONSOLE_BAUDRATE = 115200
CONSOLE_BAUDRATE_DEF = -DSYS_CONSOLE_BAUDRATE=$(SYS_CONSOLE_BAUDRATE)

#|---------------------------------------------------------------------------------------------------|
#| OPTIMIZE LEVELS                                                                                   |
#|------------|----------------------------------|--------------|---------|------------|-------------|
#|   option   | optimization levels              |execution time|code size|memory usage|complile time|
#|------------|----------------------------------|--------------|---------|------------|-------------|
#|   -O0      | compilation time                 |     (+)      |   (+)   |     (-)    |    (-)      |
#| -O1 || -O  | code size && execution time      |     (-)      |   (-)   |     (+)    |    (+)      |
#|   -O2      | more code size && execution time |     (--)     |         |     (+)    |    (++)     |
#|   -O3      | more code size && execution time |     (---)    |         |     (+)    |    (+++)    |
#|   -Os      | code size                        |              |   (--)  |            |    (++)     |
#|  -Ofast    | O3 with none math cals           |     (---)    |         |     (+)    |    (+++)    |
#|------------|----------------------------------|--------------|---------|------------|-------------|
OPTIMIZE_OPTION = -g -Os

# RTOS development option.
RTOS_DEV_OPTION = -URTOS_DEV_EN

# Release build option, that is used in fatal function, restart system when fatal, and debug levels.
RELEASE_OPTION = -URELEASE

# Enable PIN (using led life) interrupt analyzer function [entry IRQ -> led life ON] and [exit IRQ -> led life OFF].
IRQ_DEBUG_OPTION = -UAK_IO_IRQ_ANALYZER

# Enable to using USB hareware configuration.
USB_OPTION = -UUSING_USB_MOD

# Interface compile option.
IF_LINK_OPTION = -DIF_LINK_UART_EN
IF_NETWORK_NRF24_OPTION = -UIF_NETWORK_NRF24_EN

# Task compile option.
TASK_ZIGBEE_OPTION = -UTASK_ZIGBEE_EN
TASK_MBMASTER_OPTION = -DTASK_MBMASTER_EN

# Include sources file
include sources/device/Makefile
include sources/platform/Makefile
include sources/driver/Makefile
include sources/AK-mOS/Makefile
include sources/GUI/Makefile
include sources/application/Makefile

OBJECTS_DIR = build_$(NAME_MODULE)
TARGET = $(OBJECTS_DIR)/$(NAME_MODULE).axf



SOURCES_ 		= $(notdir $(SOURCES))
OBJECTS 		+= $(addprefix $(OBJECTS_DIR)/, $(SOURCES_:.c=.o))

SOURCES_CPP_ 	= $(notdir $(SOURCES_CPP))
OBJECTS 		+= $(addprefix $(OBJECTS_DIR)/, $(SOURCES_CPP_:.cpp=.o))

SOURCES_ASM_ 	= $(notdir $(SOURCES_ASM))
OBJECTS 		+= $(addprefix $(OBJECTS_DIR)/, $(SOURCES_ASM_:.s=.o))


LIBC		= $(GCC_PATH)/arm-none-eabi/lib/thumb/v7-m/nofp/libc.a
LIBM		= $(GCC_PATH)/arm-none-eabi/lib/thumb/v7-m/nofp/libm.a
LIBFPU		= $(GCC_PATH)/arm-none-eabi/lib/thumb/v7-m/nofp/libg.a
LIBRDPMON	= $(GCC_PATH)/arm-none-eabi/lib/thumb/v7-m/nofp/librdpmon.a
LIBSTDCPP_NANO	= $(GCC_PATH)/arm-none-eabi/lib/thumb/v7-m/nofp/libstdc++_nano.a

LIBGCC		= $(GCC_PATH)/lib/gcc/arm-none-eabi/10.3.1/thumb/v7-m/nofp/libgcc.a
LIBGCOV		= $(GCC_PATH)/lib/gcc/arm-none-eabi/10.3.1/thumb/v7-m/nofp/libgcov.a

LIB_PATH += -L$(GCC_PATH)/arm-none-eabi/lib/thumb/v7-m/nofp
LIB_PATH += -L$(GCC_PATH)/lib/gcc/arm-none-eabi/10.3.1/thumb/v7-m/nofp

# The command for calling the compiler.
CC		=	$(GCC_PATH)/bin/arm-none-eabi-gcc
CPP		=	$(GCC_PATH)/bin/arm-none-eabi-g++
AR		=	$(GCC_PATH)/bin/arm-none-eabi-ar
AS		=	$(GCC_PATH)/bin/arm-none-eabi-gcc -x assembler-with-cpp
LD		=	$(GCC_PATH)/bin/arm-none-eabi-ld
OBJCOPY		=	$(GCC_PATH)/bin/arm-none-eabi-objcopy
OBJDUMP		=	$(GCC_PATH)/bin/arm-none-eabi-objdump
OBJNM		=	$(GCC_PATH)/bin/arm-none-eabi-nm
ARM_GDB		=	$(GCC_PATH)/bin/arm-none-eabi-gdb-py
ARM_SIZE	=	$(GCC_PATH)/bin/arm-none-eabi-size

# Set the compiler CPU/FPU options.
# https://launchpadlibrarian.net/177524521/readme.txt
CPU = -mthumb -march=armv7-m
FPU = -mfloat-abi=soft

# Interface option
IF_OPTION +=	$(IF_LINK_OPTION)		\
		$(IF_NETWORK_NRF24_OPTION)	\

# App option
TASK_OPTION +=	$(TASK_ZIGBEE_OPTION)
TASK_OPTION +=	$(TASK_MBMASTER_OPTION)

# Console log compile option
CONSOLE_OPTION +=			\
		-DLOGIN_PRINT_EN	\
		-DSYS_PRINT_EN		\
		-DAPP_PRINT_EN		\
		-DSYS_DBG_EN		\
		-DAPP_DBG_EN		\
		-DAPP_DBG_SIG_EN	\

GENERAL_FLAGS +=			\
		$(RTOS_DEV_OPTION)	\
		$(CONSOLE_BAUDRATE_DEF)	\
		$(CONSOLE_OPTION)	\
		$(IRQ_DEBUG_OPTION)	\
		$(WARNING_OPTION)	\
		$(OPTIMIZE_OPTION)	\
		$(RELEASE_OPTION)	\
		$(APP_ADDR_OPTION)	\
		$(USB_OPTION)		\
		$(IF_OPTION)		\
		$(TASK_OPTION)		\
		-DUSE_STDPERIPH_DRIVER	\
		-DSTM32L1XX_MD		\
		-DSTM32L_PLATFORM	\
		-DUSE_EXTERNAL_FLASH	\

COMPILER_FLAGS +=			\
		$(CPU)			\
		$(FPU)			\
		-ffunction-sections	\
		-fdata-sections		\
		-fno-exceptions		\
		-fstack-usage		\
		-ffreestanding		\
		-MD			\
		-Wall			\
		-c			\

# C compiler flags
CFLAGS +=				\
		$(GENERAL_FLAGS)	\
		$(COMPILER_FLAGS)	\
		-std=c99		\

# C++ compiler flags
CPPFLAGS +=				\
		$(GENERAL_FLAGS)	\
		$(COMPILER_FLAGS)	\
		-fno-rtti		\
		-fno-exceptions		\
		-fno-use-cxa-atexit	\
		-std=c++11	\

# linker flags
LDFLAGS	=	-Map=$(OBJECTS_DIR)/$(PROJECT).map	\
		--gc-sections	\
		$(LIB_PATH)	\
		$(LIBC) $(LIBM) $(LIBSTDCPP_NANO) $(LIBGCC) $(LIBGCOV) $(LIBFPU) $(LIBRDPMON)

all: create $(TARGET)

create:
	$(Print) CREATE $(OBJECTS_DIR) folder
	@mkdir -p $(OBJECTS_DIR)


$(TARGET): $(OBJECTS) $(LIBC) $(LIBM) $(LIBSTDCPP_NANO) $(LIBGCC) $(LIBGCOV) $(LIBFPU) $(LIBRDPMON)
	$(Print) LD $@
	@$(LD) --entry Reset_Handler -T $(LDFILE) $(LDFLAGS) -o $(@) $(^)
	$(Print) OBJCOPY $(@:.axf=.bin)
	@$(OBJCOPY) -O binary $(@) $(@:.axf=.bin)
	@$(OBJCOPY) -O binary $(@) $(@:.axf=.out)
	@$(OBJCOPY) -O binary $(@) $(@:.axf=.elf)
	@$(ARM_SIZE) $(TARGET)

$(OBJECTS_DIR)/%.o: %.c
	$(Print) CC $@
	@$(CC) $(CFLAGS) -o $@ $<

$(OBJECTS_DIR)/%.o: %.cpp
	$(Print) CXX $@
	@$(CPP) $(CPPFLAGS) -c -o $@ $<

$(OBJECTS_DIR)/%.o: %.s
	$(Print) AS $@
	@$(AS) $(CFLAGS) -o $@ $<

.PHONY: help
help:
	$(Print) "[make flash dev=/dev/tty*] burn firmware via ak bootloader"
	$(Print) "             Note: This option is needed install ak-flash. Link download & install: https://github.com/epcbtech/ak-flash"
	$(Print) "             Example: make flash dev=/dev/ttyUSB0"
	$(Print) "[make flash] burn firmware via st-link"
	$(Print) "[make com dev=/dev/tty*] console AK Embedded Base Kit"
	$(Print) "[make debug gdb=ddd] gdb debug using ddd"
	$(Print) "[make debug] gdb debug"
	$(Print) "[make clean] clean build project folder"
	$(Print) "[make asm] generate asm file"
	$(Print) "[make sym] list symbol from objects file"

.PHONY: flash
flash:
	$(Print) BURNING $(TARGET:.axf=.bin) to target
	$(ST_FLASH) write $(TARGET:.axf=.bin) $(APP_START_ADDR_VAL)

.PHONY: erase
erase:
	$(ST_FLASH)	erase	$(APP_START_ADDR_VAL) 64K



.PHONY: com
com:
	minicom -D /dev/ttyACM0 -b 115200


.PHONY: debug
debug: 
	$(ARM_GDB) $(OBJECTS_DIR)/$(NAME_MODULE).elf


.PHONY: clean
clean:
	$(Print) CLEAN $(OBJECTS_DIR) folder
	@rm -rf $(OBJECTS_DIR)

asm: $(TARGET)
	$(Print) disassemble-all $(<:.axf=.asm)
	@$(OBJDUMP) -D $(<) >> $(<:.axf=.asm)

sym: $(TARGET)
	$(Print) export object name $(<:.axf=.sym)
	$(OBJNM) --size-sort --print-size $(<) >> $(<:.axf=.sym)
