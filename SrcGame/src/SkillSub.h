

int OpenPlaySkill(sSKILL *lpSkill);

int PlaySkillAttack(sSKILL *lpSkill, smCHAR *lpChar);

int GetSkillDistRange(sSKILL *lpSkill, int AttackRange, int AttackMode);

int PlaySkillLoop(int SkillCode, smCHAR *lpChar);


int SetSkillMotionBlurColor(int dwSkillCode);

int GetSkillPower(smCHAR *lpChar, smCHAR *lpChar2, int dx, int dy, int dz);

int	LearnSkillEffect(smCHAR *lpChar = 0);

int CheckPlaySkill();
