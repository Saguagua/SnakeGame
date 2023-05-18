#include <windows.h>  // Windows API�� ���
#include <tchar.h>    // ��ũ�� TCHAR�� ������
#include <stdlib.h>
#include <string.h>

//hInstance : ���� �ν��Ͻ��� ���� �ڵ�
//hPrevInstance : ���ø����̼��� ���� �ν��Ͻ��� ���� �ڵ�
//lpCmdLine : ���α׷� �̸��� ������ ���ø����̼ǿ� ���� �����
// nCmdShow : â�� ǥ���ϴ� ����� ����
// �ϴ� �� : ���ø����̼� �ʱ�ȭ, ���� â ǥ��, �޽��� �˻� �� ����ġ ������ �Է�.
// WM_QUIT �޽����� ������ �޽��� ������ �����Ѵ�. �� �������� WinMain�� ���ø����̼��� �����ϰ�,
// WM_QUIT �޽����� wParam �Ű� ������ ���Ե� ���� ���� ��ȯ�Ѵ�.

static TCHAR szWindowClass[] = _T("DeskTop");
static TCHAR szTitle[] = _T("Widows Desktop Guided");

HINSTANCE hInst;



// �̺�Ʈ�� �߻��� �� ���ø����̼��� Windows�� �����ϴ� �޽����� ó���ϴ� �ڵ� �ۼ�
// ����ڰ� ���ø����̼ǿ��� Ȯ�� ���߸� ���� �� Windows ����ڿ��� �޽����� ������ �۾��� �����ϴ� �ڵ�
// ���ø����̼ǰ� ���õ� �̺�Ʈ�� ó���ϴ� ��
// â ���ν������ �Ҹ���.


LRESULT CALLBACK WnProc(
	_In_ HWND hWnd,
	_In_ UINT message,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
)
{
	PAINTSTRUCT ps;
	HDC hdc;        //â�� Ŭ���̾�Ʈ ������ �׸� �׸��� �ڵ�
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

	//������ â Ŭ������ �����ϴ� �� ����ϴ� ����ü
	WNDCLASSEX wcex;

	// UINT, �ش� ����ü�� ũ��
	wcex.cbSize = sizeof(WNDCLASSEX);
	// UINT, Ŭ���� ��Ÿ��
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	// IpfnWndProc, â ���ν����� ���� ������
	wcex.lpfnWndProc = WnProc;
	// int, â Ŭ���� ���� ������ �Ҵ��� �߰� ����Ʈ ��, �ý����� ����Ʈ�� 0���� �ʱ�ȭ�Ѵ�.
	wcex.cbClsExtra = 0;
	// int, â �ν��Ͻ� ������ �Ҵ��� �߰� ����Ʈ ��, ���� ���� 0���� �ʱ�ȭ
	wcex.cbWndExtra = 0;
	// HINSTANCE, â ���ν����� ���Ե� �ν��Ͻ��� ���� �ڵ�
	wcex.hInstance = hInstance;
	// HICON, Ŭ���� �����ܿ� ���� �ڵ�, NULL�� ��� �⺻ �������� ����
	wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
	// HCURSOR, Ŭ���� Ŀ���� ���� �ڵ�, 
	//NULL�� ��� ���콺�� ���ø����̼��� â���� �̵��� �� ���� Ŀ���� ����� ��������� �����ؾ� �Ѵ�.
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	// HBRUSH, Ŭ���� ��� �귯�ÿ� ���� �ڵ�
	// ����� �׸��� �� ����� �귯�ÿ� ���� �ڵ� �Ǵ� �� ��
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	// LPCTSTR, ���ҽ� ���Ͽ� ǥ�õ� �� Ŭ���� �޴��� ���ҽ� �̸��� �����ϴ� null�� ������ ���ڿ��� ���� ������
	wcex.lpszMenuName = NULL;
	// LPCTSTR, null�� ������ ���ڿ��� ���� �����Ͱų� �� �� �̴�.
	wcex.lpszClassName = szWindowClass;
	// HICON, â Ŭ�����Ϳ���� ���� �����ܿ� ���� �ڵ�
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);
	

	// � ü���� ���ο� â Ŭ������ ����ϴ� ������ �Ѵ�.
	// ��ϵ� â Ŭ������ CreateWindowEx �Լ��� ������ �� �ִ�.
	//��ȯ �� ATOM or 0
	// �ڿ� A�� ���� RegisterClassExA �� wcex�� ANSI�� ����Ѵٰ� �ý��ۿ� �˸���.
	// W�� ���̸� �����ڵ��.
	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed"),
			_T("Windows Desktop Guided Tour"),
			NULL);

		return 1;
	}

	hInst = hInstance;

	// ��ȯ�� : �� â�� ���� �ڵ� �Ǵ� NULL
	HWND hWnd = CreateWindowEx(
	WS_EX_OVERLAPPEDWINDOW,           // Ȯ�� â ��Ÿ��
		szWindowClass,                // 
		szTitle,                      // â �̸�
		WS_OVERLAPPEDWINDOW,          // �����Ǵ� â�� ��Ÿ��
		CW_USEDEFAULT, CW_USEDEFAULT, // â�� �ʱ� ����, ���� ��ġ
		500, 100,                     // â�� �ʺ�, ����
		NULL,                         // â�� �θ� ���� �����ڿ� ���� �ڵ�
		NULL,                         // �޴��� ���� �ڵ� �Ǵ� â ��Ÿ�Ͽ� ���� �ڽ� â �ĺ��� ����
		hInstance,                    // â�� ������ ����� instance�� ���� �ڵ�
		NULL                          // 
	);

	if (!hWnd)
	{
		MessageBox(NULL, _T("Call to CreateWindowEx failed"),
			_T("Windows Desktop Guided"),
			NULL);

		return 1;
	}

	ShowWindow(hWnd, nCmdShow);  //â�� ǥ�õǵ���
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

