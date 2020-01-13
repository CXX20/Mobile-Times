#ifndef UTHEADER_SCRIPT
#define UTHEADER_SCRIPT
#include <map>
#include <set>
#include "globals.h"

namespace ut {
class Script
{
public:
	struct Demand
	{
		enum class Type;

		Demand();
		Demand(const Type&, const std::set<int>&);
		virtual ~Demand();

		Type type;
		std::set<int> ids;
	};
	struct ConstructorParameter
	{
		ConstructorParameter()
		{}
		virtual ~ConstructorParameter()
		{}

		int id;
		bool hasToBeCalled;
		bool canRepeat;
		std::map<int, Demand> idToDemand;
		std::pair<int, int> idCalledAndTimeWaited;
	};

	Script();
	Script(const ConstructorParameter&);
	virtual ~Script();

	const int cId;
	// happen-conditions:
	const bool cHasToBeCalled;
	const bool cCanRepeat;
	const std::map<int, Demand> cIdToDemand;
	// if conditions are ok:
	// .first = script id, .second = time waited:
	const std::pair<int, int> cIdCalledAndTimeWaited;

	const auto& get_hasHappened()
	{
		return mHasHappened;
	}

	void set_hasHappened(const bool& dcHasHappened)
	{
		mHasHappened = dcHasHappened;
	}

private:
	static int smIdNext;
	bool mHasHappened;
};

} // namespace ut;

#endif // ! UTHEADER_SCRIPT;

