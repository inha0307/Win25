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
    printf("          ������������������������������������������������������  \n");
    printf("         ������ �̼ҳ� ���� �ùķ��̼� ������                  \n");
    printf("   \n");
    printf("          / �׳࿡�� ����ϱ� ������Ʈ / \n");
    printf("          ������������������������������������������������������   \n");
    printf("            ~  1: ���� ����   2: ����  ~\n");
    printf("\n");
}

int waitForSpacebar() {
    Sleep(500);
    printf("\n\n\n\n\n-�����̽��ٸ� ��������\n");
    while (1) {
        char ch = getch();
        if (ch == ' ') {
            break;
        }
    }
    return 0;
}

//Ÿ�̹� ����
void timingGame(int totalScore) {
    int pos = 0, dir = 1, success = 0;
    const int maxPos = 20;

    system("cls");
    printf("�� ��� Ÿ�̹� ���� ��\n\n");
    printf("��Ʈ�� �� �� ��� ���� �����̽��ٸ� ��������!\n");
    Sleep(2000);
    printf("�غ�...\n");
    Sleep(1000);
    printf("����!\n");
    Sleep(500);

    while (1) {
        system("cls");
        printf("��� Ÿ�̹�!\n\n");
        for (int i = 0; i < maxPos; i++) {
            if (i == pos) printf("��");
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
        printf("����! �׳డ ����� ����� �޾Ƶ鿴���ϴ�! ������\n");
    }
    else {
        printf("����... Ÿ�̹��� ���ưų� ������ �����մϴ�...\n");
    }
    Sleep(3000);
}


void gamemain() {
    int totalScore = 0;

    // ù ��° ����
    system("cls");
    printf("  *******************************\n");
    printf("  *   ()            ()            *\n");
    printf("  *   ||            ||            *\n");
    printf("  *  /  \\          /  \\           *\n");
    printf("  *   ||            ||            *\n");
    printf("  *******************************\n\n");
    printf("  �� �׳��! ���� �׳࿡�� ���� �ɾ���� \n\n");

    int correctAnswer = 1;
    printf("+-----------------------------+\n");
    printf("|  1. ���� �׳�               |\n");
    printf("|  2. ������ �׳�             |\n");
    printf("+-----------------------------+\n");
    printf("�����ϼ��� (1or2): ");

    char choice = getchar();
    while (getchar() != '\n'); // �Է� ���� ����

    int playerChoice = choice - '0';

    if (playerChoice == correctAnswer) {
        totalScore += 20;

        // �� ��° ����
        system("cls");
        printf("�ݰ���! ���� ��հڴ�! \n");
        Sleep(1500);

        system("cls");
        Sleep(1000);
        printf("�������! �� �� ������ ����?\n\n");
        printf("������? ������? �� �԰� ���� ���� �־�?\n\n");

        int secondCorrectAnswer = 2;

        printf("+--------------------------------------------+\n");
        printf("|  1. ���� ���������� �԰� �;�              |\n");
        printf("|  2. ������ ��������? ������ ����������?    |\n");
        printf("|  3. ��...�װ� ���                         |\n");
        printf("+--------------------------------------------+\n");
        printf("�����ϼ��� (1~3): ");

        char secondChoice = getchar();
        while (getchar() != '\n');

        int secondPlayerChoice = secondChoice - '0';

        system("cls");
        if (secondPlayerChoice == secondCorrectAnswer) {
            totalScore += 20;
            printf("�ʹ� ����!! ���� �� �ӱ׷� ����\n");
        }
        else {
            printf("�� ������ ������ ����~\n");
        }
        Sleep(2000);

        // ����° ����

        system("cls");
        Sleep(1000);
        printf("         (o_o)              (^-^)\n");
        printf("        /|   |\\            /|   |\\\n");
        printf("        /     \\            /     \\\n");
        printf("       ----------------------------\n");
        printf("       |         ��   Ź          |\n");
        printf("       ----------------------------\n\n");
        printf("�� �� �ٲ� �� ����?\n\n");

        int thirdCorrectAnswer = 3;

        printf("+--------------------------------------------+\n");
        printf("|  1.�������� ���� �� ���۰�?                |\n");
        printf("|  2.�𸣰ڴµ�...                           |\n");
        printf("|  3.�ոӸ� �߶�����!                        |\n");
        printf("+--------------------------------------------+\n");
        printf("�����ϼ��� (1~3): ");

        char thirdChoice = getchar();
        while (getchar() != '\n');

        int thirdPlayerChoice = thirdChoice - '0';

        system("cls");
        if (thirdPlayerChoice == thirdCorrectAnswer) {
            totalScore += 20;
            printf("����~���� �ǰ� �����ϴ�\n");
        }
        else {
            printf("��������������\n");
        }
        Sleep(2000);

        // �� ��° ����

        system("cls");
        Sleep(1000);
        printf("  _____________________\n");
        printf(" |  _________________  |\n");
        printf(" | |                 | |\n");
        printf(" | |                 | |\n");
        printf(" | |                 | |\n");
        printf(" | |     (������)    | |\n");
        printf(" | |                 | |\n");
        printf(" | |                 | |\n");
        printf(" | |                 | |\n");
        printf(" | |_________________| |\n");
        printf(" |  ___ ___ ___ ___ ___|\n");
        printf(" | |  |  |  |  |  |  | |\n");
        printf(" | |__|__|__|__|__|__| |\n");
        printf(" |_____________________|\n");


        printf("�� ����� ��¥ ���� �� ���� \n\n");

        int fourthCorrectAnswer = 1;

        printf("+-----------------------------------+\n");
        printf("|  1. �۽�? ������ ���� ���� ��     |\n");
        printf("|  2. �������� ��¥ �����ڱ� ��     |\n");
        printf("|  3. ��������� �װ� �� ����       |\n");
        printf("+-----------------------------------+\n");
        printf("�����ϼ��� (1~3): ");

        char fourthChoice = getchar();
        while (getchar() != '\n');

        int fourthPlayerChoice = fourthChoice - '0';

        system("cls");

        if (fourthPlayerChoice == fourthCorrectAnswer) {
            totalScore += 20;
            printf("��¥? �� ���� ����̴� ���� ");
            Sleep(2000);
        }
        else if (fourthPlayerChoice == 2) {
            printf("��������������;;;;;\n");
            Sleep(2000);
        }
        else if (fourthPlayerChoice == 3) {
            printf("..���� ������ε�\n");
            Sleep(2000);
        }

        // �ټ���° ����
        system("cls");
        printf("�� ��θ��� ������!\n\n");
        Sleep(1000);
        printf("�ް�Ŀ�� ���� ���� �� �� ���Ǳ�?\n\n");
        Sleep(1000);
        printf("- ����!\n\n");
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

        printf(" ��� !! �� ī�� ���� �������ݾ�!! �Ф�\n");

        printf("+--------------------------------------+\n");
        printf("| 1. ���� ���� �޴��� ������           |\n");
        printf("| 2. �׷��� ���� ������ ���� ����      |\n");
        printf("| 3. �׷�? �׷� �ް����� ���� ����?    |\n");
        printf("| 4. ����κ��Ӥ���                    |\n");
        printf("+----------------------------------+\n");
        printf("�����ϼ��� (1~4): ");

        char fifthChoice = getchar();
        while (getchar() != '\n');
        int fifthPlayerChoice = fifthChoice - '0';

        if (fifthPlayerChoice == 2) {
            totalScore += 10;
            printf("���� ����!\n");
            Sleep(2000);
        }
        else if (fifthPlayerChoice == 3) {
            totalScore += 20;
            printf("�� ����!! �� ���� ���� ����\n");
            Sleep(2000);
        }
        else if (fifthPlayerChoice == 1) {
            system("cls");
            printf("Ŀ�ǰ� �ű⼭ �ű���. �� �׳� ������\n");
            Sleep(1000);
            printf("�׳డ ��������Ƚ��ϴ�\n");
            Sleep(3000);
            exit(0);
        }
        else if (fifthPlayerChoice == 4) {
            system("cls");
            printf("���� �ް�Ŀ�������� ��ġ��? �� ����\n");
            Sleep(1000);
            printf("�׳డ ��������Ƚ��ϴ�\n");
            Sleep(3000);
            exit(0);
        }

        // ������° ����

        system("cls");
        printf("�� ����� �� ����??\n\n");
        Sleep(1000);
        printf("�ƾƵ� �԰� �Ͱ� �����䵵 �԰� ������..\n\n");

        printf("+-------------------------------------+\n");
        printf("| 1. �� ������ �Ծ��¡             |\n");
        printf("| 2. ���� ���Ѽ� ��������             |\n");
        printf("| 3. �ƾƴ� �? ������� ���� ������|\n");
        printf("| 4. �ƾƸԾ� ������� �� ��          |\n");
        printf("+-------------------------------------+\n");
        printf("�����ϼ��� (1~4): ");

        char sixthChoice = getchar();
        while (getchar() != '\n');
        int sixthPlayerChoice = sixthChoice - '0';

        if (sixthPlayerChoice == 2) {
            totalScore += 10;  // ���� ���� ����
            printf("�׷�! ������� ����ϱ� ���ݸ� �Ծ�߰ڴ� \n");
            Sleep(2000);
        }
        else if (sixthPlayerChoice == 3) {
            totalScore += 20;  // ���� ���� ����
            printf("�׷�! ������ �� �� �Ը� �԰� �;��� �ʲ� ���� ������!\n");
            Sleep(2000);
        }
        else if (sixthPlayerChoice == 1) {
            system("cls");
            printf("�� ���� �Ծ�~^^\n");
            Sleep(1000);
            printf("�׳డ ��������Ƚ��ϴ�\n");
            Sleep(3000);
            exit(0);
        }
        else if (sixthPlayerChoice == 4) {
            system("cls");
            printf("�׳� �ƹ��͵� �ȸ�����. �� ���� \n");
            Sleep(1000);
            printf("�׳డ ��������Ƚ��ϴ�\n");
            Sleep(3000);
            exit(0);
        }

        //���� ũ����
        system("cls");
        printf("\n\n\n");
        printf("�׳ฦ ���� �������ָ�\n");
        Sleep(1500);
        printf("�� ������ ���Ұž�...\n");
        Sleep(1500);
        printf("������ Ÿ�̹��̴�!!\n");
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
                printf("������ ���� �����ϴ� �׳���� ����Ʈ ��... \n");
                sleepMs(1000);
                printf("�ݵ�� ������ �׳��� ������ ��� ����� �ؾ���..!\n");

                waitForSpacebar();

                gamemain();
            }
            else if (choice == '2') {
                system("cls");
                printf("������ �����մϴ�.\n");
                sleepMs(1000);
                return 0;
            }
            else {
                printf("�߸��� �Է��Դϴ�. ���α׷��� �����մϴ�.\n");
                sleepMs(1000);
                return 0;
            }
            return 0;

        }
