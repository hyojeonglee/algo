#include <iostream>
#include <set>
#include <string>

using namespace std;

int main(void) {
    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        set<string> s;
        string result;
        int K; // 1부터 시작
        string tgt;
        cin >> K;
        cin >> tgt;

        int len = (int) tgt.length();

        // 모든 접미어 구하기
        // 접미어들의 모든 접두어 구해서 set에 저장
        int i = len - 1;
        while (i >= 0) {
            string tmp = "";
            for (int j = i; j < len; j++) {
                tmp += tgt[j];
            }
            int tmp_len = (int) tmp.length();
            int n = 0;
            while (n < tmp_len) {
                string head = "";
                for (int m = 0; m <= n; m++) {
                    head += tmp[m];
                }
                // push to set
                s.insert(head);
                n++;
            }
            i--;
        }

        // set iteration해서 K번째 문자열 찾기
        int count = 1;
        bool flag = false;
        for (auto it = s.begin(); it != s.end(); it++) {
            if (count == K) {
                cout << "#" << t << " " << *it << endl;
                flag = true;
                break;
            }
            count++;
        }
        if (!flag)
            cout << "#" << t << " " << "none" << endl;
    }

    return 0;
}
