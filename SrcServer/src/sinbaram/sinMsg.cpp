

#include "sinLinkHeader.h"


#include "Language\\Language.h"

#ifdef	_LANGUAGE_KOREAN

sMESSAGEBOX	sMessageBox[100] = {
	{"아이템 수납 공간이 부족합니다  "},
	{"수납할수 있는 무게를 초과하였습니다"},
	{"현재 사용할수 없는 아이템 입니다"},
	{"     돈이 부족합니다      "},
	{"아이템을 믹스쳐할 수 없습니다 "},
	{"거래할수있는 갯수를 초과하였습니다"},
	{"거래가 취소되었습니다     "},
	{"물약은 보관할수 없습니다  "},
	{"아이템 믹스쳐를 실패하셨습니다"},
	{"돈을 기부하셨습니다 감사합니다"},
	{"아이템의 갯수가 많아 보관할 수 없습니다"},
	{"에이징을 할수없는 아이템입니다"},
	{"아이템이 바뀌었습니다 확인해주세요"},
	{"소지할수있는 돈을 초과하였습니다"},
	{"아이템 에이징에 실패하셨습니다"},
	{"    능력치를 초기화 했습니다   "},
	{"   아이템 이미지가 없습니다   "},
	{"초기화는 1회만 가능합니다 "},
	{"클랜원만 사용가능합니다 "},
	{"정식 클랜원만이 사용할 수 있습니다"},
	{"레벨 제한으로 이동하실 수 없습니다"},
	{"에이징 레벨이 -1 하락 됐습니다"},
	{"에이징 레벨이 -2 하락	됐습니다"},
	{"에이징 레벨이 +1 상승 됐습니다"},
	{"에이징 레벨이 +2 상승 됐습니다"},
	{"퀘스트 아이템의 공격속도가 하락됬습니다"},
	{"   퀘스트 아이템 레벨업    "},
	{"   생명력이 +15 상승되었습니다 "},
	{"   퍼즐이 완성되었습니다    "},
	{"   퍼즐이 잘못되었습니다    "},
	{"   판매할 아이템이 없습니다  "},
	{"해당아이템이 이미 판매되었습니다"},
	{"판매자의 개인상점이 종료되었습니다"},
	{"   판매자를 찾을수없습니다   "},
	{"    갯수가 맞지않습니다     "},
	{"    남자 캐릭터는 사용할수 없습니다    "},
	{"    여자 캐릭터는 사용할수 없습니다    "},
	{" 여자 캐릭터는 입수할수 없는 아이템입니다 "},
	{" 남자 캐릭터는 입수할수 없는 아이템입니다 "},
	{"    아이템 가격이 변동이 있었습니다  "},
	{"    찾으실 클랜 상금이 없습니다    "},
	{"  대상 오브를 사용할수 없는 레벨입니다  "},
	{"     현재 오브가 사용중입니다    "},
	{"     공격력 함수 테스트중입니다    "},
	{"    포스 오브 제련이 완료되었습니다    "},
	{"    스탯 포인트 +5 상승되었습니다    "},
	{"    스킬 포인트 +1 상승되었습니다    "},
	{"스탯 +5 , 스킬 +1 포인트 상승되었습니다"},
	{"스탯 +5 , 스킬 +2 포인트 상승되었습니다"},
	{"   사망경험치 1% 하락되었습니다  "},
	{"    생명력 +40  상승되었습니다   " },
	{"    진행중인 퀘스트가 있습니다      " },
	{"80이후 레벨당 스탯+7로 변경되었습니다" },
	{"90이후 레벨당 스탯+10로 변경되었습니다" },
	{"사냥한 몬스터의숫자가 초기화되었습니다" },
	{"시간초과로 퀘스트를 실패하셨습니다" },
	{"용병숫자를 초과 하였습니다."},
	{"현재 사용중인 스킬아이템 입니다."},
	{"블레스 캐슬로 이동할수 없습니다.(운영팀에 문의해주세요)"},
	{"개인상점에 등록 할수없는 물품입니다."},
	{"현재 찾으실 세금이 없습니다."},
	{"이미 설문조사에 참여하셨습니다."},
	{"설문조사에 참여해 주셔서 감사합니다"},
	{"레벨에 맞지 않는 씰아이템입니다."},
	{"아이템이 재구성되었습니다"},
	{"퓨리와의 대결에서 승리 하였습니다."},
	{"퓨리와의 대결에서 패배 하였습니다."},
	{" 아이템을 보상으로 지급 받았습니다."},
	{"같은 속성의 아이템은 중복 사용할 수 없습니다."},
	{"잠시후에 사용가능 합니다"},
	{"쉘텀 조합 상태에서 취소가 불가능 합니다."},
	{"쉘텀 조합 상태에서 무기를 들수 없습니다."},
	{"현재의 헤어와 동일한 헤어틴트 포션은 사용할 수 없습니다."},
	{"아이템 제련에 실패하셨습니다."},
	{"아이템 제작에 실패하셨습니다."},
	{"쉘텀 조합 상태에서 광석/수정을 들수 없습니다."},
	{"룬 조합 상태에서 레시피를 들수 없습니다."},
	{"같은 종류의 광석/수정이 아닙니다"},
	{"제작 공식이나 배열 순서가 맞지 않습니다"},
	{"펫 아이템은 10레벨부터 사용가능합니다."},
	{"숙성시킬 에이징된 아이템이 없습니다."},
	{"     숙련할 스킬이 없습니다.     "},
	{"에이징 아이템이 숙성되었습니다."},
	{"스킬 숙련이 완료되었습니다."},
	{"그라비티 스톤은 5개까지만 사용 가능 합니다."},
	{"그라비티 스톤을 사용 하였습니다."},
	{"스톤이 있는 상태에서 아이템을 들 수 없습니다."},
	{"아이템 없이는 스톤을 올릴 수 없습니다."},
	{"스톤이 올려져 있으면 취소가 불가능 합니다."},
	{"믹스쳐된 아이템의 리셋을 실패하였습니다."},
	{"믹스쳐된 아이템 리셋이 성공하였습니다."},
	{"아이템 재구성을 할 수 없습니다."},
};

