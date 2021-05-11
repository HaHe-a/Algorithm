#include<bits/stdc++.h>

using namespace std;
int T[100005];
int n;
int lowbit(int x)
{
    return x&(-x);
}
void add(int pos,int x)
{
    for(int i=pos;i<=n;i+=lowbit(i)){
        T[i]+=x;
    }
}
int getsum(int pos)
{
    int ans=0;
    for(int i=pos;i>0;i-=lowbit(i)){
        ans+=T[i];
    }
    return ans;
}
int a[100005];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    int ans=0;
    for(int i=1;i<=n;i++){
        add(a[i],1);
        //cout<<i-getsum(a[i])<<endl;
        ans+=i-getsum(a[i]);
    }
    cout<<ans<<endl;
}
