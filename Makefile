#DEVICE = stm8s003f3
DEVICE = stm8s103f3

BASE_HEADERS = ../include
SRC_DIR = src
INC_DIR = inc
TMP_DIR = tmp
OUT_DIR = bin

PROGRAM = $(lastword $(subst /, ,$(CURDIR)))
SOURCES = $(wildcard *.c $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:.c=.rel)
HEADERS = $(wildcard *.h $(INC_DIR)/*.h)

CC = sdcc
OBJCOPY = sdobjcopy
PROGRAMMER = stlinkv2

DEFINES = -D__SDCC__

## Set MCU-type DEFINE
ifeq ($(DEVICE),stm8s003f3)
    DEFINES += -DSTM8S003
endif
ifeq ($(DEVICE),stm8s103f3)
    DEFINES += -DSTM8S103
endif

INCLUDE_DIR = -I$(SRC_DIR) -I$(INC_DIR) -I$(BASE_HEADERS)

LDFLAGS = -mstm8 -lstm8
CFLAGS_OPT = --opt-code-size --all-callee-saves 

CFLAGS = --Werror --std-sdcc99 -mstm8 --opt-code-size --verbose --stack-auto --fverbose-asm --no-peep --max-allocs-per-node 10000 $(DEFINES)

ifeq ($(DEBUG), 1)
	CFLAGS += --out-fmt-elf --debug
else
	CFLAGS += --out-fmt-ihx
endif


%.rel: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $(INCLUDE_DIR) -o $(subst $(SRC_DIR),$(TMP_DIR), $@) $<

.PHONY: all clean flash

$(PROGRAM).ihx: $(OBJECTS)
	$(CC) $(LDFLAGS) --out-fmt-ihx $(subst $(SRC_DIR),$(TMP_DIR), $^) -o $(OUT_DIR)/$@

$(PROGRAM).elf: $(OBJECTS)
	$(CC) $(LDFLAGS) --out-fmt-elf --debug  $(subst $(SRC_DIR),$(TMP_DIR), $^) -o $(OUT_DIR)/$@

clean:
	@echo "--- Czyszczenie katalogow: bin, tmp ---"
	rm -f $(OUT_DIR)/*
	rm -f $(TMP_DIR)/*

size:
	@$(OBJCOPY) -I ihex --output-target=binary $(OUT_DIR)/$(PROGRAM).ihx $(OUT_DIR)/$(PROGRAM).bin
	@echo "--- Rozmiar binarki ---"
	@stat -L -c %s $(OUT_DIR)/$(PROGRAM).bin

flash: $(PROGRAM).ihx
	stm8flash -c $(PROGRAMMER) -p $(DEVICE) -w $(OUT_DIR)/$(PROGRAM).ihx

debug: $(PROGRAM).elf

gdb:
	@echo "--- Uruchomienie debugera (DBG) ---"
	stm8-gdb --tui $(OUT_DIR)/$(PROGRAM).elf --directory=./$(SRC_DIR)

openocd:
	@echo " --- Uruchomienie OpenOCD ----"
	openocd -f interface/stlink.cfg -f target/stm8s003.cfg -c "init" -c "reset halt"
