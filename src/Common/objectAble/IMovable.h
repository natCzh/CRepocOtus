#ifndef _I_MOVABLE_H_
#define _I_MOVABLE_H__

#include <vector>
#include <boost/any.hpp>

class IMovable
{
public:
	virtual boost::any getLocation() = 0;
	virtual boost::any getVelocity() = 0;
	virtual void setLocation(boost::any &newValue) = 0;
};

#endif /* _I_MOVABLE_H_ */
