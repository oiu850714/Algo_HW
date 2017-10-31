#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

using std::pair; using std::cout; using std::cin;
using std::vector; using std::sort; using std::min;
using std::abs;
using std::ios_base;
using std::nth_element;

vector<pair<int64_t, int64_t>> points;
auto points_sorted_by_x = points;
auto points_sorted_by_y = points;

//shitcode

int64_t closest_pair(vector<pair<int64_t, int64_t>>::iterator first,
                     vector<pair<int64_t, int64_t>>::iterator last);
int64_t distance_square(pair<int64_t, int64_t> &p1,
                        pair<int64_t, int64_t> &p2);

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int64_t n;
    cin >> n;
    while(n--)
    {
        int64_t x, y;
        cin >> x >> y;
        pair<int64_t, int64_t> p(x, y);
        points.push_back(p);
        points_sorted_by_x.push_back(p);
        p.first = y, p.second = x;
        points_sorted_by_y.push_back(p);
    }
    
    sort(points_sorted_by_x.begin(), points_sorted_by_x.end());
    sort(points_sorted_by_y.begin(), points_sorted_by_y.end());

    cout << closest_pair(points_sorted_by_y.begin(), points_sorted_by_y.end()) << "\n";
}

int64_t closest_pair(vector<pair<int64_t, int64_t>>::iterator first,
    vector<pair<int64_t, int64_t>>::iterator last)
{
    if(last - first < 3)
    {
        int64_t min_value = INT64_MAX;
        for(auto fir_pt_it = first; fir_pt_it < last - 1; fir_pt_it++)
        {
            for(auto sec_pt_iter = fir_pt_it + 1; sec_pt_iter < last; sec_pt_iter++)
            {
                auto dis = distance_square(*fir_pt_it, *sec_pt_iter);
                min_value = min_value <= dis ? min_value : dis;
            }
        }
        return min_value;
    }
    
    auto mid = first + (last-first)/2;

    int64_t subproblem_min = min(closest_pair(first, mid),
                        closest_pair(mid + 1, last));
    
    vector<pair<int64_t, int64_t>> in_min_boundary;
    for(auto it = points_sorted_by_x.begin(); it < points_sorted_by_x.end(); it++)
    {
        if( abs((it->second - mid->second)) < subproblem_min)
            in_min_boundary.push_back(*it);
    }
    //select points whose y - mid's y < sudproblem_min

    for(auto it_first = in_min_boundary.begin(); it_first != in_min_boundary.end(); it_first++)
    {
        for(auto it_eight = it_first + 1; it_eight != in_min_boundary.end(); it_eight++)
        {
            int64_t temp_dis = distance_square(*it_first, *it_eight);
            subproblem_min = temp_dis < subproblem_min ? temp_dis : subproblem_min;
        }
    }
    return subproblem_min;
}

int64_t distance_square(pair<int64_t, int64_t> &p1, pair<int64_t, int64_t> &p2)
{
    //cout << "I'n stupid: " << (p1.first - p2.first) * (p1.first - p2.first)
    //+ (p1.second - p2.second) * (p1.second - p2.second) << "\n";
    return (p1.first - p2.first) * (p1.first - p2.first)
    + (p1.second - p2.second) * (p1.second - p2.second);
}