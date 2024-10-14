#ifndef _I_O_C_H_
#define _I_O_C_H_

class IoC
{
	template<>
	public static T Resolve<T>(const string &key, params object[] args);
};



#endif /* _I_O_C_H_ */