#include<stdio.h>
#include<math.h>
#include<Windows.h>
#include<graphics.h>

#define mixnum 100//圆最多数目
//四个边界线
#define leftline 1001
#define rightline 1002
#define upline 1002
#define downline 1001
#define ki 100

int head=0;//结构体数组右侧
int tail=0;//结构体数组左侧

struct Circle
{
	double r;//圆的半径
	double x;//横坐标
	double y;//纵坐标
	int serial;//序号
	int a[3];//关联圆或线
};

Circle circles[mixnum];//为什么不能用mixnum??//因为多了分号
Circle temp;

void sort();//给新生圆排序
void creat();//创建新生圆
void draw();//画圆
void mainfunc();


void init()//初始化
{
	
	line(2*ki, 0, 2*ki, 4*ki);
	line(0, 2*ki, 4*ki, 2* ki);
	double r = 0, x = 0, y = 0;
	circles[tail].x = 0;
	circles[tail].y = 0;
	circles[tail].r = ki;
	circles[tail].serial = 0;
	//circles[tail].a = { 0 };
	draw();
	if (tail == 0)
	{
		printf("the first %d circle\n", tail);
		tail++;

		head++;
		r = (3 - 2 * sqrt((double)2))*ki;
		x = ki - r;
		y = ki - r;
		circles[head].r = r;
		circles[head].x = x;
		circles[head].y = y;
		circles[head].serial = head;
		circles[head].a[0] = upline;
		circles[head].a[1] = rightline;
		circles[head].a[3] = 0;
		printf("the child %d circle\n", head);

		head++;
		circles[head].r = r;
		circles[head].x = -x;
		circles[head].y = y;
		circles[head].serial = head;
		circles[head].a[0] = upline;
		circles[head].a[1] = leftline;
		circles[head].a[3] = 0;
		printf("the child %d circle\n", head);

		head++;
		circles[head].r = r;
		circles[head].x = x;
		circles[head].y = -y;
		circles[head].serial = head;
		circles[head].a[0] = downline;
		circles[head].a[1] = rightline;
		circles[head].a[3] = 0;
		printf("the child %d circle\n", head);

		head++;
		circles[head].r = r;
		circles[head].x = -x;
		circles[head].y = -y;
		circles[head].serial = head;
		circles[head].a[0] = downline;
		circles[head].a[1] = leftline;
		circles[head].a[3] = 0;
		printf("the child %d circle\n", head);
		return;
	}
}
void type1(int i1,int i2,int i3)//角形,i1是父代，i2是上下，i3是左右
{
	double x, y, r;
	double R = 0;
	R = circles[i1].r;
	r = (3 - 2 * sqrt((double)2))*R;
	if (i3==leftline)
	    x = (-1)*(ki - r);
	else
		x = ki - r;
	if (i2==downline)
	    y = (-1)*(ki - r);
	else
		y = ki - r;
    head++;
	circles[head].r = r;
	circles[head].x = x;
	circles[head].y = y;
	circles[head].serial = head;
	circles[head].a[0] = i2;
	circles[head].a[1] = i3;
	circles[head].a[2] = i1;
	printf("the child %d circle and banjing %f\n", circles[head].serial,r);
}
void type2(int i1, int i2, int i3)//y线性
{
	double x1, x2, y1, y2, r1, r2, x, y, r;
	x1 = circles[i1].x;
	y1 = circles[i1].y;
	r1 = circles[i1].r;
	x2 = circles[i3].x;
	y2 = circles[i3].y;
	r2 = circles[i3].r;
	r = r1*r2 / (r1 + r2 + 2 * sqrt(r1*r2));
	if (i2 == downline)
		y = r - ki;
	else
		y = ki - r;
	if (x1 < x2)
		x = x1 + sqrt(((r1 + r)*(r1 + r) - (y1 - y)*(y1 - y)));
	else
		x = x2 + sqrt(((r2 + r)*(r2 + r) - (y2 - y)*(y2 - y)));
	head++;
	circles[head].r = r;
	circles[head].x = x;
	circles[head].y = y;
	circles[head].serial = head;
	circles[head].a[0] = i2;
	circles[head].a[1] = i3;
	circles[head].a[2] = i1;
	printf("the child %d circle and banjing %f\n", circles[head].serial, r);
}
void type3(int i1, int i2, int i3)//x线性
{
	double x1, x2, y1, y2, r1, r2, x, y, r;
	x1 = circles[i1].x;
	y1 = circles[i1].y;
	r1 = circles[i1].r;
	x2 = circles[i2].x;
	y2 = circles[i2].y;
	r2 = circles[i2].r;
	r = r1*r2 / (r1 + r2 + 2 * sqrt(r1*r2));
	if (i3 == leftline)
		x = r - ki;
	else
		x = ki - r;
	if (y1 < y2)
		y = y1 + sqrt(((r1 + r)*(r1 + r) - (x1 - x)*(x1 - x)));
	else
		y = y2 + sqrt(((r2 + r)*(r2 + r) - (x2 - x)*(x2 - x)));
	head++;
	circles[head].r = r;
	circles[head].x = x;
	circles[head].y = y;
	circles[head].serial = head;
	circles[head].a[0] = i2;
	circles[head].a[1] = i3;
	circles[head].a[2] = i1;
	printf("the child %d circle and banjing %f\n", circles[head].serial, r);
}
void type(int i1, int i2, int i3)//圆形
{
	double x1, x2, x3 ,y1, y2, y3, r1, r2, r3, x=0, y=0, r=0;
	x1 = circles[i1].x;
	y1 = circles[i1].y;
	r1 = circles[i1].r;
	x2 = circles[i2].x;
	y2 = circles[i2].y;
	r2 = circles[i2].r;
	x3 = circles[i3].x;
	y3 = circles[i3].y;
	r3 = circles[i3].r;
	printf("i1=%d,i3=%d,i2=%d\n",i1, i3, i2);
	printf("%f   %f   %f\n", x1, x2, x3);
	printf("%f   %f   %f\n", y1, y2, y3);
	printf("%f   %f   %f\n", r1, r2, r3);

	//计算
	double A[3][3], b[3];
	A[0][0] = 2 * (x2 - x1);
	A[0][1] = 2 * (y2 - y1);
	A[0][2] = -2 * (r1 - r2);
	A[1][0] = 2 * (x3 - x2);
	A[1][1] = 2 * (y3 - y2);
	A[1][2] = -2 * (r2 - r3);
	A[2][0] = 2 * (x3 - x1);
	A[2][1] = 2 * (y3 - y1);
	A[2][2] = -2 * (r1 - r3);

	b[0] = r1*r1 - r2*r2 - (x1*x1 - x2*x2) - (y1*y1 - y2*y2);
	b[1] = r2*r2 - r3*r3 - (x2*x2 - x3*x3) - (y2*y2 - y3*y3);
	b[2] = r1*r1 - r3*r3 - (x1*x1 - x3*x3) - (y1*y1 - y3*y3);

	printf("打印扩展矩阵\n");
	printf("%f    %f    %f    %f\n", A[0][0], A[0][1], A[0][2], b[0]);
	printf("%f    %f    %f    %f\n", A[1][0], A[1][1], A[1][2], b[1]);
	printf("%f    %f    %f    %f\n", A[2][0], A[2][1], A[2][2], b[2]);

	A[1][1] = A[1][1] - A[0][1] * A[1][0] / A[0][0];
	A[1][2] = A[1][2] - A[0][2] * A[1][0] / A[0][0];
	b[1] = b[1] - b[0] * A[1][0] / A[0][0];
	A[1][0] = 0;

	printf("打印扩展矩阵\n");
	printf("%f    %f    %f    %f\n", A[0][0], A[0][1], A[0][2], b[0]);
	printf("%f    %f    %f    %f\n", A[1][0], A[1][1], A[1][2], b[1]);
	printf("%f    %f    %f    %f\n", A[2][0], A[2][1], A[2][2], b[2]);

	A[2][1] = A[2][1] - A[0][1] * A[2][0] / A[0][0];
	A[2][2] = A[2][2] - A[0][2] * A[2][0] / A[0][0];
	b[2] = b[2] - b[0] * A[2][0] / A[0][0];
	A[2][0] = 0;

	printf("打印扩展矩阵\n");
	printf("%f    %f    %f    %f\n", A[0][0], A[0][1], A[0][2], b[0]);
	printf("%f    %f    %f    %f\n", A[1][0], A[1][1], A[1][2], b[1]);
	printf("%f    %f    %f    %f\n", A[2][0], A[2][1], A[2][2], b[2]);

	A[2][2] = A[2][2] - A[1][2] * A[2][1] / A[1][1];
	b[2] = b[2] - b[1] * A[2][1] / A[1][1];
	A[2][1] = 0;

	printf("打印扩展矩阵\n");
	printf("%f    %f    %f    %f\n", A[0][0], A[0][1], A[0][2], b[0]);
	printf("%f    %f    %f    %f\n", A[1][0], A[1][1], A[1][2], b[1]);
	printf("%f    %f    %f    %f\n", A[2][0], A[2][1], A[2][2], b[2]);

	A[0][2] = A[0][2] - A[1][2] * A[0][1] / A[1][1];
	b[0] = b[0] - b[1] * A[0][1] / A[1][1];
	A[0][1] = 0;

	printf("打印扩展矩阵\n");
	printf("%f    %f    %f    %f\n", A[0][0], A[0][1], A[0][2], b[0]);
	printf("%f    %f    %f    %f\n", A[1][0], A[1][1], A[1][2], b[1]);
	printf("%f    %f    %f    %f\n", A[2][0], A[2][1], A[2][2], b[2]);
	
	double j=0;
	printf("A[0][2]=%f\n", A[0][2]);
	if ((int)A[0][2] == -0.000000)//比较不成
	{
		x = b[0] / A[0][0];//并不都是x,也会有只产生y的？？
			j = r1 - b[1] / A[1][1];
			y = ((x - x1)*(x - x1) + y1*y1 - j*j) / (2 * (y1 + j));
			r = j - r1 + y;
		printf("x=%f  ,y=%f  ,r=%f  ,j=%f \n", x, y, r, j);
	}
	else if ((int)A[1][2] == 0)
	{
		    y = b[1] / A[1][1];
		    j = r1 - b[0] / A[0][0];
		    x = ((y - y1)*(y - y1) + x1*x1 - j*j) / (2 * (x1 + j));
	     	r = j - r1 + x;
		printf("x=%f  ,y=%f  ,r=%f  ,j=%f \n", x, y, r, j);
	}
	else
	{
		r = b[2] / A[2][2];
		y = (b[1] - A[1][2] * r) / A[1][1];
		x = (b[0] - A[0][2] * r - A[0][1] * y) / A[0][0];
	}

	//问题：三个方程组线性相关；


	head++;
	circles[head].r = r;
	circles[head].x = x;
	circles[head].y = y;
	circles[head].serial = head;
	circles[head].a[0] = i2;
	circles[head].a[1] = i3;
	circles[head].a[2] = i1;
	printf("the child %d circle and banjing %f\n", circles[head].serial, r);
}
void type4(int i1,int i2,int i3)
{
	double x1, x2, x3, y1, y2, y3, r1, r2, r3, x = 0, y = 0, r = 0,b,c,a;
	x1 = circles[i1].x;
	y1 = circles[i1].y;
	r1 = circles[i1].r;
	x2 = circles[i2].x;
	y2 = circles[i2].y;
	r2 = circles[i2].r;
	x3 = circles[i3].x;
	y3 = circles[i3].y;
	r3 = circles[i3].r;
	a = r3 + r2;
	b = r1 + r3;
	c = r1 + r2;
	x = (a*x1 + b*x2 + c*x3) / (a + b + c);
	y = (a*y1 + b*y2 + c*y3) / (a + b + c);
	r = sqrt((x - x1)*(x - x1) + (y - y1)*(y - y1)) - r1;
	printf("x=%f,  y=%f,  r=%f\n", x, y, r);

	head++;
	circles[head].r = r;
	circles[head].x = x;
	circles[head].y = y;
	circles[head].serial = head;
	circles[head].a[0] = i2;
	circles[head].a[1] = i3;
	circles[head].a[2] = i1;
}

