#ifndef CERRINFO_H
#define CERRINFO_H
#include <string>

class CErrInfo
{
public:
    CErrInfo();
    void ShowInfo(
            const char* strUsrInfo,
            int nErrCode,
            const char* strSysErr);
};

#endif // CERRINFO_H
