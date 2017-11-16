#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::vector;
using std::max;
using std::lower_bound;
using std::reverse;

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

auto LIS(vector<int> &seq, const int n)
{
    //vector<int> prev_elements;
    vector<int> IS_of_length_i(n + 1, INT32_MAX);
    vector<int> prev(n + 1, -1);
    for(int i = 0; i <= n; i++)
    {
        auto location = lower_bound(IS_of_length_i.begin(), IS_of_length_i.end(), seq[i]);
        *location = seq[i];
        prev[i] = location - IS_of_length_i.begin();
    }

    
    int lis_len = n;
    for(; lis_len >= 0; lis_len--)
    {
        if(IS_of_length_i[lis_len] != INT32_MAX)
            break;
    }
    

    vector<int> LIS_seq;
    for(int i = n; i >= 0; i--)
    {
        if(prev[i] != lis_len)
        {
            continue;
        } 
        else
        {
            LIS_seq.push_back(seq[i]);
            lis_len--;
        }
    }
    reverse(LIS_seq.begin(), LIS_seq.end());
    return LIS_seq;
}

void LCS(vector<int> &first_seq, vector<int> &sec_seq, const int n)
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

    auto LIS_result = LIS(sec_seq_to_encode_array, n);
    for(int i = 1; i < LIS_result.size(); i++)
    {
        std::cout << first_seq[LIS_result[i]] << " ";
    }
    std::cout << "\n";
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
        LCS(correct_answer, student_answers[i], n);
    }

}