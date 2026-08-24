#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif

/*
 * 计算成功时返回 1，并把计算结果写入 result。
 * 计算失败时返回 0。
 */
int calculate(double a, char operator, double b, double *result)
{
    switch (operator) {
        case '+':
            *result = a + b;
            return 1;

        case '-':
            *result = a - b;
            return 1;

        case '*':
            *result = a * b;
            return 1;

        case '/':
            if (b == 0) {
                printf("错误：除数不能为零！\n");
                return 0;
            }
            *result = a / b;
            return 1;

        case '%':
            if (a != (int)a || b != (int)b) {
                printf("错误：取模运算只能使用整数！\n");
                return 0;
            }
            if ((int)b == 0) {
                printf("错误：取模运算的除数不能为零！\n");
                return 0;
            }
            *result = (int)a % (int)b;
            return 1;

        default:
            printf("错误：不支持运算符 '%c'！\n", operator);
            return 0;
    }
}

int main(void)
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif

    char input[100];

    printf("=== 小型 C 语言计算器 ===\n");
    printf("支持的运算符：+  -  *  /  %%\n");
    printf("输入 q 可以退出程序。\n\n");

    while (1) {
        double a;
        double b;
        double result;
        char operator;
        char extra;

        printf("请输入算式，例如 10 + 5：");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("\n输入结束，程序退出。\n");
            break;
        }

        if (input[0] == 'q' || input[0] == 'Q') {
            printf("计算器已退出。\n");
            break;
        }

        /* 多读取一个字符，用来发现算式后面多余的内容。 */
        if (sscanf(input, " %lf %c %lf %c", &a, &operator, &b, &extra) != 3) {
            printf("输入格式错误，请按照“数字 运算符 数字”的格式输入。\n\n");
            continue;
        }

        if (calculate(a, operator, b, &result)) {
            printf("计算结果：%.2f\n\n", result);
        } else {
            printf("请重新输入。\n\n");
        }
    }

    return 0;
}
