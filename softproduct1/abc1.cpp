#include<stdio.h>
#include<math.h>
#include<Windows.h>
#include<graphics.h>

#define mixnum 100//Բ�����Ŀ
//�ĸ��߽���
#define leftline 1001
#define rightline 1002
#define upline 1002
#define downline 1001
#define ki 100

int head=0;//�ṹ�������Ҳ�
int tail=0;//�ṹ���������

struct Circle
{
	double r;//Բ�İ뾶
	double x;//������
	double y;//������
	int serial;//���
	int a[3];//����Բ����
};

Circle circles[mixnum];//Ϊʲô������mixnum??//��Ϊ���˷ֺ�
Circle temp;

void sort();//������Բ����
void creat();//��������Բ
void draw();//��Բ
void mainfunc();


void init()//��ʼ��
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
void type1(int i1,int i2,int i3)//����,i1�Ǹ�����i2�����£�i3������
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
void type2(int i1, int i2, int i3)//y����
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
void type3(int i1, int i2, int i3)//x����
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
void type(int i1, int i2, int i3)//Բ��
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

	//����
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

	printf("��ӡ��չ����\n");
	printf("%f    %f    %f    %f\n", A[0][0], A[0][1], A[0][2], b[0]);
	printf("%f    %f    %f    %f\n", A[1][0], A[1][1], A[1][2], b[1]);
	printf("%f    %f    %f    %f\n", A[2][0], A[2][1], A[2][2], b[2]);

	A[1][1] = A[1][1] - A[0][1] * A[1][0] / A[0][0];
	A[1][2] = A[1][2] - A[0][2] * A[1][0] / A[0][0];
	b[1] = b[1] - b[0] * A[1][0] / A[0][0];
	A[1][0] = 0;

	printf("��ӡ��չ����\n");
	printf("%f    %f    %f    %f\n", A[0][0], A[0][1], A[0][2], b[0]);
	printf("%f    %f    %f    %f\n", A[1][0], A[1][1], A[1][2], b[1]);
	printf("%f    %f    %f    %f\n", A[2][0], A[2][1], A[2][2], b[2]);

	A[2][1] = A[2][1] - A[0][1] * A[2][0] / A[0][0];
	A[2][2] = A[2][2] - A[0][2] * A[2][0] / A[0][0];
	b[2] = b[2] - b[0] * A[2][0] / A[0][0];
	A[2][0] = 0;

	printf("��ӡ��չ����\n");
	printf("%f    %f    %f    %f\n", A[0][0], A[0][1], A[0][2], b[0]);
	printf("%f    %f    %f    %f\n", A[1][0], A[1][1], A[1][2], b[1]);
	printf("%f    %f    %f    %f\n", A[2][0], A[2][1], A[2][2], b[2]);

	A[2][2] = A[2][2] - A[1][2] * A[2][1] / A[1][1];
	b[2] = b[2] - b[1] * A[2][1] / A[1][1];
	A[2][1] = 0;

	printf("��ӡ��չ����\n");
	printf("%f    %f    %f    %f\n", A[0][0], A[0][1], A[0][2], b[0]);
	printf("%f    %f    %f    %f\n", A[1][0], A[1][1], A[1][2], b[1]);
	printf("%f    %f    %f    %f\n", A[2][0], A[2][1], A[2][2], b[2]);

	A[0][2] = A[0][2] - A[1][2] * A[0][1] / A[1][1];
	b[0] = b[0] - b[1] * A[0][1] / A[1][1];
	A[0][1] = 0;

	printf("��ӡ��չ����\n");
	printf("%f    %f    %f    %f\n", A[0][0], A[0][1], A[0][2], b[0]);
	printf("%f    %f    %f    %f\n", A[1][0], A[1][1], A[1][2], b[1]);
	printf("%f    %f    %f    %f\n", A[2][0], A[2][1], A[2][2], b[2]);
	
	double j=0;
	printf("A[0][2]=%f\n", A[0][2]);
	if ((int)A[0][2] == -0.000000)//�Ƚϲ���
	{
		x = b[0] / A[0][0];//��������x,Ҳ����ֻ����y�ģ���
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

	//���⣺����������������أ�


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
void sort()//��ȡ���������㷨
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
	printf("����һ������\n");
}
void draw()
{
	printf("������������Բ%d\n", tail);
	printf("Բ�İ뾶%f\n", circles[tail].r);
	printf("Բ��x����%f\n", circles[tail].x);
	printf("Բ��y����%f\n", circles[tail].y);

	setcolor(RED);
	circle(circles[tail].x+2*ki, circles[tail].y+2*ki, circles[tail].r);

}
void mainfunc()//���� һ�����
{	
	draw();
	printf("�������Ӵ�\n");
	creat();
	tail++;
	sort();
}

void debug()
{
	int i = 0;
	printf("��֤����\n");
	for (; i <= head; i++)
	{
		printf("%d��Բ�İ뾶��%f\n", i, circles[i].r);
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
	int counts = 20;//�������ٸ�Բ
	init();
	while (counts--)
		mainfunc();
	debug();
	system("pause");
	return 0;
}

