#include <string>
#include <memory>
#include <unordered_map>

class UObject
{
public:
	/// [out] - error
	/// [in-out] nameProperty
	/// [in-out] value
	virtual int getProperty(const std::string &nameProperty, int &value) = 0;
	virtual int setProperty(const std::string &nameProperty, int newValue) = 0;
};

class StateShip: public UObject
{
public:

	StateShip()
	{
		mapKey["position_x"] = 0;
		mapKey["position_y"] = 0;
		mapKey["velocity_x"] = 0;
		mapKey["velocity_y"] = 0;
		mapKey["direction"] = 0;
		mapKey["angleRotate"] = 0;
	}

	virtual ~StateShip() {};

	/// [out] - error
	/// [in-out] nameProperty
	/// [in-out] value
	int getProperty(const std::string &nameProperty, int &value) override
	{
		auto iter = mapKey.find(nameProperty);
		if (iter == mapKey.end())
			return 1;

		value = iter->second;
		return 0;
	}

	int setProperty(const std::string &nameProperty, int newValue) override
	{
		auto iter = mapKey.find(nameProperty);
		if (iter == mapKey.end())
			return 1;

		iter->second = newValue;
		return 0;
	}

private:

	std::unordered_map<std::string, int> mapKey;
};

/*class MoveCommand : public IMovable
{
	IMovable0;

};*/

class ICommand
{
public:
	virtual int Execute() = 0;
};

class MoveCommand: ICommand
{
public:
	MoveCommand(const std::shared_ptr<UObject> &obj)
		: o(obj)
	{}

	// return 0 - ok,
	 // 1 - error
	int Execute()
	{
		int posCur, velCur;
		int errorCode = o->getProperty("position_x", posCur);
		if (errorCode)
			return 1;
		errorCode = o->getProperty("velocity_x", velCur);
		if (errorCode)
			return 1;
		o->setProperty("position_x", posCur + velCur);

		errorCode = o->getProperty("position_y", posCur);
		if (errorCode)
			return 1;
		errorCode = o->getProperty("velocity_y", velCur);
		if (errorCode)
			return 1;
		o->setProperty("position_y", posCur + velCur);

		return 0;
	}

private:
	std::shared_ptr<UObject> o;
};

class RotateCommand: ICommand
{
public:
	RotateCommand(const std::shared_ptr<UObject> &obj)
		: o(obj)
	{}

	// return 0 - ok,
	 // 1 - error
	int Execute()
	{
		int dirCur, angleRotCur;
		int errorCode = o->getProperty("direction", dirCur);
		if (errorCode)
			return 1;
		errorCode = o->getProperty("angleRotate", angleRotCur);
		if (errorCode)
			return 1;
		o->setProperty("direction", dirCur + angleRotCur);

		return 0;
	}

private:
	std::shared_ptr<UObject> o;
};