sMESSAGEBOX2 sMessageBox2[20] = {
	{"몇개의 아이템을","사시겠습니까?"},
	{"몇개의 아이템을","파시겠습니까?"},
	{"몇개의 아이템을","버리시겠습니까?"},
	{"얼마의 돈을","버리시겠습니까?"},
	{"",""},
	{"얼마의 돈을"," 거래겠습니까?"},
	{"얼마의 돈을","이동하시겠습니까?"},
	{"얼마의 돈을","회수하시겠습니까?"},
	{" 몇개의 별을 ","사시겠습니까?"},
	{"  얼마의 돈을  ","기부하시겠습니까?"},
	{"아이템의 금액을","등록하시겠습니까? "},
	{"몇개의 아이템을","사시겠습니까?"},
	{"얼마의 상금을","찾으시겠습니까?"},
	{"  아이템을  ","사시겠습니까?"},
	{"  아이템을  ","사시겠습니까?"},
	{"얼마의 돈을","찾으시겠습니까."},
	{"몇명의 용병을","구입하시겠습니까?"}

};

sMESSAGEBOX3 sMessageBox3[MESSAGE3_MAX] = {
	{"스킬 습득을 ","하시겠습니까?"},
	{"  전업을  ", "하시겠습니까?"},
	{"퀘스트 수행을","하시겠습니까?"},
	{" 재분배를 ","하시겠습니까?"},
	{"이벤트참가비용 ","원 입니다"},
	{"능력치를 초기화 ","하시겠습니까?"},
	{"퀘스트 수행을", "하시겠습니까?"},
	{" 아이템을", "받으시겠습니까?"},
	{" 유니온코어를", "등록하시겠습니까?"},
	{"  아이템을", "받으시겠습니까?"},
	{"  지역 으로", "이동하시겠습니까? "},
	{"","번호를 입력해주세요"},
	{" 별아이템을","구매하시겠습니까?"},
	{" 아이템을", "파시겠습니까?"},
	{"퀘스트 수행을", "하시겠습니까?"},
	{" 원의 기부금을 ", "지불하시겠습니까?"},
	{" 개인상정 ", "홍보문구라눼 우야라고"},
	{"아이템으로", "교환하시겠습니까? "},
	{"  아이템을", "사시겠습니까?"},
	{"  등록을 ", "취소하시겠습니까?"},
	{"아이템으로", "교환하시겠습니까? "},
	{"아이템으로", "교환하시겠습니까? "},
	{"퀘스트 수행을", "하시겠습니까?"},
	{"퀘스트 수행을", "하시겠습니까?"},
	{"퀘스트 수행을", "하시겠습니까?"},
	{"퀘스트 수행을", "하시겠습니까?"},
	{"퀘스트 수행을", "하시겠습니까?"},
	{"퀘스트 수행을", "하시겠습니까?"},
	{"퀘스트 수행을", "하시겠습니까?"},
	{"로 텔레포트", "하시겠습니까?"},
	{"퀘스트 수행을", "하시겠습니까?"},
	{"퀘스트 수행을", "하시겠습니까?"},
	{"퀘스트 수행을", "하시겠습니까?"},
	{"  전업을  ", "하시겠습니까?"},
	{"아이템으로", "교환하시겠습니까? "},
	{"로 텔레포트", "하시겠습니까?"},
	{"크리스탈 타워를","구입하시겠습니까?"},
	{"퀘스트 수행을", "하시겠습니까?"},
	{"퀘스트 수행을", "하시겠습니까?"},
	{"퀘스트 수행을", "하시겠습니까?"},
	{"퀘스트 수행을", "하시겠습니까?"},
	{"퀘스트 수행을", "하시겠습니까?"},
	{"퀘스트 수행을", "하시겠습니까?"},
	{"퀘스트 수행을", "하시겠습니까?"},
	{"을 사용", "하시겠습니까?"},
	{"퀘스트 수행을 ", "하시겠습니까?"},
	{"아이템을 ", "받으시겠습니까?"},
	{"대련장으로","이동하겠습니까?"},
	{"로 텔레포트", "하시겠습니까?"},
	{"아이템으로", "교환하시겠습니까? "},
	{"텔레포트", "하시겠습니까?"},
	{"아이템을", "제작 하시겠습니까?"},
	{"텔레포트", "하시겠습니까?"},
	{"아이템으로", "교환하시겠습니까? "},
	{"아이템으로", "교환하시겠습니까? "},
	{"선물을", "받으시겠습니까?"},
	{"아이템으로", "교환하시겠습니까? "},
	{"아이템으로", "교환하시겠습니까? "},
	{"아이템으로", "교환하시겠습니까? "},
	{"아이템으로", "교환하시겠습니까? "},
	{"아이템으로", "교환하시겠습니까? "},
	{"아이템으로", "교환하시겠습니까? "},
	{"아이템으로", "교환하시겠습니까? "},
};


