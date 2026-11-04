/* CS100 Fall 2026 - HW3 Problem 2: Palindrome
 *
 * Read n strings and test whether each of them is a palindrome.
 * Print "Yes" / "No" on one line per string.
 * Use dynamic memory to store each input string (no fixed-size arrays).
 * Do not rename this file.
 */
#include <stdio.h>

int main(void)
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        int len;
        scanf("%d", &len);

        // dynamic allocation, +1 for '\0'
        char *s = (char *)malloc((len + 1) * sizeof(char));

        scanf("%s", s);

        int is_pal = 1;
        for (int j = 0; j < len / 2; j++)
        {
            if (s[j] != s[len - 1 - j])
            {
                is_pal = 0;
                break;
            }
        }

        if (is_pal)
        {
            printf("Yes\n");
        }
        else
        {
            printf("No\n");
        }

        free(s);
    }

    /* TODO: your code here */
    return 0;
}
