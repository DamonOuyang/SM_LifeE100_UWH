#ifndef _ERROR_MAPPING_FACTORY_H_
#define _ERROR_MAPPING_FACTORY_H_

#include "common.h"

#include "adm_err.h"
#include "sys_err.h"
#include "paymenterror.h"
#include "stat_warning.h"

#include <string>
using namespace std;

class ErrorMappingFactory
{
public:
	static string mappingAdmErrorCode(EAdmErrorCode err);
	static string mappingSysErrorCode(ESysErrorCode err);
	static string mappingBoardErrorCode(unsigned char boardId);
	static string mappingPaymentErrorCode(ErrorPaymentType_t paymentType, unsigned char err);
	static string mappingStatWarning(EStatWarning warning);
};

#endif