char *SkillMaster[4] = {
	"     스킬 배우기",
	"        전업하기 ",
	"       게임 종료 "

};
char *SkillMaster2[4] = {
	"",
	"",
	""

};

char *ReStartMsg[4] = {
	"     필드에서 시작",
	"     마을에서 시작",
	"       게임 종료 ",
	"   경험치가 부족하여"

};
char *ReStartMsg2[4] = {
	"추가패널티(돈/경험치)1%",
	"",
	"",
	"필드시작을 할수없습니다",

};

char *SkillUseInfoText[10] = { "      기술/마법 수련      ","    새로 배우거나 향상시킬   ","   스킬/마법을 선택하십시오    ","  현재 스킬포인트가 없으므로 ","   스킬을 배울수 없습니다 " };
char *sinMsgSkillPoint = "       스킬 포인트 : %d";
char *sinMsgEliteSkillPoint = "엘리트 스킬 포인트 : %d";
char *sinStateName[5] = { "생명력 : %d/%d  ","기 력 : %d/%d  ","근 력 : %d/%d  ","경험치 : %d/%d  ","경험치 : %dM/%dM  " };


char *TownName[3] = { "리카르텐으로 귀환\r","네비스코로 귀환\r","필라이로 귀환\r" };

char *sinAbilityName[50] = { "공격력: \r","무기속도: \r","사정거리: \r","크리티컬: \r","방어력: \r","명중력: \r",
					"흡수력: \r","블럭율: \r","이동속도: \r","내구력: \r","기력회복: \r","생명력회복:\r",
					"근력회복: \r","생속성: \r","자연속성: \r","화속성: \r","빙속성: \r","뢰속성: \r","독속성: \r",
					"물속성: \r","바람속성: \r","생명력재생: \r","기력재생: \r","근력재생: \r","생명력추가: \r",
					"기력추가: \r","근력추가: \r","물약보유공간: \r","요구레벨: \r","요구힘: \r","요구정신력: \r",
					"요구재능: \r","요구민첩성: \r","요구건강: \r" };


char *sinSpecialName[50] = { "특화공격속도: \r","특화크리티컬: \r","특화방어력: \r","특화흡수력: \r",
						"특화블럭율: \r","마법숙련도: \r","특화이동속도: \r","특화생체속성: \r","특화자연속성: \r",
						"특화불속성: \r","특화냉기속성: \r","특화번개속성: \r","특화독속성: \r","특화물속성: \r","특화바람속성: \r",
						"특화공격력: \r","특화명중력: \r","특화사정거리: \r","특화생체공격: \r","특화자연공격: \r","특화불공격: \r","특화냉기공격: \r",
						"특화번개공격: \r","특화독공격: \r","특화물공격: \r","특화바람공격: \r","특화생명력추가: \r","특화기력추가: \r",
						"특화생명력재생: \r","특화기력재생: \r","특화근력재생: \r","판매가격: \r","구입가격: \r" };


char *SpecialName3 = "%s 특화\r";
char *MixResultTitle = "아이템 믹스쳐 결과";
char *NowLevelText = "현재 레벨\r";
char *NextLevelText = "다음 레벨\r";

char *NormalAttckName = "기본 공격";
char *RequirLevel = "%s (요구레벨:%d)\r";
char *UseItemGroupName = "사용가능 아이템군\r";

