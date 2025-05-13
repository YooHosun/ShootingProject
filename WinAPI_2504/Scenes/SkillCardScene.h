#pragma once

class SkillCardScene
{
public:
    SkillCardScene();
    ~SkillCardScene();

    void Update();
    void Render(HDC hdc);
    void Show(Player* p);
    void Hide();
    bool IsActive() const { return isActive; }
    void SetPlayer(Player* p) { player = p; }

private:
    void CheckClick();

private:
    bool isActive = false;

    struct Card
    {
        RECT rect;
        PlayerAbility ability;
        string name;

    };
    Player* player;

    vector<Card> cards;
    string GetAbilityName(PlayerAbility ability);
};
