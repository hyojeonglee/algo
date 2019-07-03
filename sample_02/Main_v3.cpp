#include <iostream>
#include <vector>
#include <limits.h>
#include <queue>

using namespace std;

typedef vector<int> child_v;
vector<child_v> edge_info;
vector<int> visited;
vector<int> count;
vector<int> depth;

queue<int> q;

// bfs
void bfs(int v) {
	visited[v] = 1;
	q.push(v);
	// visit했을 때 하는 일 (맨 처음 노드에 대해)
	// cout << "visit: " << v << endl;
	
	// Main loop
	while (!q.empty()) {
		int tmp_v = q.front();
		q.pop();
		child_v cv = edge_info[tmp_v];
		
		if (cv.size() != 0) {
			for (int i = 0; i < cv.size(); i++) {
				if (visited[cv[i]] == 0) {
					q.push(cv[i]);
					visited[cv[i]] = 1;
					// visit했을 때 하는 일
					count[cv[i]] = count[tmp_v] + 1;
					// cout << "visit: " << cv[i] << endl;
				}
			}
		}
		else {
			// cout << "leaf: " << tmp_v << endl;
			// cout << "count: " << count[tmp_v] << endl;
			depth.push_back(count[tmp_v]);
		}
	}
}

// dfs
void dfs(int v) {
	visited[v] = 1; // 방문
	// cout << "visit node: " << v << endl;
	child_v cv = edge_info[v];
	// 이 때 cv.size() == 0이면 지금 v는 leaf노드라는 뜻
	if (cv.size() != 0) {
		for (int i = 0; i < cv.size(); i++) {
			if (visited[cv[i]] == 0) {
				count[cv[i]] = count[v] + 1;
				dfs(cv[i]);
			}
		}
	} else {
		// leaf까지의 거리 기록
		// cout << "leaf: " << v << endl;
		// cout << "count: " << count[v] << endl;
		depth.push_back(count[v]);
	}
}

int main() {
	// 입력을 받는다 (이 때, 부모-자식으로 간선 정보를 담은 자료구조 만들어준다) -> 부모-(자식벡터)
	int V, E; // E는 입력받기용
	cin >> V >> E;
	
	// 공간 낭비?
	edge_info.resize(V);
	visited.resize(V);
	count.resize(V);
	
	for (int i = 0; i < visited.size(); i++) {
		visited[i] = 0;
		count[i] = 0;
	}
	
	for (int i = 0; i < E; i++) {
		int parent, child;
		cin >> parent >> child;
		// 부모랑 자식벡터 어떻게 만들지?
		child_v v = edge_info.at(parent);
		v.push_back(child);
		edge_info[parent] = v;
	}
	// DFS(재귀)로 루트부터 끝까지 경로를 검색한다
	// 이 때, 트리의 최대 최소 길이를 구해서 둘을 빼준다 (내려갈때 count++, 올라갈때 count--, leaf이면 leaf-높이로 기록하기
	/*
	dfs(0);
	*/
	
	bfs(0);
	
	// 공통코드
	int max = -1;
	int min = INT_MAX;
	for (int i = 0; i < depth.size(); i++) {
		int val = depth[i];
		if (val > max)
			max = val;
		if (val < min)
			min = val;
	}
	cout << max-min << endl;
	
	return 0;
}
