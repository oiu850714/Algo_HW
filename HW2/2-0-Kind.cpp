#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::vector;
using std::max;
using std::lower_bound;

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
    for(int i = 0; i < n; i++)
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
    /*
    vector<int> old_row(n+1, 0);
    vector<int> new_row(n+1, 0);

    for(int i = 0; i <= n; i++) //there are n+1 elements in these two rows
    {
        for(int j = 0; j <= n; j++)
        {
            if(i == 0 || j == 0)
            {
                continue;
            } 
            else if(first_seq[i - 1] == sec_seq[j - 1]) 
            {//offset by -1, two seq have length n, but table row has length n + 1!
                new_row[j] = 1 + old_row[j-1];
            }
            else
            {
                new_row[j] = max(new_row[j-1], old_row[j]);
            }
        }
        old_row = new_row;
        new_row = vector<int>(n+1, 0);
    }
    return old_row[n];
    */
    vector<int> indices_of_sec_seq_i_in_first_seq(n + 1, 0);
    // define indices_of_sec_seq_i_in_first_seq[i]: the index of sec_seq[i],
    // which is a charactor appearing in first_seq, in first_seq

    //create hash table
    for(int i = 0; i <= n; i++)
    {
        indices_of_sec_seq_i_in_first_seq[first_seq[i]] = i;
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