





#ifndef __FILTEREFFECT_H__
#define __FILTEREFFECT_H__



enum eNEW_RENDER_TARGET_TYPE
{
	ORG_TARGET = 1,
	NEW_TARGET_PRIMARY = 2,
	NEW_TARGET_BACK = 3,
	NEW_TARGET_RATE_BACK = 4,
};



enum eFILTER_EFFECT_TYPE
{
	FILTER_EFFECT_NULL = 0,
	FILTER_EFFECT_SET_MOTION_BLUR = 1,
	FILTER_EFFECT_SET_BRIGHT_CONTRAST = 2,
	FILTER_EFFECT_DEL_MOTION_BLUR = 3,
	FILTER_EFFECT_DEL_BRIGHT_CONTRAST = 4,
};



extern DDPIXELFORMAT				g_ddpfPixelFormatZ;



extern int			CreateNewRenderTarget(void);
extern void			ReleaseNewRenderTarget(void);
extern inline int	IsCreateNewRenderTarget(void);

extern inline int	GetRenderTarget(void);
extern int			ChangeRenderTarget(eNEW_RENDER_TARGET_TYPE eRTtype);

extern inline int	GetFilterEffect(void);
extern void			SetFilterEffect(eFILTER_EFFECT_TYPE eFEtype, DWORD dwAlpha);

extern void SetNewTargetTextureState(void);
extern void DefaultsNewTargetTextureState(void);
extern void RenderFilterEffect(void);


#endif 
