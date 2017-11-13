#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

using std::pair; using std::cout; using std::cin;
using std::vector; using std::sort; using std::min;
using std::abs;
using std::ios_base;
using std::nth_element;

struct point_class
{
    int64_t x, y;
};

bool compX(point_class p1, point_class p2);
bool compY(point_class p1, point_class p2);

vector<point_class> points;
auto points_sorted_by_x = points;
auto points_sorted_by_y = points;

vector<point_class>::iterator CP1;
vector<point_class>::iterator CP2;

//shitcode

int64_t closest_pair(vector<point_class>::iterator first,
                     vector<point_class>::iterator last); //last not included
int64_t distance_square(point_class &p1,
                        point_class &p2);

int64_t bruteForce(vector<point_class>::iterator first,
                   vector<point_class>::iterator last);

int flag = 0;

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
        point_class p = {x, y};
        points.push_back(p);
        points_sorted_by_x.push_back(p);
        points_sorted_by_y.push_back(p);
        //points_nth_element_by_y.push_back(p);
    }
    //sort(points_sorted_by_x.begin(), points_sorted_by_x.end(), compX);
    sort(points_sorted_by_y.begin(), points_sorted_by_y.end(), compY);
    //sort(points_sorted_by_x.begin(), points_sorted_by_x.end());

    //cout << closest_pair(points_sorted_by_y.begin(), points_sorted_by_y.end()) << "\n";
    closest_pair(points_sorted_by_y.begin(), points_sorted_by_y.end());
    flag = 1;
    auto delete_1_CP = closest_pair(points_sorted_by_y.begin(), points_sorted_by_y.end());
    flag = 2;
    auto delete_2_CP = closest_pair(points_sorted_by_y.begin(), points_sorted_by_y.end());
    cout << (delete_1_CP < delete_2_CP ? delete_1_CP : delete_2_CP) << "\n";
}


bool compX(point_class p1, point_class p2)
{
    return p1.x < p2.x;
}
bool compY(point_class p1, point_class p2)
{
    return p1.y < p2.y;
}

int64_t closest_pair(vector<point_class>::iterator first,
    vector<point_class>::iterator last)
{
    if(last - first <= 800)
        return bruteForce(first, last);
    
    auto mid = (last-first)/2;
    //nth_element(first, first + mid, last, ); //partition to two set of points,
    //USE Y coordinate!!!!!!!
    auto subproblem_min = min(closest_pair(first, first + mid),
                        closest_pair(first + mid, last));
    if (subproblem_min == 0)
        return subproblem_min;
    
    vector<point_class> in_sub_min_boundary;
    for(auto it = first; it < last; it++)
    {
        if(flag == 0)
            ;
        else if(flag == 1)
        {
            if(it == CP1 || (first + mid) == CP1)
                continue;
        }
        else if(flag == 2)
        {
            if(it == CP2 || (first + mid) == CP2)
                continue;
        }
        if( abs((it->y - (first + mid)->y)) < subproblem_min)
            in_sub_min_boundary.push_back(*it);
    }
    sort(in_sub_min_boundary.begin(), in_sub_min_boundary.end(), compX);
    //select points whose y - mid's y < sudproblem_min

    for(auto it_first = in_sub_min_boundary.begin(); it_first < in_sub_min_boundary.end(); it_first++)
    {
        for(auto it_eight = it_first + 1; 
                it_eight < in_sub_min_boundary.end() && it_eight - it_first < 8;
                it_eight++)
        {
            if(flag == 0)
            {   auto temp_dis = distance_square(*it_first, *it_eight);
                //subproblem_min = temp_dis < subproblem_min ? temp_dis : subproblem_min;
                if(temp_dis < subproblem_min)
                {
                    subproblem_min = temp_dis;
                    CP1 = it_first;
                    CP2 = it_eight;
                }
                if(temp_dis == 0)
                    return temp_dis;
            }
            else if(flag == 1)
            {
                if(it_first == CP1 || it_eight == CP2)
                    continue;
                auto temp_dis = distance_square(*it_first, *it_eight);
                //subproblem_min = temp_dis < subproblem_min ? temp_dis : subproblem_min;
                if(temp_dis < subproblem_min)
                {
                    subproblem_min = temp_dis;
                }
                if(temp_dis == 0)
                    return temp_dis;
            }
            else if(flag == 2)
            {   
                if(it_first == CP2 || it_eight == CP2)
                    continue;
                auto temp_dis = distance_square(*it_first, *it_eight);
                //subproblem_min = temp_dis < subproblem_min ? temp_dis : subproblem_min;
                if(temp_dis < subproblem_min)
                {
                    subproblem_min = temp_dis;
                }
                if(temp_dis == 0)
                    return temp_dis;
            }
        }
    }
    return subproblem_min;
}

int64_t distance_square(point_class &p1, point_class &p2)
{
    //cout << "I'n stupid: " << (p1.first - p2.first) * (p1.first - p2.first)
    //+ (p1.second - p2.second) * (p1.second - p2.second) << "\n";
    return (p1.x - p2.x) * (p1.x - p2.x)
    + (p1.y - p2.y) * (p1.y - p2.y);
}

int64_t bruteForce(vector<point_class>::iterator first,
    vector<point_class>::iterator last)
{
    int64_t min_value = INT64_MAX;
    for(auto fir_pt_it = first; fir_pt_it != last; fir_pt_it++) // first to last-2
    {
        for(auto sec_pt_iter = fir_pt_it + 1; sec_pt_iter != last; sec_pt_iter++)
        {
            if(flag == 0)
            {
                auto dis = distance_square(*fir_pt_it, *sec_pt_iter);
                if(dis < min_value)
                {
                    min_value = dis;
                    CP1 = fir_pt_it;
                    CP2 = sec_pt_iter;
                }
                //min_value = min_value <= dis ? min_value : dis;
                if(min_value == 0)
                    return min_value;
            }
            else if(flag == 1)
            {
                if(fir_pt_it == CP1 || sec_pt_iter == CP1)
                    continue;
                
                auto dis = distance_square(*fir_pt_it, *sec_pt_iter);
                min_value = min_value <= dis ? min_value : dis;
            }
            else if(flag == 2)
            {
                if(fir_pt_it == CP2 || sec_pt_iter == CP2)
                continue;

                auto dis = distance_square(*fir_pt_it, *sec_pt_iter);
                min_value = min_value <= dis ? min_value : dis;
            }
        }
    }
    return min_value;
}