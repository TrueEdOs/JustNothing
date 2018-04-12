#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef double ld;
#define sqr(a) (a)*(a)

struct TreapNode
{
	static const int MOD = 100337853;
	TreapNode *L, *R;
	int key, val, subTreeSize;
	TreapNode(int val):val(val), key(rand() % MOD), subTreeSize(1), L(nullptr), R(nullptr){}
};


struct Treap
{
	TreapNode *root;
	Treap():root(nullptr){}
	Treap(TreapNode *root):root(root){}
	
	void insert(int val)
	{
		TreapNode* NewNode = new TreapNode(val);
		TreapNode *L, *R;
		//cout << "OK1" << endl;
		split(root, L, R, val);
		//cout << "OK2" << endl;
		merge(L, L, NewNode);
		//cout << "OK3" << endl;
		merge(root, L, R); 
		//cout << "Ok4" << endl;
	}
	
	void erase(int val)
	{
		erase(root, val);
	}
	void eraseAll(int val)
	{
		while(erase(root, val));
	}
	
	int lowerbound(int val)
	{
		return lowerbound(root, val);
	}
	
private:	
	static void split(TreapNode *T, TreapNode* &L, TreapNode* &R, int val)
	{
		if(T == nullptr)
		{
			L = nullptr;
			R = nullptr;
			return;
		}
		
		//cout << T->val << endl;
		if(T->val > val)
		{
			split(T->L, L, T->L, val);
			R = T;
		}
		else
		{
			split(T->R, T->R, R, val);
			L = T;
		}
	}
	
	static void merge(TreapNode* &T, TreapNode *L, TreapNode *R)
	{
		if(L == nullptr || R == nullptr)
		{
			T = (L == nullptr ? R: L);
			return;
		}
		
		if(L->key < R->key)
		{
			merge(R->L, L, R->L);
			T = R;
		}
		else
		{
			merge(L->R, R, L->R);
			T = L;
		}
	}
	
	bool erase(TreapNode* &T, int val)
	{
		if(T == nullptr)
			return false;
		cout << val << endl;
		if(T->val == val)
		{
			merge(T, T->L, T->R);
			return true;
		}
		else
			erase((T->val > val ? T->L: T->R), val);
		return false;
	}
	
	int lowerbound(TreapNode* &T, int val)
	{
		if(T == nullptr)
			return (1<<31) - 1;
		if(T->val < val)
			return lowerbound(T->R, val);
		else
			return min(T->val, lowerbound(T->L, val));
	}
};

int nextInt()
{
	int res = 0;
	char a;
	while(true)
	{
		a = getchar();
		if(a < '0' || a > '9')
			return res;
		res = (res * 10) + a - '0';
	}
}

	
int main()
{

    //freopen("input", "r", stdin);
	ios_base::sync_with_stdio(false);
	Treap tree;
	while(true)
	{
		char type;
		int val;
		cin >> type;
		switch(type)
		{
			case '-':
				cin >> val;
				tree.erase(val);
				break;
			case '+':
				cin >> val;
				tree.insert(val);
				break;
			case '?':
				cin >> val;
				cout << tree.lowerbound(val) << endl;
				break;
			case '!':
				return 0;
				break;
		}
	}
    return 0;
}
