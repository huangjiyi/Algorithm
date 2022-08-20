//
// Created by huangjiyi on 2022/8/20.
//
// 该文件用于实现一些经典的排序算法
// 原理参考：https://zhuanlan.zhihu.com/p/42586566
// 可以在 https://leetcode.cn/problems/sort-an-array/ 测试实现的排序算法
#include "utils.h"

class Solution {
  public:
    // 1. 冒泡排序
    // 从左到右遍历长度为 n 数组 nums, 依次比较相邻元素, 升序不变降序则交换
    // 一次遍历后 nums[n-1] 为最大元素, 然后按同样的方式遍历 nums[:n-1]
    // 不断循环上述过程, 直到排序完成 (一次遍历没有交换就是排序成功)
    // 时间复杂度: O(n2), 空间复杂度: O(1), 稳定性: 稳定 (相邻两个元素相等不会交换)
    vector<int> bubbleSort(vector<int> &nums) {
        bool sorted;
        for (int i = (int) nums.size() - 1; i > 0; --i) {
            sorted = true;
            for (int j = 0; j < i; ++j)
                if (nums[j] > nums[j + 1]) {
                    swap(nums[j], nums[j + 1]);
                    sorted = false;
                }
            if (sorted) break;
        }
        return nums;
    }

    // 2. 选择排序
    // 寻找数组 nums 中最小的元素, 然后将其与 nums[0] 交换
    // 然后在寻找 nums[1:] 中最小的元素并与 nums[1] 交换, 不断重复这个过程
    // 时间复杂度: O(n2), 空间复杂度: O(1),
    // 稳定性: 在数组中交换是不稳定的，如 [5, 5, 2], 在把 2 交换到前面时会破坏不同 5 的稳定性
    //        如果用链表实现时稳定的，只需要把结点 2 删除再插入到前面。
    vector<int> selectSort(vector<int> &nums) {
        int min_pos;
        for (int i = 0; i < (int) nums.size() - 1; ++i) {
            min_pos = i;
            for (int j = i + 1; j < nums.size(); ++j)
                if (nums[j] < nums[min_pos])
                    min_pos = j;
            swap(nums[i], nums[min_pos]);
        }
        return nums;
    }

    // 3. 插入排序
    // 将 nums[:1] 看作一个有序数组, 然后将后面的元素依次插入到这个列表中
    // 插入的过程:
    //     假设 nums[:k] 已经有序, 从 nums[:k] 最后一个元素向左遍历,
    //     不断与 nums[k] 进行比较, 如果 nums[k] 更小就交换, 否则就停止
    // 时间复杂度: O(n2), 空间复杂度: O(1), 稳定性: 稳定 (后插入的元素在插入时遇到相等的元素便停止)
    vector<int> insertSort(vector<int> &nums) {
        for (int i = 1; i < (int) nums.size(); ++i)
            for (int j = i; j > 0 and nums[j] < nums[j - 1]; --j)
                swap(nums[j], nums[j - 1]);
        return nums;
    }

    // 4. 快速排序
    // 从数组中 (随机) 挑出一个元素，称为基准 (pivot)
    // 重新排列数组，所有比基准值小的元素摆放在基准前面，所有比基准值大的元素摆在基准后面，称为分区操作
    // 递归地对 pivot 左边和右边的子数组进行分区操作, 完成排序
    // 分区操作具体实现:
    //     先将选择的 pivot 与第一个元素交换, 维护一个指针 border 指向最后一个不大于 pivot 的元素, 初始化为 pivot 的索引
    //     然后遍历后面的元素, 每遇到一个小于 pivot 的元素, 就将他和 nums[border + 1] 交换
    //     遍历结束后将 pivot 与 nums[border] 交换
    static int partition(vector<int> &nums, int left, int right) {
        default_random_engine e(chrono::system_clock::now().time_since_epoch().count());
        uniform_int_distribution<int> u(left, right);
        swap(nums[left], nums[u(e)]);
        int border = left;
        for (int i = left + 1; i <= right; ++i) {
            if (nums[i] < nums[left])
                swap(nums[i], nums[++border]);
        }
        swap(nums[left], nums[border]);
        return border;
    }

