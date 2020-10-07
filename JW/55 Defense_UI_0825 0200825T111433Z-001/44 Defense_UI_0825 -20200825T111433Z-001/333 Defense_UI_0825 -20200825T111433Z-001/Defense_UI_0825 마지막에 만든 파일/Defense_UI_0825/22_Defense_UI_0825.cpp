// Defense_UI_0825.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "Defense_UI_0825.h"
#include "resource.h"	// ���ҽ��� ���� ������ ������ ���ҽ� ����� ���ǵǾ��ֱ� ����
#include <vector>
using namespace std;

#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

HINSTANCE g_hInstance = NULL;


static int bullet_x_pos, bullet_y_pos;
static int x, y, px, py;	//rect ����ü�� x�� y�� ������ +  x1,y1�� player�� �̵��� ���ؼ� 
static RECT rectView;		// �����ؾ� RECT ����ü ��밡��

int enemy_x = 300, enemy_y = 150; // �� ������ ���ؼ� ���������� i ,j��  enemy_x, enemy_y �� �ٲ��ְ� Ÿ�̸ӿ����� ����ϰ� ����



POINT pos;




class Bullet
{
public:
	int bbx, bby, bbr;
	RECT rect;
public:
	Bullet(int to_access_bx, int to_access_by, int to_access_br) // ������ (��ü�� �����ɋ� �����) >> Ŭ������ �ν��Ͻ�ȭ��� �θ�
	{
		bbx = to_access_bx;
		bby = to_access_by;
		bbr = to_access_br;
	}
	Bullet() {};												// �Ҹ��� ( Ŭ������ �Ҹ� �ɋ� ����)

	void Draw_bullet(HDC hdc)
	{
		Rectangle(hdc, bbx - bbr, bby - bbr, bbx + bbr, bby + bbr);
		rect = { bbx - bbr, bby - bbr, bbx + bbr, bby + bbr };
	}

	void Move_bullet()
	{
		bby -= 40;
	}
};

vector<Bullet*> Bullet_object; // ���� ��ü ����
vector<Bullet*> Bullet_various;



// =================���Ϳ��� ==================================

vector<int> vector_variable;				 // ���� ����
vector<int> v1(4);						// ���ڸ�ŭ ���ͻ��� int�� ���� ���� �� ũ�⸦ 4�� �Ҵ�(��� ���Ϳ�� 0���� �ʱ�ȭ)
vector<int> v2 = { 1,2,3 };				// ���� ���� �� 1,2,3���� ���� ������ �ʱ�ȭ
vector<int> v3[] = { { 1,2 },{ 3,4 } };		// int �� ���� ����, ���� ���������� ���� ����
vector<vector<int>> v4;					// 2���� ���� ���� (�� �� ��� ����)
vector<int> v5 = { 1,2,3,4,5 };			// 


//================= ���Ϳ��� =================================



class enemy			// ����ü ��ſ� class	 // enemy ����ü �������ٰ� wm_paint���� for������ �׷���� enemy�� ǥ���������. �׷��� wm_paint���� ȣ���غ���
{
private:
	int ex, ey, er;
public:
	void enemy_update();
	void draw();
};

enemy approach_enemy; // class�� �����ϱ� ���� ��ü ����

void enemy::enemy_update()
{
	int enemy;
	if (enemy < rectView.left)	// enemy�� ���� ���� �ε����� y������ �� ĭ �����ϰ� ������ �������� �̵�
	{
		y += 50;
		px += 40;
	}
	if (enemy < rectView.right)	// enemy�� ������ ���� �ε����� y������ �� ĭ �����ϰ� ������ �������� �̵�
	{
		y += 50;
		px -= 40;
	}
}


void enemy::draw()
{
	HDC hdc;
	Ellipse(hdc, pos.x, pos.y, pos.x, pos.y);
}


class vEnemy
{
public:
	RECT Enemy;
	int x;
	int y;
	int r;
public:
	vEnemy(int hx, int hy, int hr) 
	{
		x = hx; y = hy; r = hr;
	};
	~vEnemy() {};

