#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <queue>
#include <cstring>
#include <string>
#include <functional>
#include <utility>
using namespace std;
int N, M, H;
typedef pair <int, int> PairInt;
int vec[31][11] = { 0, }; //��->��
int vec2[31][11] = { 0, }; //��->��
int checked[31][11] = { 0, };
int ans = 987654321;
int used[31][11] = { 0, };
/*
	��ٸ� �������� �Լ�(��߹�ȣ)
	���μ� ���� ��ġ���� �ƴ��� �˻��ϴ� �Լ�.
	�߰��ϴ� ���μ��� 3 �ʰ��� �Ǹ� return, �� ���Ҵµ��� �ȵǸ� -1.
	�߰��� ������ 3�ʰ��� �ƴϰ�, ��� i���μ� ��� i�� �ش� ������ ������� �ּ� ������ ���ؼ� �ּҰ��� �ֽ�ȭ. 


*/


void enter_line(int x,int y) {//x:��,y:��
	vec[x][y] = 1;
	vec2[x][y + 1] = 1;
	checked[x][y] = 1;
	checked[x][y+1] = 1;
}

void remove_line(int x, int y) {
	vec[x][y] = 0;
	vec2[x][y + 1] = 0;
	checked[x][y] = 0;
	checked[x][y + 1] = 0;
}

void enter() {
	cin >> N >> M >> H; // H��, N�� , ��ȭ�Ǵ������� ���� M
	for (int i = 0; i < M; i++) {
		int x, y; //y�� x��
		cin >> x >> y;
		enter_line(x, y);
	}
}

void degug1() {
	/*
	for (int i = 1; i < N+1; i++) {
		if (!vec2[i].empty()) {
			vector <int> ::iterator v_iter = vec2[i].begin();
			for (; v_iter != vec2[i].end(); v_iter++) {
				cout << i << "��° ���μ���" << (*v_iter) << "�࿡�� ��ȭ" << endl;
			}

		}
	}
	*/
}

int ladder_gotounder(int depth,int N) {//depth �� , N�� 
	/*
		depth���� H+1 �� �Ǹ� �ش� N���� ����.
	*/
	while (depth != H + 1) {
//		cout << N << "���μ�" << depth << "����" << endl;
		if (vec[depth][N] == 1) {
//			cout << "�����̵�" << endl;
			++N;
		}
		else if (vec2[depth][N] == 1) {
//			cout << "�����̵�" << endl;
			--N;
		}
		
		++depth;
//		cout << endl;
	}

	return N;
}

//��ġ�� 1 ��ȯ
int is_checked(int x,int y) {
	if (checked[x][y] == 1 || checked[x][y + 1] == 1) return 1;
	else return 0;
}
//��� i���μ��� i���.
int all_pass() {
	int a = 0;
	for (int i = 1; i < N + 1; i++) {
	//cout << i << "���μ� ��� : " << ladder_gotounder(0, i) << endl; 
		//�Ǽ� 2: �־��� ��Ʈ�� �� �Ⱥþ�? ����� �������� �� ������� �������� �ٷ� ã�Ƴ��ݾ�. �װ� �� �ϰ� Ǯ�� �ֳ�~
	
		if (ladder_gotounder(0,i) == i) {
			a++;
		}
	}
	if (a == N) return 1;
	else return 0;
}

int min(int a,int b) {
	if (a < b) return a;
	else return b;

}


void dfs(int cnt,int I,int J) {

	if (all_pass()) {
		ans = min(ans, cnt-1);
	//	cout << "<<<<<<<<<<"<<cnt - 1<<">>>>>>>>>>" << endl;
		return;
	}
	if (cnt == 4) return;

	
	for (int i = I; i < H+1; i++) { //�� I : 3
//		cout << i << endl;
		for (int j = 1; j < N; j++) {
			if (i == I) j = J++; //�� i : 3 j : 4 ���� ����
//			cout << j << endl;
			if (!is_checked(i, j) ) { // 0 1 2 / 0 1 3 / 0 1 4 / 0 2 1(X) / 0 2 3 / 0 2 4 / 0 3 1(X) / 0 3 2 (X) / 0 3 4 / 0 4 1(X) / 0 4 2(X) / 0 4 3(X)
				enter_line(i, j);
//				cout << "-------"<< cnt <<"-------" << endl;
//				cout << i << " " << j<<endl; //�簡�� : i: 3 j :3
				dfs(cnt + 1,i,j+1); // ��i: 3 j+1 :4
				remove_line(i, j);
			}
			
		}
	}
	






}

int main() {
	enter();
	dfs(1,1,1);
	if (ans == 987654321) ans = -1;
	cout << ans;
	system("pause");
}