#include "EJBindingCanvasGradient.h"
#include "EJConvertColorRGBA.h"

JSObjectRef * EJBindingCanvasGradient::createJSObjectWithContext(ctx, view, gradient) {
    
        EJBindingCanvasGradient *binding = EJBindingCanvasGradient->initWithContext(ctx, 0, NULL];
        binding->gradient = gradient->retain();
	
        JSObjectRef obj = createJSObjectWithContext(ctx, view, binding);
	delete binding;
	return obj;
}

EJCanvasGradient * EJBindingCanvasGradient::gradientFromJSValue(value) {
    	if( !value ) { return NULL; }
	
	EJBindingCanvasGradient *binding = (EJBindingCanvasGradient *)JSObjectGetPrivate((JSObjectRef)value);
	return (binding && [binding isMemberOfClass:[EJBindingCanvasGradient class]]) ? binding->gradient : NULL;
}

EJBindingCanvasGradient::~EJBindingCanvasGradient() {
	delete gradient;
	[super dealloc];
}

EJ_BIND_FUNCTION(EJBindingCanvas, addColorStop, ctx, argc, argv) {
	if( argc < 2 ) { return NULL; }
	
	float offset = JSValueToNumberFast(ctx, argv[0]);
	if( offset < 0 || offset > 1 ) { return NULL; }
	
	EJColorRGBA color = JSValueToColorRGBA(ctx, argv[1]);
	
	gradient->addStopWithColor(color, offset);
	return NULL;
}

REFECTION_CLASS_IMPLEMENT(EJBindingCanvasGradient);