    void qsort(vector<int> &nums, int left, int right) {
        if (left < right) {
            int border = partition(nums, left, right);
            qsort(nums, left, border - 1);
            qsort(nums, border + 1, right);
        }
    }

    vector<int> quickSort(vector<int> &nums) {
        qsort(nums, 0, (int) nums.size() - 1);
        return nums;
    }

    // 5. 归并排序
    // 参考: https://zhuanlan.zhihu.com/p/124356219
    // 将待排序的数组分解成若干个只有一个元素的数组，然后不断两两合并成一个有序数组
    // 合并过程:
    //     申请一个合并后大小的数组空间，维护两个指针分别指向 2 个待排序子数组的第一个元素，
    //     不断比较两个指针指向的元素，将更小的元素放入合并空间同时右移对应的指针
    //     直到某一指针到达列尾，将另一数组剩下的所有元素直接复制到合并空间
    void merge(vector<int> &nums, vector<int> &reg, int start, int end) {
        if (start == end) return;
        int left_end = (start + end) / 2;
        merge(nums, reg, start, left_end);
        merge(nums, reg, left_end + 1, end);
        int left = start, right = left_end + 1;
        int k = start;
        while (left <= left_end and right <= end)
            reg[k++] = nums[left] > nums[right] ? nums[right++] : nums[left++];
        while (left <= left_end)
            reg[k++] = nums[left++];
        while (right <= end)
            reg[k++] = nums[right++];
        for (int i = start; i <= end; ++i)
            nums[i] = reg[i];
    }

    vector<int> mergeSort(vector<int> &nums) {
        vector<int> reg((int) nums.size(), 0);
        merge(nums, reg, 0, (int) nums.size() - 1);
        return nums;
    }

    // 6. 希尔排序
    // 参考: https://zhuanlan.zhihu.com/p/122632213
    // 前言: 插入排序在数组基本有序时效率很高，时间复杂度近似 O(n), 但当数组较大且基本无序的情况下性能会迅速恶化。
    // 希尔排序是对插入排序的改进，称为分组插入排序，或递减增量排序算法
    // 思路: 将待排序数组分割为若干个“相间”的子数组 (每个子数组由相隔某个"增量"的元素构成)，
    // 对每个子数组分别进行插入排序, 不断减小"增量"重复这个过程，直到增量为1时对整个数组进行直接插入排序
    // 增量序列的选取:
    //     1. [1, 2, ..., n/4, n/2], Shell增量, 时间复杂度: O(n2)
    //     2. [1, 3, ..., 2k - 1], Hibbard增量, 时间复杂度: O(n1.5)
    //     3. [1, 5, 19, 41, 109, ...], Sedgewick增量, 时间复杂度: O(nlogn)
    void delta_insert_sort(vector<int> &nums, int start, int delta) {
        for (int i = start + delta; i < nums.size(); i += delta) {
            for (int j = i; j - 1 >= 0 and nums[j] < nums[j - 1]; j -= delta)
                swap(nums[j], nums[j - 1]);
        }
    }

    vector<int> shellSort(vector<int> &nums) {
        for (int delta = (int) nums.size() / 2; delta > 0; delta /= 2)
            for (int i = 0; i < delta; ++i)
                delta_insert_sort(nums, i, delta);
        return nums;
    }

    // 7. 堆排序
    // 等学完了树在实现
    vector<int> heapSort(vector<int> &nums) {
        return nums;
    }


};

int main() {
    Solution solve;
    vector<int> nums = {5, 1, 1, 2, 0, 0};
    // print(solve.bubbleSort(nums));
    // print(solve.selectSort(nums));
    // print(solve.insertSort(nums));
    // print(solve.quickSort(nums));
    // print(solve.mergeSort(nums));
    print(solve.shellSort(nums));
    return 1;
}