// DepositSlot.cpp
// Member-function definition for class DepositSlot.
#include "DepositSlot.h" // DepositSlot class definiton

// indicates whether envelope was received (always returns true,
// because this is only a software simulation of a real deposit slot)
bool DepositSlot::isEnvelopeReceived() const
{
	return true; // deposit envelope was received
} // end function isEnvelopeReceived
