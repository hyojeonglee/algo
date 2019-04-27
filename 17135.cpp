#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

bool debug = false;
int N, M, D;
int arr[16][16];
int arr_rep[16][16];

int check[16][16];
// left-up-right
int dir[3][2] = {{0,-1}, {-1,0}, {0,1}};
vector<pair<int,int> > enemy;

bool enemy_left() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (arr[i][j] == 1)
                return true;
        }
    }
    return false;
}

void update_arr() {
    int tmp[N][M];
    // copy arr to tmp
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            tmp[i][j] = arr[i][j];
        }
    }
    // push below by 1 blk
    for (int i = 0; i < N-1; i++) {
        for (int j = 0; j < M; j++) {
            arr[i+1][j] = tmp[i][j];
        }
    }
    // make 0 to arr's first row
    for (int i = 0; i < M; i++)
        arr[0][i] = 0;
}

void reset_arr_all() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            arr[i][j] = arr_rep[i][j];
        }
    }
}

bool is_inside(int a, int b) {
    return (a >= 0 && a < N) && (b >= 0 && b < M);
}

void bfs(int r, int c) {
    int cur_y = r-1, cur_x = c;
    
    queue<pair<int,int> > q;
    q.push(pair<int,int>(cur_y, cur_x));
    check[cur_y][cur_x] = 1;
    
    while (!q.empty()) {
        cur_y = q.front().first;
        cur_x = q.front().second;
        q.pop();

        if (arr[cur_y][cur_x] == 1) {
            enemy.push_back(pair<int,int>(cur_y, cur_x));
            return;
        }

        // left-up-right
        for (int i = 0; i < 3; i++) {
            int next_y = cur_y + dir[i][0];
            int next_x = cur_x + dir[i][1];
            
            if (!is_inside(next_y, next_x) || check[next_y][next_x] != 0)
                continue;
            
            if (check[cur_y][cur_x] + 1 <= D) {
                check[next_y][next_x] = check[cur_y][cur_x] + 1;
                q.push(pair<int,int>(next_y, next_x));
            }

            // if (is_inside(next_y, next_x) && check[next_y][next_x] <= D && arr[next_y][next_x] == 1) {
                // push enemy vector
            //    enemy.push_back(pair<int,int>(next_y, next_x));
            //    return;
            // }

        }
    }
}

int main(void) {
    // 입력받기
    cin >> N >> M >> D;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> arr[i][j];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            arr_rep[i][j] = arr[i][j];
    int max_count = -1;
    int cur_count = 0;
    // initial hunter array
    int hunter[M];
    for (int i = 0; i < M; i++) {
        if (i < 3) hunter[i] = 1;
        else hunter[i] = 0;
    }
    // make cases (comb)
    sort(hunter, hunter+M);
    do {
        // insert cases
        for (int i = 0; i < M; i++)
            arr[N][i] = hunter[i];
        // for this case
        while (enemy_left()) {
            for (int h = 0; h < M; h++) {
                if (arr[N][h] == 1) {
                    for (int i = 0; i < N; i++) {
                        for (int j = 0; j < M; j++)
                            check[i][j] = 0;
                    }
                    bfs(N, h);
                }
            }
            pair<int,int> e;
            for (auto &e : enemy) {
                int r = e.first;
                int c = e.second;
                if (arr[r][c] == 1)
                    cur_count++;
                arr[r][c] = 0;
            }
            if (debug) {
                for (int i = 0; i <= N; i++) {
                    for (int j = 0; j < M; j++) {
                        cout << arr[i][j] << " ";
                    }
                    cout << "\n";
                }
                cout << "--------------\n";
            }
            update_arr();    
            enemy.clear();
        }
        if (max_count < cur_count) {
            if (debug) {
                cout << "#########" << cur_count << "\n";
            }
            max_count = cur_count;
        }

        reset_arr_all();
        cur_count = 0;
    } while (next_permutation(hunter, hunter+M));

    cout << max_count << "\n";
    return 0;

}
