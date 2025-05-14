#include "Framework.h"
#include "SkillCardScene.h"
#include "Objects/Player.h"


SkillCardScene::SkillCardScene()
{
    vector<PlayerAbility> allAbilities = {
        PlayerAbility::TripleShot,
        PlayerAbility::DoubleShot,
        PlayerAbility::RLShot,
        PlayerAbility::BackShot,
        PlayerAbility::X2Shot
    };

    shuffle(allAbilities.begin(), allAbilities.end(), default_random_engine((unsigned int)time(nullptr)));

    PlayerAbility first = allAbilities[0];
    PlayerAbility second = allAbilities[1];

    Card left;
    left.rect = { 60, 300, SCREEN_WIDTH / 2, SCREEN_HEIGHT - 300 };
    left.name = GetAbilityName(first);
    left.ability = first;
    cards.push_back(left);

    Card right;
    right.rect = { SCREEN_WIDTH / 2 + 10, 300, SCREEN_WIDTH - 50, SCREEN_HEIGHT - 300 };
    right.name = GetAbilityName(second);
    right.ability = second;
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

        // 텍스트
        SetBkMode(hdc, TRANSPARENT);
        DrawTextA(hdc, card.name.c_str(), -1, (LPRECT)&card.rect, DT_CENTER);
    }

    SelectObject(hdc, oldBrush);
    DeleteObject(brush);
}

string SkillCardScene::GetAbilityName(PlayerAbility ability)
{
    switch (ability)
    {
    case PlayerAbility::TripleShot: return "Triple Shot";
    case PlayerAbility::DoubleShot: return "Double Shot";
    case PlayerAbility::RLShot:     return "RL Shot";
    case PlayerAbility::BackShot:   return "Back Shot";
    case PlayerAbility::X2Shot:     return "X2 Shot";
    default:                        return "Unknown";
    }
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
        ScreenToClient(hWnd, &pt); // 마우스 좌표 변환

        if (pt.x < SCREEN_WIDTH / 2)
        {
            // 왼쪽 카드 클릭
            if (player)
                player->SetAbility(cards[0].ability); // 왼쪽 카드의 능력 설정

            Hide();
        }
        else
        {
            // 오른쪽 카드 클릭
            if (player)
                player->SetAbility(cards[1].ability); // 오른쪽 카드의 능력 설정

            Hide();
        }
    }

}
