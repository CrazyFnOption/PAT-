/*
	这个算法的思路跟我一模一样，只不过其有一个地方的优化就在于 将好的路 费用为0，坏的费用直接保存下来
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int inf = 0x3f3f3f3f;

struct Edge{
    int u, v, w;
    bool operator < (const Edge &b) const{
        return w < b.w;
    }
}edge[404014];

struct Node{
    int id, sum_w;
    bool operator < (const Node &b) const{
        if(sum_w == b.sum_w) return id < b.id;
        return sum_w > b.sum_w;
    }
}rec[504];

int n, m;
int f[504];

void init_f() {
    for(int i = 0; i <= n; i++)
        f[i] = i;
    return;
}

int get_f(int x){
    if(x == f[x]) return x;
    return f[x] = get_f(f[x]);
}

bool Merge(int x, int y){
    int t1 = get_f(x);
    int t2 = get_f(y);
    if(t1 == t2) return false;
    else {
        f[t2] = t1;
        return true;
    }
}
int Kruskal(int id){
    int num = 0, sum = 0;
    init_f();
    for(int i = 0; i < m; i++){
        if(edge[i].u == id || edge[i].v == id)
            continue;
        if(Merge(edge[i].u, edge[i].v)){
            num++;
            sum += edge[i].w;
        }
        if(num == n-2) break;
    }
    if(num == n-2) return sum;
    else return inf;
}

int main(){
    int sa;
    while(~scanf("%d %d", &n, &m)){
        if(n == 1){
            printf("0\n");
        }
        for(int i = 0; i < m; i++){
            scanf("%d %d %d %d", &edge[i].u, &edge[i].v, &edge[i].w, &sa);
            if(sa) edge[i].w = 0;
        }
        sort(edge, edge+m);
        for(int i = 1; i <= n; i++){
            rec[i].id = i;
            rec[i].sum_w = Kruskal(i);
        }
        sort(rec+1, rec+n+1);
        int mav = rec[1].sum_w;
        if(mav == 0){
            printf("0\n");
        }
        else {
            printf("%d", rec[1].id);
            for(int i = 2; i <= n; i++){
                if(rec[i].sum_w == mav){
                    printf(" %d", rec[i].id);
                }
                else break;
            }
            printf("\n");
        }
    }
    return 0;
}



