#include "pch.h"
#include "RegDM.h"

//创建新的大漠对象
Idmsoft* InitNewDm()
{
    Idmsoft* m_dm = NULL;
    //COleVariant temp1,temp2;
    bool m_bInit = false;

    //下面直接加载dll创建对象，避免进行注册文件
    typedef HRESULT(__stdcall* pfnGCO) (REFCLSID, REFIID, void**);
    pfnGCO fnGCO = NULL;
    HINSTANCE hdllInst = LoadLibrary(L"dm.dll");
    fnGCO = (pfnGCO)GetProcAddress(hdllInst, "DllGetClassObject");
    if (fnGCO != 0)
    {
        IClassFactory* pcf = NULL;
        HRESULT hr = (fnGCO)(__uuidof(dmsoft), IID_IClassFactory, (void**)&pcf);
        if (SUCCEEDED(hr) && (pcf != NULL))
        {
            hr = pcf->CreateInstance(NULL, __uuidof(Idmsoft), (void**)&m_dm);
            if ((SUCCEEDED(hr) && (m_dm != NULL)) == FALSE)
                return false;
        }
        pcf->Release();
        m_bInit = true;
    }
    else
        m_bInit = false;

    return m_dm;
};