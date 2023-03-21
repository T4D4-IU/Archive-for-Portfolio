#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

//################################################メイン関数ここから#################################################

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;//候補者数が決まる
    if (candidate_count > MAX_CANDIDATES)//候補者数がMAXより多い場合2を返す
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)//候補者の人数だけ名前と得票数と欠落判定の初期化を行う
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");//投票する回数を入力
    if (voter_count > MAX_VOTERS)//投票する回数がMAXより多い場合3を返す
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)//投票する回数だけ繰り返し
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)//候補者の数だけ繰り返し
        {
            string name = get_string("Rank %i: ", j + 1);//自分が投票する人の名前を入力

            // Record vote, unless it's invalid    vote関数で75行目で入れた人の名前が54～58行目で入れた人と合致するか確認。
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists　勝利者が現れるまで終らない
    while (true)
    {
        // Calculate votes given remaining candidates　残りの候補者の得票数を計算する
        tabulate();

        // Check if election has been won　当選しているかどうかを確認するもし勝っていればBreak
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates　最下位候補の排除
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins　もし引き分けなら全員勝利でBreak
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes 最小得票の人を排除する
        eliminate(min);

        // Reset vote counts back to zero　全員の得票数を０にリセットする
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

//####################################################関数ココカラ###############################################################


// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // TODO エラーが消えたので完了
    for (int i = 0; i < candidate_count; i ++)
    {
        string s = candidates[i].name;
        if (strcmp(s, name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // TODO エラー消えたので完了
    for (int i = 0; i < voter_count; i++)
    {
        int j = 0;
        while (candidates[preferences[i][j]].eliminated == true)
        {
            j++;
        }
        candidates[preferences[i][j]].votes++;
    }
    return;
}

// Print the winner of the election, if there is one　
bool print_winner(void)
{
    // TODO　エラーが消えたので完了
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes >= voter_count / 2 + 0.5)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has 残りの候補者の最小得票数を返します。
int find_min(void)
{
    // TODO エラー消えたので完了
    int min = candidates[0].votes;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes < min && candidates[i].eliminated == false)
        {
            min = candidates[i].votes;
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise すべての候補者が同点の場合はtrue、それ以外はfalseを返す。
bool is_tie(int min)
{
    // TODO　各候補者の得票数を最小投票者の得票数と比較する試行を候補者の人数分繰り返しtrueかfalseを返す
    int counttie = 0;
    int remain = 0;
    bool istie = false;
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated)
        {
            remain++;
        }
        if (candidates[i].votes == min)
        {
            counttie++;
        }
        if (counttie == remain)
        {
            istie = true;
        }
        if (counttie != remain)
        {
            istie = false;
        }
    }
    return istie;
}

// Eliminate the candidate (or candidates) in last place 最下位候補の排除
void eliminate(int min)
{
    // TODO　各候補者の得票数を最下位候補の得票数と比較する試行を候補者の人数分繰り返し、最下位候補者と得票数が同じ人のeliminatedをtrueにする
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}