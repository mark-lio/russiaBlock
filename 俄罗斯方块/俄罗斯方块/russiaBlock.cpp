#include<stdio.h>
#include<graphics.h>
#include<iostream>
#include<time.h>
#include<conio.h>//kbhit()�����ͷ�ļ�
#include<mmsystem.h>
#pragma comment(lib, "winmm.lib")

using namespace std;

#define BLOCK_COUNT  5
#define BLOCK_WIDTN  5
#define BLOCK_HEIGHT 5
#define UNIT_SIZE    20//С��������
#define START_X     130
#define START_Y      30
#define KEY_UP       72     //�������ASCII��ֵ
#define KEY_DOWN     80     //�������ASCII��ֵ
#define KEY_LEFT     75     //�������ASCII��ֵ
#define KEY_RIGHT    77     //�������ASCII��ֵ
#define KEY_SPACE    32		//�ո��ASCII��ֵ

typedef enum{
	BLOCK_UP,
	BLOCK_RIGHT,
	BLOCK_DOWN,
	BLOCK_LEFT
}block_dir;

typedef enum{
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT
}move_dir;

int level = 0;//�ȼ�
int score = 0;//����
int NextIndex = -1;//��һ�����������
int BlockIndex = -1;//��ǰ���������
int speed = 500;
int minX = 30;
int minY = 30;

int color[BLOCK_COUNT] = {
	GREEN, CYAN, MAGENTA, BROWN, YELLOW
};

int visit[30][15];//��������
int markColor[30][15];

int block[BLOCK_COUNT * 4][BLOCK_HEIGHT][BLOCK_WIDTN] = {//ÿ�ַ�����������̬
	//���η���
	{
		0, 0, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 0, 0, 0,
	},
	{
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 1, 1, 1, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
	},
	{
		0, 0, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 0, 0, 0,
	},
	{
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 1, 1, 1, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
	},

	//L�η���
	{
		0, 0, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 1, 1, 0,
		0, 0, 0, 0, 0,
	},
	{
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 1, 0,
		0, 1, 1, 1, 0,
		0, 0, 0, 0, 0,
	},
	{
		0, 0, 0, 0, 0,
		0, 0, 1, 1, 0,
		0, 0, 0, 1, 0,
		0, 0, 0, 1, 0,
		0, 0, 0, 0, 0,
	},
	{
		0, 0, 0, 0, 0,
		0, 1, 1, 1, 0,
		0, 1, 0, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
	},

	//�����η���
	{
		0, 0, 0, 0, 0,
		0, 1, 1, 0, 0,
		0, 1, 1, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
	},
	{
		0, 0, 0, 0, 0,
		0, 1, 1, 0, 0,
		0, 1, 1, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
	},
	{
		0, 0, 0, 0, 0,
		0, 1, 1, 0, 0,
		0, 1, 1, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
	},
	{
		0, 0, 0, 0, 0,
		0, 1, 1, 0, 0,
		0, 1, 1, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
	},

	//T�η���
	{
		0, 0, 0, 0, 0,
		0, 1, 1, 1, 0,
		0, 0, 1, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
	},
	{
		0, 0, 0, 0, 0,
		0, 0, 0, 1, 0,
		0, 0, 1, 1, 0,
		0, 0, 0, 1, 0,
		0, 0, 0, 0, 0,
	},
	{
		0, 0, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 1, 1, 1, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
	},
	{
		0, 0, 0, 0, 0,
		0, 1, 0, 0, 0,
		0, 1, 1, 0, 0,
		0, 1, 0, 0, 0,
		0, 0, 0, 0, 0,
	},

	//Z�η���
	{
		0, 0, 0, 0, 0,
		0, 1, 1, 0, 0,
		0, 0, 1, 1, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
	},
	{
		0, 0, 0, 0, 0,
		0, 0, 1, 1, 0,
		0, 1, 1, 0, 0,
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
	},
	{
		0, 0, 0, 0, 0,
		0, 0, 1, 0, 0,
		0, 1, 1, 0, 0,
		0, 1, 0, 0, 0,
		0, 0, 0, 0, 0,
	},
	{
		0, 0, 0, 0, 0,
		0, 1, 0, 0, 0,
		0, 1, 1, 0, 0,
		0, 0, 1, 0, 0,
		0, 0, 0, 0, 0,
	}
};


