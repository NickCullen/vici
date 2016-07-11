#include "Macros.h"
#include <stdio.h>
#include "PIL/Timer/Timer.h"
#include "Core/EngineIncludes.h"
#include <time.h>
#include <random>
#include "PIL/Platform//Window.h"

class TestSerializationClass
{
public:
	int x;

	float y;

	VString name;

	VArray<VString> MyArray;

	TestSerializationClass()
	{
		x = 5;
		y = 42.66f;
		name = "ThisIsMyName";

		MyArray.push_back(VString("String1"));
		MyArray.push_back(VString("String2"));
		MyArray.push_back(VString("String3"));
		MyArray.push_back(VString("String4"));
	}

	template< class Archive >
	void serialize(Archive & ar)
	{
		ar(CEREAL_NVP(x), CEREAL_NVP(y), CEREAL_NVP(name), CEREAL_NVP(MyArray));
	}
};

int main(int argc, char** argv)
{
	srand(time(nullptr));

	VWindow win;
	win.SetTitle("MyGame");
	win.SetSize(1920, 1080);
	win.SetPosition(0, 0);
	
	std::ofstream oss("Window.xml", std::ios::binary);
	cereal::XMLOutputArchive archive1(oss);

	archive1(win);

	return 1;

	TEST(Serialization)
	{
		std::ofstream os("out.cereal", std::ios::binary);
		cereal::XMLOutputArchive archive(os);

		TestSerializationClass myData;
		archive(myData);
	}
	END()


	TEST(Deserialize)
	{
		std::ifstream is("out.cereal", std::ios::binary);
		cereal::XMLInputArchive archive(is);

		TestSerializationClass myData;
		archive(myData);
		
		printf("Hello");
	}
	END()

	return 0;
}