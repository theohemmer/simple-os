CC = $$HOME/opt/cross/bin/i686-elf-gcc
LD = $$HOME/opt/cross/bin/i686-elf-ld

KERNEL_SRC = 	kernel/kernel.c \
				driver/vga_text_mode.c \
				driver/vga_graphic_mode.c \
				driver/port.c \
				driver/pic.c

LIB_SRC = $(wildcard kernel/lib/stdio/*.c kernel/lib/stdlib/*.c kernel/lib/string/*.c)

KERNEL_OBJ = $(KERNEL_SRC:.c=.o)
LIB_OBJ = $(LIB_SRC:.c=.o)

INTERRUPTS = 	interrupts/idt.c \
				interrupts/isr.c \
				interrupts/irq.c

INTERRUPTS_OBJ = $(INTERRUPTS:.c=.o)

interrupt_handler.o: interrupts/handler.asm
	nasm $< -f elf -o $@

%.o: %.c
	$(CC) -ffreestanding -nostdlib -c $< -o $@ -I./

kernel_entry.o: kernel/kernel_entry.asm
	nasm $< -f elf -o $@

kernel.bin: kernel_entry.o $(KERNEL_OBJ) $(LIB_OBJ) $(INTERRUPTS_OBJ) interrupt_handler.o
	$(LD) -nostdlib -o $@ -Ttext 0x1000 $^ --oformat binary

kernel.elf: kernel_entry.o $(KERNEL_OBJ) $(LIB_OBJ)  $(INTERRUPTS_OBJ) interrupt_handler.o
	$(LD) -nostdlib -o $@ -Ttext 0x1000 $^

boot.bin: bootloader/boot.asm
	nasm $< -f bin -o $@

image_os: boot.bin kernel.bin
	cat $^ > $@

calculate_kernel_size: kernel.bin
	./calculate_kernel_size.py

image: calculate_kernel_size image_os

run: clean image
	qemu-system-i386 -hda image_os -serial stdio

debug: clean image kernel.elf
	qemu-system-i386 -s -S -hda image_os &
	gdb -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

clean:
	rm -f *.o
	rm -f *.bin
	rm -f kernel/*.o
	rm -f kernel/lib/*/*.o
	rm -f interrupts/*.o
	rm -f driver/*.o
	rm -f image_os
	rm -f kernel.elf
