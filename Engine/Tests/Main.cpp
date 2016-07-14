#include "Macros.h"
#include <stdio.h>
#include "PIL/Timer/Timer.h"
#include <time.h>
#include <random>
#include "PIL/Platform/Window.h"
#include "Tests/Classes.h"



int main(int argc, char** argv)
{
	
	TEST(GameObjectSer)
	{
		VSharedPointer<GameObject> go1 = std::make_shared<GameObject>();
		go1->Name = "MyName";

		std::ofstream oss("test.xml", std::ios::binary);
		cereal::XMLOutputArchive archive1(oss);

		archive1(cereal::make_nvp("GameObject", go1));

	}
	END()

	TEST(GameObjectDeser)
	{
		VSharedPointer<GameObject> go;

		std::ifstream iss("test.xml", std::ios::binary);
		cereal::XMLInputArchive archive1(iss);

		archive1(go);

		

	}
	END()


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