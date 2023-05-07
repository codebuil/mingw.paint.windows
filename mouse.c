#include <windows.h>
 HDC hdc;
    PAINTSTRUCT ps;
    RECT rect;
    int iiii=0;
// Ponto para armPOINT ptLastClickazenar as coordenadas do último clique do mouse
POINT ptLastClick[500];
// Protótipo da função de tratamento de mensagens
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);




// Função principal
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Definir as informações da janela
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "MyWindowClass";
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    RegisterClassEx(&wcex);
    
    // Criar a janela
    HWND hWnd = CreateWindow("MyWindowClass", "Minha Janela", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, hInstance, NULL);
    if (!hWnd)
    {
        return -1;
    }

    // Mostrar a janela
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // Loop de mensagens
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

// Função de tratamento de mensagens
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int n=0;
    switch (message)
    {
    case WM_LBUTTONDOWN:
        // Obter as coordenadas do clique do mouse
        ptLastClick[iiii].x = LOWORD(lParam);
        ptLastClick[iiii].y = HIWORD(lParam);
        

        // Redesenha a janela para exibir o círculo
        InvalidateRect(hWnd, NULL, TRUE);
        iiii++;
        break;

    
case WM_PAINT:
            
            hdc = BeginPaint(hWnd, &ps);
            
            // Define a cor de fundo da janela para azul
            HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255));
            FillRect(hdc, &ps.rcPaint, hBrush);
            
            DeleteObject(hBrush);
            
            // Define a cor das linhas para branco
            HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
            SelectObject(hdc, hPen);
            for(n=0;n<iiii;n++){
             // Desenha as linhas com base nas coordenadas fornecidas
                Ellipse(hdc, ptLastClick[n].x - 5, ptLastClick[n].y - 5, ptLastClick[n].x + 5, ptLastClick[n].y + 5);
            }
            // Libera os recursos utilizados
            DeleteObject(hPen);
            EndPaint(hWnd, &ps);
            break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}
