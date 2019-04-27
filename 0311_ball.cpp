#include<iostream>
#include<queue>
#include<utility>

using namespace std;
#define MAX_SIZE 11
int N, M;
char map[MAX_SIZE][MAX_SIZE];
bool visit_R[MAX_SIZE][MAX_SIZE];
bool visit_B[MAX_SIZE][MAX_SIZE];
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int p_R[2];
int p_B[2];
int p_H[2];

int bfs() {
    queue<pair<pair<int,int>, int> > q1;
    queue<pair<pair<int,int>, int> > q2;
    q1.push(make_pair(make_pair(p_R[0], p_R[1]), 1));
    visit_R[p_R[0]][p_R[1]] = 1;
    q2.push(make_pair(make_pair(p_B[0], p_B[1]), 1));
    visit_B[p_B[0]][p_B[1]] = 1;

    while(!q1.empty()) {
        int x = q1.front().first.second;
        int y = q1.front().first.first;
        int z = q1.front().second;

        q1.pop();
        
        if (x == p_H[0] && y == p_H[1])
            return z;

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx < 0 || ny < 0 || nx >= M || ny >= N)
                continue;
            if (visit_R[ny][nx] == 1)
                continue;
            if (map[ny][nx] != '.')
                continue;
            if (map[ny][nx] == '0')
                return z;

            q1.push(make_pair(make_pair(ny, nx), z+1));
            visit_R[ny][nx] = 1;
        }
    }
    return -1;
}

int main(void) {

    cin >> N >> M;

    for (int i = 0; i < N; i++) {
        cin >> map[i];
    }

    for (int i = 0; i < N; i++) { 
        for (int j = 0; j < M; j++)
            cout << map[i][j];
        cout << '\n';
    }

    // memorize location of R, B, 0
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (map[i][j] == 'R') {
                p_R[0] = j; p_R[1] = i;
            } else if (map[i][j] == 'B') {
                p_B[0] = j; p_B[1] = i;
            } else if (map[i][j] == '0') {
                p_H[0] = j; p_H[1] = i;
            }
        }
    }

    


    cout << bfs();

    return 0;
    // roll(start_point, vec) A and B
    // return case
    // 1. A meet # --> return 1 (remember A and B's location)
    // 2. A meet 0 --> return 0 (if total roll count is under 10, then return roll count else -1)
    // 3. B meet 0 --> -1

    // can move to up, down, left, right until reaching # or hole(0)
    // R and B move together
}
