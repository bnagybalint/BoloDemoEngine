

// ----------------
// Class: AbstractCallback
// Common base for member and static function callback mechanisms
//
template<typename Ret DLG_TEMPLATE_LIST>
class AbstractCallback<Ret(DLG_TYPE_LIST)>
{
public:

	typedef AbstractCallback<Ret(DLG_TYPE_LIST)> ThisClassType;

public:

	virtual ~AbstractCallback()
	{
	}

	virtual Ret call(DLG_PARAMETER_LIST) = 0;
	virtual ThisClassType* clone() = 0;
	virtual bool equals(const ThisClassType& other) = 0;

	int getType() const {
		return mType;
	}

protected:

	AbstractCallback(int type)
		: mType(type)
	{
	}

protected:

	int mType;
};

// ----------------
// Class: StaticCallback
// Represents/stores a static function call.
// 
template<typename Ret DLG_TEMPLATE_LIST>
class StaticCallback<Ret(DLG_TYPE_LIST)> : public AbstractCallback<Ret(DLG_TYPE_LIST)>
{
public:

	typedef StaticCallback<Ret(DLG_TYPE_LIST)>   ThisClassType;
	typedef AbstractCallback<Ret(DLG_TYPE_LIST)> ParentClassType;

	typedef Ret (*FunctionType)(DLG_TYPE_LIST);

public:

	StaticCallback(FunctionType func)
		: ParentClassType(0)
		, mFunction(func)
	{
	}

	Ret call(DLG_PARAMETER_LIST) override
	{
		return mFunction(DLG_ARGUMENT_LIST);
	}

	ParentClassType* clone() override
	{
		return new ThisClassType(mFunction);
	}

	bool equals(const ParentClassType& other) override
	{ 
		if (getType() != other.getType())
			return false;
		const ThisClassType* otherPtr = static_cast<const ThisClassType*>(&other);
		return mFunction == otherPtr->mFunction;
	}

private:

	FunctionType mFunction;
};

// ----------------
// Class: MethodCallback
// Represents/stores a member function call of an object.
// 
template<typename Obj, typename Ret DLG_TEMPLATE_LIST>
class MethodCallback<Obj, Ret(DLG_TYPE_LIST)> : public AbstractCallback < Ret(DLG_TYPE_LIST) >
{
public:

	typedef MethodCallback<Obj, Ret(DLG_TYPE_LIST)> ThisClassType;
	typedef AbstractCallback<Ret(DLG_TYPE_LIST)>    ParentClassType;

	typedef Ret(Obj::*MemberFunctionType)(DLG_TYPE_LIST);

public:

	MethodCallback(Obj* obj, MemberFunctionType func)
		: ParentClassType(1)
		, mObject(obj)
		, mMemberFunction(func)
	{
	}

	Ret call(DLG_PARAMETER_LIST) override
	{
		return (mObject->*mMemberFunction)(DLG_ARGUMENT_LIST);
	}

	ParentClassType* clone() override
	{
		return new ThisClassType(mObject, mMemberFunction);
	}

	bool equals(const ParentClassType& other) override
	{
		if (getType() != other.getType())
			return false;
		const ThisClassType* otherPtr = static_cast<const ThisClassType*>(&other);
		return (mObject == otherPtr->mObject) && (mMemberFunction == otherPtr->mMemberFunction);
	}

private:

	Obj*               mObject;
	MemberFunctionType mMemberFunction;
};

// ----------------
// Class: Delegate
// Represents/stores a generic function call. Hides the differences of using 
// static and member functions, making it something like the delegate 
// concept of C#.
// 
template<typename Ret DLG_TEMPLATE_LIST>
class Delegate<Ret(DLG_TYPE_LIST)>
{
public:

	typedef AbstractCallback<Ret(DLG_TYPE_LIST)> AbstractCallbackType;
	typedef Delegate<Ret(DLG_TYPE_LIST)>         ThisClassType;

public:

	Delegate()
		: mCallback(NULL)
	{
	}

	Delegate(Ret(*func)(DLG_TYPE_LIST))
		: mCallback(new StaticCallback<Ret(DLG_TYPE_LIST)>(func))
	{
	}

	template <typename Obj>
	Delegate(Obj* obj, Ret(Obj::*func)(DLG_TYPE_LIST))
		: mCallback(new MethodCallback<Obj, Ret(DLG_TYPE_LIST)>(obj, func))
	{
	}

	Delegate(const ThisClassType& other)
		: mCallback(other.mCallback->clone())
	{
	}

	~Delegate()
	{
		Assert(mCallback);
		delete mCallback; mCallback = NULL;
	}

	ThisClassType& operator = (const ThisClassType& other)
	{
		if (this == &other)
			return *this;
		if (mCallback)
			delete mCallback;
		mCallback = other.mCallback->clone();
		return *this;
	}

	bool operator == (const ThisClassType& other)
	{
		return mCallback->equals(other.mCallback);
	}

	Ret operator () (DLG_PARAMETER_LIST)
	{
		Assert(mCallback);
		return mCallback->call(DLG_ARGUMENT_LIST);
	}

private:

	AbstractCallbackType* mCallback;
};

// ----------------
// Class: Callback
// Extension to the Delegate class that also stores the call-arguments 
// of the delegate call. This makes them very convenient to use as callbacks.
// (E.g. when we want delayed execution of a function)
//
template<typename Ret DLG_TEMPLATE_LIST>
class Callback<Ret(DLG_TYPE_LIST)> : public CallbackBase
{
private:
	typedef Delegate<Ret(DLG_TYPE_LIST)> DelegateType;
	typedef Tuple<DLG_TYPE_LIST>         ArgumentsTupleType;
public:
	Callback(const DelegateType& dlg DLG_PARAMETER_LIST_WITH_COMMA)
		: mDelegate(dlg)
		, mArguments(DLG_ARGUMENT_LIST)
	{
	}

	Callback(const Callback& other)
		: mDelegate(other.mDelegate)
		, mArguments(other.mArguments)
	{
	}

	~Callback() {}

	Ret operator () (DLG_PARAMETER_LIST)
	{
		return mDelegate(DLG_ARGUMENT_LIST_TUPLE(mArguments));
	}

	void call () override
	{
		mDelegate(DLG_ARGUMENT_LIST_TUPLE(mArguments));
	}

private:
	Callback();

private:
	DelegateType mDelegate;
	ArgumentsTupleType mArguments;
};