char *PoisonName = "독 속성:\r";
char *FireName = "불 속성:\r";
char *AttackAreaName = "공격범위:\r";
char *Attack_RateName = "명중률:\r";
char *Max_DamageIncre = "최대 데미지증가:\r";
char *DamageAddName = "공격력가중:\r";
char *Attack_SpeedAdd = "공격스피드증가:\r";
char *IncreBlock = "블럭율증가:\r";
char *CountinueTime = "유지시간:\r";
char *UseManaName = "사용기력:\r";
char *DamageName = "공격력:\r";
char *ShootingRangeName = "사정거리:\r";
char *IncreAsorb = "흡수량증가:\r";
char *SecName = "초";
char *PlusDamageName = "공격력추가치:\r";
char *HitNumName = "연타횟수:\r";
char *DecreLifeName = "생명력감소치:\r";
char *Attck_RateAdd = "명중력추가치:\r";
char *Add_CriticalName = "크리티컬추가:\r";
char *Push_AreaName = "밀어내는거리:\r";
char *FireAttackDamageAdd = "화 계열공격추가 :\r";
char *IceName = "빙 속성:\r";
char *IceAttackDamageAdd = "빙계 공격력 :\r";
char *StuneRate = "스턴확률:\r";
char *DefenseRateIncre = "블럭율 증가:\r";
char *WeaponSizeName = "무기 크기:\r";
char *HwakRotationNum = "매의회전수:\r";
char *WeaponSpeedAddName = "무기스피드가중:\r";
char *IncreAttack_RateName = "명중력증가:\r";
char *ShootingNumName = "발사 갯수:\r";
char *SeriesShootingCount = "연속 발사화살수:\r";
char *UseStaminaName = "사용근력:\r";
char *MasterSkillMoneyName = "스킬수련비용:\r";

char *sinGold = "%d원";
char *sinGiveItem5 = "증정용 아이템\r";
char *sinCopyItem5 = "복사된 아이템\r";
char *sinNum7 = "회";
char *sinSkillPointName = "스킬포인트";
char *sinG_Pike_Time3 = "동결 시간:\r";
char *sinItemLimitTimeOverMsg = "유통기한이 지났습니다\r";
char *sinDeadSongPyeunEat = "이런! 상한 음식이잖아!";
char *SmeltingResultTitle = "아이템 제련 결과";
char *ManufactureResultTitle = "아이템 제작 결과";
char *ManufacturingTitle = "랜덤으로";


char *sinMaxDamageAdd = "최대 공격력 가중+\r";
char *sinDamagePiercing = "(관통 공격)\r";
char *sinAddStamina = "근력 추가량:\r";
char *sinAddLife = "생명력 회복치:\r";

char *sinDamageUndead50 = "Undead 계열에겐 50% 공격력 가중:\r";
char *sinNumCount2 = "개수:\r";
char *sinNumCount3 = "개\r";
char *sinDecreDamage = "공격력 감소치:\r";
char *sinConvert4 = "변환량:\r";
char *sinIncreElement = "원소속성 상승치:\r";
char *sinPartyIncreElement = "파티원은 속성상승의50% 적용\r";
char *sinFireBallDamage2 = "(정확하게 맞은 적은 100% 데미지)\r";
char *sinFireBallDamage3 = "(타격 반경 60 (1/3 데미지))\r";
char *sinAddDamage7 = "추가공격력:\r";
char *PlusDamageWeapon = "무기";
char *SparkDamage = "개당 공격력:\r";
char *SparkNum7 = "최대스파크수:\r";
char *StunRage = "스턴거리:\r";
char *RecvPotion7 = "개의 물약을";


char *PartyArea7 = "시전시 파티반경:\r";
char *Area17 = "반경:\r";
char *AddAttack_Rate9 = "명중력가중:\r";
char *PiercingRange = "관통거리:\r";
char *IncreDefense = "방어력증가:\r";
char *AddShootingRange = "사정거리증가:\r";
char *LifeAbsorb = "생명력흡수량:\r";
char *FireDamage = "불속성 추가 공격력:\r";
char *IceDamage = "냉속성 추가 공격력:\r";
char *LightningDamage = "뇌속성 추가 공격력:\r";
char *AddManaRegen = "기력재생 추가:\r";
char *LightNum = "번개갯수:\r";
char *ReturnDamage = "되돌릴데미지:\r";
char *Area18 = "유효반경:\r";
char *IncreMana5 = "기력증가:\r";
char *Area19 = "유효거리:\r";
char *HelpTitle8 = "도   움   말";
char *QuestTitle8 = "퀘   스   트";
char *ResearchTitle8 = "설 문  조 사";
char *TeleportTitle8 = "텔 레  포 트";


