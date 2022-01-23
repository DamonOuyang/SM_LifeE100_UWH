#include "ErrorMappingFactory.h"

#include <assert.h>

#include <sstream>
#include <iomanip>
using namespace std;

static const string s_ECM="ECM";

string ErrorMappingFactory::mappingAdmErrorCode(EAdmErrorCode err)
{
	string ret;
	switch(err)
	{
	case eAdmErrFileIO:
		ret=s_ECM;
		break;
	default:
		assert(false);
		break;
	}
	return ret;
}

string ErrorMappingFactory::mappingSysErrorCode(ESysErrorCode err)
{
	string ret;
	switch(err)
	{
	case eSysErrReadFile:
	case eSysErrWriteFile:
		ret=s_ECM;
		break;
	case eSysNoMachineConnected:
		ret="EC_2";
		break;
	case eSysNoReady:
		ret="EC_3";
		break;
	case eSysNoPaymentDevice:
		ret="EC_4";
		break;
	case eSysInternal:
		ret="EC_5";
		break;
    case  eNoInternet:
        ret = "EC_6";
        break;
    case eNoInternet2:
        ret = "EC_7";
        break;
    case eNoInternet3:
        ret = "EC_8";
        break;

	default:
		assert(false);
		break;
	}
	return ret;
}

string ErrorMappingFactory::mappingBoardErrorCode(unsigned char boardId)
{
	ostringstream os;
	os << "ECE" << "_" << static_cast<int>(boardId);
	return os.str();
}

string ErrorMappingFactory::mappingPaymentErrorCode(ErrorPaymentType_t paymentType, unsigned char err)
{
	ostringstream os;
	switch(paymentType)
	{
	case PT_COIN:
		os << "EA";
		break;
	case PT_BILL_READER:
		os << "EN";
		break;
	case PT_CARD1:
		os << "EK";
		break;
	case PT_CARD2:
		os << "EK2";
		break;
	default:
		assert(false);
		break;
	}
	os << "_" << static_cast<int>(err);
	return os.str().c_str();
}

string ErrorMappingFactory::mappingStatWarning(EStatWarning warning)
{
	string ret;
	switch(warning)
	{
	case eCupStorage:
		ret="EFB_6";
		break;
	case ePowderBeanStorage:
		ret="EFB_7";
		break;
	case eChangeHotWaterFilter:
		ret="EFB_8";
		break;
	case eChangeColdWaterFilter:
		ret="EFB_9";
		break;
    case eInternetConnectError:
        ret = "INT_1";
        break;
    case eInternetConnectError2:
        ret = "INT_2";
        break;
    case eHopperMotor:
        ret = "HOPPER_1";
        break;
    case eHopperLowLevel:
        ret = "HOPPER_2";
        break;
    case eHopperPrism:
        ret = "HOPPER_3";
        break;
    case eHopperShaft:
        ret = "HOPPER_4";
        break;
    case eHopperBusy:
        ret = "HOPPER_5";
        break;
	default:
		assert(false);
		break;
	}
	return ret;
}
