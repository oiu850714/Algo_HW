#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::vector;
using std::max;

void get_answer(int n, vector<int> &answer_arr)
{

    for(int i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        answer_arr.push_back(tmp);
    }
}

int LCS(vector<int> &first_seq, vector<int> &sec_seq, const int n)
{
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