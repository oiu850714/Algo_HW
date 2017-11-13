#include <iostream>
#include <string>

using std::cin; using std::cout; using std::ios_base;
using std::string;

bool f(const string &S1, const string &S2);
void compute_min_equavelence(string &S_result, const string &S_start);

int main()
{
    string S1, S2;
    int n;
    cin >> n;

    while(n--)
    {
        cin >> S1 >> S2;
        f(S1, S2);
    }
}

bool f(const string &S1, const string &S2)
{
    if(S1 == S2)
        cout << "Yes\n";
    else if(S1.size() % 2) // two string are smae length so only chack S1
        cout << "No\n";
    else
    {
        string equivelenct_min_S1, equivelenct_min_S2;
        compute_min_equavelence(equivelenct_min_S1, S1);
        compute_min_equavelence(equivelenct_min_S2, S2);
        //cout << equivelenct_min_S1 << "  VS  " << equivelenct_min_S2 << "\n";
        equivelenct_min_S1 == equivelenct_min_S2 ? cout << "Yes\n" : cout << "No\n";
    }
}

void compute_min_equavelence(string &S_result, const string &S_start)
{
    if(S_start.size() % 2) // S_start is odd
    {
        S_result = S_start;
    }
    else
    {
        string S_start_left(S_start, 0, S_start.size()/2);
        string S_start_right(S_start, S_start.size()/2); // +1 is important?
        string equivelenct_min_S_start_left;
        string equivelenct_min_S_start_right;
        compute_min_equavelence(equivelenct_min_S_start_left, S_start_left);
        compute_min_equavelence(equivelenct_min_S_start_right, S_start_right);
        if(equivelenct_min_S_start_left <= equivelenct_min_S_start_right)
            S_result = equivelenct_min_S_start_left + equivelenct_min_S_start_right;
        else
            S_result = equivelenct_min_S_start_right + equivelenct_min_S_start_left;
    }
}