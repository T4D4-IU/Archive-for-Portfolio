#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//プロトタイプ宣言
int only_digits(string s);
char rotate(int a, int b);

int main(int argc, string argv[])
{
    if (argc == 2) // プログラムが1つのコマンドライン引数で実行されたことを確認する。
    {
        if (only_digits(argv[1]) == false)
//コマンドライン引数内に数字以外が含まれている場合。
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
        else//コマンドライン引数が数字のみ
        {
            int n = atoi(argv[1]);
            string text = get_string("plaintext:");
            printf("ciphertext:");
            for (int i = 0; i < strlen(text); i++)//forループでtextの中身を出力
            {
                printf("%c", rotate(text[i], n));
            }
            printf("\n");
            return 0;
        }
    }
    else
    {
        printf("Usage:./ceaser key\n");//コマンドライン引数が1つで無い場合
        return 1;
    }
}

//int only_digitalsの中身
int only_digits(string s)
{
    for (int i = 0; i < strlen(s); i++)//テキストの長さ繰り返し
    {
        if (s[i] <= 48 || s[i] >= 57)//48↓もしくは57↑の場合エラー
        {
            return false;
            break;
        }
    }
    return true;
}


//char rotateの中身
char rotate(int a, int b)
{
    if (a >= 65 && a <= 90)//aの値が65～90の場合
    {
        a = a + (b % 26);
        if (a > 90)
        {
            a = a - 26;
            return a;
        }
        else
        {
            return a;
        }
    }
    else if (a >= 97 && a <= 122)
    {
        a = a + (b % 26);
        if (a > 122)
        {
            a = a - 26;
            return a;
        }
        else
        {
            return a;
        }
    }
    else
    {
        return a;
    }
}