char *IncreWeaponAttack_RateName = "무기명중력증가:\r";
char *AddMaxDamage = "기술공격력가중:\r";
char *LinkCoreName = "클랜원에게로 이동\r";
char *DesLinkCore = "대상:";
char *Itemul = "아이템을";
char *ItemRecvOk = "받으시겠습니까?";
char *Money5 = "원을";
char *Exp5 = "경험치를";
char *WingItemName[] = { "메탈윙","실버윙","골드윙","다이아윙","케이아스윙", "익스트림윙" };
char *WarpGateName[] = { "워프 게이트","리 카 르 텐","필라이 타운","황혼의  숲","대나무  숲","루이넨 빌리지","네비스코 타운","금단의  땅","유라 빌리지","로스트아일랜드" };
char *sinWarningName5 = "경     고";
char *ClanCristalName = "클랜원 전용\r";
char *NowMyShopSell = "판 매 중\r";
char *SecretNumName = "인증번호 입력";
char *MyShopExpDoc7 = "상 점 홍 보";
char *NotAgingItem2 = "에이징 할수없는 아이템";
char *ExpPercent2 = "경험치 : %d.%d%s";
char *ExpPercent3 = "경험치 : %d.0%d%s";
char *Mutant7 = "뮤턴트";
char *Mechanic7 = "메카닉";
char *Demon7 = "디먼";
char *Nomal7 = "노멀";
char *Undead7 = "언데드";
char *MonsterAddDamage2 = "추가 데미지)\r";
char *MonsterAddDamageFire = "화속성 추가 데미지)\r";
char *HaWarpGateName[] = { "블레스 캐슬",0 };
char *FallGameName = "일그러진 숲";
char *EndlessGameName = "끝없는 탑";
char *LookHelp = ">>자세히보기...";



char *HoldStarNumDoc = "보유하고 있는 별의 갯수";
char *StarItemBuy7 = "별아이템 구입";
char *ChangeMoney7 = "(별 1개 가격 : 100000원)";




char *LightningDamage2 = "뢰 데미지:\r";
char *SheildDefense = "방어력 추가:\r";

char *DemonDamage4 = "디먼VS공격력가중:\r";
char *PoisonDamage3 = "(초당)독 공격력:\r";
char *PikeNum4 = "창의 갯수:\r";
char *poisoningTime = "중독 시간:\r";
char *PlusCriticalName = "크리티컬확률 추가:\r";
char *SpiritFalconDamage2 = "스피릿 팰컨 데미지:\r";
char *LifeGegenPlus = "생명 재생력 증가:\r";
char *PlusDamage4 = "추가 폭발 데미지:\r";
char *PiercingPercent = "관통할 확률:\r";
char *DamageToLife = "데미지환원량:\r";
char *MyMonster7 = "아군이될 확률:\r";
char *LifeIncre4 = "생명력 증가치:\r";
char *UndeadDamage3 = "언데드 공격력가중:\r";

char *AttackNum3 = "연속공격횟수:\r";
char *AttackRateMinus = "명중력감소:\r";
char *MaxDamagePlus2 = "최대공격력추가:\r";
char *LightningAddDamage3 = "뢰속성 추가공격력:\r";
char *ReLifePercent4 = "소생확률:\r";
char *GetExp3 = "획득경험치:\r";
char *ResurrectionChar4 = "소생캐릭터LV";
char *ExtinctionPercent2 = "소멸될확률:\r";
char *ExtinctionAmount2 = "소멸될량:\r";
char *IncreLifePercent2 = "생명력증가량:\r";

char *ReduceDamage3 = "데미지 감소치:\r";
char *IncreMagicDamage = "마법공격력가중:\r";
char *AttackDelay3 = "공격딜레이:\r";

char *FireDamage2 = "화속성 공격력:\r";
char *IceDamage2 = "냉속성 공격력:\r";
char *AddDefense8 = "방어력 가중:\r";
char *SkillDamage5 = "기술공격력:\r";

char *FireDamage3 = "화속성 추가공격력:\r";
char *AddSpeed7 = "이동속도 증가:\r";
char *AfterDamage7 = "시전후데미지증가:\r";
char *MonsterSight7 = "몬스터시야:\r";



char *LinghtingAddDamage4 = "라이트추가공격력:\r";
char *MaxBoltNum4 = "최대볼트:\r";
char *AddAbsorb4 = "흡수력추가:\r";
char *IncreArea4 = "범위증가:\r";
char *IncreAttack4 = "공격력증가:\r";
char *GolemLife4 = "생명력:\r";


char *SubAbsorb4 = "흡수력하락:\r";
char *AreaDamage4 = "범위공격력:\r";
char *MaxAttackNum4 = "최대타격수:\r";
char *LifeUp4 = "생명력추가량:\r";

char *CriticalAddDamage4 = "크리티컬공격력증가:\r";
char *MonstervsSubCritical4 = "몬스터크리티컬약화:\r";
char *ChargingAddPercentDamage4 = "차징시공격력가중:\r";

char *IncreEvasionPercent4 = "추가회피확률:\r";
char *AddShadowNum4 = "잔상콤보증가:\r";

char *WolverinLife4 = "생명력:\r";
char *WolverinRate4 = "명중력:\r";
char *WolverinDefense4 = "방어력:\r";
char *AddEvasion4 = "추가회피능력증가:\r";
char *AddDamage4 = "공격력증가:\r";
char *FalconAddDamage4 = "펠컨공격력증가:\r";


char *IncreAttackAbsorb4 = "공격흡수력증가:\r";

char *RectAngleArea4 = "공격범위:\r";

char *MonsterSubSpeed4 = "타격된적속도저하:\r";


