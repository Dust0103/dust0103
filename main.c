/*
     1.�������
     2.ģ�黯���
     3.ʵ�ֹ���
  */

#include <Windows.h> //������õ�API
#include <conio.h>   //�������
#include <stdio.h>
#include <stdlib.h>
#include <time.h> //ʳ�����

/////////////////�������////////////////////////
////////////�ߵĽṹ��///////////////
struct
{
    int speed;
    int length;
    int x[100]; //��������ÿһ��С������x������
    int y[100]; //��������ÿһ��С������y������

} Snake;

///////////ʳ��Ľṹ��/////////////////////
struct
{
    //���ȥ��λ������
    int x;
    int y;
} food;

/////////////ȫ�ֱ���////////////////
void KeyDown();     //KeyDown�������������ߵ��ƶ�
void CreateFood();  //CreatFood������������ʳ��
int ChangeFlag = 0; //�����ж����Ƿ�Ե�ʳ��
int key = 72;       //�����ж��ߵ��ƶ�����72�����¡��������������
int score = 0;      //������Ϸ����
int highScore = 0;  //������Ϸ����߷�
int SnakeStatus();

/////////////�����ն�������ɫ///////////////////
int setColor(int c)
{
    //GetStdHandle: ��ȡָ���ı�׼�豸�ľ��
    //STD_OUTPUT_HANDLE ��׼������
    //c ��ɫֵ
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
    return 0;
}

/////////////////��������������ƶ�///////////////////////////
int gotoXY(int x, int y)
{
    //1.�ҵ�����̨���������
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    //2.���Ľṹ��
    COORD coord; //��Ź�����Ϣ
                 //3.��������
    coord.X = x;
    coord.Y = y;
    //4.ͬ��������̨Set Console Cursor Position(���ÿ���̨���λ��)
    SetConsoleCursorPosition(handle, coord);
    return 0;
}

///////////////����һ��///////////////////////////
int printSnake(void) //�����ַ���
{
    system("cls"); //����system��������

    gotoXY(35, 1);
    setColor(6);
    printf("/^\\/^\\"); //üë

    gotoXY(34, 2);
    printf("|_0|  O|"); //�۾�

    gotoXY(33, 2);
    setColor(2);
    printf("_");

    gotoXY(25, 3);
    setColor(12);
    printf("\\/"); //����

    gotoXY(31, 3);
    setColor(2);
    printf("/");

    gotoXY(37, 3);
    setColor(6);
    printf(" \\_/"); //���۾�

    gotoXY(41, 3);
    setColor(10);
    printf(" \\");

    gotoXY(26, 4);
    setColor(12);
    printf("\\____"); //��ͷ

    gotoXY(32, 4);
    printf("_________/");

    gotoXY(31, 4);
    setColor(2);
    printf("|");

    gotoXY(43, 4);
    setColor(10);
    printf("\\");

    gotoXY(32, 5);
    setColor(2);
    printf("\\_______"); //�첿

    gotoXY(44, 5);
    setColor(10);
    printf("\\");

    gotoXY(39, 6);
    printf("|     |                  \\"); //����

    gotoXY(38, 7);
    printf("/      /                   \\");

    gotoXY(37, 8);
    printf("/      /                    \\ \\");

    gotoXY(35, 9);
    printf("/      /                       \\ \\");

    gotoXY(34, 10);
    printf("/     /                           \\  \\");

    gotoXY(33, 11);
    printf("/     /             _----_           \\  \\");

    gotoXY(32, 12);
    printf("/     /           _-~      ~-_         |  |");

    gotoXY(31, 13);
    printf("(      (        _-~    _--_    ~-_     _/  |");

    gotoXY(32, 14);
    printf("\\     ~-____-~    _-~    ~-_    ~-_-~    /");

    gotoXY(33, 15);
    printf("~-_           _-~          ~-_       _-~");

    gotoXY(35, 16);
    printf("~--______-~                ~-___-~");

    return 0;
}

///////////////////����һ��///////////////////////////////
int WelcomeGame(void)
{
    int i;
    int n = 0;
    printSnake(); //��ӡ�ַ���

    setColor(11);
    gotoXY(50, 17);
    printf("̰����");

    //��ӡ�߿򣬱߿�42����10
    setColor(14);
    gotoXY(31, 18);
    printf("������������������������������������������������������������������������������������");
    gotoXY(31, 19);
    for (i = 19; i <= 23; i++)
    {
        gotoXY(31, i);
        printf("��");
        gotoXY(72, i);
        printf("��");
    }
    gotoXY(31, 24);
    printf("������������������������������������������������������������������������������������");
    setColor(12);
    gotoXY(36, 20);
    printf("1. ��ʼ��Ϸ");
    gotoXY(56, 20);
    printf("2. ��Ϸ˵��");
    gotoXY(36, 22);
    printf("3. �˳���Ϸ");
    gotoXY(85, 24);
    setColor(12);
    printf("\n  \n                                  ��������Чѡ��[1-3]�� ");
    setColor(13);
    scanf("%d", &n);
    getchar();
    return n;
}

