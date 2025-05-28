#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>

void sleepMs(int ms) {
    Sleep(ms);
}

void playShalalaEffect() {
    for (int i = 0; i < 5; i++) {
        system("cls");
        for (int j = 0; j < 20; j++) {
            for (int k = 0; k < 80; k++) {
                if (rand() % 15 == 0) printf("*");
                else printf(" ");
            }
            printf("\n");
        }
        sleepMs(100);
    }
    system("cls");
}


void showStartScreen() {
    printf("\n\n");
    printf("          ♡♥♡♥♡♥♡♥♡♥♡♥♡♥♡♥♡♥♡♥♡♥♡♥♡♥♡  \n");
    printf("         ♥♥♥ 미소녀 연애 시뮬레이션 ♥♥♥                  \n");
    printf("   \n");
    printf("          / 그녀에게 고백하기 프로젝트 / \n");
    printf("          ♡♥♡♥♡♥♡♥♡♥♡♥♡♥♡♥♡♥♡♥♡♥♡♥♡♥♡   \n");
    printf("            ~  1: 게임 시작   2: 종료  ~\n");
    printf("\n");
}

int waitForSpacebar() {
    Sleep(500);
    printf("\n\n\n\n\n-스페이스바를 누르세요\n");
    while (1) {
        char ch = getch();
        if (ch == ' ') {
            break;
        }
    }
    return 0;
}

//타이밍 게임
void timingGame(int totalScore) {
    int pos = 0, dir = 1, success = 0;
    const int maxPos = 20;

    system("cls");
    printf("★ 고백 타이밍 게임 ★\n\n");
    printf("하트가 ♥ 에 닿는 순간 스페이스바를 누르세요!\n");
    Sleep(2000);
    printf("준비...\n");
    Sleep(1000);
    printf("시작!\n");
    Sleep(500);

    while (1) {
        system("cls");
        printf("고백 타이밍!\n\n");
        for (int i = 0; i < maxPos; i++) {
            if (i == pos) printf("♥");
            else printf("-");
        }
        printf("\n");

        Sleep(100);

        pos += dir;
        if (pos == 0 || pos == maxPos - 1) dir = -dir;

        if (_kbhit()) {
            char ch = _getch();
            if (ch == ' ') {
                if (pos >= 8 && pos <= 12) success = 1;
                break;
            }
        }
    }

    system("cls");
    if (totalScore >= 80 && success) {
        printf("성공! 그녀가 당신의 고백을 받아들였습니다! ♥♥♥\n");
    }
    else {
        printf("실패... 타이밍을 놓쳤거나 점수가 부족합니다...\n");
    }
    Sleep(3000);
}


