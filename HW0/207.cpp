#include <iostream>
#include <string>
#include <algorithm>

using std::ios_base; using std::cin; using std::cout; using std::string; using std::max_element;
using std::begin; using std::end;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int frequency[26] = {0};

    string input;

    cin >> input;
    for(auto c : input)
        frequency[c - 97]++;
    
    cout << *max_element(begin(frequency), end(frequency));
}