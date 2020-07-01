#include "pch.h"
#include "RegDM.h"

//�����µĴ�Į����
Idmsoft* InitNewDm()
{
    Idmsoft* m_dm = NULL;
    //COleVariant temp1,temp2;
    bool m_bInit = false;

    //����ֱ�Ӽ���dll�������󣬱������ע���ļ�
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