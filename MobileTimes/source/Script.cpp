#include "Script.h"

using ut::Script;

// Script::Demand:

enum class Script::Demand::Type
{
	error,
	active,
	// but isn't active any more:
	wasActive,
	inactive
};

Script::Demand::Demand()
{
	type = Script::Demand::Type::error;
}
Script::Demand::Demand(const Script::Demand::Type& dcType,
	const std::set<int>& dcIds)
{
	type = dcType;
	ids = dcIds;
}
Script::Demand::~Demand()
{}

// Script:

Script::Script()
	:
	cId(ut::glb::NegativeId::scError),
	cHasToBeCalled(true),
	cCanRepeat(false),
	cIdToDemand(),
	cIdCalledAndTimeWaited(ut::glb::NegativeId::scNone, 0)
{
	mHasHappened = false;
}
Script::Script(const Script::ConstructorParameter& dcParam)
	:
	cId(smIdNext),
	cHasToBeCalled(dcParam.hasToBeCalled),
	cCanRepeat(dcParam.canRepeat),
	cIdToDemand(dcParam.idToDemand),
	cIdCalledAndTimeWaited(dcParam.idCalledAndTimeWaited)
{
	++smIdNext;
	mHasHappened = false;
}

Script::~Script()
{}

// private:

int Script::smIdNext = ut::glb::cIdFirst;