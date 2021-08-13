#include <stddef.h>
#include "kernel/lib/include/string.h"
#include "kernel/lib/include/stdlib.h"

static const size_t base_addr = 0x100000;

typedef struct __attribute__ ((aligned (32))) block_s {
    char is_free;
    size_t size;
    struct block_s *next;
    void *data;
} block_t;

static size_t getpagesize(void)
{
    return (4096);
}

static void *sbrk(size_t size)
{
    static size_t act_addr = base_addr;
    size_t to_ret = act_addr;

    act_addr += size;
    return ((void *) to_ret);
}

static void *calc_addr(void *base_addr, unsigned long inc)
{
    unsigned long tmp = (unsigned long) base_addr;

    tmp = tmp + inc;
    return ((void *) tmp);
}

static size_t get_sbrk_size(size_t size)
{
    size_t page_size = getpagesize();
    int nbr_of_pages = 0;

    for (int i = 0; i < size; i += page_size, nbr_of_pages++);
    if (nbr_of_pages % 2 != 0)
        nbr_of_pages++;
    return (nbr_of_pages * page_size);
}

static size_t get_data_size(size_t size)
{
    int f_size = 2;

    for (; f_size < size; f_size *= 2);
    return (f_size);
}

static size_t get_block_size(size_t size)
{
    size = get_data_size(size);
    size += sizeof(block_t);
    return (size);
}

static void *where_is_first_block(void *addr)
{
    static void *first_block = NULL;

    if (addr != NULL)
        first_block = addr;
    return (first_block);
}

static block_t *find_free(size_t data_size)
{
    block_t *act = where_is_first_block(NULL);
    block_t *best_fit = NULL;
    size_t diff = -1;

    if (act == NULL)
        return (NULL);
    while (act != NULL) {
        if (act->is_free && act->size >= data_size) {
            best_fit = (act->size - data_size < diff) ? act : best_fit;
            diff = best_fit->size - data_size;
        }
        act = act->next;
    }
    return (best_fit);
}

static block_t *get_last_block(void)
{
    block_t *act = where_is_first_block(NULL);

    if (act == NULL)
        return (NULL);
    while (act->next != NULL)
        act = act->next;
    return (act);
}

static void *do_sbrk(size_t sbrk_size)
{
    return (sbrk(sbrk_size));
}

static void concat_chained_free(void)
{
    block_t *act = where_is_first_block(NULL);

    while (act != NULL) {
        if (act->is_free && act->next && act->next->is_free) {
            act->size = act->size + act->next->size + sizeof(block_t);
            act->next = act->next->next;
        } else {
            act = act->next;
        }
    }
}

static block_t *create_first_block(block_t *tmp, size_t sbrk_size)
{
    block_t *act = tmp;
    act->next = NULL;
    act->size = sbrk_size - sizeof(block_t);
    act->data = calc_addr(act, sizeof(block_t));
    act->is_free = 1;
    return (act);
}

static char add_a_free_block_at_end(size_t block_size, size_t sbrk_size)
{
    block_t *act = where_is_first_block(NULL);
    block_t *tmp = do_sbrk(sbrk_size);

    if (act == ((void *) - 1))
        return (0);
    if (act == NULL) {
        act = create_first_block(tmp, sbrk_size);
        where_is_first_block(act);
    } else {
        while (act->next != NULL)
            act = act->next;
        act->next = calc_addr(act->data, act->size);
        act->next->size = sbrk_size - sizeof(block_t);
        act->next->data = calc_addr(act->next, sizeof(block_t));
        act->next->is_free = 1;
        act->next->next = NULL;
    }
    return (1);
}

static void new_block(block_t *act, block_t *next, block_t *block_to_use, size_t size)
{
    block_t *new_block;

    new_block = calc_addr(act->data, size);
    new_block->is_free = 1;
    new_block->data = calc_addr(new_block, sizeof(block_t));
    new_block->next = next;
    new_block->size = act->size - size - sizeof(block_t);
    block_to_use->next = new_block;
}

