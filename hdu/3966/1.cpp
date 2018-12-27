/*
int dfs(int now, int prev = -1){
    node[now].fa = prev;
    int ret = 1, cursize = -1;
    for(int i = head[now]; i != -1; i = node[i].ne){
        int nxt = node[i].to;
        if(nxt == prev)continue;
        int sonsize = dfs(nxt, now);
        if(sonsize > cursize){
            cursize = sonsize;
            node[now].son = nxt;
        }
        ret += sonsize;
    }
    node[now].size = ret;
    return ret;
}

void _dfs(int now, int prev = -1){
    printf("in _dfs(): now = %d, prev = %d\n", now, prev);
    if(node[now].top == -1){
        node[now].top = now;
    }
    seq[totw ++] = now;
    for(int i = head[now]; i != -1; i = node[i].ne){
        int nxt = node[i].to;
        if(nxt == prev)continue;
        if(nxt == node[i].son){
            node[nxt].top = node[now].top;
            _dfs(nxt, now);
        }
    }
    for(int i = head[now]; i != -1; i = node[i].ne){
        int nxt = node[i].to;
        if(nxt == prev || nxt == node[i].son)continue;
        _dfs(nxt, now);
    }
}
*/