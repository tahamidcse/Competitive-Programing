#include <bits/stdc++.h>
using namespace std;
#define  LL    long long
#define  LIM   1000000
#define  base1 129
#define  base2 137
#define  MOD1  1479386893
#define  MOD2  1928476349
string text;
LL pow1[LIM+5], pow2[LIM+5];
void calPower(){
    pow1[0] = pow2[0] = 1;
    for(int i = 1; i < LIM; i++){
        pow1[i] = (pow1[i-1]*base1)%MOD1;
        pow2[i] = (pow2[i-1]*base2)%MOD2;
    }
}
int getHash(){
    LL hash1 = 0, hash2 = 0, revHash1 = 0, revHash2 = 0;
    int maxPal = 1;
    for(int i = 0; text[i]; i++){
        hash1 = ((hash1*base1)%MOD1 + (text[i]-'a' + 1))%MOD1;
        hash2 = ((hash2*base2)%MOD2 + (text[i] - 'a' + 1))%MOD2;
        revHash1 = (revHash1 + ((text[i]-'a' + 1)*pow1[i])%MOD1)% MOD1;
        revHash2 = (revHash2 + ((text[i]-'a' + 1)*pow2[i])%MOD2)% MOD2;
        if(hash1 == revHash1 && hash2 == revHash2) maxPal = max(maxPal, i+1);
    }
    return maxPal;
}
int main(){
    calPower();
    int T; cin>>T;
    for(int t = 1; t <= T; t++){
        cin>>text;
        reverse(text.begin(), text.end());
        int maxPal = getHash(); //to store max palindrome length from right side
        int matched = maxPal;
        maxPal = 2*text.size() - maxPal;
        printf("Case %d: %d\n", t, maxPal);
    }
