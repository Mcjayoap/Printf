#include <stdarg.h>
#include "main.h"
#include <stddef.h>

/**
 * get_f - select function for conversion char
 * @c: char to check
 * Return: pointer to function
 */
int (*get_f(const char c))(va_list)
{
	int i = 0;

	flags_p fp[] = {
		{"c", print_char},
		{"s", print_str},
		{"i", print_decimal},
		{"d", print_decimal},
		{"b", print_binary},
		{"o", print_octal},
		{"x", print_hexa_lower},
		{"X", print_hexa_upper},
		{"u", print_unsigned},
		{"S", print_str_unprintable},
		{"r", print_str_reverse},
		{"p", print_ptr},
		{"R", print_rot13},
		{"%", print_percent}
	};
	while (i < 14)
	{
		if (c == fp[i].c[0])
		{
			return (fp[i].f);
		}
		i++;
	}
	return (NULL);
}

/**
 * _printf - Reproduce behavior of printf function
 * @format: format string
 * Return: value of printed chars
 */

int _printf(const char *format, ...)
{
	va_list arg;
	int sum = 0, i = 0;
	int (*f)();

	if (!format || (format[0] == '%' && format[1] == '\0'))
		return (-1);
	va_start(arg, format);

	while (format[i])
	{
		if (format[i] == '%')
		{
			if (format[i + 1] != '\0')
				f = get_f(format[i + 1]);
			if (f == NULL)
			{
				_putchar(format[i]);
				sum++;
				i++;
			}
			else
			{
				sum += f(arg);
				i += 2;
				continue;
			}
		}
		else
		{
			_putchar(format[i]);
			sum++;
			i++;
		}
	}
	va_end(arg);
	return (sum);
}