char *AddLifeRegen4 = "생명재생력추가:\r";
char *AddManaRegen4 = "기력재생력추가:\r";
char *MagicArea4 = "시전범위:\r";
char *ChainNum4 = "연결갯수:\r";
char *ChainRange4 = "연결거리:\r";
char *UndeadDamageAbsorb4 = "언데드공격흡수치:\r";
char *UserBlockPercent4 = "추가블록율:\r";

char *SecondIncreMana4 = "초당기력증가:\r";
char *FireDamage4 = "불공격력:\r";
char *DecreSpeed4 = "속도저하:\r";
char *DecreAttack4 = "공격저하:\r";
char *AddPercentDamage4 = "공격력가중:\r";



char *ChainDamage3 = "인계)\r";
char *BrandishDamage3 = "브렌디쉬 데미지";
char *PhysicalAbsorb3 = "피지컬앱소션 흡수량";
char *SparkDamage3 = "스파크 데미지";
char *BrutalSwingCritical3 = "부르틀스윙 크리티컬";
char *Attck_RateAdd5 = "명중력추가:\r";
char *Triumph4 = "트라이엄프";
char *DivineShield4 = "디바인쉴드블록율";





char *QuestMonsterName[] = { "바곤","스켈레톤 워리어","헤드커터","아머드 비틀","스켈레톤 레인저","타이탄" ,
						 "잊혀진땅 몬스터","오아시스 몬스터","고대감옥1층 몬스터" };



char *VampOption[10] = { "에이징확률상승: \r","흡혈: \r","데미지반사: \r","생명력감소: \r","행운: \r" };


char *Quest3ItemName[] = { "디먼 헌터","앤션트 리벤지","미스트","데블 사이드","아나콘다","플레티넘 소드","고스트" };

char *Quset3ItemDoc15 = "퀘스트 아이템이";
char *Quset3ItemDoc16 = " 사라졌 습니다 ";

char *SparkDamage10 = "스파크데미지 인계:\r";

char *RequirLevel3 = "(습득요구레벨:%d)\r";

char *RecvItemTT = "아이템을 받았습니다";
char *PuzzleEvent5 = "완성된 퍼즐을";
char *BabelHorn = "바벨의 뿔을";
char *ChristMas = "반짝반짝 가루를";
char *NineTailFoxItem = "나인테일 아물렛을";
char *MyShopItemSell5 = "판매가격: \r";
char *CristalItem = "일곱개의 크리스탈을";


char *WatermelonItem = "7개의 수박을";

char *PumpkinItem = "7개의 호박을";

char *StarItem = "7개의 별조각을";

char *ValentineItem = "7개의 초콜릿을";

char *PristonAlphabetItem = "7개의 알파벳으로";

char *CandydaysItem = "7개의 캔디를";

char *MagicalGreenEmeraldItem = "7개의 에메랄드를";

char *MagicalGreenJadeItem = "7개의 비취를";

char *TearOfKaraItem = "7개의 카라의 눈물을";

char *ExpireItem = "기간만료";

char *FindinvestigatorItem = "나인아뮬렛을";
char *FindinvestigatorNineItem = "나인아뮬렛을";
char *FindinvestigatorTaleItem = "테일아뮬렛을";



char *InventoryFull = "인벤토리 공간부족";
char *InvenSpaceSecure = "공간을 확보해 주세요";

char *sinDeadCandyEat = "이런! 오래되서 맛이 없잖아!";

char *PotionCntDoc2 = "개당 판매 금액을";
char *ItemPrice7 = "아이템의  금액을";

char *BuyMyShopItem7 = "%s님이 %s 아이템을 %d원에 %d개 사셨습니다";
char *BuyMyShopItem8 = "%s님의 %s 아이템을 %d원에 %d개 사셨습니다";
char *ItemName87 = "아이템이";

char *sinEvent87 = "위험한 수집가의 부탁";
char *sinAddDamageItem = "추가공격력: \r";
char *sinContinueTimeItem = "유지시간: \r";
char *BuyPotionMoney = "금액:";
char *BuyPotionKind = "수량:";
char *SheltomName2[] = { "러씨디","쎄레네오","파데오","스파키","레이던트","트랜스패로","머키","데비네","셀레스토", "미라지", "인페르나", "이니그마" };


char *BillingMagicForceName = "매직 포스";


char *MagicForceName = "매직";

char *AddPercentDamage3 = "공격력가중: \r";

char *sinLuckyBox = "복주머니";

char *SodMessage_Etc[] = {
"벨라트라 운영 클랜에게 지급되는 수익금은",
"해당 클랜의 클랜칩만 찾을 수 있습니다.",
"현재 세율은 %d%s 입니다.",
};

char *SodMessage_Clan[] = {
"어제 벨라트라에서 우리 클랜에게 배당된",
"총 수익금은 다음과 같습니다.",
};

