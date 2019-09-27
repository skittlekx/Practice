#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
class Solution {
	//代码模板
	void hdux() {
		int T;
		cin >> T;
		int n[20], *b[20];
		for (int i = 0; i < T; i++) {
			cin >> n[i];
			b[i] = new int[n[i]];
			for (int j = 0; j < n[i]; j++) {
				cin >> b[i][j];
			}
		}
		for (int i = 0; i < T; i++) {
			if (i)cout << endl;

			cout << "Case " << i + 1 << ":" << endl;
			cout << endl;
		}
	}
	int sum_(int *a, int start, int count) {
		int sum = 0;
		while (count-- > 0) {
			sum += a[start++];
		}
		return sum;
	}
	void print(int *A, int n) {
		for (int i = 0; i < n; i++) {
			cout << A[i] << " ";
		}
		cout << endl;
	}
public://hduoj
	void hdu1001() {
		int n;
		while (std::cin >> n) {
			int sum = n % 2 ? (n + 1) / 2 * n : n / 2 * (n + 1);
			std::cout << sum << "\n\n";
		}
	}
	void hdu1002() {
		int T;
		cin >> T;
		char a[20][1000], b[20][1000], c[20][1000];
		for (int i = 0; i < T; i++) {
			cin >> a[i] >> b[i];
		}
		for (int i = 0; i < T; i++) {
			cout << endl;
			int na = strlen(a[i]);
			int nb = strlen(b[i]);
			int pre = 0, count = 0;
			int j = na - 1, k = nb - 1;
			while (j >= 0 && k >= 0) {
				int res = pre + a[i][j--] + b[i][k--] - 2 * '0';
				pre = res / 10;
				c[i][count++] = res % 10;
			}
			while (j >= 0) {
				int res = pre + a[i][j--] - '0';
				pre = res / 10;
				c[i][count++] = res % 10;
			}
			while (k >= 0) {
				int res = pre + b[i][k--] - '0';
				pre = res / 10;
				c[i][count++] = res % 10;
			}

			cout << "Case " << i + 1 << ":" << endl
				<< a[i] << " + " << b[i] << " = ";
			while (count > 0) {
				int r = c[i][--count];
				cout << r;
			}
			cout << endl;
		}
	}
	void hdu1003() {
		int T;
		cin >> T;
		int n[20], *a[20];
		for (int i = 0; i < T; i++) {
			cin >> n[i];
			a[i] = new int[n[i]];
			for (int j = 0; j < n[i]; j++) {
				cin >> a[i][j];
			}
		}
		for (int i = 0; i < T; i++) {
			if(i)cout << endl;
			int max[3] = { a[i][0],1,1 };
			int staInd = 0;
			int sum = 0;
			for (int j = 0; j < n[i]; j++) {
				sum += a[i][j];
				if (sum > max[0]) {
					max[0] = sum;
					max[1] = staInd+1;
					max[2] = j+1;
				}
				
				if (sum < 0) {
					sum = 0;
					staInd = j + 1;
				}
			}
			cout << "Case " << i + 1 << ":" << endl;
			cout << max[0] << ' ' << max[1] << ' ' << max[2];
			cout << endl;
		}
		for (int i = 0; i < T; i++) delete[] a[i];
	}
	void hdu1004() {
		int n;
		map<string, int>mp;
		while (cin >> n)
		{
			if (n == 0)break;
			int max = 0;
			string res;
			mp.clear();
			for (int i = 0; i < n; i++)
			{
				string color;
				cin >> color;
				mp[color]++;
				if (mp[color] > max)
				{
					max = mp[color];
					res = color;
				}
			}
			cout << res << endl;
		}
	}
	void hdu1005() {
		int n, a, b;
		while (cin >> a >> b >> n) {
			if (!(a&&b&&n)) break;
			int *Res = new int[50];
			int tag[7][7];
			memset(tag, -1, 49 * sizeof(int));
			int i;
			Res[0] = 1;
			Res[1] = 1;
			for (i = 2; i < 50; i++) {
				Res[i] = (Res[i - 1] * a + Res[i - 2] * b) % 7;
				if (tag[1][1] == Res[i] && Res[i - 1] == 1) {
					i -= 2;
					break;
				}
				else {
					tag[Res[i - 1]][Res[i - 2]] = Res[i];
				}
			}
			cout << Res[(n - 1) % i == 0 ? i : (n - 1) % i] << endl;
			delete[]Res;
		}
	}
	
public://cugoj
	static bool cmp1010(const pair<string, int> &a, const pair<string, int> &b) {
		if (a.second == b.second)
			return a.first.compare(b.first) < 0;
		else
			return a.second > b.second;
	}
	int cug1010() {
		vector<pair<string, int>> Rec;
		string name;
		int grade;
		while (cin >> name >> grade) {
			Rec.push_back(pair<string, int>(name, grade));
		}
		sort(Rec.begin(), Rec.end(), cmp1010);
		for (int i = 0; i < Rec.size(); i++) {
			cout << Rec[i].first << ' ' << Rec[i].second << endl;
		}
		return 0;
	}
public://上机材料
	int DFS(int *A,int s,int s1,int n,int count = 0) {
		if (s == n || s1 >= n)
			if (A[s] >= s1) return count + 1;
			else return count;

		int i = 0;
		int res1 =  DFS(A, s + 1, s1, n, count);
		int res2 = 0;
		if(A[s] >= s1) 
			res2 = DFS(A, s + 1, A[s]+1, n, count + 1);
		return res1 > res2 ? res1:res2;
	}
	int prB() {
		int n;
		int *A;
		cin >> n;
		A = new int[n];
		memset(A, 0, sizeof(int)*n);


		for (int i = 0; i < n; i++) {
			int a, b;
			cin >> a >> b;
			A[a-1] = b - 1;
		}
		int res = 0;
		res = DFS(A, 0, 0, n-1);
		cout << res;
		return 0;
	}

};

int main() {
	Solution a;
	a.hdu1005();
	system("pause");
	return 0;
}