//��ӭ����
void welcome(void){
	//��ʼ������
	initgraph(550,660);

	//���ô��ڱ���
	HWND window=GetHWnd();//��ȡ��ǰ����
	SetWindowText(window, _T("����˹����----*Coding_King*"));//���ô��ڱ���

	//�����ı���������ʽ
	settextstyle(40, 0, _T("�����п�"));//�߶�40,��Ȳ�ָ��(����Ӧ),����
	setcolor(GREEN);
	outtextxy(205, 200, _T("����˹����"));

	settextstyle(22, 0, _T("�����п�"));
	setcolor(YELLOW);
	outtextxy(191, 300, _T("���,�Ӷ���˹���鿪ʼ!"));

	Sleep(4000);//����

}


//��ʼ����Ϸ����
void initGameScene(void){
	mciSendString("play lonelyDance.mp3 repeat", 0, 0, 0);
	char str[16];

	cleardevice();//�����Ļ

	rectangle(27, 27, 336, 635);
	rectangle(29, 29, 334, 633);
	rectangle(370, 50, 515, 195);

	settextstyle(24, 0, _T("�����п�"));
	setcolor(LIGHTGRAY);
	outtextxy(405, 215, _T("��һ��"));

	setcolor(RED);
	outtextxy(405, 280, _T("����"));
	sprintf_s(str, "%d", score);
	outtextxy(425, 310, str);
	
	outtextxy(405, 375, _T("�ȼ�"));
	sprintf_s(str, "%d", level);
	outtextxy(425, 405, str);

	//����˵��
	setcolor(LIGHTBLUE);
	outtextxy(390, 475, "����˵��");
	outtextxy(390, 500, "��:��ת");
	outtextxy(390, 525, "��:�½�");
	outtextxy(390, 550, "��:����");
	outtextxy(390, 575, "��:����");
	outtextxy(390, 600, "�ո�:��ͣ");


}

//������Ͻ�����(�ķ���)
void clearBlock(void){
	setcolor(BLACK);
	settextstyle(23, 0, "����");
	for (int i = 0; i < BLOCK_HEIGHT; i++){
		for (int j = 0; j < BLOCK_WIDTN; j++){
			int x = 391 + j*UNIT_SIZE;
			int y = 71 + i*UNIT_SIZE;
			outtextxy(x, y, "��");
		}
	}

}

//��������
//���ָ��λ��ָ������ķ���
//����x:�������Ͻǵ�x����
//����y:��������Ͻ�����Ϸ�����ڵ�����,������Ϸ���򶥲��ľ���
void clearBlock(int x,int y,block_dir dir){
	setcolor(BLACK);
	int id = BlockIndex * 4 + dir;

	for (int i = 0; i < BLOCK_HEIGHT; i++){
		for (int j = 0; j < BLOCK_WIDTN; j++){
			if (block[id][i][j] == 1){
				//�����÷���ĵ�i�е�j��
				outtextxy(x + j*UNIT_SIZE, y + i*UNIT_SIZE + START_Y,"��");
			}
		}
	}
}


//�����Ͻ������л�����һ������
void drawBlock(int x,int y){
	setcolor(color[NextIndex]);
	settextstyle(23, 0, "����");
	for (int i = 0; i < BLOCK_HEIGHT; i++){
		for (int j = 0; j < BLOCK_WIDTN; j++){
			if (block[NextIndex * 4][i][j] == 1){
				int x1 = x + j*UNIT_SIZE;
				int y1 = y + i*UNIT_SIZE;
				outtextxy(x1, y1, "��");
			}
		}
	}
}

//���Ƶ�ǰ����,��ָ��λ�û���ָ�������ָ������
void drawBlock(int x, int y, int blockIndex, block_dir dir){
	setcolor(color[blockIndex]);
	settextstyle(23, 0, "����");
	int id = blockIndex * 4 + dir;
	for (int i = 0; i < BLOCK_HEIGHT; i++){
		for (int j = 0; j < BLOCK_WIDTN; j++){
			if (block[id][i][j] == 1){
				int x1 = x + j*UNIT_SIZE;
				int y1 = y + i*UNIT_SIZE;
				outtextxy(x1, y1, "��");
			}
		}
	}
}

