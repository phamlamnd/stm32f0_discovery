PRO_DIR		:= .
PROJ_NAME	:= stm32f0_codebase
OUTPUT_PATH := $(PRO_DIR)/output

INC_DIR		:= $(PRO_DIR)/inc
SRC_DIR 	:= $(PRO_DIR)/src
LINKER_FILE	:= $(PRO_DIR)/linker/stm32f0_discovery.ld

COMPILER_DIR 	:= C:/tools/gcc_7_2017-q4-major
PREFIX_GCC_COMPILER	:= arm-none-eabi
CC				:= $(COMPILER_DIR)/bin/$(PREFIX_GCC_COMPILER)-gcc
ASM				:= $(COMPILER_DIR)/bin/$(PREFIX_GCC_COMPILER)-as
LD				:= $(COMPILER_DIR)/bin/$(PREFIX_GCC_COMPILER)-ld

FILE_TO_LINK	:= $(OUTPUT_PATH)/main.o \
				   $(OUTPUT_PATH)/startup_ARMCM0.o \
				   $(OUTPUT_PATH)/interrupt_manager.o \
				   $(OUTPUT_PATH)/clock_driver.o \
				   $(OUTPUT_PATH)/gpio_driver.o \
				   $(OUTPUT_PATH)/systick_driver.o \
				   $(OUTPUT_PATH)/uart_driver.o \
				   $(OUTPUT_PATH)/tm1637_driver.o \
				   $(OUTPUT_PATH)/adc_driver.o

CC_OPT			:= -march=armv6-m -mcpu=cortex-m0 -c -O0 -g -mthumb -I$(INC_DIR)
ASM_OPT			:= -march=armv6-m -mcpu=cortex-m0 -c -mthumb
LD_OPT			:= -T $(LINKER_FILE) -Map $(OUTPUT_PATH)/$(PROJ_NAME).map $(FILE_TO_LINK)

all: clean build

$(OUTPUT_PATH)/main.o: $(SRC_DIR)/main.c
	@echo "compile $(SRC_DIR)/main.c file"
	$(CC) $(CC_OPT) $(SRC_DIR)/main.c -o $(OUTPUT_PATH)/main.o

$(OUTPUT_PATH)/startup_ARMCM0.o: $(SRC_DIR)/startup_ARMCM0.S
	@echo "compile $(SRC_DIR)/startup_ARMCM0.S file"
	$(ASM) $(ASM_OPT) $(SRC_DIR)/startup_ARMCM0.s -o $(OUTPUT_PATH)/startup_ARMCM0.o

$(OUTPUT_PATH)/interrupt_manager.o: $(SRC_DIR)/interrupt_manager.c
	@echo "compile $(SRC_DIR)/interrupt_manager.c file"
	$(CC) $(CC_OPT) $(SRC_DIR)/interrupt_manager.c -o $(OUTPUT_PATH)/interrupt_manager.o

$(OUTPUT_PATH)/clock_driver.o: $(SRC_DIR)/clock_driver.c
	@echo "compile $(SRC_DIR)/clock_driver.c file"
	$(CC) $(CC_OPT) $(SRC_DIR)/clock_driver.c -o $(OUTPUT_PATH)/clock_driver.o

$(OUTPUT_PATH)/gpio_driver.o: $(SRC_DIR)/gpio_driver.c
	@echo "compile $(SRC_DIR)/gpio_driver.c file"
	$(CC) $(CC_OPT) $(SRC_DIR)/gpio_driver.c -o $(OUTPUT_PATH)/gpio_driver.o

$(OUTPUT_PATH)/systick_driver.o: $(SRC_DIR)/systick_driver.c
	@echo "compile $(SRC_DIR)/systick_driver.c file"
	$(CC) $(CC_OPT) $(SRC_DIR)/systick_driver.c -o $(OUTPUT_PATH)/systick_driver.o

$(OUTPUT_PATH)/uart_driver.o: $(SRC_DIR)/uart_driver.c
	@echo "compile $(SRC_DIR)/uart_driver.c file"
	$(CC) $(CC_OPT) $(SRC_DIR)/uart_driver.c -o $(OUTPUT_PATH)/uart_driver.o

$(OUTPUT_PATH)/tm1637_driver.o: $(SRC_DIR)/tm1637_driver.c
	@echo "compile $(SRC_DIR)/tm1637_driver.c file"
	$(CC) $(CC_OPT) $(SRC_DIR)/tm1637_driver.c -o $(OUTPUT_PATH)/tm1637_driver.o

$(OUTPUT_PATH)/adc_driver.o: $(SRC_DIR)/adc_driver.c
	@echo "compile $(SRC_DIR)/adc_driver.c file"
	$(CC) $(CC_OPT) $(SRC_DIR)/adc_driver.c -o $(OUTPUT_PATH)/adc_driver.o

build: $(FILE_TO_LINK) $(LINKER_FILE)
	@echo "link object files to create new binary image ($(PROJ_NAME).elf)"
	$(LD) $(LD_OPT) -o $(OUTPUT_PATH)/$(PROJ_NAME).elf

clean:
	@rm -rf $(OUTPUT_PATH)/*