char *SodMessage_Master[] = {
"어제 벨라트라에서 우리 클랜에게 배당된",
"총 수익금은 다음과 같습니다.",
"지금 찾으시겠습니까?",
};

char *OtherClanMaster[] = {
"상금 중 일부가 남아있습니다",
"찾으시려는 금액을 입력하세요.",

};

char *SiegeMessage_Taxrates[] = {
	"세율을 %d%s로 변경 합니다.",
	"지금까지 누적된 세금총액",
	"원입니다.",
	"세금을 찾으시겠습니까?.",
	"현재 세율은 %d%s입니다.",
};
char *SiegeMessage_MercenrayA[] = {
	"리카르텐 민병대",
	"민병으로 구성된 전투병으로",
	"값싼 대신 전투력이 가장 약합니다.",
	"최대용병인원:20 / %d",
};
char *SiegeMessage_MercenrayB[] = {
	"리카르텐 경비대",
	"가격 성능 모두 균형 있는 용병으로",
	"중간급의 전투력을 가집니다.",
	"최대용병인원:20 / %d",
};
char *SiegeMessage_MercenrayC[] = {
	"블레스왕국 경비대",
	"가장 상위의 고급 용병으로서",
	"전투력이 가장 강합니다.",
	"최대용병인원:20 / %d",
};
char *SiegeMessage_TowerIce[] = {
	"아이스 크리스탈",
	"아이스 속성으로 이동속도 하락과",
	"공격속도 하락의 특수 능력이 있습니다.",
	"아이스 크리스탈 설정완료",
};
char *SiegeMessage_TowerFire[] = {
	"파이어 크리스탈",
	"파이어 속성으로 공격력은 가장 높지만",
	"특수한 능력은 없습니다.",
	"파이어 크리스탈 설정완료",
};
char *SiegeMessage_TowerLighting[] = {
	"라이트닝 크리스탈",
	"라이트닝 속성으로 이동속도 하락과 ",
	"공격속도 하락의 특수 능력이 있습니다.",
	"라이트닝 크리스탈 설정완료",
};
char *SiegeMessage_MerMoney = "용병 비용: ";
char *SiegeMessage_TowerMoney = "타워 비용: ";

char *sinClanMaster7 = "클랜장";
char *sinPrize7 = "상금";

char *sinLevelQuestMonster[] = { "바곤","머핀","다이어 비","타이푼","라투","그로테스크","아이언 피스트" };
char *sinLevelQusetDoc = "퀘스트> %s %d마리사냥";
char *sinTeleportDoc[] = { "버섯동굴 입구","벌집동굴 입구","저주받은 땅","금단의 땅" };
char *sinLevelQuest90_2Mon[] = { "오메가","디-머신","마운틴" };
char *sinLevelQusetDoc2 = "<퀘스트> %s %d마리를 사냥하시오";
char *sinLevelQusetDoc3 = "<퀘스트> %s 로부터 아이템을 획득하시오";
char *sinLimitTiem2 = "제한시간: \r";
char *sinMinute2 = "분";
char *sinDay4 = "일";
char *sinHour4 = "시";
char *sinLevelQusetDoc4 = "<퀘스트> %s %d마리사냥 완료";

sinSTRING sinTestMsg7("메롱 만만세 니들다 즐!");

char *sinMonCodeName[] = {
	0,
	"바곤",
	"스켈레톤 워리어",
	"헤드 커터",
	"아머드 비틀",
	"스켈레톤 레인져",
	"타이탄",
	"머핀",
	"다이비",
	"타이푼",
	"라투",
	"그로데스크",
	"아이언 피스트",
	"오메가",
	"디 머신",
	"마운틴",
	"스켈레톤 나이트",
	"솔리드 스네일",
	"쏜 크로울러",
	"머미",
	"둠 가드",
	"파이곤",
	"스톤 자이언트",
	"스톤 고렘",
	"아이언 가드",
	"아벨린",
	"아벨리스크-L",
	"비블",
	"일루젼 나이트",
	"나이트 메어",
	"위치",
	"헤비 고블린",
	"다우린",
	"스티지언",
	"인큐버스",
	"체인 고렘",
	"다크 스펙터",
	"메트론",
	"아벨리스크 로드",
	"더스크",
	"새드니스",
	0,
};

char *ChargingTime4 = "차징속도향상:\r";
char *AddIceDamage4 = "빙속성 추가공격력:\r";
char *IceTime4 = "동결시간:\r";
char *sinAttackType = "공격타입:\r";
char *sinAttackType2[2] = { "수동\r","자동\r" };

char *Won = "원";


