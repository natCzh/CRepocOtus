#ifndef _U_OBJECT_H_
#define _U_OBJECT_H_

#include <boost/any.hpp>

#include <string>
#include <unordered_map>

class UObject
{
public:
	/// [out] - error
	/// [in-out] nameProperty
	/// [in-out] value
	virtual int getProperty(const std::string &nameProperty, boost::any &value) = 0;
	virtual int setProperty(const std::string &nameProperty, boost::any newValue) = 0;

	virtual int getNumberProperty() = 0;
	virtual int getPropertyIter(unsigned int iter, std::string &nameProperty, boost::any &value) = 0;
};

#endif /* _U_OBJECT_H_ */
