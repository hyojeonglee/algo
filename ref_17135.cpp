#include <iostream>
#include <cstdio> // for dbg_p
#include <vector>
#include <utility> // for pair
#include <queue> // for bfs
#include <cstring> // for memcpy

using namespace std;

//#define DBG_ON 1

#ifdef DBG_ON
#define DBG_P(fmt, args...) printf(fmt, ##args)
#else
#define DBG_P(fmt, args...)
#endif

int n, m, d;
int map[16][15];
int const_map[16][15];
int max_erase_cnt=0;

int dr[] = {0,-1,0};
int dc[] = {-1,0,1};

vector<pair<int, int> > archer(3);

bool chk(int r, int c){
	if(r>=0 && r<n && c>=0 && c<m)
		return true;
	
	return false;
}

void dfs(int now, int end, int before){
	if(now == end){
		// 다 골라짐
		int tmp_erase_cnt=0;

		for(int it=0; it<n; it++){
			DBG_P("iter: %d\n", it);

			vector< pair<int,int> > to_erase;
			
			for(int ac=0; ac<3; ac++){
				
				queue< pair<int,int> > q_travel;
				
				int dist[16][15] = {0,};
				int st_r = archer[ac].first -1;
				int st_c = archer[ac].second;
				
				dist[st_r][st_c] = 1;
				q_travel.push(make_pair(st_r, st_c));

				while(!q_travel.empty()){
					int now_r = q_travel.front().first;
					int now_c = q_travel.front().second;
					int now_dist = dist[now_r][now_c];

					q_travel.pop();
						
					if(map[now_r][now_c] == 1){
						to_erase.push_back(make_pair(now_r, now_c));
						break;
					}

					for(int dir=0; dir<3; dir++){
						int nxt_r = now_r + dr[dir];
						int nxt_c = now_c + dc[dir];
						
						if(!chk(nxt_r, nxt_c))
							continue;

						if(dist[nxt_r][nxt_c] != 0)
							continue;
						
						if( now_dist +1 <= d){
							dist[nxt_r][nxt_c] = now_dist + 1;
							q_travel.push(make_pair(nxt_r, nxt_c));							
						}
					}
				}// end while
			}// end for 3 archers

			// erase
			for(int i=0; i<to_erase.size(); i++){
				if(map[to_erase[i].first][to_erase[i].second] != 0){
					DBG_P("erase (%d, %d)\n", to_erase[i].first, to_erase[i].second);
					map[to_erase[i].first][to_erase[i].second] = 0;
					tmp_erase_cnt++;
				}
			}
			
			// move down
			for(int i=n-2; i>=0; i--){
				for(int j=0; j<m; j++ ){
					map[i+1][j] = map[i][j];
					if(i==0)
						map[i][j] = 0;
				}
			}
		
		}// end for it
		
		//done
		if(tmp_erase_cnt > max_erase_cnt)
			max_erase_cnt = tmp_erase_cnt;
	
		//recover
		memcpy(map, const_map, sizeof(const_map));
	}
	else{
		for(int i=before+1; i<m; i++){
			archer[now] = make_pair(n, i);
			dfs(now+1, end, i);
		}
	}

}

int main(void){
	cin >> n >> m >> d;
	
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			cin >> map[i][j];
			const_map[i][j] = map[i][j];
		}
	}
	
	dfs(0,3,-1);

	cout << max_erase_cnt << "\n";
}

