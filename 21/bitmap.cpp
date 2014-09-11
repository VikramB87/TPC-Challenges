#include <iostream>
#include <cstdio>
#include <queue>
#include <utility>
using namespace std;

const int MAX=200;

typedef pair<int,int> Point;

short row, col;
short dist[MAX][MAX];
char bitmap[MAX][MAX];

void BreadthFirstTraverse (queue<Point> &visited)
{
    short i, j, x, y, d;
    short neighbours[][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};
    Point p;

    while (!visited.empty()) {
        // Remove first element
        p = visited.front();
        visited.pop();
        d = dist[p.first][p.second];

        // Visit all unvisited adjacent nodes
        for (i=0; i < 4; i++) {
            x = p.first + neighbours[i][0];
            y = p.second + neighbours[i][1];
            if (dist[x][y] == -1) {
                visited.push(Point(x,y));
                dist[x][y] = d+1;
            }
        }
    }
}

int main()
{
    int n, i, j;
    queue<Point> visited;

    // Number of test cases
    cin >> n;
    while(n--) {
        // Read in number of rows and columns in bitmap
        cin >> row >> col;
        // Read in the bitmap
        for(i=0; i<row; i++) {
            cin >> bitmap[i];
        }

        // Initialize distances
        for(i=0; i < row; i++) {
            for(j=0; j < col; j++) {
                dist[i][j] = -1;
            }
        }

        for(i=0; i < row; i++) {
            for(j=0; j < col; j++) {
                // White cell - we need to traverse from this cell
                if (bitmap[i][j]== '1') {
                    dist[i][j] = 0;
                    visited.push(Point(i,j));
                }
            }
        }

        BreadthFirstTraverse (visited);

        // Print output
        for (i = 0; i < row; i++) {
            for(j=0; j < col; j++) cout << dist[i][j] << " ";
            cout << endl;
        }
    }
    return 0;
}
