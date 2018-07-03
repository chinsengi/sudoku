#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cstdlib>
using namespace std;

const int maxn = 400;
const int maxnode = 2000;
const int maxr = 100;
struct DLX{
	int n,sz;
	int s[maxn];
	int row[maxnode], col[maxnode];
	int L[maxnode], R[maxnode], U[maxnode], D[maxnode];
	
	int ansd, ans[maxr];
	
	void init(int n){
		this->n = n;
		
		for(int i = 0; i <= n; i++){
			U[i] = i; D[i] = i; L[i] = i-1; R[i] = i+1;
		}
		R[n] = 0; L[0] = n;
		
		sz = n+1;
		memset(s, 0, sizeof s);
	}
	
	void addRow(int r, vector<int> columns){
		int first = sz;
		for(int i = 0; i < columns.size(); i++){
			int c = columns[i];
			L[sz] = sz - 1; R[sz] = sz +1; D[sz] = c; U[sz] = U[c];
			D[U[c]] = sz; U[c] = sz;
			row[sz] = r; col[sz] = c;
			s[c]++; sz++;
			
		}
		R[sz-1] = first ; L[first] = sz-1;
		
	}
	
	#define FOR(i,A, s) for(int i = A[s]; i!=s; i = A[i])
		
	void remove(int c){
		L[R[c]] = L[c];
		R[L[c]] = R[c];
		FOR(i,D,c) FOR(j,R,i){
			U[D[j]] = U[j]; D[U[j]] = D[j]; --s[col[j]];
		}
	}
	
	void restore(int c){
		FOR(i,U,c) FOR(j,L, i){
			++s[col[j]]; U[D[j]] = j; D[U[j]] = j;
		}
		L[R[c]] = c;
		R[L[c]] = c;
	}
	
	bool dfs(int d){
		if(R[0]==0){
			ansd = d;
			return true;
		}
		
		int c = R[0];
		FOR(i,R,0) if(s[i]< s[c]) c = i;
		
		remove(c);
		FOR(i,D,c){
			ans[d] = row[i];
			FOR(j,R,i) remove(col[j]);
			if(dfs(d+1)) return true;
			FOR(j,L,i) restore(col[j]);
			
		}
		restore(c);
		
		return false;
	}
	
	bool solve(vector<int>& v){
		v.clear();
		if(!dfs(0)) return false;
		for(int i = 0; i < ansd; i++) v.push_back(ans[i]);
		return true;
	}
};

const int maxd = 10;

int su[maxd][maxd];
int Slot[maxd][maxd];
int Row[maxd][maxd];
int Col[maxd][maxd];
int sub[maxd][maxd];
int decode[1500];

inline int ws(int a, int b){return ((a-1)/3)*3+(b-1)/3+1;}
#define rep(i,s,n) for(int i = s; i < n; i++)

bool pre(int i, int j,int k, vector<int>& co){
	int a = Slot[i][j]; int b = Col[j][k];
	int c = Row[i][k]; int d = sub[ws(i,j)][k];
	if(a==-1||b==-1||c==-1||d==-1) return false;
	else{
		co.push_back(a);
		co.push_back(b);
		co.push_back(c);
		co.push_back(d);
		return true;
	}
}

void print(){
	rep(i,1,10){
		rep(j,1,10){
			cout<<su[i][j]<<" ";
		}
		cout<<endl;
	}
}

int main(){
	DLX solver;
	
	for(int i = 1; i < 10; i++)
		for(int j = 1; j < 10; j++){
			char a;
			cin>>a;
			su[i][j] = a-'0';
			if(su[i][j]!=0){
				int d = su[i][j];
				Slot[i][j] = -1;Col[j][d] = -1;
				Row[i][d] = -1;sub[ws(i,j)][d] = -1;
			}
		}
	int count = 0;
	rep(i,1,10) rep(j, 1, 10) if(Slot[i][j]!=-1) Slot[i][j] = ++count;
	rep(i,1,10) rep(j, 1, 10) if(Row[i][j]!=-1) Row[i][j] = ++count;
	rep(i,1,10) rep(j, 1, 10) if(Col[i][j]!=-1) Col[i][j] = ++count;
	rep(i,1,10) rep(j, 1, 10) if(sub[i][j]!=-1) sub[i][j] = ++count;
	solver.init(count);
	int r = 1;
	rep(i, 1,10) rep(j,1,10)rep(k,1,10){
		vector<int> co;
		if(!pre(i,j,k,co)) continue;
		//cout<<i<<" "<<j<<" "<<k<<endl;
		//for(auto c: co) cout<< c<<" "; cout<<endl;
		solver.addRow(r, co);
		decode[r] = 100*i+10*j+k;
		r++;
	}
	vector<int> ans; 
	if(solver.solve(ans)){
		for(auto a: ans){
			int tmp = decode[a];
			//cout<<tmp<<endl;
			int i,j,k;
			i = tmp/100; tmp %= 100;
			j = tmp/10; tmp %= 10;
			k = tmp;
			su[i][j] = k;
		}
		cout<<"\n\n";
		print();
	}else cout<<"impossible"<<endl;
	
}




