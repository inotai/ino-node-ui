#ifndef __UI_TRAITS_H__
#define __UI_TRAITS_H__

namespace ui { namespace traits {

	template<class T>
	struct TByRef
	{
		typedef T StorageType;
		typedef const T & PassType;
	};

	template<class T>
	struct TByVal
	{
		typedef T StorageType;
		typedef T PassType;
	};

	template<class TupleT>
	struct Tuple : public TByRef<TupleT>
	{};

	typedef TByRef<std::wstring> String;
	typedef TByVal<bool> Boolean;
	typedef TByVal<int> Integer;
	typedef TByVal<float> Float;

}}

#endif // __UI_TRAITS_H__