//#include <iostream>
//#include <string>
//
////#include <stack>
//#include <cmath>
//
//#define Random(x) rand()%x
//
//using namespace std;
//
//
//int* cut(int *A,int m, int k)
//{
//	if (k == 1)
//	{
//		return ;
//	}
//	int *res = new int[k - 1];
//	int tag = (m / 2) * 500;
//	int oldtag = 0;
//	
//	int ae = m - k + 1;
//	int step = 1;
//	while (step++) {
//		bool isok = false;
//		for (int i = k - 1 - step; i >= 0; i--)
//		{
//			res[i] = m - (k - 2 - i) - 1;
//		}
//
//		while (juge(A, res, m, tag))
//		{
//			int temp = (tag + oldtag) / 2;
//			oldtag = tag;
//			tag = temp;
//		}
//		cut(A, res[k - 2], k - step);
//
//	}
//	
//	return res;
//}
//int calarr(int*A, int a, int b)
//{
//	if (a < 0)return 0;
//	if (a > b)return 0;
//	if (a == b)return A[a];
//
//	int res = 0;
//	for (int i = a; i < b; i++)
//	{
//		res += A[i];
//	}
//	return res;
//}
//bool juge(int *A, int *C, int m,int x)
//{
//	int k = 0;
//	for (int a = 0, b = C[k++];k<m-1; a = C[k], b = C[++k])
//	{
//		int sum = calarr(A,a,b);
//		if (sum > x)return false;
//	}
//	return true;
//}
//int main()
//{
//	int m = 10;
//	int k = 3;
//	int *arr = new int[m];
//	for (int i = 0; i < m; i++)
//	{
//		arr[i] = Random(500);
//	}
//	int *res = cut(arr, m, k);
//	system("pause");
//}

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <stack>
#include <vector>
#include <algorithm>
#define random(x) rand()%x

using namespace std;
const int N = 505;
typedef long long ll;
int n, m;
ll max_num, min_num;

int books[N];
int visit[N];

int type = 1;
ll Min(const ll a, const ll b) { return a < b ? a : b; }

void printia(int *a, int n) {
	for (int i = 0; i < n; i++) {
		if (i == n / 2) {
			cout << " <<" << a[i] << ">> ";
			continue;
		}
		cout << a[i] << ' ';
	}
	cout << endl;
}

