#ifndef V_OBJECT
#define V_OBJECT

class Object
{
	friend class SceneLoader;
private:
	static unsigned int _count;
	unsigned int _instance;
	
	bool _indestructable;
protected:

public:
	Object();
	~Object();

	//copy ctor
	Object(const Object& other);

	//ovrridable condition checks
	virtual bool operator==(Object& o);
	virtual bool operator!=(Object& o);

	//makes an object indestructable
	void MakeIndestructable();

	//inline getters/setters
	inline bool Indestructable()
	{
		return _indestructable;
	}

};

#endif