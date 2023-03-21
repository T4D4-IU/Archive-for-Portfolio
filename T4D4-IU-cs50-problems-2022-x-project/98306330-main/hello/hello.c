#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("what is your name?/n"); //nameに名前を書き込む
    printf("hello, %s\n", name);
}