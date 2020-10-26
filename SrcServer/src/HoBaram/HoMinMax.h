#ifndef _HO_MIN_MAX_H
#define _HO_MIN_MAX_H
#include <vector>
#include <string>

#ifndef D3D_OVERLOADS
#define D3D_OVERLOADS
#endif

using namespace std;
inline void MakeUpperCase(std::string &str)
{
	for(std::string::iterator i = str.begin(); i != str.end(); i++)
	{
		*i = toupper(*i);
	}
}

inline std::string RemoveQuotes(std::string &str)
{
	for(std::string::iterator i = str.begin(); i != str.end(); i++)
	{
		if(*i == '\"')
		{
			i = str.erase(i); if(i == str.end())
				break;
		}
	}
	return(str);
}


int RandomNumber(int iMin, int iMax);
float RandomNumber(float fMin, float fMax);
D3DVECTOR RandomNumber(D3DVECTOR vMin, D3DVECTOR vMax);
D3DCOLORVALUE RandomNumber(D3DCOLORVALUE Min, D3DCOLORVALUE Max);





template <class T> class HoMinMax
{
public:
	HoMinMax()
	{
		Min = T(); Max = T();
	}

	HoMinMax(T tMin, T tMax)
	{
		Min = tMin; Max = tMax;
	}

	~HoMinMax()
	{
	}

	T Min;
	T Max;

	T GetRandomNumInRange(void)
	{
		return(RandomNumber(Min, Max));
	}

	T GetRange(void)
	{
		return(abs(Max - Min));
	}
};

#endif