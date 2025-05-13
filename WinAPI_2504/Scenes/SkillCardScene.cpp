#include "Framework.h"
#include "SkillCardScene.h"
#include "Objects/Player.h"

SkillCardScene::SkillCardScene()
{
    // ���� ī��
    Card left;
    left.rect = { 60, 300, SCREEN_WIDTH / 2, SCREEN_HEIGHT - 300 };
    left.name = "Triple Shot";
    left.ability = PlayerAbility::TripleShot;
    cards.push_back(left);

    // ������ ī��
    Card right;
    right.rect = { SCREEN_WIDTH / 2 + 10, 300, SCREEN_WIDTH - 50, SCREEN_HEIGHT - 300 };
    right.name = "Double Shot";
    right.ability = PlayerAbility::DoubleShot;

    cards.push_back(right);
}

SkillCardScene::~SkillCardScene()
{
}

void SkillCardScene::Update()
{
    if (!isActive) return;

    CheckClick();
}

void SkillCardScene::Render(HDC hdc)
{
    if (!isActive) return;

    HBRUSH brush = CreateSolidBrush(RGB(200, 200, 255));
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);

    for (const Card& card : cards)
    {
        Rectangle(hdc, card.rect.left, card.rect.top, card.rect.right, card.rect.bottom);

        // �ؽ�Ʈ
        SetBkMode(hdc, TRANSPARENT);
        DrawTextA(hdc, card.name.c_str(), -1, (LPRECT)&card.rect, DT_CENTER);
    }

    SelectObject(hdc, oldBrush);
    DeleteObject(brush);
}

void SkillCardScene::Show(Player* p)
{
    player = p;
    isActive = true;
}

void SkillCardScene::Hide()
{
    isActive = false;
}

void SkillCardScene::CheckClick()
{
    if (Input::Get()->IsKeyDown(VK_LBUTTON))
    {
        POINT pt;
        GetCursorPos(&pt);
        ScreenToClient(hWnd, &pt); // ���콺 ��ǥ ��ȯ

        if (pt.x < SCREEN_WIDTH / 2)
        {
            // ���� ī�� Ŭ��
            if (player)
                player->SetAbility(cards[0].ability); // ���� ī���� �ɷ� ����

            Hide();
        }
        else
        {
            // ������ ī�� Ŭ��
            if (player)
                player->SetAbility(cards[1].ability); // ������ ī���� �ɷ� ����

            Hide();
        }
    }

}
