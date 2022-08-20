#include "utils.h"

// 暴力匹配, 时间复杂度O(mn), 空间复杂度O(1)
int naiveMatch(const string &s, const string &t) {
    int pos = -1;
    for (int i = 0; i < s.length(); ++i) {
        bool match = true;
        for (int j = 0; j < t.length(); ++j)
            if (s[i + j] != t[j]) {
                match = false;
                break;
            }
        if (match) pos = i;
    }
    return pos;
}

// 获取KMP算法中的next数组
vector<int> getNext(const string &t) {
    // 参考: https://www.zhihu.com/question/21923021
    // k-前缀: 字符串的前 k 个字符, k-后缀: 字符串的后 k 个字符, k 必须小于字符串长度 (next[0] = 0)
    // next[i]: P[0]~P[i]这一段字符串, 使得k-前缀恰等于k-后缀的最大的k.
    // 维护左右两个指针, 右指针从1开始, 表示当前要计算next[i]的i，左指针则表示用来最大k-前缀的末尾下标
    // 令 left = next[right-1], 这样 t 中前 left 个元素与 t[right] 左边 left 个元素相等 (根据 next[i] 定义)
    // 比较 t[right] 和 t[left], 如果 t[right] == t[left], 则 next[right] = left + 1,
    // 如果 t[right] != t[left], 则令 left = next[left], 继续比较 t[right] 和 t[left],
    // 不断重复直到 left = 0, 还不相等就令 next[right] = 0
    vector<int> next(t.length(), 0);
    int left = 0, right = 1;
    while (right < t.length()) {
        if (t[right] == t[left])
            next[right++] = left++ + 1;
        else if (left > 0)
            left = next[left - 1];
        else
            left++;
    }
    return next;
}

// KMP字符串匹配算法
vector<int> kmpMatch(const string &s, const string &t) {
    // 先获取模式串的 next 数组
    // 后面匹配的逻辑与计算 next 数组时类似
    vector<int> result;
    auto next = getNext(t);
    int i = 0, cur = 0;
    while (i < s.length()) {
        if (s[i] == t[cur]) {
            cur++;
            i++;
        } else if (cur) {
            cur = next[cur - 1];
        } else {
            i++;
        }
        if (cur == t.length()) {
            result.push_back(i - cur);
            cur = next[cur - 1];
        }
    }
    return result;
}

int main() {
    string s = "ababcdabbabababad";
    string t = "ab";
    print(s.find(t));
    print(naiveMatch(s, t));
    print(getNext(t));
    print(kmpMatch(s, t));
    return 0;
}
