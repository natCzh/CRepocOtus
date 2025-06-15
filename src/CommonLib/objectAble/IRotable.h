#ifndef _I_ROTABLE_H_
#define _I_ROTABLE_H_

#include <vector>
#include <boost/any.hpp>

class IRotable
{
public:
	virtual boost::any getDirecton() = 0;
	virtual boost::any getDirectonAngular() = 0;
	virtual boost::any getDirectonNumber() = 0;
	virtual void setDirection(boost::any &newValue) = 0;
	//virtual void setDirectionAngular(boost::any &newValue) = 0; // ���� �������������� 1 ��� -1 (������ �������, �� �������)
};

#endif /* _I_ROTABLE_H_ */
