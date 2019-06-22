PRO_DIR		:= .
PROJ_NAME	:= stm32f0_discovery_usart
OUTPUT_PATH := $(PRO_DIR)/output

INC_DIR		:= $(PRO_DIR)/inc
SRC_DIR 	:= $(PRO_DIR)/src
LINKER_FILE	:= $(PRO_DIR)/linker/stm32f0_discovery.ld

COMPILER_DIR 	:= C:/tools/gcc_7_2017-q4-major


PREFIX_GCC_COMPILER	:= arm-none-eabi
CC				:= $(COMPILER_DIR)/bin/$(PREFIX_GCC_COMPILER)-gcc
ASM				:= $(COMPILER_DIR)/bin/$(PREFIX_GCC_COMPILER)-as
LD				:= $(COMPILER_DIR)/bin/$(PREFIX_GCC_COMPILER)-ld

FILE_TO_LINK	:= $(OUTPUT_PATH)/clock.o $(OUTPUT_PATH)/gpio.o $(OUTPUT_PATH)/interrupt.o $(OUTPUT_PATH)/main.o $(OUTPUT_PATH)/startup_ARMCM0.o $(OUTPUT_PATH)/tm1637.o $(OUTPUT_PATH)/systick.o $(OUTPUT_PATH)/usart.o

CC_OPT			:= -march=armv6-m -mcpu=cortex-m0 -c -O0 -g -mthumb -I$(INC_DIR)
ASM_OPT			:= -march=armv6-m -mcpu=cortex-m0 -c -mthumb
LD_OPT			:= -T $(LINKER_FILE) -Map $(OUTPUT_PATH)/$(PROJ_NAME).map $(FILE_TO_LINK)

all: clean build

$(OUTPUT_PATH)/clock.o: $(SRC_DIR)/clock.c
	$(CC) $(CC_OPT) $(SRC_DIR)/clock.c -o $(OUTPUT_PATH)/clock.o

pre: $(SRC_DIR)/gpio.c
	$(CC) $(CC_OPT) -E $(SRC_DIR)/gpio.c -o $(OUTPUT_PATH)/new_gpio.c

asm_code: $(OUTPUT_PATH)/new_gpio.c
	$(CC) $(CC_OPT) -S $(OUTPUT_PATH)/new_gpio.c -o $(OUTPUT_PATH)/new_gpio.s
	
build_asm: $(OUTPUT_PATH)/new_gpio.s
	$(CC) $(CC_OPT) $(OUTPUT_PATH)/new_gpio.s -o $(OUTPUT_PATH)/new_gpio.o
	
$(OUTPUT_PATH)/gpio.o: $(SRC_DIR)/gpio.c
	$(CC) $(CC_OPT) $(SRC_DIR)/gpio.c -o $(OUTPUT_PATH)/gpio.o

$(OUTPUT_PATH)/interrupt.o: $(SRC_DIR)/interrupt.c
	$(CC) $(CC_OPT) $(SRC_DIR)/interrupt.c -o $(OUTPUT_PATH)/interrupt.o
	
$(OUTPUT_PATH)/main.o: $(SRC_DIR)/main.c
	$(CC) $(CC_OPT) $(SRC_DIR)/main.c -o $(OUTPUT_PATH)/main.o
	
$(OUTPUT_PATH)/startup_ARMCM0.o: $(SRC_DIR)/startup_ARMCM0.S
	$(ASM) $(ASM_OPT) $(SRC_DIR)/startup_ARMCM0.s -o $(OUTPUT_PATH)/startup_ARMCM0.o

$(OUTPUT_PATH)/tm1637.o: $(SRC_DIR)/tm1637.c
	$(CC) $(CC_OPT) $(SRC_DIR)/tm1637.c -o $(OUTPUT_PATH)/tm1637.o

$(OUTPUT_PATH)/systick.o: $(SRC_DIR)/systick.c
	$(CC) $(CC_OPT) $(SRC_DIR)/systick.c -o $(OUTPUT_PATH)/systick.o

$(OUTPUT_PATH)/usart.o: $(SRC_DIR)/usart.c
	$(CC) $(CC_OPT) $(SRC_DIR)/usart.c -o $(OUTPUT_PATH)/usart.o
	
build: $(FILE_TO_LINK) $(LINKER_FILE)
	$(LD) $(LD_OPT) -o $(OUTPUT_PATH)/$(PROJ_NAME).elf

clean:
	@rm -rf $(OUTPUT_PATH)/*