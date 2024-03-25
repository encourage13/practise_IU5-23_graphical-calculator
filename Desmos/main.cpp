#include "Logo.h"
#include "Irr.h"
#include "Indct.h"
#include "Trig.h"
#include "Degree.h"

#include "framework.h"
#include "WindowsProject2.h"

#define IDC_STATIC_PANEL 101
#define IDC_EDIT_TEXT 102
#define IDC_BUTTON_DRAW 103

#include <windows.h>

bool shouldDrawGraph = false;

int g_scale = 50; // начальный масштаб: единичный отрезок = 50 пикселей

// Индикатор того, что перемещение активно
bool g_isDragging = false;
// Текущее положение центра координат
POINT g_center = { 0, 0 };
// Начальная точка перемещения
POINT g_dragStart = { 0, 0 };

// Прототип функции обработчика сообщений
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void DrawGraph(HDC hdc, const RECT& rect, int scale)
{
    int centerX = g_center.x;
    int centerY = g_center.y;

    HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0)); // Красное перо для графика
    HGDIOBJ hOldPen = SelectObject(hdc, hPen);

    MoveToEx(hdc, 0, centerY, NULL);
    for (int x = -centerX; x <= centerX; x += 1) {
        int graphX = centerX + x * scale;
        int graphY = centerY - x * scale;
        if (x == -centerX) {
            MoveToEx(hdc, graphX, graphY, NULL);
        }
        else {
            LineTo(hdc, graphX, graphY);
        }
    }

    SelectObject(hdc, hOldPen);
    DeleteObject(hPen);
}


void DrawGridAndAxes(HDC hdc, const RECT& rect, int scale)
{
    int centerX = g_center.x;
    int centerY = g_center.y;

    // Рисуем сетку
    HPEN hPenGrid = CreatePen(PS_SOLID, 1, RGB(180, 180, 180)); // Серое перо для сетки
    SelectObject(hdc, hPenGrid);
    for (int x = centerX % scale; x < rect.right; x += scale) {
        MoveToEx(hdc, x, 0, NULL);
        LineTo(hdc, x, rect.bottom);
    }
    for (int y = centerY % scale; y < rect.bottom; y += scale) {
        MoveToEx(hdc, 0, y, NULL);
        LineTo(hdc, rect.right, y);
    }
    DeleteObject(hPenGrid);

    // Рисуем координатные оси красным цветом
    HPEN hPenAxes = CreatePen(PS_SOLID, 2, RGB(255, 255, 255)); // Красное перо для осей
    SelectObject(hdc, hPenAxes);
    // Ось X
    MoveToEx(hdc, 0, centerY, NULL);
    LineTo(hdc, rect.right, centerY);
    // Ось Y
    MoveToEx(hdc, centerX, 0, NULL);
    LineTo(hdc, centerX, rect.bottom);
    DeleteObject(hPenAxes);
}




// Имя класса окна
LPCWSTR szClassName = L"MyWindowClass";

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
    HWND hwnd;               // Дескриптор окна
    MSG messages;            // Сообщения для приложения
    WNDCLASSEX wincl;        // Структура для класса окна

    // Определение класса окна
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      // Функция обработчика сообщений
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof(WNDCLASSEX);

    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 // Нет меню
    wincl.cbClsExtra = 0;                      // Нет дополнительных данных класса
    wincl.cbWndExtra = 0;                      // Нет дополнительных данных окна
    wincl.hbrBackground = (HBRUSH)COLOR_BACKGROUND;

    if (!RegisterClassEx(&wincl)) return 0;

    // Создание окна
    hwnd = CreateWindowEx(
        0,                   // Расширенный стиль окна
        szClassName,         // Имя класса окна
        L"Des/mos",   // Заголовок окна
        WS_OVERLAPPEDWINDOW, // Стиль окна
        CW_USEDEFAULT,       // Позиция по X
        CW_USEDEFAULT,       // Позиция по Y
        GetSystemMetrics(SM_CXSCREEN) / 2,                 // Ширина окна
        GetSystemMetrics(SM_CYSCREEN) / 2,                 // Высота окна
        HWND_DESKTOP,        // Родительское окно
        NULL,                // Нет меню
        hThisInstance,       // Дескриптор экземпляра
        NULL                 // Нет данных создания окна
    );

    ShowWindow(hwnd, nCmdShow);

    // Цикл обработки сообщений
    while (GetMessage(&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }

    return messages.wParam;
}

