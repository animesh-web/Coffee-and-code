#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define ll long long int
#define ld long 
#define str string
#define modinv(a,m) modEx(a,m-2,m)
#define moddiv(a,b,m) (a*modinv(b,m))%m

template<typename T>
void print_arr(T arr[], int l=-1, int r=-1){
    if(l==-1)l=0;
    if(r==-1)r=sizeof(arr)/sizeof(arr[0]);
    for(int i=l;i<r;i++)cout<<arr[i]<<" ";
    cout<<endl;
}

template<typename T>
void print_vec(vector<T> v, int l=-1, int r=-1){
    if(l==-1)l=0;
    if(r==-1)r=v.size();
    for(int i=l;i<r;i++)cout<<v[i]<<" ";
    cout<<endl;
}

const int MOD = 1e9 + 7;
// i>2.10^9/2^31 ll>2.10^18/2^63


ll find_cnt(const vector<int> &v, int l, int r, const vector<pair<int, int>> &old_inds, int &ind){
    ll tot = 0;
    int prev = l;
    for(;ind<old_inds.size();ind++){
        auto rn = old_inds[ind];
        if(rn.F > r)break;
        if((l<=rn.F && rn.S<=r)){
            tot += (rn.F - prev + 1) * (r - rn.S + 1);
            prev = rn.F+1;
        }
    }
    return tot;
}

int main() {
    // ios_base::sync_with_stdio(false);
	// cin.tie(NULL);

    int t;
    scanf("%d", &t);
    while(t--){
		ll n, k;
		scanf("%lld %lld", &n, &k);

		vector<int> v(n);
        vector<vector<int>> inds(n+1);
        vector<pair<int, int>> all_inds;

		for(int i=0;i<n;i++){scanf("%d", &v[i]);inds[v[i]].push_back(i);}
        for(int i=0;i<=n;i++)inds[i].push_back(n);
        
        int prev = 0, ans = n;
        ll tot = 0;

        for(int ind : inds[0]){
            tot += (ind - prev)*((ind - prev)+1)/2;
            prev = ind + 1;
            all_inds.push_back({ind, ind});
        }

        if(tot>=k)ans = 0;

        for(int i=1;i<n && ans!=0;i++){
            prev = 0;
            int oi = 0;
            for(int ind : inds[i]){
                tot += find_cnt(v, prev, ind-1, all_inds, oi);
                prev = ind+1;
            }
            if(tot>=k){ans=i;break;}

            vector<pair<int, int>> tmp_inds;
            int a=0, b=0;
            while(a<all_inds.size() && b<(inds[i].size()-1)){
                if(inds[i][b] < all_inds[a].F){
                    tmp_inds.push_back({inds[i][b], all_inds[a].S});
                    b++;
                }
                else if(inds[i][b] < all_inds[a].S){
                    tmp_inds.push_back(all_inds[a]);
                    a++;
                }
                else{
                    tmp_inds.push_back({all_inds[a].F, inds[i][b]});
                    a++;
                }
            }
            all_inds = tmp_inds;
        }

        cout<<ans<<endl;
    }
    
    return 0;
}