/////////////ѡ��2��Ϸ˵��//////////////////////////////
int GameShows(void)
{
    int i, j;
    system("cls"); //����system��������
    setColor(13);
    gotoXY(47, 2);
    printf("��Ϸ˵��");
    setColor(13);
    gotoXY(20, 4);
    for (i = 1; i <= 62; i++) //�����ϱ߿򣬳�62
        printf("=");
    gotoXY(20, 24);
    for (i = 1; i <= 62; i++) //�����±߿򣬳�62
        printf("=");
    for (j = 5; j <= 23; j++) //�������ұ߿򣬸�18
    {
        gotoXY(20, j);
        printf("��");
        gotoXY(80, j);
        printf("��");
    }
    gotoXY(23, 7);
    setColor(6);
    printf("��");
    setColor(11);
    printf("��Ϸ�Ĵ��ڲ˵�������˲˵���,����ѡ��ʼ��Ϸ,�˽�");
    gotoXY(23, 9);
    printf("��Ϸ����");

    gotoXY(23, 12);
    setColor(6);
    printf("��");
    setColor(12);
    printf("����һ��Ƚ���Ҫ���ĵ���Ϸ�����������ҿ����ߵķ���Ѱ");
    gotoXY(23, 14);
    printf("��ʳ�ÿ�Ե�һ��ʳ����ܵõ�һ���Ļ��֣�������Ӧ������");
    gotoXY(23, 16);
    printf("��Ϸ�����������ǡ����� ��");

    gotoXY(23, 19);
    setColor(6);
    printf("��");
    setColor(14);
    printf("����Ϸ������ҷ���һ����ʾ��ǰ�ĵ÷�����������������");
    gotoXY(23, 21);
    printf("���Լ��ĵ÷�");
    setColor(12);
    gotoXY(20, 26);
    printf("���»س�������������...");
    getchar();
    return 0;
}

///////////��Ϸ��������//////////////////////////
int GameMap(void)
{
    int i, j;
    system("cls"); //����system��������
    setColor(11);
    gotoXY(70, 0); //�����Ʒֿ򣬳�26
    printf("��");
    for (i = 1; i <= 26; i++)
        printf("��");
    printf("��");
    gotoXY(70, 12);
    printf("��");
    for (i = 1; i <= 26; i++)
        printf("��");
    printf("��");
    for (j = 1; j <= 11; j++) //�����Ʒֿ򣬸�11
    {
        gotoXY(70, j);
        printf("��");
        gotoXY(97, j);
        printf("��");
    }

    ////////////////��Ϸ��������/////////////////////
    gotoXY(77, 14);
    setColor(12);
    printf("�����ܰ��ʾ���");
    gotoXY(71, 16);
    setColor(11);
    for (i = 1; i <= 27; i++)
        printf("=");
    gotoXY(71, 28);
    for (i = 1; i <= 27; i++)
        printf("=");

    gotoXY(71, 18);
    setColor(6);
    printf("��");
    setColor(13);
    printf("�Ե�ÿ��ʳ��÷֣�5");

    gotoXY(71, 20);
    setColor(6);
    printf("��");
    setColor(13);
    printf("����ײ��ǽ������ҧ���Լ�");

    gotoXY(71, 22);
    setColor(6);
    printf("��");
    setColor(13);
    printf("ʹ�ÿո����ͣ�������Ϸ");

    gotoXY(71, 24);
    setColor(6);
    printf("��");
    setColor(13);
    printf("ʹ�á�����������ǰ���ķ���");

    gotoXY(71, 26);
    setColor(6);
    printf("��");
    setColor(13);
    printf("����ESC��������Ϸ");

    gotoXY(73, 2);
    setColor(6);
    printf("�����߷ּ�¼��");
    gotoXY(81, 5);
    setColor(30);
    printf("500");

    gotoXY(73, 8);
    setColor(6);
    printf("��ǰ�÷֣�");
    gotoXY(83, 8);
    setColor(32);
    printf("0");

    ////////////////////ģ�黯���/////////////////
    //////���ܵĻ��֡���>���󵽺���/////////////

    //////////////////����Ϸ��///////////////////
    /////////////1.������ͼ////////////////////
    setColor(11);
    gotoXY(0, 0);
    printf("��"); //����̰���߻��Χ
    for (i = 1; i <= 65; i++)
        printf("��");
    printf("��");
    gotoXY(0, 29);
    printf("��");
    for (i = 1; i <= 65; i++)
        printf("��");
    printf("��");
    for (j = 1; j <= 28; j++) //�������һ��Χ����65����27
    {
        gotoXY(0, j);
        printf("��");
        gotoXY(66, j);
        printf("��");
    }
    while (1) //������ɳ�ʼʳ��
    {
        srand((unsigned int)time(NULL));
        food.x = rand() % (65 - 4) + 2;
        food.y = rand() % (27 - 2) + 1;
        /*
        ���ɵ�ʳ����������ż����ͳ���ʱ��ͷ�����������żһ�£���Ϊһ��ʳ��ռ�����ֽ�λ�ã�����һ��
        �ᵼ�³�ʳ���ʱ��ֻ�Ե�һ��
        */
        if (food.x % 2 == 0)
            break;
    }

    setColor(12);
    gotoXY(food.x, food.y); //������Ƶ�ʳ��������ӡʳ��
    printf("��");

    Snake.length = 3; //��ʼ���ߵ�����
    Snake.speed = 300;

    Snake.x[0] = 66 / 2 + 1; //�ڵ�ͼ�м�������ͷ��x����Ϊż��
    Snake.y[0] = 27 / 2;

    setColor(10);
    gotoXY(Snake.x[0], Snake.y[0]); //��ӡ��ͷ
    printf("��");
    for (i = 1; i < Snake.length; i++) //���ɳ�ʼ������
    {
        Snake.x[i] = Snake.x[i - 1]; //��ӡ���������겻�䣬������Ϊ��һ�����������ֵ
        Snake.y[i] = Snake.y[i - 1];
        gotoXY(Snake.x[i], Snake.y[i]);
        printf("��");
    }
    gotoXY(100, 0); //������ƶ��������ط�������Ӱ����Ϸ����
    return 0;
}

