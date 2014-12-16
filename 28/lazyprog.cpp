#include <queue>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <ios>

typedef unsigned int UInt;

const UInt MAX_JOBS = 100000;

struct Job {
    UInt a;
    UInt b;
    UInt d;
};
Job jobs[MAX_JOBS];

bool CompareJobs (const Job &a, const Job &b)
{
    return (a.d < b.d);
}

typedef bool (*CompareFunc) (const Job&, const Job&);
bool CompareJobsByA (const Job &a, const Job &b)
{
    return (a.a < b.a);
}

int main()
{
    UInt t;
    UInt n;

    std::cin >> t;

    for(UInt i = 0; i < t; ++i)
    {
        std::cin >> n;
        for(UInt j = 0; j < n; j++) {
            std::cin >> jobs[j].a >> jobs[j].b >> jobs[j].d;
        }

        // Sort by deadline
        std::sort (jobs, jobs + n, CompareJobs);

        // Priority queue sorted by 'a'
        std::priority_queue <Job, std::vector<Job>, CompareFunc> queue(CompareJobsByA);
        UInt total = 0;
        long double extra = 0;

        for (UInt j = 0; j < n; j++) {

            queue.push (jobs[j]);
            total = total + jobs[j].b;

            // Still within deadline
            if (total < jobs[j].d) {
                continue;
            } else {
                while (total > jobs[j].d) {
                    // Get job with highest 'a'
                    Job x = queue.top ();
                    queue.pop();

                    if((total - jobs[j].d) < x.b) {
                        extra += (long double) ((total - jobs[j].d)/ ((long double) x.a));
                        x.b -= (total - jobs[j].d);
                        queue.push (x);
                        total = jobs[j].d;
                    } else {
                        extra +=  (((long double) x.b) / ((long double) x.a));
                        total -= x.b;
                    }
                }
            }
        }

        std::cout << std::setiosflags (std::ios::fixed) << std::setprecision(2) << extra << std::endl;
    }

    return 0;
}
