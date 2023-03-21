#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

const int BLOCK_SIZE = 512;
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
//プログラムが正確に1つのコマンドライン引数で実行されていない場合は、ユーザに正しい使い方を知らせ、mainは1を返します。
//プログラムは、JPEGを復元するフォレンジックイメージの名前であるコマンド行引数を1つだけ受け入れる必要があります。
    if (argc != 2)//コマンドライン引数が1つ以外の場合で分岐
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    //ファイルを開く
    FILE *input_file = fopen(argv[1], "r");//open memory card
    if (input_file == NULL)
    {
        printf("Error: cannot open file\n");
        return 1;
    }
    BYTE buffer[BLOCK_SIZE];
    //ファイル名を保存する変数
    //string filename = malloc;
    int counter = 0;
    char filename[8];
    //アウトプットファイルを保存する変数
    FILE *output_file;

    while (fread(&buffer, sizeof(BYTE), BLOCK_SIZE, input_file))
    {
        //最初の４バイトがjpgの始まりであることが判別できる
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //もし書き出し中のファイルがあれば閉じる
            if (!(counter == 0))
            {
                fclose(output_file);
            }

            //ファイル名
            sprintf(filename, "%03i.jpg", counter);
            output_file = fopen(filename, "w");
            counter++;
        }
        if (!(counter == 0))
        {
            fwrite(&buffer, sizeof(BYTE), BLOCK_SIZE, output_file);
        }
    }
    //開いたファイルをすべて閉じる
    fclose(input_file);
    fclose(output_file);
    return 0;
}