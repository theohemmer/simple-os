#!/bin/python3
import os

file_ = "./kernel.bin"
size = os.stat(file_).st_size

base_size = size / 512
if size % 512 > 0:
    base_size += 1

print("calculate_kernel_size.py: \033[91m" + str(int(base_size)) + " sectors will be loaded into the ram \033[0m")

to_write = open("./bootloader/kernel_size.asm", "w");
to_write.write("%define kernel_size " + str(int(base_size)))
to_write.close()