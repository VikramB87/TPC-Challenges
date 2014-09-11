#include <iostream>
#include <vector>
#include <stack>
#include <cassert>
using namespace std;

#define MAX 1000

vector<int> graph[MAX+1], rgraph[MAX+1];
stack<int> vstack;
int group[MAX+1], indegrees[MAX+1];
bool visited[MAX+1];

void DepthFirstTraversal (int vertex)
{
    visited[vertex] = true;
    for (int i = 0; i < graph[vertex].size(); i++) {
        if (!visited[graph[vertex][i]]) {
            DepthFirstTraversal (graph[vertex][i]);
        }
    }
    vstack.push(vertex);
}

void AssignGroupNumber (int vertex, int groupNum)
{
    visited[vertex] = false;
    group[vertex]   = groupNum;

    for (int i = 0; i < rgraph[vertex].size(); ++i ) {
        if (visited[rgraph[vertex][i]])  AssignGroupNumber (rgraph[vertex][i], groupNum);
    }
}

int main()
{
    int t, i, j, n, v, groupNum;

    cin >> t;
    while (t--) {

        cin >> n;

        // Initialize
        for (i = 1; i <= n; ++i) {
            graph[i].clear();
            rgraph[i].clear();
            visited [i] = false;
            indegrees[i] = 0;
        }

        for (i = 1; i <= n; ++i) {
            int m;
            cin >> m;
            for (j = 0; j < m; ++j) {
                cin >> v;
                graph[v].push_back (i);
                rgraph[i].push_back (v);
            }
        }

        for (i = 1; i <= n; ++i) {
            if (!visited[i]) DepthFirstTraversal (i);
        }

        // Assign group numbers
        groupNum = 0;
        while (!vstack.empty ()) {
            if (visited[vstack.top()]) {
                AssignGroupNumber (vstack.top(), groupNum);
                groupNum++;
            }
            vstack.pop ();
        }

        // Calculate indegrees for each group - how many people can beat the group?
        for (i = 1; i <= n; ++i) {
            for (j = 0; j < graph[i].size(); ++j) {
                if (group[i] != group[graph[i][j]]) {
                    indegrees[group[graph[i][j]]]++;
                }
            }
        }

        // Which group can no one beat?
        int count = 0;
        for (i = 0; i < groupNum; ++i) {
            if (indegrees[i] == 0)  ++count;
        }

        assert (count > 0);
        if (count == 1) {
            // Find the number of vertices in the group which has
            // indegree of 0.
            count = 0;
            for (i = 1; i <= n; ++i) {
                if (indegrees[group[i]] == 0) ++count;
            }
            cout << count << endl;
        } else {
            // More than one group has indegree of 0 - groups are disconnected
            cout << 0 << endl;
        }
    }

    return 0;
}

