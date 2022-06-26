// 122Games.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "122Games.h"

#include "Box.h"
#include "CppScreen.h"
#include "Game.h"
#include "Joystick.h"


constexpr auto MAX_LOADSTRING = 100;

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

CppScreen _cppScreen;
Box _box;
bool _timersAreSet = false;

static const int IDT_TIMER1 = 666;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    _box.setup();

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY122GAMES, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY122GAMES));

    MSG msg;

    // Main message loop:
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
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY122GAMES));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY122GAMES);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    _box.loop();
    _box.GetGames()->GetActiveGame()->Play();

    if (!_timersAreSet)
    {
        SetTimer(hWnd,             // handle to main window 
            IDT_TIMER1,            // timer identifier 
            20,                    // milli second interval 
            (TIMERPROC)NULL);      // no timer callback 
        _timersAreSet = true;
    }

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
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

    case WM_PAINT:
        {
            if (!_box.GetUi()->IsInitialized())
            {
                break;
            }

            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            
            Game* activeGame = _box.GetGames()->GetActiveGame();
            if (activeGame != nullptr)
            {
               _cppScreen.Draw(_box.GetUi(), hdc, hWnd);
            }
            
            EndPaint(hWnd, &ps);
        }
        break;

    case WM_TIMER:
        switch (wParam)
        {
        case IDT_TIMER1:
            if (!_box.GetUi()->IsInitialized())
            {
                break;
            }
                
            Game* activeGame = _box.GetGames()->GetActiveGame();

            if (activeGame != nullptr)
            {
                activeGame->Play();
                RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE);
            }
            
            return 0;
        }
        break;
    
    case WM_KEYDOWN:
        {
            if (!_box.GetUi()->IsInitialized())
            {
                break;
            }

            Game* activeGame = _box.GetGames()->GetActiveGame();
            if (activeGame == nullptr)
            {
                return 0;
            }

            switch (wParam)
            {
            case VK_NUMPAD0:
                activeGame->HandleButton(Game::EButton::Select);
                break;

            case VK_NUMPAD1:
                activeGame->HandleDirection(JoyStick::EDirection::LeftDown);
                break;

            case VK_NUMPAD2:
                activeGame->HandleDirection(JoyStick::EDirection::Down);
                break;

            case VK_NUMPAD3:
                activeGame->HandleDirection(JoyStick::EDirection::RightDown);
                break;

            case VK_NUMPAD4:
                activeGame->HandleDirection(JoyStick::EDirection::Left);
                break;

            case VK_NUMPAD5:
                activeGame->HandleDirection(JoyStick::EDirection::Center);
                break;

            case VK_NUMPAD6:
                activeGame->HandleDirection(JoyStick::EDirection::Right);
                break;

            case VK_NUMPAD7:
                activeGame->HandleDirection(JoyStick::EDirection::LeftUp);
                break;

            case VK_NUMPAD8:
                activeGame->HandleDirection(JoyStick::EDirection::Up);
                break;

            case VK_NUMPAD9:
                activeGame->HandleDirection(JoyStick::EDirection::RightUp);
                break;

            default:
                // Ignore other keys
                break;
            }
        }
        break;

    case WM_KEYUP:
    {
        if (!_box.GetUi()->IsInitialized())
        {
            break;
        }

        Game* activeGame = _box.GetGames()->GetActiveGame();
        if (activeGame == nullptr)
        {
            return 0;
        }

        switch (wParam)
        {
        case '1': // Fall through
        case '2': // Fall through
        case '3': // Fall through
        case '4': // Fall through
        case '5': // Fall through
        case '6': // Fall through
        case '7': // Fall through
        case '8': // Fall through
        case '9': // Fall through
            activeGame->HandleDirection(JoyStick::EDirection::Center);
            break;

        default:
            // Ignore other keys
            break;
        }
        break;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
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
