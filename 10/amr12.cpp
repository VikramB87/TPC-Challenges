#include <vector>
#include <set>
#include <map>
#include <utility>
#include <iostream>
#include <cassert>
#include <algorithm>
using namespace std;

const int MAX_HOBBITS = 100;
const int MAX_HOLES   = 100;
const int MAX_TIME    = 10000000;
const int MAX_HOBBITS_PER_HOLE = 2;

int n, m, k, c;
int gTime[MAX_HOBBITS][MAX_HOLES];
int gTimeCopy[MAX_HOBBITS][MAX_HOLES];
unsigned char gHole[MAX_HOLES];   // Number of hobbits assigned to a hole

struct MinTimes {
    map<pair<int, int>, MinTimes*> paths;
    int min_time;       // Min time to get a better path
    int max_time;       // Max time on this path (a lesser time will result in the same or longer path)

    MinTimes () {
        min_time = 0;
        max_time = MAX_TIME+1;
    }
};

bool check (int from, int max_time, int done, MinTimes &minTimes, int &max_time_on_path, int &min_time)
{
    bool res;
    map<pair<int, int>, MinTimes*>::iterator it;
    MinTimes *mt = NULL;
    int tm;
    int lmax;

    min_time = MAX_TIME+1;

    for (int i = from; i < n; i++) {
        for (int j = 0; j < m; j++) {

            it = minTimes.paths.find (pair<int, int> (i, j));
            if (it != minTimes.paths.end()) mt = it->second;

            // We found a 'good' path, which took less time than 'max_time', we would find it again
            if (mt && (mt->max_time <= max_time)) return true;

            if (gTimeCopy[i][j] < min_time && gHole[j] < 2) min_time = gTimeCopy[i][j];

            if (gTimeCopy[i][j] <= max_time && gHole[j] < 2) {

                // A viable path
                if (gTimeCopy[i][j] > max_time_on_path) max_time_on_path = gTimeCopy[i][j];

                if (done + 1 == k) return true;

                if (mt && mt->min_time > max_time) {
                    // Can't get a better path with the required time
                    continue;
                }

                if (!mt) {
                    mt = new MinTimes;
                    minTimes.paths.insert (pair<pair<int, int>, MinTimes*> (pair<int, int>(i, j), mt));
                }

                if (gHole[j] == 0) {
                    for (int x = i+1; x < n; x++) gTimeCopy[x][j] = std::max (gTime[x][j], gTime[i][j]+c);
                }

                gHole[j]++;
                lmax = max_time_on_path;
                res = check (i+1, max_time, done+1, *mt, max_time_on_path, tm);

                // Restore state for next iteration
                gHole[j]--;
                if (gHole[j] == 0) {
                    for (int x = i+1; x < n; x++) gTimeCopy[x][j] = gTime[x][j];
                }

                if (res) {
                    if (max_time_on_path < mt->max_time) mt->max_time = max_time_on_path;
                } else {
                    max_time_on_path = lmax;
                    if (min_time > mt->min_time) mt->min_time = tm;
                }

                if (res) return true;
            }
        }
    }
    return false;
}

int solve (const vector<int> times)
{
    int low = 0, high = times.size()-1, mid;
    bool res;
    int x = 0, y = MAX_TIME+1;
    MinTimes mt;

    while (low != high) {
        // assert (low < high);
        mid = (low+high)/2;
        res = check (0, times[mid], 0, mt, x, y);
        if (!res) low = mid+1;
        else high = mid;
    }
    return times[low];
}

int main()
{
    int tc;
    set<int> all_times_set;
    vector<int> all_times_vec(MAX_HOLES * MAX_HOBBITS * MAX_HOBBITS_PER_HOLE);

    cin >> tc;
    for (int t = 0; t < tc; t++) {
        cin >> n >> m >> k >> c;
        all_times_set.clear ();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> gTime[i][j];
                gTimeCopy[i][j] = gTime[i][j];
                all_times_set.insert (gTime[i][j]);
                all_times_set.insert (gTime[i][j] + c);
            }
        }

        all_times_vec.clear ();
        all_times_vec.assign (all_times_set.begin (), all_times_set.end ());
        // for (vector<int>::iterator it = all_times_vec.begin(); it != all_times_vec.end(); it++) cout << *it << " ";
        cout << solve(all_times_vec) << endl;
    }
    return 0;
}


