#include <stddef.h>
#include "driver/rsdp.h"
#include "driver/acpi.h"
#include "kernel/lib/include/string.h"

static void *check_rsdp_addr(rsdp_descriptor_t *rsdp_search)
{
    unsigned char *byte;
    unsigned char sum = 0;

    if (memcmp(rsdp_search, "RSD PTR ", 8) == 0) {
        printf("RSDP Descriptor found at %p\n\rChecking checksum.\n\r", rsdp_search);
        byte = (unsigned char *) rsdp_search;
        sum = 0;
        for (size_t i = 0; i < sizeof(rsdp_descriptor_t); i++)
            sum += byte[i];
        if (sum == 0) {
            printf("Valid Checksum found!\n\r");
            printf("Version: %d\n\r", rsdp_search->revision);
            return rsdp_search;
        } else {
            printf("Invalid Checksum.\n\r");
        }
    }
    return (NULL);
}

static void *find_rsdp_descriptor(void)
{
    rsdp_descriptor_t *rsdp_found = NULL;
    rsdp_descriptor_t *rsdp_search = (rsdp_descriptor_t *) 0x000E0000;
    short *ebda;

    for (; (unsigned int) rsdp_search < 0x000FFFFF; rsdp_search += 8) {
        if (check_rsdp_addr(rsdp_search) != NULL)
            return (rsdp_search);
    }
    printf("No valid RSDP Descriptor in Main BIOS area\n\rSearching in Extended BIOS Area\n\r");
    ebda = (short *) *((short *) 0x40E);
    for (rsdp_search = ebda; (unsigned int) rsdp_search < ebda + 1000; rsdp_search += 8) {
        if (check_rsdp_addr(rsdp_search) != NULL)
            return (rsdp_search);
    }
    return (NULL);
}

static int check_version_2(rsdp2_descriptor_t *rsdp)
{
    unsigned char *byte = (unsigned char *) rsdp;
    unsigned char sum = 0;

    printf("Checking version 2\n\r");
    for (size_t i = 0; i < sizeof(rsdp2_descriptor_t); i++)
        sum += byte[i];
    if (sum == 0) {
        printf("Valid version 2\n\r");
        return (0);
    }
    printf("Invalid version 2\n\r");
    return (1);
}

acpi_sdt_header_t *find_acpi_sdt_header_in_rsdp(void)
{
    rsdp_descriptor_t *rsdp = find_rsdp_descriptor();
    rsdp2_descriptor_t *rsdp2 = NULL;

    if (rsdp == NULL) {
        printf("No valid RSDP Descriptor on this system.\n\r");
        return (NULL);
    }
    if (rsdp->revision > 0)
        if (check_version_2((rsdp2_descriptor_t *) rsdp) == 0)
            rsdp2 = (rsdp2_descriptor_t *) rsdp;
    if (rsdp2 != NULL)
        return ((acpi_sdt_header_t *) rsdp2->xsdt_address);
    return ((acpi_sdt_header_t *) rsdp->rsdt_address);
}