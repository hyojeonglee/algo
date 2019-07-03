#include <iostream>
#include <string>
#include <vector>

# define NO_OF_CHARS 128 // 소문자는 122까지 였던걸로 기억 (ascii)

using namespace std;

int freq;

// 보이어무어: A utility function to get maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}
 
// 보이어무어: The preprocessing function for Boyer Moore's bad character heuristic
void badCharHeuristic(string str, int size, int badchar[NO_OF_CHARS]) {
    int i;
 
    // Initialize all occurrences as -1
    for (i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;
    // Fill the actual value of last occurrence of a character
    for (i = 0; i < size; i++)
        badchar[(int) str[i]] = i;
}
 
// 보이어무어
void search(string txt, string pat) {
  int m = (int) pat.length();
  int n = (int) txt.length();
 
  int badchar[NO_OF_CHARS];
 
  badCharHeuristic(pat, m, badchar);

  int s = 0; // txt에서의 패턴의 시작점
  while (s <= (n - m)) {
    int j = m - 1; // 패턴 인덱스 (뒤부터)
		while (j >= 0 && pat[j] == txt[s + j])
			j--;
		if (j < 0) { // 해당 패턴이 등장함 (j만큼 다 찾음)
      		// printf("\n pattern occurs at shift = %d", s);
			freq++; // 찾았을 때 할 일: 여기서는 프리퀀시 높이기
			s += (s + m < n) ? m - badchar[txt[s + m]] : 1; // s 업데이트: (1)s + m < n? 아직 txt의 끝에 도달하지 못함 (2)s + m >= n? 패턴의 끝이 txt의 끝에 도달
    } else { // 패턴이 등장하지 않음 (j만큼 다 못찾음)
      s += max(1, j - badchar[txt[s + j]]); // s 업데이트: 가능하면 스킵하거나, 원래대로 1만큼만 가거나
		}
	}
}

int main() {
	// BM (보이어-무어) 알고리즘 --> O(n/m)
	
	// start - 공통
	string hint = "";
	int n;
	vector<string> v;
	
	cin >> hint;
	cin >> n;
	
	for (int i = 0; i < n; i++) {
		string tmp;
		cin >> tmp;
		v.push_back(tmp);
	}
	
	int max_freq = -1;
	int max_idx = -1;
  // end - 공통
	
	string txt = hint;
	for (int i = 0; i < n; i++) {
		freq = 0;
  	string pat = v.at(i);
 		search(txt, pat);
		if (freq > 0 && max_freq < freq) {
			max_freq = freq;
			max_idx = i;
		}
	}
	
	if (max_freq == -1)
		cout << "null";
	else
		cout << v.at(max_idx);
	
	/*
	// KMP algorithm --> O(n+m) 최악의 경우는 O(n*m)
	// --> 큰 테스트 케이스에서 죽음

	// 1000 * 5000000 = 5000000000 = 5억 --> 약 5초 (1억에 1초라고 대충 감안)
	for (int x = 0; x < n; x++) { // 최대 1000개
		string tmp = v.at(x);
		int freq = 0;
		
		// get pi funtion --> 접미어배열의 각 접미어들에 대한 LCP 구할때 똑같이 쓸 수 있음
		int tmp_len = (int) tmp.length();
		pi.resize(tmp_len);
		int k = 0;
		// 1부터 시작함을 주의!
		for (int i = 1; i < tmp_len; i++) {
			while (k > 0 && tmp[i] != tmp[k])
				k = pi[k - 1];
			if (tmp[i] == tmp[k])
				pi[i] = ++k;
		}
		
		// check
		// 최악의 경우라면? (kmp가 적용될 수 없는 상황 == pi가 다 0이면?) --> 50000 * 100 = 5000000
		int j = 0;
		for (int i = 0; i < (int) hint.length(); i++) { // 최대 hint는 50000 길이, tmp는 100 길이
			while (j > 0 && hint[i] != tmp[j])
				j = pi[j-1];
			if (hint[i] == tmp[j]) {
				if (j == tmp_len - 1) {
					freq++;
					j = pi[j];
				}
				else
					j++;
			}
		}
		
	  if (max_freq < freq && freq > 0) {
			max_freq = freq;
			max_idx = x;
		}
	}
	
	if (max_freq == -1)
		cout << "null";
	else
		cout << v.at(max_idx);
	*/
	
	// non-optimized version --> 문제 이해 잘못함
	// 아마 시간 초과나겠지만, search의 시작점을 업데이트해주게 바꾸면 쓸모없는 알고리즘은 아님
	/*

	for (int i = 0; i < n; i++) {
		string tmp = v.at(i);
		int len = (int) tmp.length();
		// 최적화 포인트1: 길이가 최대길이보다 짧으면 검사할 필요도 없음
		if (len < max_len)
			continue;
		if (hint.find(tmp) != string::npos) {
			if (max_len < len) {
				max_len = len;
				max_idx = i;
			}
		}
	}
	
	if (max_idx == -1)
		cout << "null";
	else
		cout << v.at(max_idx);
	*/
  return 0;
}
