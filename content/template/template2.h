#include <bits/stdc++.h>
// using namespace __gnu_pbds;
using namespace std;

#define pb push_back
#define v vector
#define int long long
#define ll long long
#define vll v<ll>
#define pll pair<ll,ll>
#define vpll v<pair<ll,ll>>
#define db long double
#define matriz v<v<ll>>

// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// typedef tree<
//     int,
//     null_type,
//     less<int>,
//     rb_tree_tag,
//     tree_order_statistics_node_update
// > ordered_set;


//using ordered_multiset = __gnu_pbds::tree<pair<int,int>, __gnu_pbds::null_type, 
// less<pair<int,int>>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;
long double PI = acos(-1);

#define sz(a) (ll)a.size()
#define rep loop
#define all full

constexpr inline ll lg(unsigned ll x)           {return __bit_width(x)-1;}
constexpr inline ll getBit(ll x, ll i)  {return ((1LL<<i)& x);}
constexpr inline ll getMsb(ll x)        {return ((1LL<<lg(x)));}
constexpr inline ll getfirst1(ll x)     {return x & -x;}
