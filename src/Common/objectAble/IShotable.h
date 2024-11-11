#ifndef _I_SHOTABLE_H_
#define _I_SHOTABLE_H_

#include <vector>
#include <boost/any.hpp>

class IShotable
{
public:
	virtual boost::any getNumberShot() = 0;
	virtual void setShotAct() = 0;
	virtual void setNumberShot(boost::any &newValue) = 0;
};

#endif /* _I_SHOTABLE_H_ */