	void DrawEnemy(HDC hdc)
	{
		Rectangle(hdc, x - r, y - r, x + r, y + r);
		Enemy = { x - r, y - r, x + r, y + r };
	}
	

};

vector<vEnemy*> vEnemyv;


void Collider(HDC hdc)
{	
	RECT TEMP;

	for (vector<Bullet*>::iterator i = Bullet_various.begin(); i < Bullet_various.end();)
	{
		bool a = false;
		for (vector<vEnemy*>::iterator j= vEnemyv.begin(); j < vEnemyv.end();)
		{
			if (IntersectRect(&TEMP, &(*i)->rect, &(*j)->Enemy))
			{
				a = true;
				TextOut(hdc, 500, 500, _T("HI"), 2);
				delete (*i);
				i = Bullet_various.erase(i);
				delete (*j);
				j = vEnemyv.erase(j);
				break;
			}		
			++j;		
		}
		if (a == true)
			break;
		++i;
	}
	
}




// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


RECT r1 = { 0,0,800,600 };

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ���⿡ �ڵ带 �Է��մϴ�.

    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DEFENSE_UI_0825, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEFENSE_UI_0825));

    MSG msg;

    // �⺻ �޽��� �����Դϴ�.
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEFENSE_UI_0825));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DEFENSE_UI_0825);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 1000, 1000, nullptr, nullptr, hInstance, nullptr);  // CW_USEDEFAULT

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}





BOOL Ellipse(HDC hdc, const POINT& center, int radius) // Ellipse�� �Լ� �����ε��ؼ� �� ����� �Ű����� ���̰ų� �ø��°�
{
	return Ellipse(hdc,
		center.x - radius, center.y - radius,
		center.x + radius, center.y + radius);
}


