#include "EJBindingBase.h"
#include "EJCanvasGradient.h"

class EJBindingCanvasGradient : public EJBindingBase {
public:
        EJCanvasGradient *gradient;
        EJ_BIND_FUNCTION_DEFINE(createLinearGradient, ctx, argc, argv );
        
private:        
        //JSObjectRef* createJSObjectWithContext(JSContextRef ctx, EJJavaScriptView *scriptView, EJCanvasGradient *gradient);
        EJCanvasGradient *gradientFromJSValue(JSValueRef value);
        ~EJBindingCanvasGradient(addColorStop, ctx, argc, argv);
};