static block_t *use_free_block(block_t *block_to_use, size_t data_size)
{
    block_t *act = where_is_first_block(NULL);
    block_t *next = NULL;

    if (act == NULL)
        return (NULL);
    while (act != NULL) {
        if (act == block_to_use) {
            next = block_to_use->next;
            break;
        }
        act = act->next;
    }
    if (act->size > (data_size + sizeof(block_t) + 2))
        new_block(act, next, block_to_use, data_size);
    else
        data_size = act->size;
    block_to_use->size = data_size;
    block_to_use->is_free = 0;
    concat_chained_free();
    return (block_to_use);
}

static void re_set_free_block(block_t *block, size_t new_size)
{
    block_t *tmp_next = block->next->next;
    size_t tmp_size = block->next->size;
    size_t l_size = block->size;

    block->size = new_size;
    block->next = calc_addr(block->data, new_size);
    block->next->data = calc_addr(block->next, sizeof(block_t));
    block->next->is_free = 1;
    block->next->next = tmp_next;
    block->next->size = tmp_size - new_size - l_size;
}

static block_t *copy_create_new_block(block_t *block, size_t size)
{
    void *new_malloc = malloc(size);
    block_t *act = where_is_first_block(NULL);

    if (new_malloc == NULL)
        return (NULL);
    memmove(new_malloc, block->data, block->size);
    free(block->data);
    while (act != NULL) {
        if (act->data == new_malloc)
            return (act);
        act = act->next;
    }
    return (NULL);
}

static block_t *enlarge_block(block_t *block, size_t size)
{
    block_t *new;

    if (block->size > size) {
        new = use_free_block(block, size);
        concat_chained_free();
        return (new);
    }
    if (block->size < size && block->next && block->next->is_free &&
    block->next->size > (block->size + size + 2 + sizeof(block_t))) {
        re_set_free_block(block, size);
        return (block);
    }
    return (copy_create_new_block(block, size));
}

void *malloc(size_t size)
{
    size_t data_size = get_data_size(size);
    size_t block_size = get_block_size(size);
    size_t sbrk_size = get_sbrk_size(block_size);
    block_t *block = NULL;
    block_t *last;

    if (size == 0)
        return (NULL);
    if ((block = find_free(data_size)) != NULL)
        return (use_free_block(block, data_size)->data);
    last = get_last_block();
    if (where_is_first_block(NULL) == NULL || !last->is_free ||
        last->size < block_size)
        if (!add_a_free_block_at_end(block_size, sbrk_size))
            return (NULL);
    concat_chained_free();
    block = find_free(data_size);
    block = use_free_block(block, data_size);
    return (block->data);
}

void free(void *ptr)
{
    block_t *act = where_is_first_block(NULL);

    if (ptr == NULL)
        return;
    while (act != NULL) {
        if (act->data == ptr) {
            act->is_free = 1;
            break;
        }
        act = act->next;
    }
    concat_chained_free();
}

void *realloc(void *ptr, size_t size)
{
    block_t *act = where_is_first_block(NULL);
    block_t *to_ret;

    if (size == 0) {
        free(ptr);
        return (NULL);
    }
    if (ptr == NULL || act == NULL)
        return (malloc(size));
    while (act != NULL) {
        if (act->data == ptr)
            break;
        act = act->next;
    }
    if (act == NULL)
        return (NULL);
    to_ret = enlarge_block(act, get_data_size(size));
    if (to_ret != NULL)
        return (to_ret->data);
    return (NULL);
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    size_t size_to_malloc = nmemb * size;
    void *to_ret;

    if (size_to_malloc != 0 && size_to_malloc / nmemb != size)
        return (NULL);
    to_ret = realloc(ptr, size_to_malloc);
    return (to_ret);
}

void *calloc(size_t nmemb, size_t size)
{
    size_t size_to_malloc = nmemb * size;
    void *to_ret;

    if (nmemb == 0 || size == 0)
        return (NULL);
    to_ret = malloc(size_to_malloc);
    if (to_ret == NULL)
        return (NULL);
    memset(to_ret, 0, get_data_size(size_to_malloc));
    return (to_ret);
}