ARCH = armv7-armv7
MCPU = cortex-a8

CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
OC = arm-none-eabi-objcopy

LINKER_SCRIPT = ./SimpleOS.ld

ASM_SRCS = $(wildcard boot/*.S)
ASM_OBJS = $(patsubst boot/%.S, build/%.o, $(ASM_SRCS))

INC_DIRS = include

SimpleOS = build/SimpleOS.axf
SimpleOS_bin = build/SimpleOS.bin

.PHONY: all clean run debug gdb

all: $(SimpleOS)

clean:
  @rm -fr build
  
run: $(SimpleOS)
  qemu-system-arm -M realview-pb-a8 -kernel $(SimpleOS)
  
debug: $(SimpleOS)
  qemu-system-arm -M realview-pb-a8 -kernel $(SimpleOS) -S -gdb tcp::1234, ipv4
  
gdb:
  arm-none-eabi-gdb
  
$(SimpleOS): $(ASM_OBJS) $(LINKER_SCRIPT)
  $(LD) -n -T $(LINKER_SCRIPT) -o $(SimpleOS) $(ASM_OBJS)
  $(OC) -O binary $(SimpleOS) $(SimpleOS_bin)
  
build/%.o: boot/%.S
  mkdir -p $(shell dirname $@)
  $(AS) -march=S(ARCH) -mcpu=$(MCPU) -I $(INC_DIRS) -g -o $@ $<


