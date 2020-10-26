




class tSCROLL
{
public:
	tSCROLL();
	~tSCROLL();

	int lifef;
	int step;
	int top, bot;
	int allLineSu;
	int viewLineSu;

	void Init(int flag);
	void Init(int t, int b, int menuSu, int ViewLineSu);
	int topScrollLineNum(int point);


	int ret_WHEELpoint(int wheelN, int point);
};

void TJBscrollWheelClear();

#ifdef TJSCROLL_CPP

class tSCROLL tscr;
class tSCROLL tscr_CL;
class tSCROLL tscr_Guide;


#else 

extern class tSCROLL tscr;
extern class tSCROLL tscr_CL;
extern class tSCROLL tscr_Guide;


#endif

void TJBscrollWheelClear_Guide();
