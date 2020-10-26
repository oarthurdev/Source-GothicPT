
#ifndef _CurseFilter_h_
#define _CurseFilter_h_

extern int LoadCurses(const char *filename);
extern int LoadCursesDebug(const char *filename);
extern int LoadCursesID(const char *filename);
extern int LoadCursesDebugID(const char *filename);

extern bool IsCurse(const char *str);
extern bool IsCurseID(const char * str);
extern bool BadTaiwanID(const char * str);

extern char *ConvertString(char *str, int max_len);
extern char *ConvertStringTHAI(char * str, int max_len);
extern char *ConvertStringTaiwanChat(char * str, int max_len);

extern void PassCode(char PassBefore[], char PassAfter[], int number);
extern void PassCodeID(char PassBefore[], char PassAfter[], int number);
extern int ChatChkSum();
extern int ChatChkSumID();

#endif
