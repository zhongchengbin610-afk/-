#include <stdio.h>
#include <string.h>

#define MAX 100
#define FILE_NAME "schedule.dat"

/* 排课信息结构体 */
typedef struct {
    char courseName[50];   // 课程名称
    char teacherName[50];  // 教师姓名
    char className[50];    // 班级名称
    char roomId[20];       // 机房编号
    int weekDay;           // 星期几，1-7
    int lesson;            // 第几节课
} Schedule;

Schedule schedules[MAX];
int count = 0;

/* 函数声明 */
void menu();
void addSchedule();
void showSchedules();
void searchSchedule();
void modifySchedule();
void deleteSchedule();
int checkConflict(char roomId[], int weekDay, int lesson, int ignoreIndex);
void loadData();
void saveData();

int main() {
    int choice;

    loadData();

    while (1) {
        menu();
        printf("请输入功能编号：");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addSchedule();
                break;
            case 2:
                showSchedules();
                break;
            case 3:
                searchSchedule();
                break;
            case 4:
                modifySchedule();
                break;
            case 5:
                deleteSchedule();
                break;
            case 0:
                saveData();
                printf("数据已保存，程序退出。\n");
                return 0;
            default:
                printf("输入错误，请重新选择。\n");
        }
    }

    return 0;
}

/* 菜单 */
void menu() {
    printf("\n========== 机房排课管理系统 ==========\n");
    printf("1. 添加排课信息\n");
    printf("2. 显示所有排课信息\n");
    printf("3. 查询排课信息\n");
    printf("4. 修改排课信息\n");
    printf("5. 删除排课信息\n");
    printf("0. 退出系统\n");
    printf("=====================================\n");
}

/* 添加排课信息 */
void addSchedule() {
    Schedule s;

    if (count >= MAX) {
        printf("排课信息已满，无法继续添加。\n");
        return;
    }

    printf("请输入课程名称：");
    scanf("%s", s.courseName);

    printf("请输入教师姓名：");
    scanf("%s", s.teacherName);

    printf("请输入班级名称：");
    scanf("%s", s.className);

    printf("请输入机房编号：");
    scanf("%s", s.roomId);

    printf("请输入星期几（1-7）：");
    scanf("%d", &s.weekDay);

    printf("请输入第几节课：");
    scanf("%d", &s.lesson);

    if (checkConflict(s.roomId, s.weekDay, s.lesson, -1)) {
        printf("添加失败：该机房在同一天同一节课已经有安排。\n");
        return;
    }

    schedules[count] = s;
    count++;

    printf("添加成功。\n");
}

/* 显示所有排课信息 */
void showSchedules() {
    int i;

    if (count == 0) {
        printf("暂无排课信息。\n");
        return;
    }

    printf("\n%-5s %-15s %-15s %-15s %-10s %-8s %-8s\n",
           "编号", "课程名称", "教师姓名", "班级名称", "机房编号", "星期", "节次");

    for (i = 0; i < count; i++) {
        printf("%-5d %-15s %-15s %-15s %-10s %-8d %-8d\n",
               i + 1,
               schedules[i].courseName,
               schedules[i].teacherName,
               schedules[i].className,
               schedules[i].roomId,
               schedules[i].weekDay,
               schedules[i].lesson);
    }
}

