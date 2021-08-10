int get_symbol(char const *str)
{
    int i = 0;
    char c = '0';
    int do_continue = 1;
    int symbol = 1;

    while ((c = str[i]) != '\0' && do_continue) {
        if (c == '-')
            symbol = 1 - symbol;
        if (!(c == '-' || c == '+'))
            do_continue = 0;
        i++;
    }
    return (symbol);
}

int get_nbr(char const *str)
{
    int i = 0;
    char c = '0';
    int result = 0;
    int do_continue = 1;

    while ((c = str[i]) != '\0' && do_continue) {
        if (c >= '0' && c <= '9') {
            result = (result * 10) + (c - '0');
        } else if (c != '-' && c != '+') {
            do_continue = 0;
        }
        i++;
    }
    return (result);
}

int check_overflow(char const *str, int symbol)
{
    int value = 0;
    int last_value = 0;
    int first_pass = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= '0' && str[i] <= '9' && !first_pass) {
            if (symbol)
                value = (value * 10) + (str[i] - '0');
            else
                value = (value * 10) - (str[i] - '0');
            if (value < last_value && symbol)
                return (0);
            if (value > last_value && !symbol)
                return (0);
            last_value = value;
        } else if (str[i] != '-' && str[i] != '+')
            first_pass = 1;
    }
    return (1);
}

int getnbr(char const *str)
{
    int result = get_nbr(str);

    for (int i = 0; str[i]; i++)
        if (!(str[i] >= '0' && str[i] <= '9'))
            return (-84848484);
    if (!check_overflow(str, get_symbol(str)))
        return (0);
    if (!get_symbol(str))
        result = -(result);
    return (result);
}
