#include <bits/stdc++.h>
using namespace std;

#define maxn 100

typedef pair<double,int> di; // valor/peso,indice

int peso[maxn],valor[maxn]; 
di V[maxn];

int guloso(int n, int cap){
	sort(V,V+n);
	int idx = n-1;
	int ans = 0;
	while(idx >= 0 && cap >= peso[V[idx].second]){
		cout << "foi pego o item " << V[idx].second << endl; 
		ans+=  peso[V[idx].second];
		idx--;
	}
	return ans;
}


int main(){
	int n;
	cin>>n;
	int cap;
	cin >> cap;
	for(int i = 0 ; i < n ; ++i){
		cin>>peso[i]>>valor[i];
		V[i] = di(valor[i]/(double)peso[i],i);
	}
	cout << "peso final da mochila : " << guloso(n,cap) << endl;;
}
