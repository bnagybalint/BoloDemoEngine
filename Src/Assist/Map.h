#pragma once

#include "Assist/Common.h"

// TODO eliminate std
#include <map>
#include <utility>

template <class Key, class Value>
class Map
{
public:

	Map();
	Map(const Map<Key,Value>& other);
	~Map();

	void add(const Key& key, const Value& val);
	bool remove(const Key& key);

	void clear();
	bool isEmpty();

	const Value& operator[] (const Key& key) const;
	Value& operator[] (const Key& key);

	const Value& get(const Key& key) const;
	Value& get(const Key& key);
	const Value* find(const Key& key) const;
	Value* find(const Key& key);

	bool contains(const Key& key) const;

private:

	std::map<Key, Value> mValueMap;
};

// TODO create real ObjectDictionary
template <class Key, class Value>
class ObjectMap : public Map<Key, Value> {};




template <class Key, class Value>
Map<Key, Value>::Map()
{

}

template <class Key, class Value>
Map<Key, Value>::Map(const Map<Key, Value>& other)
{
	mValueMap.insert(other.mValueMap.begin(), other.mValueMap.end());
}

template <class Key, class Value>
Map<Key, Value>::~Map()
{
}

template <class Key, class Value>
void Map<Key, Value>::add(const Key& key, const Value& val)
{
	mValueMap.insert(std::make_pair(key, val));
}

template <class Key, class Value>
bool Map<Key, Value>::remove(const Key& key)
{
	Assert(contains(key));
	return mValueMap.erase(key) > 0;
}

template <class Key, class Value>
void Map<Key, Value>::clear()
{
	mValueMap.clear();
}

template <class Key, class Value>
bool Map<Key, Value>::isEmpty()
{
	return mValueMap.empty();
}

template <class Key, class Value>
const Value& Map<Key, Value>::operator[] (const Key& key) const
{
	const Value* val = find(key);
	Assert(val);
	return *val;
}

template <class Key, class Value>
Value& Map<Key, Value>::operator[] (const Key& key)
{
	Value* val = find(key);
	Assert(val);
	return *val;
}

template <class Key, class Value>
const Value& Map<Key, Value>::get(const Key& key) const
{
	const Value* val = find(key);
	Assert(val);
	return *val;
}

template <class Key, class Value>
Value& Map<Key, Value>::get(const Key& key)
{
	Value* val = find(key);
	Assert(val);
	return *val;
}

template <class Key, class Value>
const Value* Map<Key, Value>::find(const Key& key) const
{
	std::map<Key,Value>::const_iterator it = mValueMap.find(key);
	if (it == mValueMap.end())
		return NULL;
	return &it->second;
}

template <class Key, class Value>
Value* Map<Key, Value>::find(const Key& key)
{
	std::map<Key, Value>::iterator it = mValueMap.find(key);
	if (it == mValueMap.end())
		return NULL;
	return &it->second;
}

template <class Key, class Value>
bool Map<Key,Value>::contains(const Key& key) const
{
	std::map<Key, Value>::const_iterator it = mValueMap.find(key);
	return it != mValueMap.end();
}

