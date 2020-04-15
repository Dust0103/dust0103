/*
     1.数据设计
     2.模块化设计
     3.实现过程
  */

#include <Windows.h> //光标设置的API
#include <conio.h>   //按键监控
#include <stdio.h>
#include <stdlib.h>
#include <time.h> //食物随机

/////////////////数据设计////////////////////////
////////////蛇的结构体///////////////
struct
{
    int speed;
    int length;
    int x[100]; //组成蛇身的每一个小方块中x的坐标
    int y[100]; //组成蛇身的每一个小方块中y的坐标

} Snake;

///////////食物的结构体/////////////////////
struct
{
    //如何去定位：坐标
    int x;
    int y;
} food;

/////////////全局变量////////////////
void KeyDown();     //KeyDown函数用来控制蛇的移动
void CreateFood();  //CreatFood函数用来生成食物
int ChangeFlag = 0; //用来判断蛇是否吃到食物
int key = 72;       //用来判断蛇的移动方向，72代表按下“↑”代表的数字
int score = 0;      //定义游戏分数
int highScore = 0;  //定义游戏的最高分
int SnakeStatus();

/////////////设置终端字体颜色///////////////////
int setColor(int c)
{
    //GetStdHandle: 获取指定的标准设备的句柄
    //STD_OUTPUT_HANDLE 标准输出句柄
    //c 颜色值
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
    return 0;
}

/////////////////辅助函数：光标移动///////////////////////////
int gotoXY(int x, int y)
{
    //1.找到控制台的这个窗口
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    //2.光标的结构体
    COORD coord; //存放光标的信息
                 //3.设置坐标
    coord.X = x;
    coord.Y = y;
    //4.同步到控制台Set Console Cursor Position(设置控制台光标位置)
    SetConsoleCursorPosition(handle, coord);
    return 0;
}

