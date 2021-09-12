#include <stdio.h> 

struct student1{
    char lastName;
    int studentId;
    char grade;
}; // typedef를 사용하지 않은 구조체

typedef struct{
    char lastName;
    int studentId;
    char grade;
} student2; // typedef를 사용한 구조체

void main(){
    printf("[----- [Jegal Dohyun] [2018038018] -----] \n\n");

    struct student1 st1 = {'A', 100, 'A'}; // typedef를 사용하지 않았기 때문에 struct를 꼭 명시해줘야 한다.

    printf("st1.lastName = %c\n", st1.lastName);
    printf("st1.studentId = %d\n", st1.studentId);
    printf("st1.grade = %c\n", st1.grade);

    student2 st2 = {'B', 200, 'B'}; // typedef를 사용했기 때문에 struct를 적지 않아도 가능하다.

    printf("\nst2.lastName = %c\n", st2.lastName);
    printf("st2.studentId = %d\n", st2.studentId);
    printf("st2.grade = %c\n", st2.grade);

    student2 st3;
    st3 = st2; // 구조체의 구조 치환

    printf("\nst3.lastName = %c\n", st3.lastName);
    printf("st3.studentId = %d\n", st3.studentId);
    printf("st3.grade = %c\n", st3.grade); // 구조 치환이 이루어져 st2의 값이 st3으로 치환되었는지 확인

    /*
    if(st3==st2)
        printf("equal\n");
    else
        printf("not equal\n");

    전체 구조의 동등성을 검사하여 st3과 st2가 같으면 equal을 출력, 다르면 not equal을 출력하는 부분
    하지만 GCC에서는 직접 비교를 허용하지 않아 사용이 불가능하다.
    */
}
