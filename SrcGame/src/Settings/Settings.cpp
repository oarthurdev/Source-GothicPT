#include "Settings.h"
#include "File\File.h"
#include "Log\Log.h"

Settings settings;
Settings settings_temp;


Settings::Settings()
{
	windowed = false;
	textureQuality = 0;
	bpp = 0;
	networkQuality = 0;
	cameraInv = false;
	motionBlur = false;
	cameraSight = false;
	width = 0;
	height = 0;
	resolution = 0;
	sound = false;
	weather = false;
	server1 = "";
	server2 = "";
	server3 = "";
	port = 0;

	rememberID = false;

	readConfig();
}

Settings::~Settings()
{
}

void Settings::readConfig()
{
	try
	{
		File file("config.ini");

		setWindowMode(file.readInt("Screen", "Windowed") != 0);
		setResolution(file.readInt("Screen", "Resolution"));

		if(resolution == 1)
		{
			setWidth(800);
			setHeight(600);
		}
		else if(resolution == 2)
		{
			setWidth(1024);
			setHeight(768);
		}
		else if(resolution == 3)
		{
			setWidth(1280);
			setHeight(960);
		}
		else if(resolution == 4)
		{
			setWidth(1366);
			setHeight(768);
		}
		else if(resolution == 5)
		{
			setWidth(1600);
			setHeight(900);
		}
		else if(resolution == 6)
		{
			setWidth(1920);
			setHeight(1080);
		}
		else if(resolution == 7)
		{
			setWidth(2560);
			setHeight(1080);
		}
		else
		{
			setWidth(800);
			setHeight(600);
		}



		setSight(file.readInt("Camera", "FarSight") != 0);
		setCamInv(file.readInt("Camera", "Inverted") != 0);
		setBitDepth(file.readInt("Graphics", "BitDepth"));
		setTextureQuality(file.readInt("Graphics", "TextureQuality"));
		setSound(file.readInt("Audio", "enabled") != 0);
		setServer1(file.readString("Connect", "IP"));
		setServer2(file.readString("Connect", "IP"));
		setServer3(file.readString("Connect", "IP"));
		setPort(file.readInt("Connect", "PORT"));
		setWheater(file.readInt("Game", "Weather") != 0);
		setRememberID(file.readInt("Game", "RememberID") != 0);

		for(unsigned short i = 0; i < 10; i++)
			setMacro(i, file.readString("Macro", "Macro" + std::to_string(i + 1)));
	}
	catch(FileException &e)
	{
		Log::getInstance()->output(LOG_ERROR, const_cast<char*>(e.what()));
	}
}

bool Settings::save()
{
	try
	{
		File file("config.ini");

		file.write("Screen", "Windowed", getWindowMode() ? 1 : 0);
		file.write("Screen", "Resolution", getResolution());
		file.write("Camera", "FarSight", getSight() ? 1 : 0);
		file.write("Camera", "Inverted", getCamInv() ? 1 : 0);
		file.write("Graphics", "BitDepth", getBitDepth());
		file.write("Graphics", "TextureQuality", getTextureQuality());
		file.write("Audio", "enabled", hasSound() ? 1 : 0);
		file.write("Game", "Weather", getWeather() ? 1 : 0);
		file.write("Game", "RememberID", getRememberID() ? 1 : 0);

		return true;
	}
	catch(FileException &e)
	{
		MessageBox(NULL, e.what(), "Error saving configs", MB_ICONERROR);
	}

	return false;
}

Settings* Settings::getInstance(bool temp)
{
	if(temp)
		return &settings_temp;
	else
		return &settings;
}


bool Settings::getWindowMode() const
{
	return windowed;
}
void Settings::setWindowMode(bool value)
{
	windowed = value;
}
int Settings::getTextureQuality() const
{
	return textureQuality;
}
void Settings::setTextureQuality(int value)
{
	textureQuality = value;
}
int Settings::getBitDepth() const
{
	return bpp;
}
void Settings::setBitDepth(int value)
{
	bpp = value;
}
int Settings::getNetworkQuality() const
{
	return networkQuality;
}
void Settings::setNetworkQuality(int value)
{
	networkQuality = value;
}
bool Settings::getCamInv() const
{
	return cameraInv;
}
void Settings::setCamInv(bool value)
{
	cameraInv = value;
}
bool Settings::isMotionBlur() const
{
	return motionBlur;
}
void Settings::setMotionBlur(bool value)
{
	motionBlur = value;
}
bool Settings::getSight() const
{
	return cameraSight;
}
void Settings::setSight(bool value)
{
	cameraSight = value;
}
int Settings::getWidth() const
{
	return width;
}
void Settings::setWidth(int value)
{
	if(value == 800)
		resolution = 1;
	else if(value == 1024)
		resolution = 2;
	else if(value == 1280)
		resolution = 3;
	else if(value == 1366)
		resolution = 4;
	else if(value == 1600)
		resolution = 5;
	else if(value == 1920)
		resolution = 6;
	else if(value == 2560)
		resolution = 7;
	else
		resolution = 1;

	width = value;
}
int Settings::getHeight() const
{
	return height;
}
void Settings::setHeight(int value)
{
	height = value;
}
int Settings::getResolution() const
{
	return resolution;
}
void Settings::setResolution(int value)
{
	resolution = value;

	switch(resolution)
	{
	case 1:
		setWidth(800);
		setHeight(600);
		break;
	case 2:
		setWidth(1024);
		setHeight(768);
		break;
	case 3:
		setWidth(1280);
		setHeight(960);
		break;
	case 4:
		setWidth(1366);
		setHeight(768);
		break;
	case 5:
		setWidth(1600);
		setHeight(900);
		break;
	case 6:
		setWidth(1920);
		setHeight(1080);
		break;
	case 7:
		setWidth(2560);
		setHeight(1080);
		break;

	default:
		setWidth(800);
		setHeight(600);
		break;
	}
}
bool Settings::isWideScreen() const
{
	
	return ((width / 4) != (height / 3));
}

bool Settings::hasSound() const
{
	return sound;
}
void Settings::setSound(bool value)
{
	sound = value;
}
bool Settings::getWeather() const
{
	return weather;
}
void Settings::setWheater(bool value)
{
	weather = value;
}
bool Settings::getRememberID() const
{
	return rememberID;
}
void Settings::setRememberID(bool value)
{
	rememberID = value;
}
std::string Settings::getServer1() const
{
	return server1;
}
void Settings::setServer1(std::string value)
{
	server1 = value;
}
std::string Settings::getServer2() const
{
	return server2;
}
void Settings::setServer2(std::string value)
{
	server2 = value;
}
std::string Settings::getServer3() const
{
	return server3;
}
void Settings::setServer3(std::string value)
{
	server3 = value;
}
unsigned short Settings::getPort() const
{
	return port;
}
void Settings::setPort(unsigned short value)
{
	port = value;
}

std::string Settings::getMacro(unsigned short index) const
{
	if(index >= 0 || index < 10)
		return macros[index];
	else
		return std::string();
}

void Settings::setMacro(unsigned short index, std::string macro)
{
	if(index >= 0 || index < 10)
	{
		macros[index] = macro;
	}
}
