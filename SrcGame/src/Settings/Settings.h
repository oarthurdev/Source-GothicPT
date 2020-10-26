#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

class Settings
{
private:
	
	bool windowed;
	int textureQuality;
	int bpp;
	int networkQuality;
	bool cameraInv;
	bool motionBlur;
	bool cameraSight;
	int width;
	int height;

	int resolution;

	bool sound;
	bool weather;
	std::string server1;
	std::string server2;
	std::string server3;
	unsigned short port;

	std::string macros[10];

	
	bool rememberID;

public:
	Settings();
	~Settings();

	bool getWindowMode() const;
	void setWindowMode(bool value);
	int getTextureQuality() const;
	void setTextureQuality(int value);
	int getBitDepth() const;
	void setBitDepth(int value);
	int getNetworkQuality() const;
	void setNetworkQuality(int value);
	bool getCamInv() const;
	void setCamInv(bool value);
	bool isMotionBlur() const;
	void setMotionBlur(bool value);
	bool getSight() const;
	void setSight(bool value);
	int getWidth() const;
	void setWidth(int value);
	int getHeight() const;
	void setHeight(int value);
	int getResolution() const;
	void setResolution(int value);
	bool isWideScreen() const;
	bool hasSound() const;
	void setSound(bool value);
	bool getWeather() const;
	void setWheater(bool value);
	bool getRememberID() const;
	void setRememberID(bool value);
	std::string getServer1() const;
	void setServer1(std::string value);
	std::string getServer2() const;
	void setServer2(std::string value);
	std::string getServer3() const;
	void setServer3(std::string value);
	unsigned short getPort() const;
	void setPort(unsigned short value);
	std::string getMacro(unsigned short index) const;
	void setMacro(unsigned short index, std::string macro);

	void readConfig();
	bool save();

	static Settings* getInstance(bool temp = false);
};


#endif 
