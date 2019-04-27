#include <iostream>
#include <cstring>
#include <cstdio>
#include <utility>
#include <vector>

//#define DBG_ON 1

#ifdef DBG_ON
#define DBG_P(fmt, args...) printf(fmt, ##args)
#else
#define DBG_P(fmt, args...)
#endif

using namespace std;

int map[10][10];
vector<pair<int,int> > serial_map;
int remain[6] = {5,5,5,5,5,5};
int cnt=0;
int __min=101;

void attach(int r, int c, int size){
	for(int i=r; i<r+size; i++){
		for(int j=c; j<c+size; j++){
			map[i][j] = 0;
		}
	}
}

bool possible(int r, int c, int size){

	if(r+size > 10 || c+size > 10)
		return false;

	for(int i=r; i<r+size; i++){
		for(int j=c; j<c+size; j++){
			if(i == r && j == c)
				continue;

			if(map[i][j] !=1){
				return false;
			}
		}
	}
	
	if(remain[size] > 0)
		return true;
	else{
		return false;
	}
}

void dfs(int now, int end){

	int r=serial_map[now].first;
	int c=serial_map[now].second;
	
	if(now == end){

		for(int i=0; i<10; i++){
			for(int j=0; j<10; j++){
				if(map[i][j] == 1){ // 다 커버 못한경우
					return;
				}
			}
		}

		if(__min > cnt){
			__min = cnt;
		}
		return;
	}

	if(map[r][c] == 0){
		//return;
		dfs(now+1, end);
		return;
	}
	
	for(int k=5; k>=1; k--){
		if(possible(r,c,k)){
			int tmp_map[10][10];
			memcpy(tmp_map, map, sizeof(map));

			attach(r,c,k);
			remain[k]--;
			cnt++;
			dfs(now+1, end);


			memcpy(map, tmp_map, sizeof(tmp_map));
			remain[k]++;
			cnt--;

		}
	}
}

int main(void){

	for(int i=0; i<10; i++){
		for(int j=0; j<10; j++){
			cin >> map[i][j];
			if(map[i][j] == 1)
				serial_map.push_back(make_pair(i,j));
		}
	}
	
	if(serial_map.size() == 0){
		cout << 0 << "\n";
		return 0;
	}

	dfs(0, serial_map.size());

	if(__min == 101)
		__min = -1;
	cout << __min << "\n";
	return 0;
}