void creat()
{
	double r = 0, x = 0, y = 0;
	int b[3] = { 0 };
	int i = 0;
	for (; i < 3; i++)
		b[i] = circles[tail].a[i];
	if (circles[tail].a[0] < 1000 && circles[tail].a[1] < 1000)
	{	
		//type4(tail, b[0], b[1]);
		//type4(tail, b[0], b[2]);
		//type4(tail, b[2], b[1]);
		return;
	}
	if (circles[tail].a[0] > 1000 && circles[tail].a[1] < 1000)
	{		
		type2(tail, b[0], b[1]);
		type2(tail, b[0], b[2]);
		//type4(tail, b[2], b[1]);
		return;
	}
	if (circles[tail].a[0] < 1000 && circles[tail].a[1] > 1000)
	{
		type3(tail, b[0], b[1]);
		type3(tail, b[2], b[1]);
		//type4(tail, b[2], b[0]);
		return;
	}
	if (circles[tail].a[0] > 1000 && circles[tail].a[1] > 1000)
	{		
		type1(tail, b[0], b[1]);
		type2(tail, b[0], b[2]);
		type3(tail, b[2], b[1]);
		return;
	}
}
void sort()//采取插入排序算法
{
	int m = head - tail;
	int t = tail;
	int i = 0;
	int j = 0;
	while (m--)
	{		
		i = t;
		temp=circles[t];
		for (; i <= head; i++)
		{
			if (circles[i].r>temp.r)
				temp = circles[i];
		}
		j = temp.serial;
		circles[j] = circles[t];
		circles[j].serial = j;
		circles[t] = temp;
		circles[t].serial = t;
		t++;
	}
	printf("进行一次排序\n");
}
void draw()
{
	printf("画出现在最大的圆%d\n", tail);
	printf("圆的半径%f\n", circles[tail].r);
	printf("圆的x坐标%f\n", circles[tail].x);
	printf("圆的y坐标%f\n", circles[tail].y);

	setcolor(RED);
	circle(circles[tail].x+2*ki, circles[tail].y+2*ki, circles[tail].r);

}
void mainfunc()//主题 一次输出
{	
	draw();
	printf("产生新子代\n");
	creat();
	tail++;
	sort();
}

void debug()
{
	int i = 0;
	printf("验证排序\n");
	for (; i <= head; i++)
	{
		printf("%d号圆的半径是%f\n", i, circles[i].r);
	}
}
int main()
{

	int driver, mode;
	driver = DETECT;
	mode = 0;
	initgraph(&driver, &mode, "");
	
	setcolor(WHITE);
	rectangle(ki, ki, 3*ki, 3*ki);
	int counts = 20;//产生多少个圆
	init();
	while (counts--)
		mainfunc();
	debug();
	system("pause");
	return 0;
}

