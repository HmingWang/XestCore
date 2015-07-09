#ifndef _IDENTITY_CARD_HPP_
#define _IDENTITY_CARD_HPP_
#include "ObjectCard.hpp"

class IdentityCard : public ObjectCard
{
public:
	char GetIdentity();
private:
	char identity; //Identity: L lord M minister T traitor S spay
};

char IdentityCard::GetIdentity()
{
	return identity;
}

#endif