///////////////////////2.����ʳ��///////////////////////////////
void CreateFood()
{

    if (Snake.x[0] == food.x && Snake.y[0] == food.y) //��ͷ����ʳ��
    {
        while (1) //���Ѿ��Ե�ʳ�������һ��ʳ��
        {
            int Flag = 1;
            srand((unsigned int)time(NULL));
            food.x = rand() % (65 - 4) + 2;
            food.y = rand() % (27 - 2) + 1;

            for (int i = 0; i < Snake.length; i++) //ʳ�ﲻ���������ߵ�������
            {
                if (Snake.x[i] == food.x && Snake.y[i] == food.y)
                {
                    Flag = 0;
                    break;
                }
            }
            if (Flag && food.x % 2 == 0) //������ɵ�ʳ�ﲻ�ܺ�����Ϊ������Ҳ����������������������
                break;
        }
        gotoXY(food.x, food.y);
        setColor(12);
        printf("��");
        gotoXY(100, 0);
        Snake.length = Snake.length + 1; //�Ե�ʳ������ȼ�1
        score = score + 5;               //ÿ�Ե�һ��ʳ���5��
        ChangeFlag = 1;                  //�Ե�ʳ��Ͳ����ٲ�����β��һ�ڣ��Դ������������������Ч��
        gotoXY(83, 8);
        setColor(32);
        printf("%d", score); //�����ǰ�÷�
    }
}

