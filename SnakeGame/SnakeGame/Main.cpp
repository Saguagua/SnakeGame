#include <windows.h>  // Windows API를 사용
#include <tchar.h>    // 매크로 TCHAR을 가져옴
#include <stdlib.h>
#include <string.h>

//hInstance : 현재 인스턴스에 대한 핸들
//hPrevInstance : 애플리케이션의 이전 인스턴스에 대한 핸들
//lpCmdLine : 프로그램 이름을 제외한 애플리케이션에 대한 명령줄
// nCmdShow : 창을 표시하는 방법을 제어
// 하는 일 : 애플리케이션 초기화, 메인 창 표시, 메시지 검색 및 디스패치 루프를 입력.
// WM_QUIT 메시지를 받으면 메시지 루프를 종료한다. 이 시점에서 WinMain이 애플리케이션을 종료하고,
// WM_QUIT 메시지의 wParam 매개 변수에 포함된 종료 값을 반환한다.

static TCHAR szWindowClass[] = _T("DeskTop");
static TCHAR szTitle[] = _T("Widows Desktop Guided");

HINSTANCE hInst;



// 이벤트가 발생할 때 애플리케이션이 Windows에 수신하는 메시지를 처리하는 코드 작성
// 사용자가 애플리케이션에서 확인 단추를 누를 대 Windows 사용자에게 메시지를 보내고 작업을 수행하는 코드
// 애플리케이션과 관련된 이벤트를 처리하는 곳
// 창 프로시저라고 불린다.


LRESULT CALLBACK WnProc(
	_In_ HWND hWnd,
	_In_ UINT message,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
)
{
	PAINTSTRUCT ps;
	HDC hdc;        //창의 클라이언트 영역에 그림 그리는 핸들
	TCHAR greeting[] = _T("Hello!");

	switch (message)
	{
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);

		TextOut(hdc, 5, 5, greeting, _tcslen(greeting));
		EndPaint(hWnd, &ps);
		break;
	}

	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
}



int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR IpCmdLine,
	_In_ int nCmdShow
)
{

	//윈도우 창 클래스를 정의하는 데 사용하는 구조체
	WNDCLASSEX wcex;

	// UINT, 해당 구조체의 크기
	wcex.cbSize = sizeof(WNDCLASSEX);
	// UINT, 클래스 스타일
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	// IpfnWndProc, 창 프로시저에 대한 포인터
	wcex.lpfnWndProc = WnProc;
	// int, 창 클래스 구조 다음에 할당할 추가 바이트 수, 시스템은 바이트를 0으로 초기화한다.
	wcex.cbClsExtra = 0;
	// int, 창 인스턴스 다음에 할당할 추가 바이트 수, 위와 같이 0으로 초기화
	wcex.cbWndExtra = 0;
	// HINSTANCE, 창 프로시저가 포함된 인스턴스에 대한 핸들
	wcex.hInstance = hInstance;
	// HICON, 클래스 아이콘에 대한 핸들, NULL인 경우 기본 아이콘을 제공
	wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
	// HCURSOR, 클래스 커서에 대한 핸들, 
	//NULL인 경우 마우스가 애플리케이션의 창으로 이동할 때 마다 커서의 모양을 명시적으로 설정해야 한다.
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	// HBRUSH, 클래스 배경 브러시에 대한 핸들
	// 배경을 그리는 데 사용할 브러시에 대한 핸들 또는 색 값
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	// LPCTSTR, 리소스 파일에 표시될 때 클래스 메뉴의 리소스 이름을 지정하는 null로 끝나는 문자열에 대한 포인터
	wcex.lpszMenuName = NULL;
	// LPCTSTR, null로 끝나는 문자열에 대한 포인터거나 원 자 이다.
	wcex.lpszClassName = szWindowClass;
	// HICON, 창 클래스와연결된 작은 아이콘에 대한 핸들
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);
	

	// 운영 체제에 새로운 창 클래스를 등록하는 역할을 한다.
	// 등록된 창 클래스는 CreateWindowEx 함수로 생성할 수 있다.
	//반환 값 ATOM or 0
	// 뒤에 A를 붙인 RegisterClassExA 는 wcex가 ANSI를 사용한다고 시스템에 알린다.
	// W를 붙이면 유니코드다.
	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed"),
			_T("Windows Desktop Guided Tour"),
			NULL);

		return 1;
	}

	hInst = hInstance;

	// 반환값 : 새 창에 대한 핸들 또는 NULL
	HWND hWnd = CreateWindowEx(
	WS_EX_OVERLAPPEDWINDOW,           // 확장 창 스타일
		szWindowClass,                // 
		szTitle,                      // 창 이름
		WS_OVERLAPPEDWINDOW,          // 생성되는 창의 스타일
		CW_USEDEFAULT, CW_USEDEFAULT, // 창의 초기 가로, 세로 위치
		500, 100,                     // 창의 너비, 높이
		NULL,                         // 창의 부모 도는 소유자에 대한 핸들
		NULL,                         // 메뉴에 대한 핸들 또는 창 스타일에 따라 자식 창 식별자 지정
		hInstance,                    // 창과 연결할 모듈의 instance에 대한 핸들
		NULL                          // 
	);

	if (!hWnd)
	{
		MessageBox(NULL, _T("Call to CreateWindowEx failed"),
			_T("Windows Desktop Guided"),
			NULL);

		return 1;
	}

	ShowWindow(hWnd, nCmdShow);  //창이 표시되도록
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

