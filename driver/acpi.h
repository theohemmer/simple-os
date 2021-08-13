#ifndef H_ACPI
#define H_ACPI

typedef struct {
    char signature[4];
    unsigned int length;
    unsigned char revision;
    unsigned char checksum;
    char oem_id[6];
    char oem_table_id[8];
    unsigned int oem_revision;
    unsigned int creator_id;
    unsigned int creator_version;
} __attribute__((packed)) acpi_sdt_header_t;

void init_acpi(void);

#endif