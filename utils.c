#include "utils.h"

size_t  ft_strlen(const char *s)
{
    size_t i = 0;
    while (s && s[i])
        i++;
    return i;
}

void    ft_putchar_fd(char c, int fd)
{
    write(fd, &c, 1);
}

void    ft_putstr_fd(const char *s, int fd)
{
    if (s)
        write(fd, s, ft_strlen(s));
}

void    ft_putnbr_fd(int n, int fd)
{
    char c;

    if (n == -2147483648)
    {
        write(fd, "-2147483648", 11);
        return;
    }
    if (n < 0)
    {
        ft_putchar_fd('-', fd);
        n = -n;
    }
    if (n >= 10)
        ft_putnbr_fd(n / 10, fd);
    c = '0' + (n % 10);
    ft_putchar_fd(c, fd);
}

int ft_atoi(const char *str)
{
    int sign = 1;
    int res = 0;

    while (*str == ' ' || (*str >= 9 && *str <= 13))
        str++;
    if (*str == '-' || *str == '+')
    {
        if (*str == '-')
            sign = -1;
        str++;
    }
    while (*str >= '0' && *str <= '9')
    {
        res = res * 10 + (*str - '0');
        str++;
    }
    return res * sign;
}
