#include "Framework.h"
#include "MenuScene.h"

MenuScene::MenuScene()
{
}

MenuScene::~MenuScene()
{
}

void MenuScene::Update()
{
	if (Input::Get()->IsKeyDown(VK_F1))
	{
		SCENE->ChangeScene("Game1");
	}

    if (Input::Get()->IsKeyDown(VK_F2))
    {
        SCENE->ChangeScene("Game2");
    }
    
    if (Input::Get()->IsKeyDown(VK_F3))
    {
        SCENE->ChangeScene("Game3");
    }

	if (Input::Get()->IsKeyDown(VK_F4))
	{
		SCENE->ChangeScene("Title");
	}

	if (Input::Get()->IsKeyDown(VK_LBUTTON))  // 마우스 왼쪽 버튼 눌렸는지
	{
        
        GetCursorPos(&pt);
        ScreenToClient(hWnd, &pt);  // 화면 좌표 → 윈도우 좌표

        if (pt.y < SCREEN_HEIGHT / 2) 
        {
            SCENE->ChangeScene("Game1");
        }
        else  
        {
            PostQuitMessage(0);  
        }
	}
}

void MenuScene::Render(HDC hdc)
{
    wstring line1 = L"=======================";
    wstring line2 = L"Game Start";
    wstring line3 = L"=======================";
    wstring line4 = L"Exit Game";
    wstring line5 = L"=======================";

    int lineHeight = 30;
    int centerY = SCREEN_HEIGHT / 2 - lineHeight * 2;


    // Line 1
    rect = { 0, centerY, SCREEN_WIDTH, centerY + lineHeight };
    DrawText(hdc, line1.c_str(), -1, &rect, DT_CENTER);

    // Line 2
    rect.top += lineHeight;
    rect.bottom += lineHeight;
    GetTextExtentPoint32(hdc, line2.c_str(), line2.length(), &textSize);
   
    DrawText(hdc, line2.c_str(), -1, &rect, DT_CENTER);

    // Line 3
    rect.top += lineHeight;
    rect.bottom += lineHeight;
    DrawText(hdc, line3.c_str(), -1, &rect, DT_CENTER);

    // Line 4
    rect.top += lineHeight;
    rect.bottom += lineHeight;
    DrawText(hdc, line4.c_str(), -1, &rect, DT_CENTER);

    // Line 5
    rect.top += lineHeight;
    rect.bottom += lineHeight;
    DrawText(hdc, line5.c_str(), -1, &rect, DT_CENTER);
}