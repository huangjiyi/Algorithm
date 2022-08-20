#ifndef _UTILS_H_
#define _UTILS_H_

#include <bits/stdc++.h>

using namespace std;

void print();

template<class T>
void print(const T &var);

template<class T>
void print(queue<T> &list);

template<class T>
void print(const vector<T> &list);

template<class T>
void print(const vector<vector<T>> &Mat);

template<class T1, class T2>
void print(const map<T1, T2> &dict);

template<class T1, class T2>
void print(const unordered_map<T1, T2> &hash_map);

void print() {
    cout << endl;
}

template<class T>
void print(const T &var) {
    cout << var << endl;
}

template<class T>
void print(const vector<T> &list) {
    cout << "[ ";
    for (const auto &item: list)
        cout << item << " ";
    cout << ']' << endl;
}

template<class T>
void print(queue<T> &list) {
    cout << "[ ";
    for (int i = 0; i < list.size(); ++i) {
        cout << list.front() << " ";
        list.push(list.front());
        list.pop();
    }
    cout << ']' << endl;
}

template<class T>
void print(const vector<vector<T>> &Mat) {
    for (const auto &row: Mat)
        print(row);
}

template<class T1, class T2>
void print(const map<T1, T2> &dict) {
    cout << "[ ";
    for (auto &item: dict) {
        cout << item.first << ": " << item.second << ' ';
    }
    cout << "]" << endl;
}

template<class T1, class T2>
void print(const unordered_map<T1, T2> &hash_map) {
    cout << "[ ";
    for (auto iter = hash_map.begin(); iter != hash_map.end(); ++iter) {
        cout << iter->first << ": " << iter->second << "  ";
    }
    cout << "]" << endl;
}

#endif