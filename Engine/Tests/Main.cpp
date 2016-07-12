#include "Macros.h"
#include <stdio.h>
#include "PIL/Timer/Timer.h"
#include <time.h>
#include <random>
#include "PIL/Platform/Window.h"
#include "Tests/Classes.h"



int main(int argc, char** argv)
{
	
	VSharedPointer<GameObject> sp = Object::Instantiate<GameObject>();
	sp->ObjectID = 21241;
	VSharedPointer<GameObject> child = Object::Instantiate<GameObject>();
	child->ObjectID = 1111;
	
	sp->Children.push_back(child);

	VSharedPointer<GameObject> spCopy = GameObject::Instantiate(sp);

	TEST(GameObjectSer)
	{
		VSharedPointer<GameObject> go1 = std::make_shared<GameObject>();
		go1->ObjectID = 1;

		for (int i = 0; i < 3; i++)
		{
			go1->Children.push_back(std::make_shared<GameObject>());
			go1->Children[i]->ObjectID = 1 + i + 1;
		}


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