char *CastlItemInfo[] = {
	{"일정시간 무적상태가 돼지만\r"},
	{"크리티컬 확률이\r"},
	{"추가 회피 확률이\r"},
	{"파티원의 생명력,기력,근력\r"},
	{"사망시 즉시 부활한다.\r"},
	{"크리티탈 타워의 공격을\r"},
	{"타켓 공격시 공격력을 20%\r"},
	0,
};
char *CastlItemInfo2[] = {
	{"공격력은 1/2로 감소한다.\r"},
	{"5% 증가한다.\r"},
	{"상승한다.\r"},
	{"을 모두 회복한다.\r"},
	{"\r"},
	{"50%상쇄한다.\r"},
	{"가중 시킨다.\r"},
	0,
};
char *CharClassTarget[8] = {
	"타켓(파이터)\r",
	"타켓(메카니션)\r",
	"타켓(파이크맨)\r",
	"타켓(아쳐)\r",
	"타켓(나이트)\r",
	"타켓(아탈란타)\r",
	"타켓(메지션)\r",
	"타켓(프리스티스)\r",
};
char *AttributeTower[4] = {
	"속성(파이어)\r",
	"속성(아이스)\r",
	"속성(라이트닝)\r",
	"유지시간:%d초\r",
};

char *SiegeMessage_MerComplete = "용병설정 완료";


char *haQuestMonsterName[] = {
	"호피",
	"래비",
	"흡고블린",
	"노쓰고블린",
	"스켈레톤",
	"커럽트",
	"싸이클롭스",
	"바곤",
	0,
};
char *ha100LVQuestItemName[] = {
	"미너터 액스",
	"익스트림 탈론",
	"드래곤 본 해머",
	"헬파이어 사이드",
	"리벤지 보우",
	"이모탈 소드",
	"샐러맨더 재블린",
	"고딕 스태프",
	0,
};

char *ha100LVQuestMonterName[] = {
	"페룸의 심장 몬스터",
	"겔루비아 계곡 몬스터",
	0,
};
char *ha100LVQuestName = "퓨리의 환영";


char *PremiumItemDoc[][2] = {
	{"스탯 포인트를\r"     ,"재분배 한다.\r"},
	{"스킬 포인트를\r"     ," 재분배 한다.\r"},
	{"스탯/스킬 포인트를\r"," 재분배한다.\r"},
	{"현재 위치에서 \r"    ,"부활한다.\r"},
	{"일정시간 무적상태가 된다.\r","1/2 공격력 감소\r"},
	{"크리티컬 판정 확률이 \r"    ,"15% 증가한다.\r"},
	{"이베이드 확률이 \r"         ,"15% 증가한다.\r"},
};
char *UpKeepItemDoc[] = {
	"잔여시간 : %d분",
	"추가아이템획득 %d%s증가",
	"추가경험치획득 %d%s증가",
	"공격력%d%s증가",
	"몬스터 생명력 일부회수",
	"몬스터 기력 일부회수",
	"소지량 %d증가",
	"기력소모 %d%s감소",
	"난 도우미 펫 테리",
	"난 도우미 펫 넵시스",
	"난 도우미 펫 이오",
	"난 도우미 펫 무트",
	"몬스터 생명력 일부회수",
	"근력소모 %d%s감소",
	0,
};
char *UpKeepItemName[] = {
	"써드 아이즈",
	"경험치증가 포션",
	"뱀피릭 커스핏",
	"마나 리차징 포션",
	"마이트 오브 아웰",
	"마나 리듀스 포션",
	"피닉스펫",
	"도우미 펫(테리)",
	"도우미 펫(넵시스)",
	"도우미 펫(이오)",
	"도우미 펫(무트)",
	"뱀피릭 커스핏EX",
	"근력 리듀스 포션",
	0,
};



char *BoosterItemInfo[] = {
	{"일정시간동안 생명력을\r"},
	{"일정시간동안 기력을\r"},
	{"일정시간동안 근력을\r"},
	0,
};
char *BoosterItemInfo2[] = {
	{"15% 상승시킨다.\r"},
	{"15% 상승시킨다.\r"},
	{"15% 상승시킨다.\r"},
	0,
};


char *SkillDelayItemInfo[] = {
	{"일정시간동안 스킬 딜레이를\r"},
	0,
};
char *SkillDelayItemInfo2[] = {
	{"50% 단축 시킨다.\r"},
	0,
}

#endif

#ifdef	_LANGUAGE_CHINESE
#include "Language\\chinese\\C_sinMsg.h"
#endif

#ifdef	_LANGUAGE_JAPANESE
#include "Language\\Japanese\\J_sinMsg.h"
#endif

#ifdef	_LANGUAGE_TAIWAN
#include "Language\\Taiwan\\T_sinMsg.h"
#endif

#ifdef	_LANGUAGE_ENGLISH
#include "Language\\English\\E_sinMsg.h"
#endif

#ifdef	_LANGUAGE_THAI
#include "Language\\THAI\\TH_sinMsg.h"
#endif

#ifdef _LANGUAGE_VEITNAM
#include "Language\\VEITNAM\\V_sinMsg.h"
#endif

#ifdef _LANGUAGE_BRAZIL
#include "Language\\BRAZIL\\B_sinMsg.h"
#endif

#ifdef _LANGUAGE_ARGENTINA
#include "Language\\ARGENTINA\\A_sinMsg.h"
#endif