///////////////////3.������������ʳ��///////////////////////////
void KeyDown()
{
    int i;
    int pre_key = key; //��¼ǰһ�������ķ���
    if (_kbhit())      //��������˼����е�ĳ����
    {
        fflush(stdin);  //��ջ��������ַ�
                        //getch()��ȡ�������ʱ�򣬻᷵�����Σ���һ�ε��÷���0����224���ڶ��ε��÷��صĲ���ʵ��ֵ
        key = _getch(); //��һ�ε��÷��صĲ���ʵ��ֵ
        key = _getch();
    }
    /*
        ���ƶ�ʱ���Ȳ�ȥ��β��һ��
        ChangeFlagΪ0������ʱû�гԵ�ʳ����ÿ��һ����Ҫ��������β���Դ�Ӫ��һ���ƶ���Ч��
        ChangeFlagΪ1�����Ե���ʳ��Ͳ���Ҫ������β����Ӫ��һ������������Ч��
   */
    if (ChangeFlag == 0)
    {
        gotoXY(Snake.x[Snake.length - 1], Snake.y[Snake.length - 1]);
        printf("  "); //����β������ո񼴲�ȥ��β
    }
    for (i = Snake.length - 1; i > 0; i--) //����ͷ�⣬���ߵ�ÿһ��������ǰ�ƶ�һ��
    {
        Snake.x[i] = Snake.x[i - 1];
        Snake.y[i] = Snake.y[i - 1];
    }
    //�߲��ܻ�ͷ
    //�����ǰ�ƶ������ǰһ�η����෴�Ļ����ѵ�ǰ�ƶ��ķ����Ϊǰһ�εķ���
    if (pre_key == 72 && key == 80) //����̨��������������֣�������72 ������80 ������75 ������77
        key = 72;
    if (pre_key == 80 && key == 72)
        key = 80;
    if (pre_key == 75 && key == 77)
        key = 75;
    if (pre_key == 77 && key == 75)
        key = 77;
    switch (key) //�ж���ͷ���ĸ������ƶ�
    {
    case 75:
        Snake.x[0] = Snake.x[0] - 2; //����
        break;
    case 77:
        Snake.x[0] = Snake.x[0] + 2; //����
        break;
    case 72:
        Snake.y[0] = Snake.y[0] - 1; //����
        break;
    case 80:
        Snake.y[0] = Snake.y[0] + 1; //����
        break;
    }
    setColor(10);
    gotoXY(Snake.x[0], Snake.y[0]); //��ӡ��ͷ
    printf("��");
    gotoXY(66 - 2, 0);
    ChangeFlag = 0; //����Ŀǰû�гԵ�ʳ�ChangFlag��ֵΪ0

    if (GetAsyncKeyState(VK_ESCAPE)) //�������ESC����������Ϸ
    {
        exit(0);
    }
}

int StartGame(void)
{
    GameMap();
    CreateFood();
    return 0;
}

//////////�ж��ߵ�״̬����Ϸ�Ƿ����/////////////////////////
int SnakeStatus()
{
    int i;
    if (Snake.y[0] == 0 || Snake.y[0] == 29) //��ͷ�������±߽磬��Ϸ����
        return 0;

    if (Snake.x[0] == 0 || Snake.x[0] == 66) //��ͷ�������ұ߽磬��Ϸ����
        return 0;

    for (i = 1; i < Snake.length; i++) //��ͷ����������Ϸ����
    {
        if (Snake.x[i] == Snake.x[0] && Snake.y[i] == Snake.y[0])
            return 0;
    }
    return 1;
}

/////////////��Ϸʧ�ܱ߿�////////////////////
int FailGame(void)
{
    int i;
    system("cls"); //����system��������

    setColor(12);
    gotoXY(46, 3);
    printf("�� Ϸ ʧ ��!!!");

    setColor(11);
    gotoXY(17, 5);

    printf("��"); //�����ϱ߿�
    for (i = 1; i <= 68; i++)
        printf("-");
    printf("��");

    gotoXY(17, 20); //�����±߿�
    printf("��");
    for (i = 1; i <= 68; i++)
        printf("-");
    printf("��");

    for (i = 6; i < 20; i++) //�������ұ߿�
    {
        gotoXY(17, i);
        printf("��");

        gotoXY(86, i);
        printf("��");
    }
    return 0;
}

///////////////////////��Ϸʧ�ܽ���/////////////////////////////
int EndGame(void)
{
    FailGame(); //��ʾ��Ϸʧ�ܱ߿�
    setColor(12);
    gotoXY(47, 9); //��ʾ�÷�
    setColor(13);
    printf("���ĵ÷�: %d", score);

    if (score < 500)
    {
        setColor(30);
        gotoXY(40, 12);
        printf("����Ŷ������߷ֻ���%d��", 500 - score);
    }

    setColor(10);
    gotoXY(38, 16);
    printf("��Ҫ���٣���һ�εĵ÷ֻ���ߣ�");

    return 0;
}

///////////////////ʵ�ֹ���////////////////////////////
int main()
{
    int Choose;
    system("mode con cols=100 lines=60"); //���ÿ���̨�Ĵ�С
    while (1)
    {
        Choose = WelcomeGame();
        switch (Choose) //�ж�������ѡ��
        {
        case 1:
            break;
        case 2:
            GameShows();
            break;
        case 3:
            exit(0);
            break;
        }
        if (Choose == 1)
            break;
    }
    GameMap();
    while (1)
    {
        KeyDown();
        if (!SnakeStatus())
            break;
        CreateFood();
        Sleep(Snake.speed);
    }
    EndGame();
    gotoXY(70, 28);
    setColor(15);
    system("pause");
    return 0;
}