void nextblock(void){
	clearBlock();

	//���ѡ��һ�ַ���
	srand(time(NULL));//ʹ��ʱ�亯���ķ���ֵ����Ϊ�������
	NextIndex = rand() % BLOCK_COUNT;
	
	drawBlock(391,71);

}

//�����ָ��λ�ÿ�����ָ�������ƶ�,�ͷ���1,����ͷ���0
int moveable(int x0, int y0, move_dir moveDir, block_dir blockDir){
	int id = BlockIndex * 4 + blockDir;//�ڼ�������
	
	//���㵱ǰ��������Ͻ���30*15����Ϸ���е�λ��(�ڶ�����,�ڶ�����)
	int x = (y0 - minY) / UNIT_SIZE;
	int y = (x0 - minX) / UNIT_SIZE;

	int ret = 1;

	if (moveDir == MOVE_DOWN){
		for (int i = 0; i < BLOCK_HEIGHT; i++){
			for (int j = 0; j < BLOCK_WIDTN; j++){
				if (block[id][i][j] == 1 &&//����1��ʾ��ǰ��С����
					(x + i + 1 >= 30 ||
					visit[x + i + 1][y + j] == 1)){
					ret = 0;
				}
			}
		}
	}
	else if (moveDir == MOVE_LEFT){
		for (int i = 0; i < BLOCK_HEIGHT; i++){
			for (int j = 0; j < BLOCK_WIDTN; j++){
				if (block[id][i][j] == 1 &&//����1��ʾ��ǰ��С����
					(y+j==0 ||
					visit[x + i ][y + j-1] == 1)){
					ret = 0;
				}
			}
		}
	}
	else if (moveDir == MOVE_RIGHT){
		for (int i = 0; i < BLOCK_HEIGHT; i++){
			for (int j = 0; j < BLOCK_WIDTN; j++){
				if (block[id][i][j] == 1 &&//����1��ʾ��ǰ��С����
					(y + j +1>= 15 ||
					visit[x + i][y + j +1] == 1)){
					ret = 0;
				}
			}
		}
	}
	return ret;
}

void failCheck(void){
	if (!moveable(START_X, START_Y, MOVE_DOWN, BLOCK_UP)){
		setcolor(RED);
		settextstyle(44, 0, "���Ŀ���");
		outtextxy(59, 299, "GAME OVER!");
		Sleep(4000);
		system("pause");
		closegraph();
		exit(0);
	}
}

void wait(int interval){
	int count = interval / 10;
	for (int i = 0; i < count; i++){
		Sleep(10);
		if (_kbhit()){
			return;
		}
	}
}

//�жϵ�ǰ�����Ƿ����ת��ָ������
//ע��,��ʱ��û��ת���÷���!
int rotatable(int x, int y , block_dir nextDir){
	int id = BlockIndex * 4 + nextDir;
	int xIndex = (y - minY) / UNIT_SIZE;
	int yIndex = (x - minX) / UNIT_SIZE;
	if (!moveable(x, y, MOVE_DOWN, nextDir)){
		return 0;
	}

	for (int i = 0; i < BLOCK_HEIGHT; i++){
		for (int j = 0; j < BLOCK_WIDTN; j++){
			if (block[id][i][j] == 1 &&
				(yIndex + j < 0 || yIndex + j >= 15 || visit[xIndex + i][yIndex + j] == 1)){
				return 0;
			}
		}
	}
	return 1;
}

//�̶�����
void mark(int x, int y, int blockIndex, block_dir dir){
	int id = blockIndex * 4 + dir;
	int x1 = (y - minY)/20;
	int y1 = (x - minX)/20;
	for (int i = 0; i < BLOCK_HEIGHT; i++){
		for (int j = 0; j < BLOCK_WIDTN; j++){
			if (block[id][i][j] == 1){
				visit[x1 + i][y1 + j] = 1;
				markColor[x1 + i][y1 + j] = color[blockIndex];
			}
		}
	}
}