///////////////界面一上///////////////////////////
int printSnake(void) //绘制字符蛇
{
    system("cls"); //利用system函数清屏

    gotoXY(35, 1);
    setColor(6);
    printf("/^\\/^\\"); //眉毛

    gotoXY(34, 2);
    printf("|_0|  O|"); //眼睛

    gotoXY(33, 2);
    setColor(2);
    printf("_");

    gotoXY(25, 3);
    setColor(12);
    printf("\\/"); //蛇信

    gotoXY(31, 3);
    setColor(2);
    printf("/");

    gotoXY(37, 3);
    setColor(6);
    printf(" \\_/"); //蛇眼睛

    gotoXY(41, 3);
    setColor(10);
    printf(" \\");

    gotoXY(26, 4);
    setColor(12);
    printf("\\____"); //舌头

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
    printf("\\_______"); //嘴部

    gotoXY(44, 5);
    setColor(10);
    printf("\\");

    gotoXY(39, 6);
    printf("|     |                  \\"); //蛇身

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

///////////////////界面一下///////////////////////////////
int WelcomeGame(void)
{
    int i;
    int n = 0;
    printSnake(); //打印字符蛇

    setColor(11);
    gotoXY(50, 17);
    printf("贪吃蛇");

    //打印边框，边框长42，宽10
    setColor(14);
    gotoXY(31, 18);
    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
    gotoXY(31, 19);
    for (i = 19; i <= 23; i++)
    {
        gotoXY(31, i);
        printf("┃");
        gotoXY(72, i);
        printf("┃");
    }
    gotoXY(31, 24);
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
    setColor(12);
    gotoXY(36, 20);
    printf("1. 开始游戏");
    gotoXY(56, 20);
    printf("2. 游戏说明");
    gotoXY(36, 22);
    printf("3. 退出游戏");
    gotoXY(85, 24);
    setColor(12);
    printf("\n  \n                                  请做出有效选择[1-3]： ");
    setColor(13);
    scanf("%d", &n);
    getchar();
    return n;
}

/////////////选择2游戏说明//////////////////////////////
int GameShows(void)
{
    int i, j;
    system("cls"); //利用system函数清屏
    setColor(13);
    gotoXY(47, 2);
    printf("游戏说明");
    setColor(13);
    gotoXY(20, 4);
    for (i = 1; i <= 62; i++) //画出上边框，长62
        printf("=");
    gotoXY(20, 24);
    for (i = 1; i <= 62; i++) //画出下边框，长62
        printf("=");
    for (j = 5; j <= 23; j++) //画出左右边框，高18
    {
        gotoXY(20, j);
        printf("┃");
        gotoXY(80, j);
        printf("┃");
    }
    gotoXY(23, 7);
    setColor(6);
    printf("☆");
    setColor(11);
    printf("游戏的窗口菜单简单设计了菜单项,方便选择开始游戏,了解");
    gotoXY(23, 9);
    printf("游戏规则");

    gotoXY(23, 12);
    setColor(6);
    printf("☆");
    setColor(12);
    printf("这是一款比较需要耐心的游戏，用上下左右控制蛇的方向，寻");
    gotoXY(23, 14);
    printf("找食物，每吃掉一个食物就能得到一定的积分，蛇身相应增长。");
    gotoXY(23, 16);
    printf("游戏的主操作键是↓↑← →");

    gotoXY(23, 19);
    setColor(6);
    printf("☆");
    setColor(14);
    printf("在游戏界面的右方有一个显示当前的得分情况，方便玩家来了");
    gotoXY(23, 21);
    printf("解自己的得分");
    setColor(12);
    gotoXY(20, 26);
    printf("按下回车键返回主界面...");
    getchar();
    return 0;
}

///////////游戏界面右上//////////////////////////
int GameMap(void)
{
    int i, j;
    system("cls"); //利用system函数清屏
    setColor(11);
    gotoXY(70, 0); //画出计分框，长26
    printf("┏");
    for (i = 1; i <= 26; i++)
        printf("━");
    printf("┓");
    gotoXY(70, 12);
    printf("┗");
    for (i = 1; i <= 26; i++)
        printf("━");
    printf("┛");
    for (j = 1; j <= 11; j++) //画出计分框，高11
    {
        gotoXY(70, j);
        printf("┃");
        gotoXY(97, j);
        printf("┃");
    }

    ////////////////游戏界面右下/////////////////////
    gotoXY(77, 14);
    setColor(12);
    printf("☆☆温馨提示☆☆");
    gotoXY(71, 16);
    setColor(11);
    for (i = 1; i <= 27; i++)
        printf("=");
    gotoXY(71, 28);
    for (i = 1; i <= 27; i++)
        printf("=");

    gotoXY(71, 18);
    setColor(6);
    printf("☆");
    setColor(13);
    printf("吃掉每个食物得分：5");

    gotoXY(71, 20);
    setColor(6);
    printf("☆");
    setColor(13);
    printf("不能撞到墙，不能咬到自己");

    gotoXY(71, 22);
    setColor(6);
    printf("☆");
    setColor(13);
    printf("使用空格键暂停或继续游戏");

    gotoXY(71, 24);
    setColor(6);
    printf("☆");
    setColor(13);
    printf("使用↑↓←→控制前进的方向");

    gotoXY(71, 26);
    setColor(6);
    printf("☆");
    setColor(13);
    printf("按下ESC键结束游戏");

    gotoXY(73, 2);
    setColor(6);
    printf("☆☆最高分纪录☆☆：");
    gotoXY(81, 5);
    setColor(30);
    printf("500");

    gotoXY(73, 8);
    setColor(6);
    printf("当前得分：");
    gotoXY(83, 8);
    setColor(32);
    printf("0");

    ////////////////////模块化设计/////////////////
    //////功能的划分——>抽象到函数/////////////

    //////////////////主游戏区///////////////////
    /////////////1.创建地图////////////////////
    setColor(11);
    gotoXY(0, 0);
    printf("┏"); //制作贪吃蛇活动范围
    for (i = 1; i <= 65; i++)
        printf("━");
    printf("┓");
    gotoXY(0, 29);
    printf("┗");
    for (i = 1; i <= 65; i++)
        printf("━");
    printf("┛");
    for (j = 1; j <= 28; j++) //画出左右活动范围，长65，高27
    {
        gotoXY(0, j);
        printf("┃");
        gotoXY(66, j);
        printf("┃");
    }
    while (1) //随机生成初始食物
    {
        srand((unsigned int)time(NULL));
        food.x = rand() % (65 - 4) + 2;
        food.y = rand() % (27 - 2) + 1;
        /*
        生成的食物横坐标的奇偶必须和初试时蛇头所在坐标的奇偶一致，因为一个食物占两个字节位置，若不一致
        会导致吃食物的时候只吃到一半
        */
        if (food.x % 2 == 0)
            break;
    }

    setColor(12);
    gotoXY(food.x, food.y); //将光标移到食物的坐标打印食物
    printf("●");

    Snake.length = 3; //初始化蛇的属性
    Snake.speed = 300;

    Snake.x[0] = 66 / 2 + 1; //在地图中间生成蛇头，x坐标为偶数
    Snake.y[0] = 27 / 2;

    setColor(10);
    gotoXY(Snake.x[0], Snake.y[0]); //打印蛇头
    printf("■");
    for (i = 1; i < Snake.length; i++) //生成初始的蛇身
    {
        Snake.x[i] = Snake.x[i - 1]; //打印蛇身，纵坐标不变，横坐标为上一节蛇身的坐标值
        Snake.y[i] = Snake.y[i - 1];
        gotoXY(Snake.x[i], Snake.y[i]);
        printf("■");
    }
    gotoXY(100, 0); //将光标移动到其它地方，避免影响游戏体验
    return 0;
}

///////////////////////2.创建食物///////////////////////////////
void CreateFood()
{

    if (Snake.x[0] == food.x && Snake.y[0] == food.y) //蛇头碰到食物
    {
        while (1) //蛇已经吃到食物，再生成一个食物
        {
            int Flag = 1;
            srand((unsigned int)time(NULL));
            food.x = rand() % (65 - 4) + 2;
            food.y = rand() % (27 - 2) + 1;

            for (int i = 0; i < Snake.length; i++) //食物不能生成在蛇的身体上
            {
                if (Snake.x[i] == food.x && Snake.y[i] == food.y)
                {
                    Flag = 0;
                    break;
                }
            }
            if (Flag && food.x % 2 == 0) //随机生成的食物不能横坐标为奇数，也不能在蛇身，否则重新生成
                break;
        }
        gotoXY(food.x, food.y);
        setColor(12);
        printf("●");
        gotoXY(100, 0);
        Snake.length = Snake.length + 1; //吃到食物，蛇身长度加1
        score = score + 5;               //每吃到一个食物加5分
        ChangeFlag = 1;                  //吃到食物，就不用再擦除蛇尾那一节，以此来造成蛇身体增长的效果
        gotoXY(83, 8);
        setColor(32);
        printf("%d", score); //输出当前得分
    }
}

///////////////////3.按键操作：吃食物///////////////////////////
void KeyDown()
{
    int i;
    int pre_key = key; //记录前一个按键的方向
    if (_kbhit())      //如果按下了键盘中的某个键
    {
        fflush(stdin);  //清空缓冲区的字符
                        //getch()读取方向键的时候，会返回两次，第一次调用返回0或者224，第二次调用返回的才是实际值
        key = _getch(); //第一次调用返回的不是实际值
        key = _getch();
    }
    /*
        蛇移动时候先擦去蛇尾的一节
        ChangeFlag为0表明此时没有吃到食物，因此每走一步就要擦除掉蛇尾，以此营造一个移动的效果
        ChangeFlag为1表明吃到了食物，就不需要擦除蛇尾，以营造一个蛇身增长的效果
   */
    if (ChangeFlag == 0)
    {
        gotoXY(Snake.x[Snake.length - 1], Snake.y[Snake.length - 1]);
        printf("  "); //在蛇尾处输出空格即擦去蛇尾
    }
    for (i = Snake.length - 1; i > 0; i--) //除蛇头外，将蛇的每一节依次向前移动一节
    {
        Snake.x[i] = Snake.x[i - 1];
        Snake.y[i] = Snake.y[i - 1];
    }
    //蛇不能回头
    //如果当前移动方向和前一次方向相反的话，把当前移动的方向改为前一次的方向
    if (pre_key == 72 && key == 80) //控制台按键所代表的数字，“↑”72 “↓”80 “←”75 “→”77
        key = 72;
    if (pre_key == 80 && key == 72)
        key = 80;
    if (pre_key == 75 && key == 77)
        key = 75;
    if (pre_key == 77 && key == 75)
        key = 77;
    switch (key) //判断蛇头往哪个方向移动
    {
    case 75:
        Snake.x[0] = Snake.x[0] - 2; //向左
        break;
    case 77:
        Snake.x[0] = Snake.x[0] + 2; //向右
        break;
    case 72:
        Snake.y[0] = Snake.y[0] - 1; //向上
        break;
    case 80:
        Snake.y[0] = Snake.y[0] + 1; //向下
        break;
    }
    setColor(10);
    gotoXY(Snake.x[0], Snake.y[0]); //打印蛇头
    printf("■");
    gotoXY(66 - 2, 0);
    ChangeFlag = 0; //由于目前没有吃到食物，ChangFlag的值为0

    if (GetAsyncKeyState(VK_ESCAPE)) //如果按下ESC键，结束游戏
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

//////////判断蛇的状态：游戏是否结束/////////////////////////
int SnakeStatus()
{
    int i;
    if (Snake.y[0] == 0 || Snake.y[0] == 29) //蛇头碰到上下边界，游戏结束
        return 0;

    if (Snake.x[0] == 0 || Snake.x[0] == 66) //蛇头碰到左右边界，游戏结束
        return 0;

    for (i = 1; i < Snake.length; i++) //蛇头碰到蛇身，游戏结束
    {
        if (Snake.x[i] == Snake.x[0] && Snake.y[i] == Snake.y[0])
            return 0;
    }
    return 1;
}

/////////////游戏失败边框////////////////////
int FailGame(void)
{
    int i;
    system("cls"); //利用system函数清屏

    setColor(12);
    gotoXY(46, 3);
    printf("游 戏 失 败!!!");

    setColor(11);
    gotoXY(17, 5);

    printf("┏"); //绘制上边框
    for (i = 1; i <= 68; i++)
        printf("-");
    printf("┓");

    gotoXY(17, 20); //绘制下边框
    printf("┗");
    for (i = 1; i <= 68; i++)
        printf("-");
    printf("┛");

    for (i = 6; i < 20; i++) //绘制左右边框
    {
        gotoXY(17, i);
        printf("┋");

        gotoXY(86, i);
        printf("┋");
    }
    return 0;
}

///////////////////////游戏失败界面/////////////////////////////
int EndGame(void)
{
    FailGame(); //显示游戏失败边框
    setColor(12);
    gotoXY(47, 9); //显示得分
    setColor(13);
    printf("您的得分: %d", score);

    if (score < 500)
    {
        setColor(30);
        gotoXY(40, 12);
        printf("加油哦，离最高分还差%d分", 500 - score);
    }

    setColor(10);
    gotoXY(38, 16);
    printf("不要气馁，下一次的得分会更高！");

    return 0;
}

///////////////////实现过程////////////////////////////
int main()
{
    int Choose;
    system("mode con cols=100 lines=60"); //设置控制台的大小
    while (1)
    {
        Choose = WelcomeGame();
        switch (Choose) //判断玩家如何选择
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
