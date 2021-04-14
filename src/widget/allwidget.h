#ifndef ALLWIDGET_H
#define ALLWIDGET_H

#include "loginwidget.h"
#include "registwidget.h"
#include "startview.h"
#include "settingwidget.h"
#include "carcorderwidget.h"
#include "showimagewidget.h"
#include "showvideowidget.h"
#include "decodewidget.h"

class AllWidget
{
public:
    AllWidget();
    static LoginWidget *pLoginWidget;
    static RegistWidget *pRegistWidget;
    static StartView *pStarview;
    static SettingWidget *pSettingWidget;
    static CarcorderWidget *pCarcorderWidget;
    static ShowImageWidget *pShowImageWidget;
    static ShowVideoWidget *pShowVideoWidget;
    static DecodeWidget *pDecodeWidget;
};

#endif // ALLWIDGET_H
