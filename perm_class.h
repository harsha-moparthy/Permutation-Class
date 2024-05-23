#include<bits/stdc++.h>
using namespace std;
bool comp(vector<int> & a,vector<int> &b){
	const int n1=a.size();
	const int n2=b.size();
	if(n1!=n2){return n1<n2;}
	return a[0]<b[0];
}
long long absll(long long int x){
	if(x<0){return -x;}
	return x;
}
vector<long long> common(long long a0,long long d0,long long a1,long long d1){
	long long d0c=d0;
	long long d1c=d1;
	long long r=a1-a0;
	long long g=__gcd(d0,d1);
	if(absll(r)%g!=0){return {0,0,0};}
	r/=g;
	d0/=g;d1/=g;
	long long aux=d1%d0;
	int rem=0;
	//cout<<d0<<endl;
	for(int i=0;i<d0;i++){
		long long val=aux*i+r;
		if(absll(val)%d0==0){rem=i;break;}
	}
	long long start=(rem*d1+r)/d0;
	if(start>=0){start=a0+start*d0c;}
	else{
		long long qu=(-start+d1-1)/d1;
		start=a0+(qu*d1+start)*d0c;
	}
	long long lc=(d0c/g)*d1c;
	return {1,start,lc};
}
class permutation{
public:
	int sz;
	vector<int> cont;
private:
	void cycle(vector<vector<int>> &v) const{
		const int n=sz;
		//cout<<"size that came is n= "<<n<<endl;
		vector<bool> vis(n,0);
		//bool vis[n];
		//for(int i=0;i<n;i++){vis[i]=0;}
		for(int i=0;i<n;i++){
			if(!vis[i]){
				int head=i;
				vector<int> temp;
				while(!vis[head]){
					//cout<<head<<endl;
					vis[head]=1;
					temp.push_back(head);
					head=cont[head];
				}
				v.push_back(temp);
			}
		}
		return;
	}
	
public:
	permutation(int n,int a[]){
		cont.resize(n);
		sz=n;
		for(int i=0;i<n;i++){
			cont[i]=a[i];
		}
		return;
	}
	~permutation(){
	}
	permutation(permutation const &q){
		const int n=q.sz;
		this->sz=n;
		cont.resize(n);
		for(int i=0;i<n;i++){
			cont[i]=q.cont[i];
		}
		return;
	}
	permutation const operator=(permutation const &q){
		const int n=q.sz;
		this->sz=n;
		cont.resize(n);
		for(int i=0;i<n;i++){
			cont[i]=q.cont[i];
		}
		return *this;
	}
	int size() const{
		return sz;
	}
	int* to_array() const{
		int *ptr=new int[sz];
		for(int i=0;i<sz;i++){
			ptr[i]=cont[i];
		}
		return ptr;
	}
	permutation const operator-() const{
		int arr[sz];
		for(int i=0;i<sz;i++){
			arr[cont[i]]=i;
		}
		permutation p(sz,arr);
		return p;
	}
	permutation const operator*(permutation const &q) const{
		const int n=sz;
		int arr[n];
		for(int i=0;i<n;i++){
			arr[i]=cont[q.cont[i]];
		}
		permutation ans(n,arr);
		return ans;
	}
	permutation const operator^(long long int i) const{
		vector<vector<int>> v;
		this->cycle(v);
		const int n=sz;
		int arr[n];
		//for(int i1=0;i1<(int)v.size();i1++){
			//for(int j=0;j<(int)v[i1].size();j++){
				//cout<<v[i1][j]<<"->";
			//}
			//cout<<endl;
		//}
		for(int i1=0;i1<(int)v.size();i1++){
			const int mod=v[i1].size();
			for(int j=0;j<mod;j++){
				int ind=(j+i)%mod;
				arr[v[i1][j]]=v[i1][ind];
			}
		}
		permutation ans(n,arr);
		return ans;
	}
	permutation const square_root() const{
		const int n=sz;
		int alter[n];
		for(int i=0;i<n;i++){
			alter[i]=i;
		}
		permutation alterperm(n,alter);
		int arr[n];
		vector<vector<int>> v;
		this->cycle(v);
		vector<int> cycs[n+1];
		for(int i=0;i<(int)v.size();i++){
			int cyclelength=(int)v[i].size();
			cycs[cyclelength].push_back(i);
		}
		for(int i=1;i<n+1;i++){
			if(i&1){
				for(int j=0;j<(int)cycs[i].size();j++){
					int cyclenum=cycs[i][j];
					vector<int> actcyc(i);
					for(int k=0;k<i;k++){
						actcyc[(2*k)%i]=v[cyclenum][k];
					}
					for(int k=0;k<i;k++){
						arr[actcyc[k]]=actcyc[(k+1)%i];
					}
				}
			}
			else{
				if(((int)cycs[i].size())%2!=0){return alterperm;}
				for(int j=0;j<(int)cycs[i].size();j+=2){
					int num1=cycs[i][j];
					int num2=cycs[i][j+1];
					for(int k=0;k<i;k++){
						arr[v[num1][k]]=v[num2][k];
						arr[v[num2][k]]=v[num1][(k+1)%i];
					}
				}
			}	
		}
		//sort(v.begin(),v.end(),comp);
		//for(int i=0;i<(int)v.size();i++){
			//int cylen=v[i].size();
			//if(cylen%2!=0){
				//vector<int> ord(cylen);
				//for(int j=0;j<cylen;j++){
					//ord[(2*j)%cylen]=v[i][j];
				//}
				//for(int j=0;j<cylen;j++){
					//arr[ord[j]]=ord[(j+1)%cylen];
				//}
			//}
			//else{
				//if(i==((int)v.size())-1){return alterperm;}
				//else{
					//int s1=v[i].size();
					//int s2=v[i+1].size();
					//if(s1!=s2){return alterperm;}
					//else{
						//int p1=0;
						//int p2=0;
						//for(int ctr=0;ctr<s1;ctr++){
							//arr[v[i][p1]]=v[i+1][p2];
							//p1++;
							//if(p1>=s1){p1%=s1;}
							//arr[v[i+1][p2]]=v[i][p1];
							//p2++;
						//}
						//i++;
					//}
				//}
			//}
		//}
		permutation ans(n,arr);
		return ans;
	}
	vector<long long> log_aux(permutation const &q) const{
		if(sz!=q.sz){return {0,0,0};}
		const int n=q.sz;
		vector<vector<int>> cyc;
		q.cycle(cyc);
		vector<pair<int,int>> cycinf(n);
		vector<int> cyclen(n); 
		for(int i=0;i<(int)cyc.size();i++){
			int cycsize=(int)cyc[i].size();
			for(int j=0;j<cycsize;j++){
				cycinf[cyc[i][j]]={i,j};
				cyclen[cyc[i][j]]=cycsize;
			}
		}
		long long a0=0;
		long long d0=1;
		for(int i=0;i<n;i++){
			int v2=cont[i];
			int v1=i;
			if(cycinf[v1].first!=cycinf[v2].first){return {0,0,0};}
			else{
				int rem=cycinf[v2].second-cycinf[v1].second;
				if(rem<0){rem+=cyclen[v1];}//assert(cyclen[v1]==cyclen[v2]);
				long long a1=rem;
				long long d1=cyclen[v1];
				//cout<<v1<<" "<<v2<<" "<<a1<<" "<<d1<<endl;
				//cout<<a0<<" "<<d0<<endl;
				if(d1==1){continue;}
				else{
					if(d0>d1){swap(d0,d1);swap(a0,a1);}
					vector<long long> ans=common(a0,d0,a1,d1);
					if(ans[0]==0){return {0,0,0};}
					a0=ans[1];
					d0=ans[2];
				}
			}
		}
		return {1,a0,d0};
		
	}
	bool is_power(permutation const &q) const{
		vector<long long> ans=this->log_aux(q);
		return ans[0];
	}
	int log(permutation const &q) const{
		vector<long long> ans=this->log_aux(q);
		const int mod=1000000000+7;
		if(ans[0]==0){return -1;}
		return ans[1]%mod;
		
	}
};
