#define UNICODE
#include<windows.h>
#include<iostream>

LRESULT CALLBACK Windowproc(HWND hwnd,UINT uMgs, WPARAM wpra, LPARAM lapara){
    switch (uMgs)
    {
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd,uMgs,wpra,lapara);
}


class Window{
public:
    Window(): m_hInstance(GetModuleHandle(nullptr)){
        const wchar_t* class_name = L"test windows class";
        WNDCLASS wndclass = {};
        wndclass.lpszClassName = class_name;
        wndclass.hInstance = m_hInstance;
        wndclass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
        wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
        wndclass.lpfnWndProc = Windowproc;

        RegisterClass(&wndclass);

        DWORD style = WS_CAPTION | WS_MAXIMIZEBOX | WS_SYSMENU | WS_BORDER | WS_VSCROLL | WS_CLIPCHILDREN;

        RECT rect;
        rect.left=250;
        rect.top=250;
        rect.right = rect.left + 500;
        rect.bottom = rect.bottom + 500;

        AdjustWindowRect(&rect,style,false);

        m_hWnd = CreateWindowEx(
            0,
            class_name,
            L"Tile",
            style,
            rect.left,
            rect.top,
            500,500,
            NULL,
            NULL,
            m_hInstance,
            NULL
        );

        ShowWindow(m_hWnd,SW_SHOW);
    }
    ~Window() {
        const wchar_t* class_name = L"test windows class";
        UnregisterClass(class_name,m_hInstance);
    };
    Window(const Window&) = delete;
    Window& operator = (const Window) = delete;

    bool process(){
        MSG msg = {};
        while (PeekMessage(&msg,nullptr,0u,0u,PM_REMOVE))
        {
            if(msg.message == WM_QUIT){
                return false;
            }
            std::cout<<msg.message<<"\n";
            TranslateMessage(&msg);
            std::wcout<<SendMessage(m_hWnd,msg.message,0,0)<<"\n";
            DispatchMessage(&msg);
        }
        

        return true;
    }

private:
    HINSTANCE m_hInstance;
    HWND m_hWnd;

};

int main(){
    std::cout<<"create";

    Window *test = new Window();
    bool running = true;
    while (running)
    {  
        if(!test->process()){
            std::cout<<"Closing window";
            running = false;
        }
        Sleep(10);
    }
    delete test;
    return 0;
}