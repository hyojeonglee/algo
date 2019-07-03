#include <iostream>
#include <string>
#include <map>

using namespace std;

int main(void) {
    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        map<string, int> m;
        string result = "";
        // input
        string tgt;
        int K; // K는 1부터 시작:
        cin >> K;
        cin >> tgt;

        // 접미어 배열 만들기 (뒤에서부터)
        // ordered map에 넣기
        int len = (int) tgt.length();
        int i = len - 1;
        while (i >= 0) {
            string tmp = "";
            for (int j = i; j < len; j++) {
                tmp += tgt[j];
            }
            string key = tmp;
            int value = i;
            m[key] = value;
            i--;
        }
        int count = 1;
        for (auto it = m.begin(); it != m.end(); it++) {
            if (K == count) {
                result = it->first;
            }
            count++;
        }

        cout << "#" << t << " " << result << endl;
    }

    return 0;
}
