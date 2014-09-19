#include <iostream>
#include <queue>
#include <bitset>
using namespace std;

typedef unsigned char Byte;

const int MAX = 25;
int n;
Byte grid[MAX][MAX];                // Input grid
Byte change_time[MAX][MAX];         // State change time

struct Point {
    int x;
    int y;
    int t;      // Time

    Point (int _x = 0, int _y = 0, int _t = 0) : x(_x), y(_y), t(_t) {}
};

void TraverseBreadthFirst ()
{
    queue<Point> q;
    const int MAX_TIME = 500;
    bitset<MAX*MAX> visited[MAX_TIME];      // Has a point (x,y) been visited at time t?
    Point p;
    int nb[][2] = {{0,1}, {0,-1}, {-1,0}, {1,0},{0,0}};
    int x, y, t;
    int pos;

    q.push (Point (0, 0, 0));       // At home at time 0

    while (!q.empty()) {
        p = q.front();
        q.pop();

        // Got to office!
        if ((p.x == n-1) && (p.y == n-1)) {
            cout << p.t << endl;
            return;
        }

        // Try all possibilities for movement, including not moving
        for (int i = 0; i < 5; i++) {
            x = p.x + nb[i][0];
            y = p.y + nb[i][1];
            t = p.t + 1;
            pos = y*MAX + x;

            // Valid neighbour and not visited at time t
            if ((x >= 0) && (y >= 0) && (x < n) && (y < n) && (t < MAX_TIME) && !visited[t][pos]) {
                // Can it be visited?
                if (change_time[x][y] == 0) {
                    if (grid[x][y] == 0) {
                        visited[t][pos] = 1;
                        q.push (Point (x, y, t));
                    }
                } else {
                    if (grid[x][y] == ((t / change_time[x][y]) & 1)) {
                        visited[t][pos] = 1;
                        q.push (Point (x, y, t));
                    }
                }
            }
        }
    }

    cout << "NO" << endl;
}

int main()
{
    int t;
    int i, j;
    char buf[32];

    cin >> t;
    while (t--) {

        cin >> n;

        for (i = 0; i < n; i++) {
            cin>>buf;
            for (j = 0; j < n; j++) {
                grid[i][j] = (buf[j] == '*');
            }
        }

        for (i = 0; i < n; i++) {
            cin >> buf;
            for (j = 0; j < n; j++) {
                change_time[i][j] = buf[j] - '0';
            }
        }

        TraverseBreadthFirst ();
    }

    return 0;
}
