ARCH = armv7-armv7
MCPU = cortex-a8

TARGET = RealViewPB

CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
OC = arm-none-eabi-objcopy

LINKER_SCRIPT = ./SimpleOS.ld
MAP_FILE = build/SimpleOS.map

ASM_SRCS = $(wildcard boot/*.S)
ASM_OBJS = $(patsubst boot/%.S, build/%.os, $(ASM_SRCS))

VPATH = boot          \
        hal/$(TARGET) \
        lib

C_SRCS = $(notdir $(wildcard boot/*.c))
C_SRCS += $(notdir $(wildcard hal/$(TARGET)/*.c))
C_SRCS += $(notdir $(wildcard lib/*.c))
C_OBJS = $(patsubst %.c, build/%.o, $(C_SRCS))

INC_DIRS = -I Include       \
           -I hal           \
           -I hal/$(TARGET) \
           -I lib
           
CFLAGS = -c -g -std=c11

SimpleOS = build/SimpleOS.axf
SimpleOS_bin = build/SimpleOS.bin

.PHONY: all clean run debug gdb

all: $(SimpleOS)

clean:
  @rm -fr build
  
run: $(SimpleOS)
  qemu-system-arm -M realview-pb-a8 -kernel $(SimpleOS) -nographic
  
debug: $(SimpleOS)
  qemu-system-arm -M realview-pb-a8 -kernel $(SimpleOS) -S -gdb tcp::1234, ipv4
  
gdb:
  arm-none-eabi-gdb
  
$(SimpleOS): $(ASM_OBJS) $(C_OBJS) $(LINKER_SCRIPT)
  $(LD) -n -T $(LINKER_SCRIPT) -o $(SimpleOS) $(ASM_OBJS) $(C_OBJS) -Map=$(MAP_FILE)
  $(OC) -O binary $(SimpleOS) $(SimpleOS_bin)
  
build/%.os: %.S
  mkdir -p $(shell dirname $@)
  $(CC) -march=S(ARCH) -mcpu=$(MCPU) $(INC_DIRS) $(CFLAGS) -o $@ $<

build/%.o: %.c
  mkdir -p $(shell dirname $@)
  $(CC) -march=S(ARCH) -mcpu=$(MCPU) $(INC_DIRS) $(CFLAGS) -o $@ $<
