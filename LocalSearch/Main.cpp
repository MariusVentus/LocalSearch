#include <windows.h>
#include <string>
#include "SettingsHandler.h"
#include "DatabaseEngine.h"

//Definitions
#define IDC_MAIN_EDIT 101
#define ID_FILE_EXIT 9001
#define ID_ABOUT 9002
#define ID_HELP 9003
#define ID_OPEN_SETTINGS 9004
#define ID_IN_PROGRESS 9020

//Globals
const char g_szClassName[] = "LocalSearchMain";
const char g_WindowTitle[] = "Local Search V0.0.0";
HWND hMainWindow = { 0 };
HWND hStatusBar;
std::string g_StatusStates[5] = { "Initializing...","Ready","Searching...","Training...","Rebuilding..." };
SettingsHandler g_Settings;
DatabaseEngine g_Engine(g_Settings);

//Forward Declarations
bool RegisterMainWindow(HINSTANCE hInstance);
bool CreateMainWindow(HINSTANCE hInstance);
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void AddMainMenu(HWND hwnd);
void AddMainControls(HWND hwnd);
void InitializeContent(void);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	MSG Msg;

	if (!RegisterMainWindow(hInstance)) {
		return 0;
	}

	if (!CreateMainWindow(hInstance)) {
		return 0;
	}

	ShowWindow(hMainWindow, nCmdShow);
	UpdateWindow(hMainWindow);

	InitializeContent();

	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}


bool RegisterMainWindow(HINSTANCE hInstance)
{
	WNDCLASSEX wc = { 0 };

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = CreateSolidBrush(RGB(1, 22, 53));
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_szClassName;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return false;
	}
	else {
		return true;
	}
}

bool CreateMainWindow(HINSTANCE hInstance)
{
	hMainWindow = CreateWindowEx(WS_EX_CLIENTEDGE, g_szClassName, g_WindowTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 700, 300, NULL, NULL, hInstance, NULL);

	if (hMainWindow == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return false;
	}
	else {
		return true;
	}
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		AddMainMenu(hwnd);
		AddMainControls(hwnd);
		break;
	case WM_COMMAND:
		switch (wParam) {
		case ID_FILE_EXIT:
			PostQuitMessage(0);
			break;
		case ID_OPEN_SETTINGS:
			ShellExecute(hwnd, "open", g_Settings.GetSettingsFileLocation().c_str(), NULL, NULL, SW_SHOW);
			break;
		case ID_ABOUT:
			MessageBox(NULL, "Just a quick psuedo-search engine, searching a \"database\" pulled from a text file.\nLearns and incorporates from user feedback.\n\n-Marius Ventus", "About", MB_OK | MB_ICONINFORMATION);
			break;
		case ID_HELP:
			MessageBox(NULL, "No help, only Zuul.\n\nOr maybe the Readme.", "Halp", MB_OK | MB_ICONINFORMATION);
			break;
		case ID_IN_PROGRESS:
			MessageBox(NULL, "Apologies, this feature is under construction.", "Under Construction", MB_OK | MB_ICONEXCLAMATION);
			break;
		}
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

void AddMainMenu(HWND hwnd)
{
	HMENU hMenu, hFileMenu;
	hMenu = CreateMenu();
	//File Menu
	hFileMenu = CreatePopupMenu();
	AppendMenu(hFileMenu, MF_STRING, ID_OPEN_SETTINGS, "Settings");
	AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hFileMenu, MF_STRING, ID_FILE_EXIT, "Exit");
	AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hFileMenu, "File");

	//Remaining Main Menu Items1e1e1e
	AppendMenu(hMenu, MF_STRING, ID_ABOUT, "About");
	AppendMenu(hMenu, MF_STRING, ID_HELP, "Help");

	SetMenu(hwnd, hMenu);
}

void AddMainControls(HWND hwnd)
{
	//Notes
	CreateWindowEx(NULL, "STATIC", " Status:", WS_CHILD | WS_VISIBLE,
		0, 0, 55, 25, hwnd, NULL, GetModuleHandle(NULL), NULL);
	hStatusBar = CreateWindowEx(NULL, "STATIC", g_StatusStates[0].c_str(), WS_CHILD | WS_VISIBLE, 
		55, 0, 100, 25, hwnd, NULL, GetModuleHandle(NULL), NULL);

}

void InitializeContent(void)
{
	g_Engine.InitializeDB();
	SetWindowText(hStatusBar, g_StatusStates[1].c_str());
}
