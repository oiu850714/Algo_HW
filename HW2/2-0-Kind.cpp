#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::vector;
using std::max;
using std::lower_bound;

//IN THIS SHITCODE, KEEP ALL FUCKING OFFSETS IN MIND, SOME OF LOOPS MAY RUTN N+1 TIMES

void get_answer(int n, vector<int> &answer_arr)
{
    answer_arr.push_back(0);// FUCK YOU OFFSET
    for(int i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        answer_arr.push_back(tmp);
    }
}

int LIS(vector<int> &seq, const int n)
{
    vector<int> IS_of_length_i(n + 1, INT32_MAX);
    for(int i = 0; i <= n; i++)
    {
        auto location = lower_bound(IS_of_length_i.begin(), IS_of_length_i.end(), seq[i]);
        *location = seq[i];
    }

    for(int i = n; i>=0; i--)
    {
        if(IS_of_length_i[i] != INT32_MAX)
            return i;
    }
}

int LCS(vector<int> &first_seq, vector<int> &sec_seq, const int n)
{
    vector<int> indices_of_sec_seq_i_in_first_seq(n + 1, 0);

    //create hash table
    for(int i = 0; i <= n; i++)
    {
        indices_of_sec_seq_i_in_first_seq[first_seq[i]] = i;
        // let first_seq[i]'s code be i
        // then indices_of_sec_seq_i_in_first_seq[first_seq[i]] is i
        //e.g.
        // 1  2  3  4  5  6  7  8  9
        //[a][d][e][c][b][f][g][h][i]
        // =>
        // a  b  c  d  e  f  g  h  i
        //[1][5][4][2][3][6][7][8][9]
    }

    vector<int> sec_seq_to_encode_array(n + 1, 0);
    for(int i = 0; i <= n; i++)
    {
        sec_seq_to_encode_array[i] = indices_of_sec_seq_i_in_first_seq[sec_seq[i]];
    }
    //encode sec_seq

    return LIS(sec_seq_to_encode_array, n);
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<int> correct_answer;
    vector< vector<int>> student_answers;

    get_answer(n, correct_answer);

    for(int i = 0; i < m; i++)
    {
        student_answers.push_back(vector<int>());
        get_answer(n, student_answers[i]);
    }

    for(int i = 0; i < m; i++)
    {
        std::cout << LCS(correct_answer, student_answers[i], n) << "\n";
    }

}