#ifndef __EJ_CONVERT_H__
#define __EJ_CONVERT_H__

#include "EJCanvas2DTypes.h"
#include <JavaScriptCore/JavaScriptCore.h>

#ifdef __cplusplus
extern "C" {
#endif

        EJColorRGBA JSValueToColorRGBA( JSContextRef ctx, JSValueRef value );
        JSValueRef ColorRGBAToJSValue( JSContextRef ctx, EJColorRGBA c );

#ifdef __cplusplus
}
#endif

#endif