//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����:  �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;					// ȭ�� �������� ���� �ʿ��� dc��
	PAINTSTRUCT ps;
	HDC MemDC;					// ��Ʈ���� �ϳ��� �ҷ����� �ʹ� �����ӵ��� �Ǳ⿡ �̸� �޸𸮿� �÷����� �ҷ����� ��� ���

	static RECT rectView;		// �����ؾ� RECT ����ü ��밡��
	HPEN newPen, oldPen;		//����� ��� ���� 3������ ��� �־����
	g_hInstance = hInst;	// �ü���� ������ ���� ���α׷��� �ν��Ͻ� ��ü�� ���������� ����ϵ��� �޾ƿ�

	HBITMAP MyBitmap, OldBitmap;	
	int btm_x, btm_y;
	BITMAP bit;
	static HBITMAP hBitMap_Char;	// ��Ʈ���� �ҷ����� ���ؼ� �ʿ��� ��Ʈ�� �ڵ� ���� ����� 
									// �Ʊ� ���ҽ��� �߰��� �̹����� �� �ڵ麯���� �ҷ��ð���


	int radi = 15;				// paint �� ������ �ڵ� ���� ������ �������ε� �������� ���� �;(timer������ ������)
	int enemy_number = 400;



    switch (message)
    {
	case WM_CREATE:
	{
		hBitMap_Char = (HBITMAP)LoadBitmap(g_hInstance, MAKEINTRESOURCE(IDB_BITMAP2)); // �Ʊ� ������� ��Ʈ�� ���� ��
																					   // ���� IDB_BITMAP1 �� ������� Resource.h�� ����
		vEnemyv.push_back(new vEnemy(50,550,40));
		vEnemyv.push_back(new vEnemy(80, 550,40)); //40�� ������
		int wx, wy, width, height;						// wx wy�� window_x window_y ��		���⼭���� 
		RECT rtDesk, rtWindow;
		GetWindowRect(GetDesktopWindow(), &rtDesk);
		GetWindowRect(hWnd, &rtWindow);

		width = rtWindow.right - rtWindow.left;  // ���� �̷��� �Ǿ��־���. width = rtWindow.right - rtWindow.left;
		height = rtWindow.bottom - rtWindow.top;

		wx = (rtDesk.right - width) / 2;
		wy = (rtDesk.bottom - height) / 2;

		MoveWindow(hWnd, wx, wy, width, height, TRUE);	// ������� ������ ����� ����� �ű�� �ڵ�

		GetClientRect(hWnd, &rectView); // �� �Լ��� �������� ���ϴ� ���� ����� �� ���� + ���ȿ��� �� �̵�
		px = 0, py = 0; // player �� �¿� �̵��� ����
			

		SetTimer(hWnd, 1, 200, NULL); // enemy,  �� Ÿ�̸�
		SetTimer(hWnd, 2, 200, NULL); // bullet, �Ѿ� Ÿ�̸�
	}
	break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // �޴� ������ ���� �м��մϴ�.
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
		/*
		rgb(255,0,0) : ���� (Red)
		rgb(0,255,0) : ��� (Green)
		rgb(0,0,255) : �Ķ� (Blue)
		rgb(192,192,192) : ȸ�� (Gray)
		rgb(255,255,0) : ��� (Yellow)
		rgb(255,0,255) : ��ȫ�� (Cerise)
*/
	case WM_TIMER:
	{
		switch (wParam)
		{
		case 1: // settimer�� �̸��� 1�ϋ�
		{
			static bool flag = true;	// static�� ������ �����ʿ� ��� ��� ������ �Ʒ��� y���� ������ �ݴ�� ���ư����ʰ�

			if (flag)
			{
				enemy_x += 40;
			}
			else
			{
				enemy_x -= 40;
			}
			

			if (enemy_x + enemy_number >= rectView.right || enemy_x <= rectView.left)		// �����ʿ� ������ �� ĭ �Ʒ� ������. flag�̿� 
			{
				enemy_y += 40;
				flag = !flag;
			}
		}
		case 2:
		{
			for (vector<Bullet>::size_type i = 0; i < Bullet_various.size(); i++)
			{
				Bullet_various[i]->Move_bullet();
			}
			//	bullet_y_pos -= 10;

			//	bool flag_bullet = false; // �Ѿ��� ������ �ٱ�����  �������� 0,1 �� �˻�.



			//	if (py >= rectView.top)
			//	{
			//		
		}
		}
	}
		InvalidateRgn(hWnd, NULL, true); 

	break;
	
    case WM_PAINT:
        {
			HDC hdc = BeginPaint(hWnd, &ps);
			
			MemDC = CreateCompatibleDC(hdc);
			MyBitmap = LoadBitmap(g_hInstance, MAKEINTRESOURCE(IDB_BITMAP3));
			OldBitmap = (HBITMAP)SelectObject(MemDC, MyBitmap);
			
			GetObject(MyBitmap, sizeof(BITMAP), &bit);
			btm_x = bit.bmWidth;
			btm_y = bit.bmHeight;

			StretchBlt(hdc, 0, 0, btm_x , btm_y*1.25, MemDC, 0, 0, btm_x, btm_y, SRCCOPY);

			for (vector<Bullet>::size_type i = 0; i < Bullet_various.size(); ++i)										//  �Ѿ� ����,,  ��Ʈ�� �׸� ������ �� �׸�����
			{
				Bullet_various[i]->Draw_bullet(hdc);
			}
			


			
			
			SelectObject(MemDC, OldBitmap);
			DeleteObject(MyBitmap);
			DeleteDC(MemDC);
			

			//// ��Ʈ�� ���� ����ϰ� �� ���� ���� ���ؼ� �׸��ű� ������ ��Ʈ�� ���⿡ �ۼ�
			//MemDC = CreateCompatibleDC(hdc);
			//SelectObject(MemDC, hBitMap_Char);
			//BitBlt(hdc, 0, 0, 512, 384, MemDC, 0, 0, SRCCOPY); // memdc�� �ִ°� hdc�� �Ű��� SRCCOPY ���� ��ŭ ����
			//DeleteObject(MemDC); // ��� �����⿡ �������� �귯���� ���̶� �Ȱ���

			HBRUSH hBrush, oldBrush;									// ���⼭ ����
			hBrush = CreateSolidBrush(NULL);   // RGB(255, 255, 255) (RGB(0, 0, 0)
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			// ���⼭ �����̳� �� �׸��� ���õ� �귯���� ����

			//Rectangle(hdc, rectView.left, rectView.top, rectView.right, rectView.bottom);   // ������ ũ�⸸ŭ ������ �귯���� ������.

			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);									// ������� ���� brush ����


			newPen = CreatePen(PS_DASH, 2, RGB(255, 0, 0)); //RGB(0,0,0)); 255 255 255�� ���ڸ� ������   0 0 0 �̸�  ������ ���� ���������� ǥ��
			oldPen = (HPEN)SelectObject(hdc, newPen);


			TextOut(hdc, 540, 20, TEXT("Devil"), 5);
			TextOut(hdc, rectView.right / 2 + 60, rectView.bottom - 40, TEXT("player"), 6);
			TextOut(hdc, rectView.left + 10, rectView.top + 50, TEXT("ĳ���� ����"), 6);
			TextOut(hdc, rectView.right - 60, rectView.top + 50, TEXT("ü�¹�"), 3);
			TextOut(hdc, rectView.left + 250, rectView.top + 200, TEXT("enemy"), 5);
			TextOut(hdc, rectView.left + 130, rectView.bottom - 250, TEXT("1�� �Ѿ�"), 5);
			//TextOut(hdc, rectView.left + 430, rectView.bottom - 250, TEXT("2�� �Ѿ�"), 5);
			TextOut(hdc, rectView.left + 770, rectView.bottom - 250, TEXT("3�� �Ѿ�"), 5);
			Rectangle(hdc, px + 400, py + 900, px + 500, py + 980);	// �÷��̾� �̵�	 �ȵǸ� �׳� 0���� ��	��									// player ��ġ		(hdc, rectView.right / 2 - 40, rectView.bottom - 80, rectView.right / 2 + 40, rectView.bottom);
			Rectangle(hdc, rectView.right / 2 - 40, rectView.top, rectView.right / 2 + 40, rectView.top + 80);			// Devil ��ġ
			Rectangle(hdc, rectView.left, rectView.top, rectView.left + 80, rectView.top + 40); // ĳ���� ����
			Rectangle(hdc, rectView.right - 60, rectView.top, rectView.right, rectView.top + 40); // ü�¹�

			TextOut(hdc, rectView.right / 2 + 60, rectView.top + 60, TEXT("charcter +++"), 12);

			//newPen = CreatePen(PS_DOT, 2, NULL); //RGB(255,255,255)); ���� pen �ڸ� pen�� ������� ó���Ϸ��� TextOut�Լ� �������� �Űܳ���
			//oldPen = (HPEN)SelectObject(hdc, newPen);

			MoveToEx(hdc, rectView.right / 3, rectView.bottom - 100, NULL);	// 1�� �Ѿ�
			LineTo(hdc, rectView.left + 100, rectView.bottom / 1.6);

			//SelectObject(hdc, oldPen);
			//DeleteObject(newPen);		// ���⿡�� newpen �����ϸ� 1���Ѿ˸� newpen���� �׸�


			//for (int j = 0; j < 10; j++)
			//{
			//	for (int i = j * 50 + 450; i < 1100; i += 30)					// 2�� �Ѿ� 
			//	{
			//		Ellipse(hdc, 500, i, 550, i + 50);
			//	}
			//}

			MoveToEx(hdc, rectView.right / 1.3, rectView.bottom - 100, NULL);
			LineTo(hdc, rectView.right - 50, rectView.bottom / 1.6);
			MoveToEx(hdc, rectView.right / 1.32, rectView.bottom - 100, NULL);	// 3�� �Ѿ�  pen �����ؼ� old �ٽð���
			LineTo(hdc, rectView.right - 60, rectView.bottom / 1.6);
			MoveToEx(hdc, rectView.right / 1.34, rectView.bottom - 100, NULL);
			LineTo(hdc, rectView.right - 70, rectView.bottom / 1.6);			

			SelectObject(hdc, oldPen);
			DeleteObject(newPen);		// ���⿡�� newpen �����ϸ� 3���Ѿ˱��� ��� ���� newpen���� �׷ȴٰ� �� �������� �� ���� ���ڴ� ��� default ���� �������� ����

			


			/*for (int i = 0; i < 10; i++)
			{
			Ellipse(hdc, i * 40 + 300, 120, i * 40 + 330, 150);			��Ģ���� ������ �ݺ����� �� �ݺ��ϱ�.
			}

			for (int i = 0; i < 10; i++)
			{
			Ellipse(hdc, i * 40 + 300, 160, i * 40 + 330, 190);
			}

			for (int i = 0; i < 10; i++)
			{
			Ellipse(hdc, i * 40 + 300, 200, i * 40 + 330, 230);
			}*/


			// Rectangle(hdc, rectView.right - 70, rectView.top, rectView.right, rectView.top + 50);	// ü�¹� �� �׸� ���⼭ �� �� �ִ� ��. ���� ��� �簢���� �׸��� ���� ��ǥ��ġ��
																										// ��� ��� �簢���� �׸��� ���� �簢���� ������ �ʰ� ����� ���δ�(�������)		
			/*for (enemy_a = 0; enemy_a < 5; enemy_a+=40)
			{
				Ellipse(hdc, enemy_a, 0, enemy_a + 40, 40);
			}*/
			
				//Ellipse(hdc,						//timer���� ȣ���ϸ� 
				//	enemy_x, 0,
				//	enemy_x + 40, 40);
			
			for (int i = 0; i < enemy_number/2; i+=40)
			{
				for (int j = 0; j < enemy_number; j+=40)					// timer �̿��ؼ� �̵��ϴ� ��,, Ellipse�� for�� �ϳ��ϳ� ����ؼ�
				{															// ��Ģ���� ã�Ƴ��� ��ġ�� �ʰ� ���ڸ� �־�����
					Rectangle(hdc,
						enemy_x + j - radi, enemy_y + i - radi,
						enemy_x + j + radi, enemy_y + i + radi);
				}
			}

			for (vector<vEnemy>::size_type i = 0; i < vEnemyv.size(); ++i)
			{
				vEnemyv[i]->DrawEnemy(hdc);
			}
			
			Collider(hdc);

			
			// �Ѿ� �׸��� ��. 

			//Ellipse(hdc, bullet_x_pos + 430, bullet_y_pos + 850, bullet_x_pos + 480, bullet_y_pos + 900); // �Ѿ�  wm_timer���� wparam==2���� �����ϰ� �����  + 900); // �Ѿ�  wm_timer���� wparam==2���� �����ϰ� ����� 

			//for (int enemy_x = 0; enemy_x < 5; enemy_x++)
			//{
			//	for (int enemy_y = 0; enemy_y < 10; enemy_y++)						// �� ���� enemy
			//	{
			//		Ellipse(hdc, enemy_y * 40 + 300, enemy_x * 40 + 120, enemy_y * 40 + 330, enemy_x * 40 + 150);
			//	}
			//}
			
			EndPaint(hWnd, &ps);
        }
        break;
	case WM_KEYDOWN:

	{
		if (wParam == VK_RIGHT)
		{
			px += 40;
			if (px + 20 > rectView.right / 2 + 60) px -= 40; // �켱�� rectView.right /2 +60 ���� �ؼ� ���� ������ ��Ȯ�� �𸣰�����
		}												// x1-=40�ص� �������� �ٽ� �׷��ִ°� �������ʰ� �� -400���������� ��Ȯ�� ���δ�
		if (wParam == VK_LEFT)
		{
			px -= 40;	// -40���� -80�ϴϱ� �߾ӿ��� �������ε� �̵��� but ���� if������ x1 +400�ϴ�  x1-=40 �ص� ������
			if (px + 400< rectView.left) px += 40;	// if(x1-20)����  if(x1 + 100) �ִϱ� �������� �� ������ �� �־���
		}
		if (wParam == VK_SPACE)
		{
			Bullet_various.push_back(new Bullet(px + 450, 900, 10));
			//bullet_y_pos -= 40;
		}


		InvalidateRgn(hWnd, NULL, true);	// �� �̰������ ������ �� ����
	}break;

    case WM_DESTROY:
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}







