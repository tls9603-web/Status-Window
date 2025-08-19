/*
====================================================================
 RPG 스탯 관리 시스템 (과제 제출용)
====================================================================
 이 프로그램은 요구사항 명세서에 따라 캐릭터의 스탯을 관리하는
 간단한 콘솔 게임입니다.
====================================================================
*/

// 필요한 라이브러리 포함
#include <iostream>

// std::cout, std::cin 등을 편하게 쓰기 위함
using namespace std;

// 함수 미리 선언 (프로토타입)
void setPotion(int count, int* p_HPPotion, int* p_MPPotion);
void showStatus(int hpPotion, int mpPotion, int status[]);
void healHP(int* p_HPPotion, int status[]);
void healMP(int* p_MPPotion, int status[]);
void enhanceHP(int status[]);
void enhanceMP(int status[]);
void useAttackSkill(int status[]);
void useUltimateSkill(int status[]);
void pseudoClearScreen(); // 화면 정리 함수 추가

// 화면을 "지우는 것처럼" 보이게 하는 함수
// 간단하게 새 줄을 50번 출력해서 이전 내용을 위로 밀어냅니다.
void pseudoClearScreen() {
    for (int i = 0; i < 50; ++i) {
        cout << '\n';
    }
}

// 프로그램의 시작점
int main() {
    // --- 데이터 초기화 ---
    // status[0]=HP, status[1]=MP, status[2]=공격력, status[3]=방어력
    int status[4] = { 0, 0, 0, 0 };

    int HPPotion = 0; // HP 포션 개수
    int MPPotion = 0; // MP 포션 개수

    // --- 캐릭터 스탯 입력 ---
    pseudoClearScreen(); // 프로그램을 시작할 때 화면을 한 번 정리

    // do-while문을 사용해 조건에 맞지 않으면 다시 입력받음
    do {
        cout << "HP를 입력하세요 (50보다 커야 합니다): ";
        cin >> status[0];
        cout << "MP를 입력하세요 (50보다 커야 합니다): ";
        cin >> status[1];

        if (status[0] <= 50 || status[1] <= 50) {
            pseudoClearScreen();
            cout << "HP와 MP는 모두 50보다 커야 합니다. 다시 입력해주세요.\n" << endl;
        }
    } while (status[0] <= 50 || status[1] <= 50);

    pseudoClearScreen();

    do {
        cout << "공격력을 입력하세요 (0보다 커야 합니다): ";
        cin >> status[2];
        cout << "방어력을 입력하세요 (0보다 커야 합니다): ";
        cin >> status[3];

        if (status[2] <= 0 || status[3] <= 0) {
            pseudoClearScreen();
            cout << "공격력과 방어력은 모두 0보다 커야 합니다. 다시 입력해주세요.\n" << endl;
        }
    } while (status[2] <= 0 || status[3] <= 0);

    // 포인터를 사용하여 포션 5개씩 지급
    setPotion(5, &HPPotion, &MPPotion);
    cout << "\n* 포션이 지급되었습니다. (HP, MP 포션 각 5개)\n" << endl;

    cout << "=============================================" << endl;
    cout << "<스탯 관리 시스템을 시작합니다>" << endl;

    // --- 게임 메인 루프 ---
    while (true) {
        // 현재 상태 보여주기
        showStatus(HPPotion, MPPotion, status);

        // 메뉴 출력
        cout << "\n<스탯 관리 시스템>" << endl;
        cout << "1. HP 회복" << endl;
        cout << "2. MP 회복" << endl;
        cout << "3. HP 강화" << endl;
        cout << "4. MP 강화" << endl;
        cout << "5. 공격 스킬 사용" << endl;
        cout << "6. 필살기 사용" << endl;
        cout << "7. 나가기" << endl;
        cout << "번호를 선택해주세요: ";

        int choice;
        cin >> choice; // 사용자 선택 입력받기

        pseudoClearScreen(); // 선택 후 결과를 보여주기 전에 다시 화면 정리

        // 선택에 따라 다른 기능 실행
        switch (choice) {
        case 1:
            healHP(&HPPotion, status);
            break;
        case 2:
            healMP(&MPPotion, status);
            break;
        case 3:
            enhanceHP(status);
            break;
        case 4:
            enhanceMP(status);
            break;
        case 5:
            useAttackSkill(status);
            break;
        case 6:
            useUltimateSkill(status);
            break;
        case 7:
            cout << "프로그램을 종료합니다." << endl;
            return 0; // return 0으로 main 함수를 끝내서 프로그램 종료
        default:
            cout << "잘못된 번호입니다. 1~7 사이의 숫자를 입력해주세요." << endl;
            break;
        }
        cout << "\n---------------------------------------------" << endl;
    }

    return 0;
}

