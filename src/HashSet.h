/**
 * A hash set.
 * Stub written by James Daly, 8 Oct 2014
 * Completed by [YOUR NAME]
 */
#pragma once

#ifndef HASH_SET_H
#define HASH_SET_H

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

template<class T>
class HashSet
{
public:
	HashSet(std::function<unsigned int(const T&)> hash, double loadFactor);
	HashSet(HashSet<T> &other);
	virtual ~HashSet();
	
	// Supplied Methods
	bool IsEmpty() const { return Size() == 0; }
	unsigned int Size() const { return size; }
	double GetLoadFactor() const { return loadFactor; }
	void DisplayItems() const { ForEach([](const T& item) { std::cout << item << std::endl; }); }
	double GetLoad() const { return ((double)Size()) / (double)NumBuckets(); }
	
	// Methods that you must complete
	unsigned int NumBuckets() const { /* TODO */ return mItems.size(); }
	bool Contains(const T& item) const;
	bool Insert(const T &item);
	bool Remove(const T &item);
	void Clear();
	void ForEach(std::function<void (const T&)> func) const;
	unsigned int MaxBucketSize() const;
	double PercentEmptyBuckets() const;
	
private:
	unsigned int size;
	double loadFactor;
	std::function<unsigned int (const T&)> hash;
	
	// You need some data source to store items
	std::vector< std::vector<T> > mItems;
	
	// You can put any helper methods here

	void rehash()
	{
		std::vector< std::vector<T> > clone = mItems;
		Clear();
		mItems.assign(NumBuckets() * 2, std::vector<T>());
		for (auto &t : clone)
		{
			for (auto &w : t)
			{
				Insert(w);
			}
		}
	}
};

/**
 * Default constructor
 */
template<class T>
HashSet<T>::HashSet(std::function<unsigned int(const T&)> hash, double loadFactor):
	size(0),
	loadFactor(loadFactor),
	hash(hash)
{
	// Empty: You can put other initialization information here
	for (unsigned int i = 0; i < 18; i++)
	{
		std::vector<T> item;
		mItems.push_back(item);
	}
}

/**
 * Copy Constructor
 * Uses uniform instantiation to initialize itself
 * and then copies all of the items from the other set
 */
template<class T>
HashSet<T>::HashSet(HashSet<T> &other) : HashSet(other.hash, other.loadFactor)
{
	auto insertItem = [=](const T& x){ this->Insert(x); };
	other.ForEach(insertItem);
}

/**
 * Destructor
 * Any cleanup you need to do can be done here
 */
template<class T>
HashSet<T>::~HashSet()
{
	// Empty: You can put any steps necessary for cleanup here
}

/**
 * Returns true iff the item is in the set
 */
template<class T>
bool HashSet<T>::Contains(const T &item) const		//DONE
{
	const std::vector<T> &bucket = mItems[hash(item) % NumBuckets()];
	auto a = find(bucket.begin(), bucket.end(), item);
	if (a != bucket.end())
		return true;
	return false;
}

/**
 * Inserts the item into the set.
 * Only one copy can exist in the set at a time.
 * Returns true iff the item was successfully added.
 */
template<class T>
bool HashSet<T>::Insert(const T &item)		//DONE
{
	if (!Contains(item))
	{
		unsigned int j = hash(item) % NumBuckets();

		mItems[j].push_back(item);
		size++;

		if (GetLoad() > GetLoadFactor())
		{
			rehash();
		}
		return true;
	}
		
	
 	return false;
}

/**
 * Removes the item from the set.
 * Returns true iff the item was successfully removed.
 */
template<class T>
bool HashSet<T>::Remove(const T &item)
{
	const std::vector<T> &bucket = mItems[hash(item) % NumBuckets()];
	auto itr = find(bucket.begin(), bucket.end(), item);
	
	if (itr != bucket.end())
		mItems.erase(itr);
		return true;
	return false;
}

/**
 * Removes all elements from the set.
 */
template<class T>
void HashSet<T>::Clear()
{
	for (auto &t : mItems)
	{
		t.clear();
	}
	size = 0;
}

/**
 * Invokes the function once on each item in the set.
 * The exact order is undefined.
 */
template<class T>
void HashSet<T>::ForEach(std::function<void (const T&)> func) const
{
	for (auto &t : mItems)
	{
		for (auto &w : t)
		{
			func(w);
		}
	}
}

/**
 * Finds the maximum number of items in a bucket.
 */
template<class T>
unsigned int HashSet<T>::MaxBucketSize() const
{
	unsigned int MaxSize = 0;
	for (auto i : mItems)
	{
		unsigned int CurrSize = i.size();
		if (CurrSize > MaxSize)
			MaxSize = CurrSize;
	}
	return MaxSize;
}

/**
 * Finds which fraction of the buckets are empty
 * The result is returned as a percent
 */
template<class T>
double HashSet<T>::PercentEmptyBuckets() const
{
	double numEmptyBuckets = 0;
	for (auto t : mItems)
	{
		if (t.empty())
			numEmptyBuckets++;
	}
	return numEmptyBuckets/NumBuckets();
}

#endif