// ------------------------------------------------------------------------------------------- ��Ʈ�� ---------------------------


//
//HBITMAP hbackImage;
//BITMAP bitBack;
//
//HBITMAP hTransparentImage;
//BITMAP bitTransparent;
//
//HBITMAP hDoubleBufferImage;
//void DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc);
//
//int Run_Frame_Min = 0;
//int cur_Frame = Run_Frame_Min;
//HBITMAP hAniImage;
//
//void CreateBitmap()
//{
//	{
//		hbackImage = (HBITMAP)LoadImage(NULL, TEXT("images/���ֹ��.bmp"),
//			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
//		GetObject(hbackImage, sizeof(BITMAP), &bitBack);
//	}
//}
//
//
//void DrawBitmap(HWND hWnd, HDC hdc)
//{
//	HDC hMemDC, hMemDC2;
//	HBITMAP hOldBitmap, hOldBitmap2;
//	int bx, by;
//
//	{
//		hMemDC2 = CreateCompatibleDC(hdc);
//		hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hTransparentImage);
//		bx = bitTransparent.bmWidth;
//		by = bitTransparent.bmHeight;
//		BitBlt(hdc, 0, 0, bx, by, hMemDC2, 0, 0, SRCCOPY);
//		TransparentBlt(hdc, 200, 100, bx, by, hMemDC2,
//			0, 0, bx, by, RGB(255, 0, 255));
//		SelectObject(hMemDC2, hOldBitmap2);
//	}
//}
//
//
//
//
//void DrawBitmapDoubleBuffering(HWND hWnd, HDC hdc)
//{
//
//	HDC hMemDC;
//	HBITMAP hOldBitmap;
//	int bx, by;
//
//	HDC hMemDC2;
//	HBITMAP hOldBitmap2;
//
//	hMemDC = CreateCompatibleDC(hdc);
//	if (hDoubleBufferImage == NULL)
//		hDoubleBufferImage = CreateCompatibleBitmap(
//			hdc, rectView.right, rectView.bottom);
//	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hDoubleBufferImage);
//
//
//	{
//		hMemDC2 = CreateCompatibleDC(hMemDC);
//		hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hbackImage);
//		bx = bitBack.bmWidth;
//		by = bitBack.bmHeight;
//		BitBlt(hMemDC, 0, 0, bx, by, hMemDC2, 0, 0, SRCCOPY);
//
//		SelectObject(hMemDC, hOldBitmap);
//	}
//
//	{
//		hMemDC2 = CreateCompatibleDC(hdc);
//		hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hTransparentImage);
//		bx = bitTransparent.bmWidth;
//		by = bitTransparent.bmHeight;
//		BitBlt(hdc, 0, 0, bx, by, hMemDC2, 0, 0, SRCCOPY);
//		TransparentBlt(hdc, 200, 100, bx, by, hMemDC2,
//			0, 0, bx, by, RGB(255, 0, 255));
//		SelectObject(hMemDC2, hOldBitmap2);
//		DeleteDC(hMemDC2);
//	}
//
//	{
//		hMemDC2 = CreateCompatibleDC(hMemDC);
//		hOldBitmap = (HBITMAP)SelectObject(hMemDC2, hAniImage);
//		bx = bitTransparent.bmWidth / 16;
//		by = bitTransparent.bmHeight / 2;
//
//		int xStart = cur_Frame *bx;
//		int yStart = 0;
//		BitBlt(hdc, 0, 0, bx, by, hMemDC, 0, 0, SRCCOPY);
//		TransparentBlt(hdc, 200, 100, bx, by, hMemDC2,
//			xStart, yStart, bx, by, RGB(255, 0, 255));
//		SelectObject(hMemDC2, hOldBitmap2);
//		DeleteDC(hMemDC2);
//	}
//
//	BitBlt(hdc, 0, 0, rectView.right, rectView.bottom,
//		hMemDC, 0, 0, SRCCOPY);
//	SelectObject(hMemDC, hOldBitmap);
//
//}







