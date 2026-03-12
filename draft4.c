// this program iterates the Elementary Cellular Automaton
#include <stdio.h>
#include <stdlib.h>

int *convertToBinary(int rule);
int getRuleOutcome(int *ruleBinary, int left, int center, int right);

int main()
{
    int aliveCellIndex, rule, numIterations;
    printf("Input the Alive Cell Index, Rule, # of interations: ");
    scanf("%d %d %d", &aliveCellIndex, &rule, &numIterations);

    // 分配当前代和下一代的内存
    int *cell = calloc(17, sizeof(int));
    int *nextCell = calloc(17, sizeof(int));

    if (cell == NULL || nextCell == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    // 防止用户输入的索引越界
    if (aliveCellIndex >= 0 && aliveCellIndex < 17)
    {
        cell[aliveCellIndex] = 1;
    }

    // convert rule to binary truth table
    int *ruleBinary = convertToBinary(rule);
    printf("\n");

    // 开始迭代代数 (你原本读入了 numIterations 但没使用)
    for (int iter = 0; iter < numIterations; iter++)
    {

        // 打印当前这一代的状态 (用 O 表示活，. 表示死，方便观察)
        for (int j = 0; j < 17; j++)
        {
            printf("%c", cell[j] ? 'O' : '.');
        }
        printf("\n");

        // 计算下一代
        for (int j = 0; j < 17; j++)
        {
            // 处理边界：如果是最左边，左邻居当做 0；如果是最右边，右邻居当做 0
            int left = (j == 0) ? 0 : cell[j - 1];
            int center = cell[j];
            int right = (j == 16) ? 0 : cell[j + 1];

            // 调用函数，不需要加 int
            nextCell[j] = getRuleOutcome(ruleBinary, left, center, right);
        }

        // 把计算好的下一代状态更新到当前数组中，准备下一次循环
        for (int j = 0; j < 17; j++)
        {
            cell[j] = nextCell[j];
        }
    }

    // 释放所有动态分配的内存
    free(cell);
    free(nextCell);
    free(ruleBinary);
    return 0;
}

int *convertToBinary(int rule)
{
    int *ruleBinary = calloc(8, sizeof(int));
    for (int i = 0; i <= 7; i++)
    {
        ruleBinary[i] = rule % 2;
        rule /= 2;
    }

    // 修复越界：打印 8 个元素，应该是 i < 8
    printf("Rule in Binary (LSB to MSB): ");
    for (int i = 0; i < 8; i++)
    {
        printf("%d ", ruleBinary[i]);
    }

    // 修复语法：去掉 int *
    return ruleBinary;
}

int getRuleOutcome(int *ruleBinary, int left, int center, int right)
{
    // 计算出十进制索引 (0 到 7 之间)
    int decimal = left * 4 + center * 2 + right;

    // 修复逻辑：返回该索引对应的规则结果（0或1），而不是直接返回索引数字
    return ruleBinary[decimal];
}