// --- 함수 정의 ---

// 포션 개수 설정 (포인터 사용)
void setPotion(int count, int* p_HPPotion, int* p_MPPotion) {
    *p_HPPotion = count;
    *p_MPPotion = count;
}

// 현재 상태 출력
void showStatus(int hpPotion, int mpPotion, int status[]) {
    cout << "--- 현재 캐릭터 상태 ---" << endl;
    cout << "HP: " << status[0] << " (남은 HP 포션: " << hpPotion << "개)" << endl;
    cout << "MP: " << status[1] << " (남은 MP 포션: " << mpPotion << "개)" << endl;
    cout << "공격력: " << status[2] << endl;
    cout << "방어력: " << status[3] << endl;
    cout << "------------------------" << endl;
}

// 1. HP 회복
void healHP(int* p_HPPotion, int status[]) {
    if (*p_HPPotion > 0) {
        status[0] += 20;
        (*p_HPPotion)--; // 포인터가 가리키는 값을 1 감소
        cout << "* HP가 20 회복되었습니다. 포션이 1개 차감됩니다." << endl;
        cout << "현재 HP: " << status[0] << endl;
        cout << "남은 포션 수: " << *p_HPPotion << endl;
    }
    else {
        cout << "* HP 포션이 없습니다!" << endl;
    }
}

// 2. MP 회복
void healMP(int* p_MPPotion, int status[]) {
    if (*p_MPPotion > 0) {
        status[1] += 20;
        (*p_MPPotion)--;
        cout << "* MP가 20 회복되었습니다. 포션이 1개 차감됩니다." << endl;
        cout << "현재 MP: " << status[1] << endl;
        cout << "남은 포션 수: " << *p_MPPotion << endl;
    }
    else {
        cout << "* MP 포션이 없습니다!" << endl;
    }
}

// 3. HP 강화
void enhanceHP(int status[]) {
    status[0] *= 2; // status[0] = status[0] * 2; 와 같음
    cout << "* HP가 2배로 증가되었습니다." << endl;
    cout << "현재 HP: " << status[0] << endl;
}

// 4. MP 강화
void enhanceMP(int status[]) {
    status[1] *= 2;
    cout << "* MP가 2배로 증가되었습니다." << endl;
    cout << "현재 MP: " << status[1] << endl;
}

// 5. 공격 스킬 사용
void useAttackSkill(int status[]) {
    if (status[1] >= 50) {
        status[1] -= 50;
        cout << "* 스킬을 사용하여 MP가 50 소모되었습니다." << endl;
        cout << "현재 MP: " << status[1] << endl;
    }
    else {
        cout << "* MP가 부족하여 스킬을 사용할 수 없습니다. (필요 MP: 50)" << endl;
    }
}

// 6. 필살기 사용
void useUltimateSkill(int status[]) {
    if (status[1] > 0) {
        int mpCost = status[1] / 2; // 현재 MP의 50% 계산
        status[1] -= mpCost;
        cout << "* 필살기를 사용하여 MP가 50% (" << mpCost << ") 소모되었습니다." << endl;
        cout << "현재 MP: " << status[1] << endl;
    }
    else {
        cout << "* MP가 없어서 필살기를 사용할 수 없습니다." << endl;
    }
}