void gamemain() {
    int totalScore = 0;

    // 첫 번째 문제
    system("cls");
    printf("  *******************************\n");
    printf("  *   ()            ()            *\n");
    printf("  *   ||            ||            *\n");
    printf("  *  /  \\          /  \\           *\n");
    printf("  *   ||            ||            *\n");
    printf("  *******************************\n\n");
    printf("  앗 그녀다! 빨리 그녀에게 말을 걸어야지 \n\n");

    int correctAnswer = 1;
    printf("+-----------------------------+\n");
    printf("|  1. 왼쪽 그녀               |\n");
    printf("|  2. 오른쪽 그녀             |\n");
    printf("+-----------------------------+\n");
    printf("선택하세요 (1or2): ");

    char choice = getchar();
    while (getchar() != '\n'); // 입력 버퍼 비우기

    int playerChoice = choice - '0';

    if (playerChoice == correctAnswer) {
        totalScore += 20;

        // 두 번째 문제
        system("cls");
        printf("반가워! 오늘 재밌겠다! \n");
        Sleep(1500);

        system("cls");
        Sleep(1000);
        printf("배고프네! 밥 뭐 먹으러 갈래?\n\n");
        printf("마라탕? 떡볶이? 넌 먹고 싶은 음식 있어?\n\n");

        int secondCorrectAnswer = 2;

        printf("+--------------------------------------------+\n");
        printf("|  1. 나는 제육볶음이 먹고 싶어              |\n");
        printf("|  2. 마라탕 괜찮은데? 마라탕 먹으러갈까?    |\n");
        printf("|  3. 흠...네가 골라                         |\n");
        printf("+--------------------------------------------+\n");
        printf("선택하세요 (1~3): ");

        char secondChoice = getchar();
        while (getchar() != '\n');

        int secondPlayerChoice = secondChoice - '0';

        system("cls");
        if (secondPlayerChoice == secondCorrectAnswer) {
            totalScore += 20;
            printf("너무 좋아!! 빨리 밥 머그러 가자\n");
        }
        else {
            printf("난 마라탕 먹을래 ㅋㅋ~\n");
        }
        Sleep(2000);

        // 세번째 문제

        system("cls");
        Sleep(1000);
        printf("         (o_o)              (^-^)\n");
        printf("        /|   |\\            /|   |\\\n");
        printf("        /     \\            /     \\\n");
        printf("       ----------------------------\n");
        printf("       |         식   탁          |\n");
        printf("       ----------------------------\n\n");
        printf("나 뭐 바뀐 거 없어?\n\n");

        int thirdCorrectAnswer = 3;

        printf("+--------------------------------------------+\n");
        printf("|  1.어제보다 오늘 더 예쁜거?                |\n");
        printf("|  2.모르겠는데...                           |\n");
        printf("|  3.앞머리 잘랐구나!                        |\n");
        printf("+--------------------------------------------+\n");
        printf("선택하세요 (1~3): ");

        char thirdChoice = getchar();
        while (getchar() != '\n');

        int thirdPlayerChoice = thirdChoice - '0';

        system("cls");
        if (thirdPlayerChoice == thirdCorrectAnswer) {
            totalScore += 20;
            printf("뭐야~ㅎㅎ 되게 세심하다\n");
        }
        else {
            printf("ㅋㅋㅋㅋㅋㅋㅋ\n");
        }
        Sleep(2000);

        // 네 번째 문제

        system("cls");
        Sleep(1000);
        printf("  _____________________\n");
        printf(" |  _________________  |\n");
        printf(" | |                 | |\n");
        printf(" | |                 | |\n");
        printf(" | |                 | |\n");
        printf(" | |     (연예인)    | |\n");
        printf(" | |                 | |\n");
        printf(" | |                 | |\n");
        printf(" | |                 | |\n");
        printf(" | |_________________| |\n");
        printf(" |  ___ ___ ___ ___ ___|\n");
        printf(" | |  |  |  |  |  |  | |\n");
        printf(" | |__|__|__|__|__|__| |\n");
        printf(" |_____________________|\n");


        printf("아 장원영 진짜 예쁜 것 같아 \n\n");

        int fourthCorrectAnswer = 1;

        printf("+-----------------------------------+\n");
        printf("|  1. 글쎄? 연예인 관심 없어 나     |\n");
        printf("|  2. ㅇㅈㅋㅋ 진짜 개예쁘긴 해     |\n");
        printf("|  3. 장원영보다 네가 더 예뻐       |\n");
        printf("+-----------------------------------+\n");
        printf("선택하세요 (1~3): ");

        char fourthChoice = getchar();
        while (getchar() != '\n');

        int fourthPlayerChoice = fourthChoice - '0';

        system("cls");

        if (fourthPlayerChoice == fourthCorrectAnswer) {
            totalScore += 20;
            printf("진짜? 너 완전 대박이다 ㅎㅎ ");
            Sleep(2000);
        }
        else if (fourthPlayerChoice == 2) {
            printf("ㅋㅋㅋㅋㅋㅋㅋ;;;;;\n");
            Sleep(2000);
        }
        else if (fourthPlayerChoice == 3) {
            printf("..상대는 장원영인데\n");
            Sleep(2000);
        }

        // 다섯번째 문제
        system("cls");
        printf("아 배부르다 나가자!\n\n");
        Sleep(1000);
        printf("메가커피 가서 음료 한 잔 마실까?\n\n");
        Sleep(1000);
        printf("- 좋아!\n\n");
        Sleep(1000);

        system("cls");

        printf("      /\\        /\\      \n");
        printf("     /  \\______/  \\     \n");
        printf("    /     (cafe)    \\    \n");
        printf("   /_________________\\   \n");
        printf("   |   _    _    _   |   \n");
        printf("   |  | |  | |  | |  |   \n");
        printf("   |__|_|__|_|__|_|__|   \n");
        printf("   |                  |  \n");
        printf("   |__________________|  \n");

        printf(" 우와 !! 저 카페 완전 느좋이잖아!! ㅠㅠ\n");

        printf("+--------------------------------------+\n");
        printf("| 1. 저런 곳은 메뉴가 맛없어           |\n");
        printf("| 2. 그러게 ㅋㅋ 다음엔 저기 가자      |\n");
        printf("| 3. 그래? 그럼 메가말고 저기 갈까?    |\n");
        printf("| 4. 개비싸보임ㅋㅋ                    |\n");
        printf("+----------------------------------+\n");
        printf("선택하세요 (1~4): ");

        char fifthChoice = getchar();
        while (getchar() != '\n');
        int fifthPlayerChoice = fifthChoice - '0';

        if (fifthPlayerChoice == 2) {
            totalScore += 10;
            printf("지금 갈래!\n");
            Sleep(2000);
        }
        else if (fifthPlayerChoice == 3) {
            totalScore += 20;
            printf("헉 좋아!! 너 정말 센스 좋다\n");
            Sleep(2000);
        }
        else if (fifthPlayerChoice == 1) {
            system("cls");
            printf("커피가 거기서 거기지. 나 그냥 집갈래\n");
            Sleep(1000);
            printf("그녀가 사라져버렸습니다\n");
            Sleep(3000);
            exit(0);
        }
        else if (fifthPlayerChoice == 4) {
            system("cls");
            printf("내가 메가커피정도의 가치야? 나 갈래\n");
            Sleep(1000);
            printf("그녀가 사라져버렸습니다\n");
            Sleep(3000);
            exit(0);
        }

        // 여섯번째 문제

        system("cls");
        printf("아 음료수 뭐 먹지??\n\n");
        Sleep(1000);
        printf("아아도 먹고 싶고 프라페도 먹고 싶은데..\n\n");

        printf("+-------------------------------------+\n");
        printf("| 1. 난 녹차라떼 먹어야징             |\n");
        printf("| 2. 둘이 시켜서 나눠먹자             |\n");
        printf("| 3. 아아는 어때? 프라페는 내가 먹을게|\n");
        printf("| 4. 아아먹어 프라페는 살 쪄          |\n");
        printf("+-------------------------------------+\n");
        printf("선택하세요 (1~4): ");

        char sixthChoice = getchar();
        while (getchar() != '\n');
        int sixthPlayerChoice = sixthChoice - '0';

        if (sixthPlayerChoice == 2) {
            totalScore += 10;  // 점수 조금 증가
            printf("그래! 프라페는 살찌니까 조금만 먹어야겠다 \n");
            Sleep(2000);
        }
        else if (sixthPlayerChoice == 3) {
            totalScore += 20;  // 점수 많이 증가
            printf("그래! 프라페 딱 한 입만 먹고 싶었어 너꺼 뺏어 먹을래!\n");
            Sleep(2000);
        }
        else if (sixthPlayerChoice == 1) {
            system("cls");
            printf("너 많이 먹어~^^\n");
            Sleep(1000);
            printf("그녀가 사라져버렸습니다\n");
            Sleep(3000);
            exit(0);
        }
        else if (sixthPlayerChoice == 4) {
            system("cls");
            printf("그냥 아무것도 안먹을래. 나 갈게 \n");
            Sleep(1000);
            printf("그녀가 사라져버렸습니다\n");
            Sleep(3000);
            exit(0);
        }

        //엔딩 크레딧
        system("cls");
        printf("\n\n\n");
        printf("그녀를 집에 데려다주며\n");
        Sleep(1500);
        printf("내 마음을 전할거야...\n");
        Sleep(1500);
        printf("지금이 타이밍이다!!\n");
        Sleep(1500);

        timingGame(totalScore);
    }
}


        int main() {
            srand(GetTickCount());
            playShalalaEffect();
            showStartScreen();

            char choice = getchar();
            while (getchar() != '\n');

            if (choice == '1') {
                system("cls");
                printf("오늘은 내가 좋아하는 그녀와의 데이트 날... \n");
                sleepMs(1000);
                printf("반드시 오늘은 그녀의 마음을 얻고 고백을 해야지..!\n");

                waitForSpacebar();

                gamemain();
            }
            else if (choice == '2') {
                system("cls");
                printf("게임을 종료합니다.\n");
                sleepMs(1000);
                return 0;
            }
            else {
                printf("잘못된 입력입니다. 프로그램을 종료합니다.\n");
                sleepMs(1000);
                return 0;
            }
            return 0;

        }
