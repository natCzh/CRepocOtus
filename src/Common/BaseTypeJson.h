#ifndef _BASE_TYPE_JSON_H_
#define _BASE_TYPE_JSON_H_

#include <string>
#include <map>

#include "Base/jsoncpp/json.h"
#include "Base/jsoncpp/jsonutils.h"

namespace commonJson
{
	template <class T>
	struct js_array : public JsonSerializable
	{
		typedef std::vector<T> js_array_type;
		js_array_type data;
		js_array(const std::string &title = "")
			: JsonSerializable(title)
		{}

		void push_back(const T &obj)
		{
			data.push_back(obj);
		}

		void clear()
		{
			data.clear();
		}

		void reserve(std::size_t s)
		{
			data.reserve(s);
		}

		bool read(const Json::Value &jsonObj)
		{
			data.reserve(jsonObj.size());
			for (int i = 0; i < (int)jsonObj.size(); ++i)
			{
				data.push_back(T());
				data.back().read(jsonObj[i]);
			}
			return true;
		}
		/*void write(Json::Value& jsonObj) const
		{
			int dS = (int)data.size();
			jsonObj.resize(dS);
			for (int i = 0; i < dS; ++i)
			{
				data[i].write(jsonObj[i]);
			}
		}*/
		bool isValid() const
		{
			return !data.empty();
		}
	};

	


}

#endif /* _BASE_TYPE_JSON_H_ */