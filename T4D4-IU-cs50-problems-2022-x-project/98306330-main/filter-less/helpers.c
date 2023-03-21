#include "helpers.h"
#include <math.h>

// Convert image to grayscale　　
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float rgbAve;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            rgbAve = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.00);
            //round()でroundのかっこの中をint型にして返す
            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i][j].rgbtRed = rgbAve;
            //右から代入されていくので同じRgbtAveの代入を3行書くより楽
        }
    }
    return;
}

// Convert image to sepia
int limit(int RGB)
//RGBの値が255を超えるとなんか変になってしまうので255より大きい場合は255を返す
{
    if (RGB > 255)
    {
        RGB = 255;
    }
    return RGB;
}

void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int SB;
    int SG;
    int SR;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            SB = limit(round((0.272 * image[i][j].rgbtRed) + (0.534 * image[i][j].rgbtGreen) + (0.131 * image[i][j].rgbtBlue)));
            SG = limit(round((0.349 * image[i][j].rgbtRed) + (0.686 * image[i][j].rgbtGreen) + (0.168 * image[i][j].rgbtBlue)));
            SR = limit(round((0.393 * image[i][j].rgbtRed) + (0.769 * image[i][j].rgbtGreen) + (0.189 * image[i][j].rgbtBlue)));
            //各色をそれぞれ計算しその結果を先に作っておいたlimit関数で255より大きくないか確かめてから代入

            image[i][j].rgbtBlue = SB;
            image[i][j].rgbtGreen = SG;
            image[i][j].rgbtRed = SR;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int tmp[3];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
//横を端から端まで2分線を中心とする線対称な位置にある点と交換すると半分を超えた所から元通りになって最終的に同じになってしまうので条件はWidth/2にする
        {
            tmp[0] = image[i][j].rgbtBlue;
            tmp[1] = image[i][j].rgbtGreen;
            tmp[2] = image[i][j].rgbtRed;

            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;

            image[i][width - j - 1].rgbtBlue = tmp[0];
            image[i][width - j - 1].rgbtGreen = tmp[1];
            image[i][width - j - 1].rgbtRed = tmp[2];
            //tmp配列を宣言し普通に交換
        }
    }
    return;
}

// Blur image
int Blured(int i, int j, int height, int width, RGBTRIPLE image[height][width], int color)
//4隅や端の事を考えて条件分岐するとプログラムが長くなり過ぎて辛いので関数を用意し解決を図る
{
    float count = 0;
    int sum = 0;
    for (int k = i - 1; k < (i + 2); k++)
    {
        for (int l = j - 1; l < (j + 2); l++)
        {
            if (k < 0 || k >= height)
            {
                break;
            }
            if (l < 0 || l >= width)
            {
                continue;
            }
            if (color == 0)
            {
                sum += image[k][l].rgbtBlue;
            }
            else if (color == 1)
            {
                sum += image[k][l].rgbtGreen;
            }
            else
            {
                sum += image[k][l].rgbtRed;
            }
            count++;
        }
    }
    return round(sum / count);//
}//

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = Blured(i, j, height, width, copy, 0);
            image[i][j].rgbtGreen = Blured(i, j, height, width, copy, 1);
            image[i][j].rgbtRed = Blured(i, j, height, width, copy, 2);
        }
    }
    return;
}
