//assignment gives the final answer if possible

void dfs1(int v,vector<vi>& g, vector<bool>& used, vi& order) {
    used[v] = true;
    for (int u : g[v]) {
        if (!used[u])
            dfs1(u,g,used,order);
    }
    order.push_back(v);
}

void dfs2(int v, int cl, vector<vi>& gt, vi& comp) {
    comp[v] = cl;
    for (int u : gt[v]) {
        if (comp[u] == -1)
            dfs2(u,cl,gt,comp);
    }
}

bool solve_2SAT(vector<vi>& g, vector<vi>& gt, vector<bool>& assignment) {
	int n = (int)g.size();
	vector<bool> used; vi comp; vi order;
    used.assign(n, false);
    for (int i = 0; i < n; ++i) {
        if (!used[i])
            dfs1(i,g,used,order);
    }

    comp.assign(n, -1);
    for (int i = 0, j = 0; i < n; ++i) {
        int v = order[n - i - 1];
        if (comp[v] == -1)
            dfs2(v,j++,gt,comp);
    }

    assignment.assign(n / 2, false);
    for (int i = 0; i < n; i += 2) {
        if (comp[i] == comp[i + 1])
            return false;
        assignment[i / 2] = comp[i] > comp[i + 1];
    }
    return true;
}

//sample example for reference
// FEW THINGS TO TAKE CARE OF IN MAIN
// 1) here n s number of terms and m is number of variables and its sored in g in order a1,!a1,a2,!a2,...,am,!am
//    so for ai index is g[2*(ai-1)] (0 indexed) and ch1,ch2 denote whether u,v are negated or not. 
// 2) If the term is (ai OR aj) then there will be 2 edges (!ai->aj) and (!aj->ai) this is done is ine 66 and 67.
// 3) Also make gt (transpose of g i.e revverting the edges) along the way.
// 4) assignment contains the final answer.
// 5) Remember to make g,gt of double the size of number of variables.

int main(void) {
    int n,m;
    cin>>n>>m;
    vector<vi> g(2*m);
    vector<vi> gt(2*m);
    vector<bool> assignment;

    for(int i = 0; i < n; i++) {
        char ch1,ch2;
        int u,v;
        cin>>ch1>>u>>ch2>>v;
        int m1=(ch1=='+'?0:1), m2=(ch2=='+'?0:1);
        g[2*(u-1)+(m1+1)%2].pb(2*(v-1)+m2);
        g[2*(v-1)+(m2+1)%2].pb(2*(u-1)+m1);
        gt[2*(v-1)+m2].pb(2*(u-1)+(m1+1)%2);
        gt[2*(u-1)+m1].pb(2*(v-1)+(m2+1)%2);
    }

    if(!solve_2SAT(g,gt,assignment)) {
        cout<<"IMPOSSIBLE"<<endl;
        return 0;
    }
    for(int i = 0; i < m; i++) {
        if(assignment[i])
            cout<<"+ ";
        else cout<<"- ";
    }
    cout<<endl;
}