// Функция обработчика сообщений
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  // Тип сообщения
    {
    case WM_MOUSEWHEEL:
    {
        // Изменение масштаба сетки
        int zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
        if (zDelta > 0) // Колесо вверх, увеличиваем масштаб
        {
            g_scale += 10;
        }
        else if (zDelta < 0 && g_scale > 10) // Колесо вниз, уменьшаем масштаб, но не менее 10 пикселей на единицу
        {
            g_scale -= 10;
        }

        // Запрос на перерисовку окна с новым масштабом
        InvalidateRect(hwnd, NULL, TRUE);
        UpdateWindow(hwnd);
        return 0;
    }
    case WM_SIZE:
    {
        // Вычисляем новый центр после изменения размера окна
        int width = LOWORD(lParam);  // Новая ширина окна
        int height = HIWORD(lParam); // Новая высота окна
        g_center.x = width / 2;
        g_center.y = height / 2;

        // Перерисовываем окно с новым центром
        InvalidateRect(hwnd, NULL, TRUE);
    }
    break;
    case WM_CREATE:
    {
        // Создаем статический контроль, который будет служить фоном
        CreateWindow(TEXT("STATIC"), NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER | SS_CENTERIMAGE,
            10, 10, 380, 40, hwnd, (HMENU)IDC_STATIC_PANEL, GetModuleHandle(NULL), NULL);

        // Создаем текстовое поле для ввода
        CreateWindow(TEXT("EDIT"), TEXT(""), WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
            20, 20, 160, 20, hwnd, (HMENU)IDC_EDIT_TEXT, GetModuleHandle(NULL), NULL);

        // Создаем кнопку для построения графика
        CreateWindow(TEXT("BUTTON"), TEXT("Построить график"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
            190, 20, 180, 20, hwnd, (HMENU)IDC_BUTTON_DRAW, GetModuleHandle(NULL), NULL);
        RECT rect;
        GetClientRect(hwnd, &rect);
        g_center.x = (rect.right - rect.left) / 2;
        g_center.y = (rect.bottom - rect.top) / 2;
    }
    break;
    case WM_CTLCOLORSTATIC:
    {
        HDC hdcStatic = (HDC)wParam;
        SetTextColor(hdcStatic, RGB(0, 0, 0)); // Устанавливаем цвет текста
        SetBkMode(hdcStatic, TRANSPARENT); // Фон будет прозрачным

        // Возвращаем кисть с нужным фоном
        static HBRUSH hBrushStatic = CreateSolidBrush(RGB(255, 255, 255)); // Белый фон
        return (INT_PTR)hBrushStatic;
    }
    break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON_DRAW: // Предполагаем, что это идентификатор вашей кнопки
            shouldDrawGraph = true; // Указываем, что пора рисовать график
            InvalidateRect(hwnd, NULL, TRUE); // Запрос на перерисовку окна
            UpdateWindow(hwnd); // Немедленно перерисовываем окно
            break;
        }
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        RECT rect;
        GetClientRect(hwnd, &rect);

        DrawGridAndAxes(hdc, rect, g_scale);
        if (shouldDrawGraph)  DrawGraph(hdc, rect, g_scale);
        EndPaint(hwnd, &ps);
    }
    break;
    case WM_LBUTTONDOWN:
    {
        // Запоминаем начало перемещения
        g_isDragging = true;
        g_dragStart.x = LOWORD(lParam);
        g_dragStart.y = HIWORD(lParam);
        SetCapture(hwnd); // Захватываем мышь
    }
    break;

    case WM_MOUSEMOVE:
    {
        if (g_isDragging)
        {
            // Вычисляем новое положение центра
            int dx = LOWORD(lParam) - g_dragStart.x;
            int dy = HIWORD(lParam) - g_dragStart.y;

            // Обновляем начальную точку для следующего перемещения
            g_dragStart.x = LOWORD(lParam);
            g_dragStart.y = HIWORD(lParam);

            g_center.x += dx;
            g_center.y += dy;

            // Перерисовываем окно с новым положением центра
            InvalidateRect(hwnd, NULL, TRUE);
        }
    }
    break;

    case WM_LBUTTONUP:
    {
        if (g_isDragging)
        {
            g_isDragging = false;
            ReleaseCapture(); // Освобождаем захват мыши
        }
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}
