
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

