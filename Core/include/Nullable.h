#ifndef _NULLABLE_H
#define _NULLABLE_H

template<typename T>
class Nullable
{
public:
	bool Null;
	T Value;

	Nullable()
	{
		Null = true;
	}
	Nullable(const T &Value)
	{
		Null = false;
		this->Value = Value;
	}
};

#endif
