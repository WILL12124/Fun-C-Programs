#include <stdio.h>

void printPairs(int arr[], int size, int target)
{
    int left = 0;
    int right = size - 1;

    while (left < right)
    {
        int sum = arr[left] + arr[right];

        if (sum == target)
        {
            // 找到匹配对，打印输出
            printf("(%d, %d)\n", arr[left], arr[right]);

            // 核心逻辑：跳过左侧的重复元素
            while (left < right && arr[left] == arr[left + 1])
            {
                left++;
            }
            // 核心逻辑：跳过右侧的重复元素
            while (left < right && arr[right] == arr[right - 1])
            {
                right--;
            }

            // 移动指针继续寻找下一对
            left++;
            right--;
        }
        else if (sum < target)
        {
            // 和太小，左指针右移以增大数值
            left++;
        }
        else
        {
            // 和太大，右指针左移以减小数值
            right--;
        }
    }
}

int main()
{
    // 测试 Example 1
    int arr1[] = {2, 2, 3, 4, 4, 5, 5};
    int target1 = 7;
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("Example 1:\n");
    printPairs(arr1, size1, target1);

    // 测试 Example 3
    int arr3[] = {1, 4, 4, 5, 5};
    int target3 = 10;
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("\nExample 3:\n");
    printPairs(arr3, size3, target3);

    return 0;
}