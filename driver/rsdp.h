#ifndef H_RSDP
#define H_RSDP

#include "driver/acpi.h"

typedef struct {
    char signature[8];
    unsigned char checksum;
    char oem_id[6];
    unsigned char revision;
    unsigned int rsdt_address;
} __attribute__((packed)) rsdp_descriptor_t;

typedef struct {
    rsdp_descriptor_t first_part;
    unsigned int length;
    unsigned int xsdt_address;
    unsigned char extended_checksum;
    unsigned char reserved[3];
} __attribute__((packed)) rsdp2_descriptor_t;

acpi_sdt_header_t *find_acpi_sdt_header_in_rsdp(void);

#endif