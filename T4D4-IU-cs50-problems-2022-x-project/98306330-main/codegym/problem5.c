#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

unsigned int hash(const string);
bool is_alphabet_only(const string);

int main(int argc, string argv[])
{
    // コマンドライン引数の検証
    if (argc != 2 || !is_alphabet_only(argv[1]))
    {
        printf("Usage: ./problem5 word\n");

        return 1;
    }

    // ハッシュかした値を出力する
    printf("%i\n", hash(argv[1]));

    return 0;
}

bool is_alphabet_only(const string word)
{
    int length = strlen(word);
    for (int i = 0; i < length; i++)
    {
        if (!isalpha(word[i]))
        {
            return false;
        }
    }

    return true;
}

// ハッシュ関数
// TODO：オリジナルのハッシュ関数をさせよう。
//       返却値は必ず0または正の整数である。
//       引数wordは、すべてアルファベットのみで構成される文字列である。
//       ハッシュ値になるべく偏りのないように実装してください。
//       難易度1：26パターン(0-25を返す)
//       難易度2：52パターン(0-51を返す)
//       難易度3：256パターン(0-255を返す)

/*難易度1
unsigned int hash(const string word)
{
    int i = 0;
    for (int j = 0; j < strlen(word); j++)
    {
        int k = *(word + j);
        i += k;
    }
    return i % 26;
}
*/

/*難易度2
unsigned int hash(const string word)
{
    int i = 0;
    for (int j = 0; j < strlen(word); j++)
    {
        int k = *(word + j);
        i += k;
    }
    return i % 52;
}
*/
//難易度3
unsigned int hash(const string word)
{
    int i = 0;
    for (int j = 0; j < strlen(word); j++)
    {
        int k = *(word + j);
        i += k;
    }
    return i % 256;
}