void move(void){
	int x = START_X;
	int y = START_Y;
	int k = 0;
	block_dir blockDir=BLOCK_UP;
	int curSpeed = speed;

	failCheck();//�����Ϸ�Ƿ����
	
	//�������½���
	while (1){
		if (_kbhit()){
			int key = _getch();
			if (key == KEY_SPACE){
				_getch();
			}
		}

		//�����ǰ����
		clearBlock(x, k, blockDir);

		if (_kbhit()){
			int key = _getch();
			if (key == KEY_UP){
				block_dir nextDir = (block_dir)((blockDir + 1) % 4);
				if (rotatable(x, y + k, nextDir)){
					blockDir = nextDir;
				}
			}
			else if (key == KEY_DOWN){
				curSpeed = 50;
			}
			else if (key == KEY_LEFT){
				if (moveable(x, y + k + UNIT_SIZE, MOVE_LEFT, blockDir)){
					x -= UNIT_SIZE;
				}
			}
			else if (key == KEY_RIGHT){
				if (moveable(x, y + k + UNIT_SIZE, MOVE_RIGHT, blockDir)){
					x += UNIT_SIZE;
				}
			}
		}

		k += 20;

		//���Ƶ�ǰ����
		drawBlock(x, y + k, BlockIndex, blockDir);

		wait(curSpeed);
		
		

		//�����"�̻�"����(�����ײ��Ͳ��ᶯ��)
		if (!moveable(x, y + k, MOVE_DOWN, blockDir)){
			mark(x, y + k, BlockIndex, blockDir);
			break;
		}
	}


}

void newblock(void){
	//ȷ������ʹ�õķ��������
	BlockIndex = NextIndex;
	

	//���ƸմӶ����½��ķ���
	drawBlock(START_X, START_Y);
	
	//���³��ֵķ�����ͣһ��,���û�ʶ��
	Sleep(100);

	//�����Ͻ����������һ������
	nextblock();

	//���齵��
	move();

}

//������i��,����������ж�����
void down(int x){
	for (int i = x; i > 0; i--){
		for (int j = 0; j < 15; j++){//������i��,��j�еķ�������
			if (visit[i - 1][j]){
				visit[i][j] = 1;
				markColor[i][j] = markColor[i - 1][j];
				setcolor(markColor[i][j]);
				outtextxy(j*UNIT_SIZE+minX, i*UNIT_SIZE+minY, "��");
			}
			else{
				visit[i][j] = 0;
				setcolor(BLACK);
				outtextxy(j*UNIT_SIZE + minX, i*UNIT_SIZE + minY, "��");
			}
		}
	}

	//�����ϵ���һ��(���б�Ϊ0����һ��)
	setcolor(BLACK);
	for (int j = 0; j < 15; j++){
		visit[0][j] = 0;
		outtextxy(j*UNIT_SIZE + minX,  minY, "��");
	}

}

//���·���,����lines��ʾ����������
void addScore(int lines){
	char str[32];
	setcolor(RED);
	score += lines * 10;
	sprintf_s(str, "%d", score);
	outtextxy(425, 310, str);
}

void updateLevel(void){
	//���µȼ�����ʾ
	level = score / 100;//����100��һ��
	char str[32];
	sprintf_s(str, "%d", level);
	setcolor(RED);
	outtextxy(425, 405, str);

	//�����ٶ�,�ȼ�Խ��,�ٶ�Խ��,speedԽС!
	//������,����:500ms,���:100ms
	speed = 500 - level * 10;
	if (speed <= 100){
		speed = 100;
	}
	
}

void check(void){
	int i, j;
	int clearLines = 0;
	for ( i = 29; i >= 0; i--){
		for ( j = 0; j < 15 && visit[i][j]; j++);//����i����û����

		//ִ�е��˴�ʱ,���������:
		//1.��i��û����,���п�λ,��ʱj<15
		//2.��i��������,��ʱj>=15
		if (j >= 15){
			//��ʱ��i������,��Ҫ������i��
			down(i);//������i��,����������ж�����
			i++;//��Ϊ������ѭ������i--,������i++,ʹ���´�ѭ��ʱ�ٰ���һ�м��һ��
			clearLines++;
		}
	}

	//���·���
	addScore(clearLines);

	//���µȼ�,�ȼ�Խ��,�ٶ�Խ��
	updateLevel();
}

int main(void){
	welcome();
	initGameScene();

	//�����·���
	nextblock();
	Sleep(500);

	//��ʼ����������
	memset(visit, 0, sizeof(visit));

	while (1){
		newblock();

		//��������,�����·����͵ȼ�
		check();

	}
	
	system("pause");
	closegraph();
	return 0;
}