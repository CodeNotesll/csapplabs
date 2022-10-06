// lo <= a <= hi
int func_4(int a, int lo, int hi) {
    int mid = (hi - lo)/2 + lo;
    if (mid == a)
        return 0;
    if (mid < a) {
        int s = func_4(a, mid + 1, hi);
        return 2*s + 1;
    }
    // a < mid
    int s = func_4(a, lo, mid - 1);
    return 2*s;
}

int func_7(int* p, int r) {
    if (!p) 
        return -1;
    int k = *p;
    if (k <= r) {
        if (k == r) 
            return 0;
        p = p + 2;
        int s = func_7(p, r);
        return 2*s + 1;
    }
    else {   // k > r
        p = p + 1;
        int s = func_7(p, r);
        return 2*s;
    }
    
}