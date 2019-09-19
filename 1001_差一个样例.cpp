/*
	这道题的问题就出在 题目上说要保护城市，且该城市不能的修理费用是最多，
    但是如果存在可能就是，去掉某个城市，剩余的城市根本不能 加载一起

    所以需要将这种特殊情况的全部根除。

    有一种思想就是直接将边进行排序，然后再使用并查集，这样的话 反而更简便
*/
#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
#include<vector>
#include<cstdio>
#include<queue>
#include<map>
#include<cmath>

using namespace std;

const int maxn = 505;
int cc[maxn][maxn];
vector<int>v[maxn];
int cost[maxn][maxn];
vector<pair<int,int> > vp;
vector<int>res;

int n,m;
bool vis[maxn];
int fa[maxn];
int cnt;

void init() {
    for (int i = 0; i < n + 10; i++) {
        fa[i] = i;
    }
    cnt = 0;
}

int find(int x) {
    if (fa[x] == x) return x;
    return fa[x] = find(fa[x]);
}

void unite(int x,int y) {
    x = find(x);
    y = find(y);
    if (x != y) fa[x] = y;
}

void check() {
    for (int i = 1; i <= n; i++) {
        if (fa[i] == i) {
            res.push_back(i);
            cnt++;
        }
    }
}

int main()
{
	
    cin >> n >> m;
    int a,b,c,d;
    memset(cc,-1,sizeof cc);
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c >> d;
        v[a].push_back(b);
        v[b].push_back(a);
        cc[a][b] = cc[b][a] = d;
        cost[a][b] = cost[b][a] = c;
        vp.push_back(make_pair(a,b));
    }

    if (n == 1) {
        cout << 0 << endl;
        return 0;
    }
    int Max = -1;
    vector<int>index;
    for (int i = 1; i <= n; i++) {
        init();
        int sum = 0;
        for (int j = 0; j < vp.size(); j++) {
            if (vp[j].first != i && vp[j].second != i && cc[vp[j].first][vp[j].second] == 1) {
                unite(vp[j].first, vp[j].second);
            }
        }
        check();
        cnt--;
        if(cnt <= 1) continue;
        int x = 0;
        for (int j = 0; j < res.size(); j++) {
            if (res[j] == i) continue;
            for (int k = j + 1; k < res.size(); k++) {
                if (res[k] == i) continue;
                if (find(res[j]) == find(res[k])) continue;
                if (cc[res[j]][res[k]] != 0) continue;
                sum += cost[res[j]][res[k]];
                unite(res[j], res[k]);
            }
            for (int i = 1; i <= n; i++) {
                if (fa[i] == i) x++;
            }
            if (x == 2) break;
        }
        x = 0;
        
        for (int i = 1; i <= n; i++) {
                if (fa[i] == i) x++;
            }
    
        if (x > 2) sum = 0x3f3f3f3f;
        if (Max < sum) {
            Max = sum;
            index.clear();
            index.push_back(i);
        }
        else if (Max == sum) index.push_back(i);
    }

    if (Max == -1) cout << 0 << endl;
    else {
        sort(index.begin(),index.end());
        for (int i = 0; i < index.size(); i++) {
            cout << index[i];
            if (i != index.size() - 1) cout << " ";
        }
        cout << endl;
    }
	
    return 0;
}