/* 查询排课信息 */
void searchSchedule() {
    int choice;
    int i;
    int found = 0;
    char key[50];
    int weekDay;

    if (count == 0) {
        printf("暂无排课信息。\n");
        return;
    }

    printf("\n========== 查询方式 ==========\n");
    printf("1. 按课程名称查询\n");
    printf("2. 按机房编号查询\n");
    printf("3. 按星期几查询\n");
    printf("=============================\n");
    printf("请选择查询方式：");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("请输入课程名称：");
        scanf("%s", key);

        for (i = 0; i < count; i++) {
            if (strcmp(schedules[i].courseName, key) == 0) {
                printf("编号：%d 课程：%s 教师：%s 班级：%s 机房：%s 星期：%d 节次：%d\n",
                       i + 1,
                       schedules[i].courseName,
                       schedules[i].teacherName,
                       schedules[i].className,
                       schedules[i].roomId,
                       schedules[i].weekDay,
                       schedules[i].lesson);
                found = 1;
            }
        }
    } else if (choice == 2) {
        printf("请输入机房编号：");
        scanf("%s", key);

        for (i = 0; i < count; i++) {
            if (strcmp(schedules[i].roomId, key) == 0) {
                printf("编号：%d 课程：%s 教师：%s 班级：%s 机房：%s 星期：%d 节次：%d\n",
                       i + 1,
                       schedules[i].courseName,
                       schedules[i].teacherName,
                       schedules[i].className,
                       schedules[i].roomId,
                       schedules[i].weekDay,
                       schedules[i].lesson);
                found = 1;
            }
        }
    } else if (choice == 3) {
        printf("请输入星期几（1-7）：");
        scanf("%d", &weekDay);

        for (i = 0; i < count; i++) {
            if (schedules[i].weekDay == weekDay) {
                printf("编号：%d 课程：%s 教师：%s 班级：%s 机房：%s 星期：%d 节次：%d\n",
                       i + 1,
                       schedules[i].courseName,
                       schedules[i].teacherName,
                       schedules[i].className,
                       schedules[i].roomId,
                       schedules[i].weekDay,
                       schedules[i].lesson);
                found = 1;
            }
        }
    } else {
        printf("查询方式输入错误。\n");
        return;
    }

    if (!found) {
        printf("未找到相关排课信息。\n");
    }
}

/* 修改排课信息 */
void modifySchedule() {
    int index;
    Schedule s;

    if (count == 0) {
        printf("暂无排课信息。\n");
        return;
    }

    showSchedules();

    printf("请输入要修改的排课编号：");
    scanf("%d", &index);

    if (index < 1 || index > count) {
        printf("编号不存在。\n");
        return;
    }

    index--;

    printf("请输入新的课程名称：");
    scanf("%s", s.courseName);

    printf("请输入新的教师姓名：");
    scanf("%s", s.teacherName);

    printf("请输入新的班级名称：");
    scanf("%s", s.className);

    printf("请输入新的机房编号：");
    scanf("%s", s.roomId);

    printf("请输入新的星期几（1-7）：");
    scanf("%d", &s.weekDay);

    printf("请输入新的第几节课：");
    scanf("%d", &s.lesson);

    if (checkConflict(s.roomId, s.weekDay, s.lesson, index)) {
        printf("修改失败：该机房在同一天同一节课已经有安排。\n");
        return;
    }

    schedules[index] = s;

    printf("修改成功。\n");
}

/* 删除排课信息 */
void deleteSchedule() {
    int index;
    int i;

    if (count == 0) {
        printf("暂无排课信息。\n");
        return;
    }

    showSchedules();

    printf("请输入要删除的排课编号：");
    scanf("%d", &index);

    if (index < 1 || index > count) {
        printf("编号不存在。\n");
        return;
    }

    index--;

    for (i = index; i < count - 1; i++) {
        schedules[i] = schedules[i + 1];
    }

    count--;

    printf("删除成功。\n");
}

/*
 * 冲突判断
 * ignoreIndex 表示忽略某条记录：
 * 添加时传 -1
 * 修改时传当前修改记录的下标
 */
int checkConflict(char roomId[], int weekDay, int lesson, int ignoreIndex) {
    int i;

    for (i = 0; i < count; i++) {
        if (i == ignoreIndex) {
            continue;
        }

        if (strcmp(schedules[i].roomId, roomId) == 0 &&
            schedules[i].weekDay == weekDay &&
            schedules[i].lesson == lesson) {
            return 1;
        }
    }

    return 0;
}

/* 读取数据 */
void loadData() {
    FILE *fp;

    fp = fopen(FILE_NAME, "rb");

    if (fp == NULL) {
        count = 0;
        return;
    }

    fread(&count, sizeof(int), 1, fp);
    fread(schedules, sizeof(Schedule), count, fp);

    fclose(fp);
}

/* 保存数据 */
void saveData() {
    FILE *fp;

    fp = fopen(FILE_NAME, "wb");

    if (fp == NULL) {
        printf("文件保存失败。\n");
        return;
    }

    fwrite(&count, sizeof(int), 1, fp);
    fwrite(schedules, sizeof(Schedule), count, fp);

    fclose(fp);
}