class Solution {
public:
	/*
	 * @param numCourses: a total of n courses
	 * @param prerequisites: a list of prerequisite pairs
	 * @return: true if can finish all courses or false
	 */
	bool DFS(int a, int end, vector<int> *flag, bool* tag) {
		for (int i = 0; i < flag[a].size(); i++) {
			int tmp = flag[a][i];
			if (tag[tmp])continue;// return true;
			if (tmp == end)return false;
			if (!DFS(tmp, end, flag, tag)) {
			//	tag[a] = true;
				return false;
			}
			else {
				tag[tmp] = true;
			}

		}
		return true;// false;
	}
	bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
		// write your code here
		bool *tag = new bool[numCourses];
		vector<int> *flag = new vector<int>[numCourses];
		for (int i = 0; i < numCourses; i++) {
			tag[i] = true;
			flag[i].resize(0);
		}
		int n = prerequisites.size();
		int k = 0;
		while (n-- > 0)
		{
			pair<int, int> tmp = prerequisites[n];
			flag[tmp.first].push_back(tmp.second);
			tag[tmp.first] = false;
		}
		for (int i = 0; i < numCourses;i++) {
			if (!DFS(i, i, flag, tag)) {
				return false;
			}
		}
		return true;
	}

	int HFS() {
		//动态规划求背包问题
		int num, c;
		cin >> c >> num;
		int *v = new int[num + 1];
		for (int i = 1; i <= num; i++)
		{
			cin >> v[i];
		}
		int *dp = new int[c + 1];
		memset(dp, 0, (c + 1) * sizeof(int));
		for (int i = 1; i <= num; i++)
		{
			for (int j = c; j >= v[i]; j--)
				dp[j] = max(dp[j], dp[j - v[i]] + v[i]);
			if (dp[c] == c)
				i = num;
		}
		cout << dp[c] << endl;

		delete[]v;
		delete[]dp;

		return 0;
	}
	int findMin(int *a, int n) {
		//循环数组求最小值
		int low = 0, high = n - 1;
		bool tag = a[low] < a[high];
		while (low < high) {
			if (low == high - 1)return a[low] < a[high] ? a[low] : a[high];
			int mid = (low + high) >> 1;
			bool HeadTag = a[low] < a[mid];
			bool TailTag = a[mid] < a[high];
			if (HeadTag^TailTag) {
				if (HeadTag^tag) {
					//从后半段找
					low = mid;
					continue;
				}
				else {
					//从前半段找
					high = mid;
					continue;
				}
			}
			else {
				//原数列有序
				return a[low] < a[high] ? a[low] : a[high];
			}
		}
	}
};
int Bigger(int a, int b) {
	return a > b;
}
int Lower(int a, int b) {
	return a < b;
}
int mymain()
{
	Solution a;
	int n = 100;
	int b[][2] = { 
	{ 6,27},{83, 9},{10,95},{48,67},{ 5,71},{18,72},{ 7,10},{92, 4},{68,84},{ 6,41},{82,41},{18,54},
	{ 0, 2},{ 1, 2},{ 8,65},{47,85},{39,51},{13,78},{77,50},{70,56},{ 5,61},{26,56},{18,19},{35,49},
	{79,53},{40,22},{ 8,19},{60,56},{48,50},{20,70},{35,12},{99,85},{12,75},{ 2,36},{36,22},{21,15},
	{98, 1},{34,94},{25,41},{65,17},{ 1,56},{43,96},{74,57},{19,62},{62,78},{50,86},{46,22},{10,13},
	{47,18},{20,66},{83,66},{51,47},{23,66},{87,42},{25,81},{60,81},{25,93},{35,89},{65,92},{87,39},
	{12,43},{75,73},{28,96},{47,55},{18,11},{29,58},{78,61},{62,75},{60,77},{13,46},{97,92},{ 4,64},
	{91,47},{58,66},{72,74},{28,17},{29,98},{53,66},{37, 5},{38,12},{44,98},{24,31},{68,23},{86,52},
	{79,49},{32,25},{90,18},{16,57},{60,74},{81,73},{26,10},{54,26},{57,58},{46,47},{66,54},{52,25},
	{62,91},{ 6,72},{81,72},{50,35},{59,87},{21, 3},{ 4,92},{70,12},{48, 4},{ 9,23},{52,55},{43,59},
	{49,26},{25,90},{52, 0},{55, 8},{ 7,23},{97,41},{ 0,40},{69,47},{73,68},{10, 6},{47, 9},{64,24},
	{95,93},{79,66},{77,21},{80,69},{85, 5},{24,48},{74,31},{80,76},{81,27},{71,94},{47,82},{ 3,24},
	{66,61},{52,13},{18,38},{ 1,35},{32,78},{ 7,58},{26,58},{64,47},{60, 6},{62, 5},{ 5,22},{60,54},
	{49,40},{11,56},{19,85},{65,58},{88,44},{86,58} };
	/*vector<pair<int, int>> pp;
	for (int i = 0; i < 150; i++)
		pp.push_back(pair<int, int>(b[i][0], b[i][1]));
	Solution a;
	cout << a.canFinish(100, pp) << endl;
*/

	int testn = 10000;
	bool isok = true;
	while (testn-- > 0) {
		int n = random(1000);
		while (n == 0) n = random(1000);
		int *A = new int[n];
		int *B = new int[n];
		int seed = random(n);
		for (int i = 0; i < n; i++) A[i] = seed++;
		//sort(A, A + n, Lower);
		int min = A[0];
		int tag = random(n);
		for (int i = 0; i < n; i++) B[i] = A[tag++%n];
		int fmin = a.findMin(B, n);
		if (fmin != min) {
			cout << "第 " << 10000 - testn << " 次:LERROR!!!" << endl;
			printia(B, n);
			cout << "n = " << n << endl;
			cout << "Min = " << min << endl;
			cout << "fMin = " << fmin << endl;
			
			isok = false;
			break;
		}
		delete[] A;
		delete[] B;
	}
	if (isok) cout << "L unequal OK" << endl;
	testn = 10000;
	isok = true;
	while (testn-- > 0) {
		int n = random(1000);
		while (n == 0)n = random(1000);
		int *A = new int[n];
		int *B = new int[n];
		int seed = random(n);
		for (int i = 0; i < n; i++) A[i] = seed++;
		//sort(A, A + n, Bigger);
		int min = A[0];
		int tag = random(n);
		for (int i = 0; i < n; i++) B[i] = A[tag++%n];
		int fmin = a.findMin(B, n);
		if (fmin != min) {
			cout << "第 " << 10000 - testn << " 次:BERROR!!!" << endl;
			printia(B, n);
			cout << "n = " << n << endl;
			cout << "Min = " << min << endl;
			cout << "fMin = " << fmin << endl;
			isok = false;
			break;
		}
		delete[] A;
		delete[] B;
	}
	if (isok) cout << "B unequal OK" << endl;

	testn = 10000;
	isok = true;
	while (testn-- > 0) {
		int n = random(1000);
		while (n == 0) n = random(1000);
		int *A = new int[n];
		int *B = new int[n];
		for (int i = 0; i < n; i++) A[i] = random(n);
		sort(A, A + n, Lower);
		int min = A[0];
		int tag = random(n);
		for (int i = 0; i < n; i++) B[i] = A[tag++%n];
		int fmin = a.findMin(B, n);
		if (fmin != min) {
			cout << "第 " << 10000 - testn << " 次:LERROR!!!" << endl;
			printia(B, n);
			cout << "n = " << n << endl;
			cout << "Min = " << min << endl;
			cout << "fMin = " << fmin << endl;
			
			isok = false;
			break;
		}
		delete[] A;
		delete[] B;
	}
	if (isok) cout << "L equal OK" << endl;
	testn = 10000;
	isok = true;
	while (testn-- > 0) {
		int n = random(1000);
		while (n == 0)n = random(1000);
		int *A = new int[n];
		int *B = new int[n];
		for (int i = 0; i < n; i++) A[i] = random(n);
		sort(A, A + n, Bigger);
		int min = A[n-1];
		int tag = random(n);
		for (int i = 0; i < n; i++) B[i] = A[tag++%n];
		int fmin = a.findMin(B, n);
		if (fmin != min) {
			cout << "第 " << 10000 - testn << " 次:BERROR!!!" << endl;
			printia(B, n);
			cout << "n = " << n << endl;
			cout << "Min = " << min << endl;
			cout << "fMin = " << fmin << endl;
			
			isok = false;
			break;
		}
		delete[] A;
		delete[] B;
	}
	if (isok) cout << "B equal OK" << endl;
	system("pause");
	return 0;
}