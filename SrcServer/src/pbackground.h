class	smBACKGROUND
{
public:

	smOBJ3D				*smObjBG;
	smMATERIAL_GROUP	*lpMaterialGroup;

	int	BackGroundNum;
	int	FadeShowCount;

	int BGMatNum;
	int	Color_A;
	int	Color_R;
	int	Color_G;
	int	Color_B;

	smBACKGROUND();

	int	Init(int BgNum);
	int Main();
	int Draw(int x, int y, int z, int ax, int ay, int az);
	int	Close();

};
