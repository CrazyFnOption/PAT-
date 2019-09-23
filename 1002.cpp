/*
	看到这道题的第一个想法就去考虑了一下 要不要使用贪心，想了很多贪心策略，
    但是后面发现，由于无论怎么取出来，都无法实现，全局选取的一个最优点就是题目所最后要求的最优点。
    所以，考虑 动态规划。

    但是这个动态规划是有条件的，得需要将 所有的deadline进行一个排序，保障deadline最优先进行考虑

    ！！！！ 到最后竟然发现是一个背包问题，真的感觉是惊呆了。
*/
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <cstdio>
#include <queue>
#include <map>
#include <cmath>

using namespace std;

struct Project{
    int profit;
    int last;
    int deadline;

    bool operator < (const Project & p)const {
        return deadline < p.deadline;
    }
}project[55];


int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    int Max = -1;
    for (int i = 0; i < n; i++) {
        cin >> project[i].profit >> project[i].last >> project[i].deadline;
        Max = max(Max,project[i].deadline);
    }

    //这里之所以存在一个排序，是建立在 需要将交换时间晚的deadlin 给先完成，这样的话，就可以在后面进行比较，看看要不要先完成这个，

    //可以当做是一个 现将deadline进行一个贪心策略的选取，然后后面使用动态规划的背包，来考虑当前位置选不选。
    sort(project,project + n);
    int dp[Max + 1];
    memset(dp,0,sizeof dp);
    
    int res = -1;
    for (int i = 0; i < n; i++) {
        //将最长完成的时间，当成这个背包的容量
        for (int j = Max; j >= project[i].last; j--) {
            //如果该任务的结束时间正好就在 总背包容量里面，那么就可以直接装入
            //但是如果 不在，那么进行一个比较，压缩这个背包，让这个背包加上这个重量，可以得到的最后利润，是否等于最后结果
            if (j > project[i].deadline) dp[j] = project[i].profit;
            else dp[j] = max(dp[j],dp[j - project[i].last] + project[i].profit);
            res = max(res, dp[j]);
        }
    }

    cout << res << endl;


    return 0;
}