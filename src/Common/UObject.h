#ifndef _U_OBJECT_H_
#define _U_OBJECT_H_

#include <boost/any.hpp>

#include <string>
#include <unordered_map>

class UObject
{
public:
	/// [out] - error
	/// [in] nameProperty
	/// [out] value
	virtual boost::any getProperty(const std::string &nameProperty) = 0;
	virtual void setProperty(const std::string &nameProperty, boost::any newValue) = 0;

	virtual int getNumberProperty() = 0;
	virtual boost::any getPropertyIter(unsigned int iter, std::string &nameProperty) = 0;
};

#endif /* _U_OBJECT_H_ */
