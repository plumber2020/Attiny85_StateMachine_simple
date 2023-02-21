#include "Transaction.h"

Transaction::Transaction(condition_func cond, action_func act) :
	cond(cond), act(act)
{
}
