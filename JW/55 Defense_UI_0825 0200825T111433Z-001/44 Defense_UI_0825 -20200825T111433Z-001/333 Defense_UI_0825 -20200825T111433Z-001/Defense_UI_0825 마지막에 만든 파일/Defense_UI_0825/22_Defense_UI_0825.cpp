// Defense_UI_0825.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Defense_UI_0825.h"
#include "resource.h"	// 리소스에 대한 디파인 값들이 리소스 헤더에 정의되어있기 떄문
#include <vector>
using namespace std;

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

HINSTANCE g_hInstance = NULL;


static int bullet_x_pos, bullet_y_pos;
static int x, y, px, py;	//rect 구조체의 x와 y축 쓰려고 +  x1,y1은 player의 이동을 위해서 
static RECT rectView;		// 선언해야 RECT 구조체 사용가능

int enemy_x = 300, enemy_y = 150; // 적 구현을 위해서 전역변수로 i ,j를  enemy_x, enemy_y 로 바꿔주고 타이머에서도 사용하게 해줌



POINT pos;




class Bullet
{
public:
	int bbx, bby, bbr;
	RECT rect;
public:
	Bullet(int to_access_bx, int to_access_by, int to_access_br) // 생성자 (객체가 생성될떄 실행됨) >> 클래스의 인스턴스화라고 부름
	{
		bbx = to_access_bx;
		bby = to_access_by;
		bbr = to_access_br;
	}
	Bullet() {};												// 소멸자 ( 클래스가 소멸 될떄 실행)

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

vector<Bullet*> Bullet_object; // 벡터 객체 생성
vector<Bullet*> Bullet_various;



// =================벡터연습 ==================================

vector<int> vector_variable;				 // 벡터 생성
vector<int> v1(4);						// 숫자만큼 벡터생성 int형 벡터 생성 후 크기를 4로 할당(모든 벡터요소 0으로 초기화)
vector<int> v2 = { 1,2,3 };				// 벡터 생성 후 1,2,3으로 변수 값으로 초기화
vector<int> v3[] = { { 1,2 },{ 3,4 } };		// int 형 벡터 생성, 행은 가변이지만 열은 고정
vector<vector<int>> v4;					// 2차원 벡터 생성 (행 열 모두 가변)
vector<int> v5 = { 1,2,3,4,5 };			// 


//================= 벡터연습 =================================



class enemy			// 구조체 대신에 class	 // enemy 구조체 변수에다가 wm_paint에서 for문으로 그려줬던 enemy를 표현해줘야함. 그래서 wm_paint에서 호출해보자
{
private:
	int ex, ey, er;
public:
	void enemy_update();
	void draw();
};

enemy approach_enemy; // class에 접근하기 위해 객체 생성

void enemy::enemy_update()
{
	int enemy;
	if (enemy < rectView.left)	// enemy가 왼쪽 벽에 부딪히면 y축으로 한 칸 증가하고 오른쪽 방향으로 이동
	{
		y += 50;
		px += 40;
	}
	if (enemy < rectView.right)	// enemy가 오른쪽 벽에 부딪히면 y축으로 한 칸 증가하고 오른쪽 방향으로 이동
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




// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
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

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DEFENSE_UI_0825, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEFENSE_UI_0825));

    MSG msg;

    // 기본 메시지 루프입니다.
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
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
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
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

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





BOOL Ellipse(HDC hdc, const POINT& center, int radius) // Ellipse를 함수 오버로딩해서 내 맘대로 매개변수 줄이거나 늘리는거
{
	return Ellipse(hdc,
		center.x - radius, center.y - radius,
		center.x + radius, center.y + radius);
}


