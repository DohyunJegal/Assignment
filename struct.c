#include <stdio.h> 

struct student1{
    char lastName;
    int studentId;
    char grade;
}; // typedef�� ������� ���� ����ü

typedef struct{
    char lastName;
    int studentId;
    char grade;
} student2; // typedef�� ����� ����ü

void main(){
    printf("[----- [Jegal Dohyun] [2018038018] -----] \n\n");

    struct student1 st1 = {'A', 100, 'A'}; // typedef�� ������� �ʾұ� ������ struct�� �� �������� �Ѵ�.

    printf("st1.lastName = %c\n", st1.lastName);
    printf("st1.studentId = %d\n", st1.studentId);
    printf("st1.grade = %c\n", st1.grade);

    student2 st2 = {'B', 200, 'B'}; // typedef�� ����߱� ������ struct�� ���� �ʾƵ� �����ϴ�.

    printf("\nst2.lastName = %c\n", st2.lastName);
    printf("st2.studentId = %d\n", st2.studentId);
    printf("st2.grade = %c\n", st2.grade);

    student2 st3;
    st3 = st2; // ����ü�� ���� ġȯ

    printf("\nst3.lastName = %c\n", st3.lastName);
    printf("st3.studentId = %d\n", st3.studentId);
    printf("st3.grade = %c\n", st3.grade); // ���� ġȯ�� �̷���� st2�� ���� st3���� ġȯ�Ǿ����� Ȯ��

    /*
    if(st3==st2)
        printf("equal\n");
    else
        printf("not equal\n");

    ��ü ������ ����� �˻��Ͽ� st3�� st2�� ������ equal�� ���, �ٸ��� not equal�� ����ϴ� �κ�
    ������ GCC������ ���� �񱳸� ������� �ʾ� ����� �Ұ����ϴ�.
    */
}