







#ifndef _HO_EFFECT_EVENT_H_
#define _HO_EFFECT_EVENT_H_
#include "math\\mathGlobal.h"
#include "math\\point3.h"
#include "math\\color4.h"
#include "HoEffectModel.h"
#include "HoEffectUtil.h"
#include <vector>
#include <string>


enum
{
    CLASS_EVENT_ANGLE = 1,
    CLASS_EVENT_TRANSLATION,
    CLASS_EVENT_SIZE,
    CLASS_EVENT_COLOR,
    CLASS_EVENT_TIMER
};

class HoEffectEventInterface
{
protected:
    int     ClassID;                            

    bool    Fade;                               
    HoEffectEventInterface *NextFadeEvent;
    float                   StartTime;          

public:
    HoEffectEventInterface(): Fade(false), NextFadeEvent(0), ClassID(0) {}
    virtual ~HoEffectEventInterface() {}


    int GetClassID() {return ClassID;}

    bool    IsFade(void) const { return(Fade); }
	void    SetFade(const bool data = true) { Fade = data; }
    void    SetStartTime(HoEffectMinMax<float> in)
    {
        StartTime = in.GetRandom();
    }

    float   GetStartTime(void) const
    {
        return(StartTime);
    }

	void    SetStartlTime(const float data)
    {
        StartTime = data;
    }

    void SetFadeNextEvent(HoEffectEventInterface *effectEvent)
    {
        if(effectEvent == NULL)
            return;
        NextFadeEvent = effectEvent;
    }

    virtual void VisitEffectModel(HoEffectModelInterface &effectModel) = 0;
};





class HoEffectEventColor : public HoEffectEventInterface
{
private:
    HoEffectMinMax<color4> Color;

public:
    HoEffectEventColor()
    {
        ClassID = CLASS_EVENT_COLOR;
    }
    ~HoEffectEventColor() {}

    void Set(HoEffectMinMax<color4> in)
    {
        Color = in;
    }

    HoEffectMinMax<color4> Get()
    {
        return Color;
    }

    void VisitEffectModel(HoEffectModelInterface &effectModel);
};

#endif 