//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;					// 화면 영역값을 위해 필요한 dc값
	PAINTSTRUCT ps;
	HDC MemDC;					// 비트맵을 하나씩 불러오면 너무 느린속도가 되기에 미리 메모리에 올려놓고 불러오는 방법 사용

	static RECT rectView;		// 선언해야 RECT 구조체 사용가능
	HPEN newPen, oldPen;		//펜생성 등록 삭제 3가지가 모두 있어야함
	g_hInstance = hInst;	// 운영체제가 보내준 현재 프로그램의 인스턴스 객체를 전역변수로 사용하도록 받아옴

	HBITMAP MyBitmap, OldBitmap;	
	int btm_x, btm_y;
	BITMAP bit;
	static HBITMAP hBitMap_Char;	// 비트맵을 불러오기 위해서 필요한 비트맵 핸들 변수 만들고 
									// 아까 리소스에 추가한 이미지를 이 핸들변수에 불러올거임


	int radi = 15;				// paint 적 구현한 코드 위에 선언한 변수들인데 전역으로 쓰고 싶어서(timer에서도 쓰려곻)
	int enemy_number = 400;



    switch (message)
    {
	case WM_CREATE:
	{
		hBitMap_Char = (HBITMAP)LoadBitmap(g_hInstance, MAKEINTRESOURCE(IDB_BITMAP2)); // 아까 만들어준 비트맵 값을 줌
																					   // 여기 IDB_BITMAP1 는 헤더파일 Resource.h에 있음
		vEnemyv.push_back(new vEnemy(50,550,40));
		vEnemyv.push_back(new vEnemy(80, 550,40)); //40개 만들어보기
		int wx, wy, width, height;						// wx wy는 window_x window_y 임		여기서부터 
		RECT rtDesk, rtWindow;
		GetWindowRect(GetDesktopWindow(), &rtDesk);
		GetWindowRect(hWnd, &rtWindow);

		width = rtWindow.right - rtWindow.left;  // 원래 이렇게 되어있었음. width = rtWindow.right - rtWindow.left;
		height = rtWindow.bottom - rtWindow.top;

		wx = (rtDesk.right - width) / 2;
		wy = (rtDesk.bottom - height) / 2;

		MoveWindow(hWnd, wx, wy, width, height, TRUE);	// 여기까지 윈도우 모니터 가운데로 옮기는 코드

		GetClientRect(hWnd, &rectView); // 이 함수로 윈도우의 원하는 곳에 출력할 수 있음 + 경계안에서 원 이동
		px = 0, py = 0; // player 의 좌우 이동을 위해
			

		SetTimer(hWnd, 1, 200, NULL); // enemy,  적 타이머
		SetTimer(hWnd, 2, 200, NULL); // bullet, 총알 타이머
	}
	break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다.
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
		rgb(255,0,0) : 빨강 (Red)
		rgb(0,255,0) : 녹색 (Green)
		rgb(0,0,255) : 파랑 (Blue)
		rgb(192,192,192) : 회색 (Gray)
		rgb(255,255,0) : 노랑 (Yellow)
		rgb(255,0,255) : 선홍색 (Cerise)
*/
	case WM_TIMER:
	{
		switch (wParam)
		{
		case 1: // settimer의 이름이 1일떄
		{
			static bool flag = true;	// static이 없으면 오른쪽에 닿고서 계속 오른쪽 아래로 y값만 증가함 반대로 돌아가지않고

			if (flag)
			{
				enemy_x += 40;
			}
			else
			{
				enemy_x -= 40;
			}
			

			if (enemy_x + enemy_number >= rectView.right || enemy_x <= rectView.left)		// 오른쪽에 닿으면 한 칸 아래 내리기. flag이용 
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

			//	bool flag_bullet = false; // 총알이 윈도우 바깥으로  나갔는지 0,1 로 검사.



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

			for (vector<Bullet>::size_type i = 0; i < Bullet_various.size(); ++i)										//  총알 벡터,,  비트맵 그린 다음에 또 그릴려고
			{
				Bullet_various[i]->Draw_bullet(hdc);
			}
			


			
			
			SelectObject(MemDC, OldBitmap);
			DeleteObject(MyBitmap);
			DeleteDC(MemDC);
			

			//// 비트맵 먼저 출력하고서 그 위에 도형 더해서 그릴거기 때문에 비트맵 여기에 작성
			//MemDC = CreateCompatibleDC(hdc);
			//SelectObject(MemDC, hBitMap_Char);
			//BitBlt(hdc, 0, 0, 512, 384, MemDC, 0, 0, SRCCOPY); // memdc에 있는걸 hdc로 옮겨줌 SRCCOPY 영역 만큼 복사
			//DeleteObject(MemDC); // 사용 끝났기에 삭제해줌 브러쉬랑 펜이랑 똑같음

			HBRUSH hBrush, oldBrush;									// 여기서 부터
			hBrush = CreateSolidBrush(NULL);   // RGB(255, 255, 255) (RGB(0, 0, 0)
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			// 여기서 도형이나 선 그리면 선택된 브러쉬로 나옴

			//Rectangle(hdc, rectView.left, rectView.top, rectView.right, rectView.bottom);   // 윈도우 크기만큼 검정색 브러쉬로 설정함.

			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);									// 여기까지 배경색 brush 선택


			newPen = CreatePen(PS_DASH, 2, RGB(255, 0, 0)); //RGB(0,0,0)); 255 255 255면 글자만 검은색   0 0 0 이면  도형선 전부 검은색으로 표현
			oldPen = (HPEN)SelectObject(hdc, newPen);


			TextOut(hdc, 540, 20, TEXT("Devil"), 5);
			TextOut(hdc, rectView.right / 2 + 60, rectView.bottom - 40, TEXT("player"), 6);
			TextOut(hdc, rectView.left + 10, rectView.top + 50, TEXT("캐릭터 설명"), 6);
			TextOut(hdc, rectView.right - 60, rectView.top + 50, TEXT("체력바"), 3);
			TextOut(hdc, rectView.left + 250, rectView.top + 200, TEXT("enemy"), 5);
			TextOut(hdc, rectView.left + 130, rectView.bottom - 250, TEXT("1번 총알"), 5);
			//TextOut(hdc, rectView.left + 430, rectView.bottom - 250, TEXT("2번 총알"), 5);
			TextOut(hdc, rectView.left + 770, rectView.bottom - 250, TEXT("3번 총알"), 5);
			Rectangle(hdc, px + 400, py + 900, px + 500, py + 980);	// 플레이어 이동	 안되면 그냥 0부터 시	작									// player 위치		(hdc, rectView.right / 2 - 40, rectView.bottom - 80, rectView.right / 2 + 40, rectView.bottom);
			Rectangle(hdc, rectView.right / 2 - 40, rectView.top, rectView.right / 2 + 40, rectView.top + 80);			// Devil 위치
			Rectangle(hdc, rectView.left, rectView.top, rectView.left + 80, rectView.top + 40); // 캐릭터 설명
			Rectangle(hdc, rectView.right - 60, rectView.top, rectView.right, rectView.top + 40); // 체력바

			TextOut(hdc, rectView.right / 2 + 60, rectView.top + 60, TEXT("charcter +++"), 12);

			//newPen = CreatePen(PS_DOT, 2, NULL); //RGB(255,255,255)); 원래 pen 자리 pen을 흰색으로 처리하려고 TextOut함수 쓰기전에 옮겨놓음
			//oldPen = (HPEN)SelectObject(hdc, newPen);

			MoveToEx(hdc, rectView.right / 3, rectView.bottom - 100, NULL);	// 1번 총알
			LineTo(hdc, rectView.left + 100, rectView.bottom / 1.6);

			//SelectObject(hdc, oldPen);
			//DeleteObject(newPen);		// 여기에서 newpen 삭제하면 1번총알만 newpen으로 그림


			//for (int j = 0; j < 10; j++)
			//{
			//	for (int i = j * 50 + 450; i < 1100; i += 30)					// 2번 총알 
			//	{
			//		Ellipse(hdc, 500, i, 550, i + 50);
			//	}
			//}

			MoveToEx(hdc, rectView.right / 1.3, rectView.bottom - 100, NULL);
			LineTo(hdc, rectView.right - 50, rectView.bottom / 1.6);
			MoveToEx(hdc, rectView.right / 1.32, rectView.bottom - 100, NULL);	// 3번 총알  pen 삭제해서 old 다시가능
			LineTo(hdc, rectView.right - 60, rectView.bottom / 1.6);
			MoveToEx(hdc, rectView.right / 1.34, rectView.bottom - 100, NULL);
			LineTo(hdc, rectView.right - 70, rectView.bottom / 1.6);			

			SelectObject(hdc, oldPen);
			DeleteObject(newPen);		// 여기에서 newpen 삭제하면 3번총알까지 흰색 펜인 newpen으로 그렸다가 이 다음부터 쓸 선과 글자는 모두 default 값인 검정으로 나옴

			


			/*for (int i = 0; i < 10; i++)
			{
			Ellipse(hdc, i * 40 + 300, 120, i * 40 + 330, 150);			규칙성이 일정한 반복문을 또 반복하기.
			}

			for (int i = 0; i < 10; i++)
			{
			Ellipse(hdc, i * 40 + 300, 160, i * 40 + 330, 190);
			}

			for (int i = 0; i < 10; i++)
			{
			Ellipse(hdc, i * 40 + 300, 200, i * 40 + 330, 230);
			}*/


			// Rectangle(hdc, rectView.right - 70, rectView.top, rectView.right, rectView.top + 50);	// 체력바 또 그림 여기서 알 수 있는 것. 검정 배경 사각형을 그리고 같은 좌표위치에
																										// 흰색 배경 사각형을 그리면 검정 사각형은 보이지 않고 흰색만 보인다(덮어씌여짐)		
			/*for (enemy_a = 0; enemy_a < 5; enemy_a+=40)
			{
				Ellipse(hdc, enemy_a, 0, enemy_a + 40, 40);
			}*/
			
				//Ellipse(hdc,						//timer에서 호출하면 
				//	enemy_x, 0,
				//	enemy_x + 40, 40);
			
			for (int i = 0; i < enemy_number/2; i+=40)
			{
				for (int j = 0; j < enemy_number; j+=40)					// timer 이용해서 이동하는 적,, Ellipse를 for문 하나하나 계산해서
				{															// 규칙성을 찾아내서 겹치지 않게 숫자를 넣어줬음
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

			
			// 총알 그리는 것. 

			//Ellipse(hdc, bullet_x_pos + 430, bullet_y_pos + 850, bullet_x_pos + 480, bullet_y_pos + 900); // 총알  wm_timer에서 wparam==2에서 동작하게 만드는  + 900); // 총알  wm_timer에서 wparam==2에서 동작하게 만드는 

			//for (int enemy_x = 0; enemy_x < 5; enemy_x++)
			//{
			//	for (int enemy_y = 0; enemy_y < 10; enemy_y++)						// 적 구현 enemy
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
			if (px + 20 > rectView.right / 2 + 60) px -= 40; // 우선은 rectView.right /2 +60 으로 해서 줬음 이유는 정확히 모르겠으나
		}												// x1-=40해도 왼쪽으로 다시 그려주는게 보이지않고 단 -400해줬을때는 명확히 보인다
		if (wParam == VK_LEFT)
		{
			px -= 40;	// -40에서 -80하니까 중앙에서 왼쪽으로도 이동함 but 밑의 if문에서 x1 +400하니  x1-=40 해도 동작함
			if (px + 400< rectView.left) px += 40;	// if(x1-20)에서  if(x1 + 100) 주니까 왼쪽으로 더 움직일 수 있었음
		}
		if (wParam == VK_SPACE)
		{
			Bullet_various.push_back(new Bullet(px + 450, 900, 10));
			//bullet_y_pos -= 40;
		}


		InvalidateRgn(hWnd, NULL, true);	// 꼭 이걸해줘야 움직일 수 있음
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

// 정보 대화 상자의 메시지 처리기입니다.
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







// ------------------------------------------------------------------------------------------- 비트맵 ---------------------------


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
//		hbackImage = (HBITMAP)LoadImage(NULL, TEXT("images/우주배경.bmp"),
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







