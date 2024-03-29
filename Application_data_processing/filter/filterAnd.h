#pragma once
#include "zlozenyFilter.h"
template <typename O>
class Filter_AND : public ZlozenyFilter<O>
{
public:
	bool pass(O obj) override;
	void vyfiltruj(structures::SortedSequenceTable<std::string, UzemnaJednotka*>& table,
		structures::UnsortedSequenceTable<std::string, UzemnaJednotka*>& newTable) override;
	Filter_AND() = default;
	Filter_AND(const ZlozenyFilter<UzemnaJednotka*>& other);
};

template<typename O>
inline bool Filter_AND<O>::pass(O obj)
{
	if (ZlozenyFilter<O>::filtre_.size() == 0)
	{
		return true;
	}
	for (auto filter : ZlozenyFilter<O>::filtre_)
	{
		if (!filter->pass(obj))
		{
			return false;
		}
	}
	return true;
}

template <typename O>
void Filter_AND<O>::vyfiltruj(structures::SortedSequenceTable<std::string, UzemnaJednotka*>& table,
	structures::UnsortedSequenceTable<std::string, UzemnaJednotka*>& newTable)
{

	for (const auto element : table)
	{
		if (pass(element->accessData()))
		{
			newTable.insert(element->getKey(), element->accessData());
		}

	}

}

template <typename O>
Filter_AND<O>::Filter_AND(const ZlozenyFilter<UzemnaJednotka*>& other)
{
	if (this != &other) {
		ZlozenyFilter<O>::filtre_.assign(other.filtre_);
	}
	return *this;
}
