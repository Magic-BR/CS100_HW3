/* CS100 Fall 2026 - HW3 Problem 3: String and character manipulation
 *
 * Implement the hw3_* functions below. Do NOT write a main function here:
 * the autograder compiles this file together with its own test driver.
 * Implementations must conform to the C standard (see cppreference) and
 * must not call any standard library string/character functions.
 * Do not rename this file.
 */
#include <stddef.h>

int hw3_islower(int ch) {
    return ch >= 'a' && ch <= 'z';
}

int hw3_isupper(int ch) {
    return ch >= 'A' && ch <= 'Z';
}

int hw3_isalpha(int ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

int hw3_isdigit(int ch) {
    return ch >= '0' && ch <= '9';
}

int hw3_tolower(int ch) {
    return (hw3_isupper(ch)) ? (ch - 'A' + 'a') : ch;
}

int hw3_toupper(int ch) {
    return (hw3_islower(ch)) ? (ch - 'a' + 'A') : ch;
}

size_t hw3_strlen(const char *str)
{
    size_t cnt = 0;
    while (str[cnt] != '\0')
    {
        cnt++;
    }
    return cnt;
}

char *hw3_strchr(const char *str, int ch)
{
    while (*str != '\0')
    {
        if (*str == (char)ch)
        {
            return (char *)str;
        }
        str++;
    }
    if ((char)ch == '\0')
    {
        return (char *)str;
    }
    return NULL;
}

char *hw3_strcpy(char *dest, const char *src)
{
    char *start = dest;
    while (*src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return start;
}

char *hw3_strcat(char *dest, const char *src)
{
    char *start = dest;
    while (*dest != '\0')
    {
        dest++;
    }
    while (*src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return start;
}

int hw3_strcmp(const char *lhs, const char *rhs)
{
    while (*lhs != '\0' && *rhs != '\0' && *lhs == *rhs)
    {
        lhs++;
        rhs++;
    }
    return (unsigned char)*lhs - (unsigned char)*rhs;
}