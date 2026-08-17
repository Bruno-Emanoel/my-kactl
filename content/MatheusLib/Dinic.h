/**
 * Author: Matheus Dias Queiroz
 * Date: 13-08-2027
 * License: no
 * Source: folklore
 * Description: Calculates a valid assignment to boolean variables a, b, c,... to a 2-SAT problem,
 * so that an expression of the type $(a||b)\&\&(!a||c)\&\&(d||!b)\&\&...$
 * becomes true, or reports that it is unsatisfiable.
 * Negated variables are represented by bit-inversions (\texttt{\tilde{}x}).
 * Usage:
 *  TwoSat ts(number of boolean variables);
 *  ts.either(0, \tilde3); // Var 0 is true or var 3 is false
 *  ts.setValue(2); // Var 2 is true
 *  ts.atMostOne({0,\tilde1,2}); // <= 1 of vars 0, \tilde1 and 2 are true
 *  ts.solve(); // Returns true iff it is solvable
 *  ts.values[0..N-1] holds the assigned values to the vars
 * Time: O(N+E), where N is the number of boolean variables, and E is the number of clauses.
 * Status: stress-tested
 */
struct dinic{
    struct edge{
        int to;
        int cap;
        int flow;
        int rev;
    };
    int n;
    v<v<edge>> graph;
    v<int> lvl;
    v<int> ptr;
    dinic(int n) : n(n), graph(n), lvl(n),ptr(n) {}
    void add_edge(int from, int to, int cap){
        graph[from].pb({to,cap,0,(int)graph[to].size()});
        graph[to].pb({from,0,0,(int)graph[from].size()-1});
    }
    bool bfs(int s, int t){
        fill(full(lvl),-1);
        lvl[s]=0;
        queue<int> q;
        q.push(s);
        while(!q.empty()) {
            int curr = q.front();
            q.pop();
            for(auto& edgea : graph[curr]){
                if(edgea.cap - edgea.flow > 0 && lvl[edgea.to] == -1){
                    lvl[edgea.to] = lvl[curr] + 1;
                    q.push(edgea.to);
                }
            }
        }
        return lvl[t] != -1;
    }
    int dfs(int curr, int e,int topush){
        if(curr == e){
            return topush;
        }
        for(int& cid = ptr[curr]; cid < graph[curr].size(); cid++){
            auto& edgea = graph[curr][cid];
            int to = edgea.to;
            if(lvl[curr]+1 != lvl[to] || edgea.cap - edgea.flow == 0){continue;}
            int pushed = dfs(to,e,min(topush,edgea.cap - edgea.flow));
            if(pushed == 0){continue;}
            edgea.flow+=pushed;
            graph[to][edgea.rev].flow -= pushed;
            return pushed;
        }
        lvl[curr]=-1;
        return 0;
    }
    int maxflow(int s, int e){
        int flow = 0;
        while(bfs(s,e)){
            fill(full(ptr),0);
            while(int pushed = dfs(s,e,INF)){
                flow+=pushed;
            }
        }
        return flow;
    }
    v<pair<int,int>> getmincutedges(int s,int e){
        bfs(s,e);
        v<pair<int,int>> ans;
        for(int i =0; i<n; i++){
            if(lvl[i]!= -1){
                for(auto& x : graph[i]){
                    if(x.cap > 0 && lvl[x.to]== -1){
                        ans.push_back({i,x.to});
                    }
                }
            }
        }
        return ans;
    }
    v<pair<int,int>> getmatching(int s, int e){
        v<pair<int,int>>ans;
        for(int i =0; i<n; i++){
            if(i == s || i == e){continue;}
            for(auto &x : graph[i]){
                if(x.cap > 0 && x.to !=s && x.to != e && x.flow > 0){
                    ans.push_back({i,x.to});
                }
            }
        }
        return ans;
    }   //note: this assumes there are only edges going from L->R, and not the opposite
        //if the opposite is true, there will be double counting
        //MINIMUM VERTEX COVER: ITS PART OF THE SOL IFF UNVISITED AND LEFTSIDE OR VISITED AND RIGHTSIDE.
};