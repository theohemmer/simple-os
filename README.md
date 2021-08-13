Simple-OS
=========

This is a basic OS that I'm creating because I've always wanted to know how does an OS work, boot, load the kernel and interract with the hardware.

It'll certainly won't go too far from, but I'm gonna work a little bit on it.


What I want to make
-------------------

I want to implements a few little things on this OS:

- [x] Creating the bootloader
- [x] VGA 360x200x256 graphic driver
- [ ] Keyboard handling
- [ ] Mouse handling
- [ ] Memory managment
- [ ] Threads?
- [ ] File System?
- [ ] Better Graphics?
- [ ] Networking?

*Maybe i'll think about other things to add here...*


Install and Run
---------------

To install this OS, you'll need a [Cross Compiler](https://wiki.osdev.org/GCC_Cross-Compiler) for i686.

You will also need [QEMU](https://www.qemu.org/) for the i386 arch.


Resources
---------

I'm using the [OSDev Wiki](https://wiki.osdev.org) to create this OS and finding usefull resources.

I've also used [this file](https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf) when I've started the bootloader.

And [this website](http://www.osdever.net/FreeVGA/vga/vga.htm) to create the VGA driver and understand the VGA registers.