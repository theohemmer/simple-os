#ifndef H_PIC
#define H_PIC

#define MPIC_COMMAND 0x20
#define SPIC_COMMAND 0xA0
#define MPIC_DATA 0x21
#define SPIC_DATA 0xA1

/*!
    Send an End Of Interrupt Signal for the IRQ received
    \param irq the IRQ to tell signal ended
*/
void pic_send_eio(unsigned char irq);

/*!
    Ignore an IRQ
    \param irq the IRQ to ignore
*/
void pic_mask_irq(unsigned char irq);

/*!
    Acknowledge an IRQ
    \param irq the IRQ to acknowledge
*/
void pic_unmask_irq(unsigned char irq);

/*!
    Remask the PIC to use interrupt from offset1 for the master and from offset2 for the slave
    \param offset1 offset of the interrupt number to use for the master PIC
    \param offset2 offset of the interrupt number to use for the slave PIC
*/
void pic_remap(unsigned int offset1, unsigned int offset2);

/*!
    Used in kernel to init the IRQ with the default params
*/
void pic_first_init(void);
#endif