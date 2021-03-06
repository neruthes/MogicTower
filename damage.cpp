#include "damage.h"

/*
    此函数计算一个怪物对勇士造成的伤害
    参数说明：
        h_atk: 勇士攻击
        h_def: 勇士防御
        h_mdef: 勇士魔防
        m_hp: 怪物生命值
        m_atk: 怪物攻击
        m_def: 怪物防御
        m_spe: 怪物特效
    返回值：
        一个整数，代表伤害值。
        如果勇士无法对怪物造成伤害，返回999999999

    怪物特效说明：
        0: 无特效
        1: 魔攻（怪物无视勇士的防御）
        2: 坚固（怪物防御=勇士攻击-1）
        3: 先攻（战斗前怪物首先攻击勇士一次）
        4: 破甲（怪物附加角色防御的90%点作为伤害）
        5: 反击（怪物每回合附加角色攻击的10%作为伤害）
        6: 模仿（怪物攻防=勇士攻防）
        7: 2连击（每回合怪物打勇士两次）
        8: 3连击（每回合怪物打勇士三次）
        9: 4连击（每回合怪物打勇士四次）
*/
int getDamage(int h_atk, int h_def, int h_mdef, int m_hp, int m_atk, int m_def, int m_spe)
{
    if (m_spe == 1) // 魔攻
        h_def = 0;
    if (m_spe == 2) // 坚固
        m_def = h_atk - 1;
    if (m_spe == 6) // 模仿
    {
        m_atk = h_atk;
        m_def = h_def;
    }

    if (h_atk <= m_def) // 无法战斗
        return 999999999;
    if (h_def >= m_atk) // 无法造成伤害
        return 0;

    int damage = 0;
    if (m_spe == 3) // 先攻
        damage += m_atk - h_def;

    int m_times = 1;
    if (m_spe == 7) // 2连击
        m_times = 2;
    if (m_spe == 8) // 3连击
        m_times = 3;
    if (m_spe == 9) // 4连击
        m_times = 4;

    int beat_times = (m_hp - 1) / (h_atk - m_def);

    if (m_spe == 4) // 破甲
        damage += h_def * 0.9;

    if (m_spe == 5) // 反击
        damage += beat_times * h_atk * 0.1;

    damage += beat_times * (m_atk - h_def) * m_times; // 怪物伤害计算公式
    damage -= h_mdef;

    return damage <= 0 ? 0 : damage;
}

int getDamage(const PlayerInfo& p, const Monster& m)
{
    return getDamage(p.getATK(), p.getDEF(), p.getMDEF(), m.getHP(), m.getATK(), m.getDEF(), m.getSPE());
}