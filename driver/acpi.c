#include "driver/rsdp.h"
#include <stddef.h>

static int validate_checksum(acpi_sdt_header_t *acpi_sdt_header)
{
    char *byte = (char *) acpi_sdt_header;
    int sum = 0;

    for (size_t i = 0; i < acpi_sdt_header->length; i++)
        sum += byte[i];
    return (sum == 0);
}

void init_acpi(void)
{
    acpi_sdt_header_t *acpi_sdt_header = find_acpi_sdt_header_in_rsdp();

    if (acpi_sdt_header == NULL)
        return;
    printf("Validating ACPI SDT Header checksum.\n\r");
    if (validate_checksum(acpi_sdt_header) == 0) {
        printf("Invalid checksum.\n\r");
        return;
    }
    printf("Valid checksum.\n\r");
}