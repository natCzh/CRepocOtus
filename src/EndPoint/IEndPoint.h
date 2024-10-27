#ifndef _I_END_POINT_H_
#define _I_END_POINT_H_

// Класс то образом принимает запрос, конвертирует в json -> string -> IMessage -> InterpretCommand
class IEndPoint
{
public:

	virtual ~IEndPoint() {}
};

#endif /* _I_END_POINT_H_ */
