#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    int n, b;
    cin >> n >> b;

    vector<pair<int, int>> queries(n);
    for (int i = 0; i < n; i++) {
        cin >> queries[i].first >> queries[i].second;
    }

    queue<pair<int, int>> q; // H�ng d?i c�c y�u c?u
    vector<int> end_times(n, -1); // Th?i di?m ho�n th�nh c?a c�c y�u c?u
    long long current_time = 0; // Th?i di?m hi?n t?i c?a m�y ch?

    for (int i = 0; i < n; i++) {
        int ti = queries[i].first;
        int di = queries[i].second;

        // X? l� c�c y�u c?u d� ho�n th�nh trong h�ng d?i tru?c khi x? l� y�u c?u m?i
        while (!q.empty() && current_time <= ti) {
            int query_index = q.front().first;
            int duration = q.front().second;
            q.pop();

            current_time = max(current_time, (long long)queries[query_index].first) + duration;
            end_times[query_index] = current_time;
        }

        if (current_time <= ti) {
            // M�y ch? r?nh t?i th?i di?m ti, b?t d?u x? l� y�u c?u n�y
            current_time = ti + di;
            end_times[i] = current_time;
        } else if (q.size() < (unsigned int)b) {
            // M�y ch? dang b?n, th�m y�u c?u n�y v�o h�ng d?i n?u c�n ch?
            q.push({i, di});
        } else {
            // M�y ch? dang b?n v� h�ng d?i d?y, t? ch?i y�u c?u n�y
            end_times[i] = -1;
        }
    }

    // X? l� c�c y�u c?u c�n l?i trong h�ng d?i
    while (!q.empty()) {
        int query_index = q.front().first;
        int duration = q.front().second;
        q.pop();

        current_time = max(current_time, (long long)queries[query_index].first) + duration;
        end_times[query_index] = current_time;
    }

    for (int i = 0; i < n; i++) {
        cout << end_times[i] << " ";
    }
    cout << endl;

    return 0;
}

