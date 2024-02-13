#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdio.h>

#include "../src/tinyprintf.h"

// Basics

Test(basics, simple, .init = cr_redirect_stdout)
{
    tinyprintf("%s [%d] %s", "Hello", 42, "world!");
    fflush(NULL);
    cr_assert_stdout_eq_str("Hello [42] world!");
}

Test(basics, hexa, .init = cr_redirect_stdout)
{
    tinyprintf("%s [%x] %s", "Hello", 42, "world!");
    fflush(NULL);
    cr_assert_stdout_eq_str("Hello [2a] world!");
}

Test(basics, percent, .init = cr_redirect_stdout)
{
    tinyprintf("%%s", "in your head");
    fflush(NULL);
    cr_assert_stdout_eq_str("%s");
}

Test(basics, unknown, .init = cr_redirect_stdout)
{
    tinyprintf("Good morning ACU! %t Tinyprintf is cool");
    fflush(NULL);
    cr_assert_stdout_eq_str("Good morning ACU! %t Tinyprintf is cool");
}

Test(basics, tricky, .init = cr_redirect_stdout)
{
    tinyprintf("%c%c is %s... %d too.", '4', '2', "the answer", '*');
    fflush(NULL);
    cr_assert_stdout_eq_str("42 is the answer... 42 too.");
}

Test(extended, unsigned, .init = cr_redirect_stdout)
{
    tinyprintf("This is an unsigned: %u", 45);
    fflush(NULL);
    cr_assert_stdout_eq_str("This is an unsigned: 45");
}

Test(extended, plaintxt, .init = cr_redirect_stdout)
{
    tinyprintf("The quick brown fox jumps over the lazy dog");
    fflush(NULL);
    cr_assert_stdout_eq_str("The quick brown fox jumps over the lazy dog");
}

Test(extended, nulllll, .init = cr_redirect_stdout)
{
    tinyprintf("The quick brown fox jumps %s over the lazy dog", NULL);
    fflush(NULL);
    cr_assert_stdout_eq_str(
        "The quick brown fox jumps (null) over the lazy dog");
}

Test(extended, null2, .init = cr_redirect_stdout)
{
    tinyprintf(NULL);
    fflush(NULL);
    cr_assert_stdout_eq_str("");
}

Test(extended, octal, .init = cr_redirect_stdout)
{
    tinyprintf("Octal: %o", 10);
    fflush(NULL);
    cr_assert_stdout_eq_str("Octal: 12");
}

Test(extended, bigbig, .init = cr_redirect_stdout)
{
    tinyprintf("big num: %u", 4294959040);
    fflush(NULL);
    cr_assert_stdout_eq_str("big num: 4294959040");
}

Test(extended, deadcode, .init = cr_redirect_stdout)
{
    tinyprintf("%x", 3735929054);
    fflush(NULL);
    cr_assert_stdout_eq_str("deadc0de");
}
