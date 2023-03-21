#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string text);

int main(void)
{
    string text = get_string("Text:");//input texts

    int T = count_letters(text);
    //printf("%d\n", T);

    if (T < 1)//1未満と1以上で分ける
    {
        printf("Before Grade 1\n");
    }
    else if (T > 16)//16より大きいか16以下かで分ける
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", T);
    }

}

int count_letters(string text)
{
    int j = strlen(text);
    double L = 0;//L=文字数になるので初期値0
    double S = 0;//S=文数になるので初期値
    double B = 1;
//B=単語数になる。正確には空白の数を数えていて単語の数＝空白の数＋１なので初期値１
//51行目～53行目で空白の数を数えている。1単語のみでは空白は出来ないので初期値1

    for (int i = 0; i < j; i++)
    {
        if (isupper(text[i]))//アルファベットの大文字か判定
        {
            L += 1;
            //printf("L:%f\n", L);
        }
        else if (islower(text[i]))//アルファベットの小文字か判定
        {
            L += 1;
            //printf("L:%f\n", L);
        }
        else if ((text[i]) == '.' || text[i] == '!' || text[i] == '?')
        {
            S += 1;
            //printf("S:%f\n", S);
        }
        else if (isspace(text[i]))
        {
            B += 1;
            //printf("B:%f\n", B);
        }
    }


    //printf("L:%f,S*%f,B:%f\n", L, S, B);
    double Letter = L / B * 100;
    //printf("Letter:%f\n", Letter);
//100単語あたりの平均字数LetterはL÷B×100=Letterで求めれる
    double Sentence = S / B * 100;
    //printf("Sentence:%f\n", Sentence);
//100単語あたりの平均文数SentenceはS÷B×100=Sentenceで求めれる
    double index = 0.0588 * Letter - 0.296 * Sentence - 15.8;//Coleman-Liau Index
    //printf("index:%f\n", index);
    int indexx = 0.0588 * Letter - 0.296 * Sentence - 15.8;
    if (index - indexx >= 0.5)
    {
        index++;
    }
    //printf("index:%f\n", index);


    return index;
}