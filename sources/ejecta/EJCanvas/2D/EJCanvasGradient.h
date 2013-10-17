#include "EJCanvas2DTypes.h"
#include "../EJCanvasContext.h"
#include "../EJTexture.h"
#include "../../EJCocoa/NSArray.h"

#define EJ_CANVAS_GRADIENT_WIDTH 1024

typedef enum {
	kEJCanvasGradientTypeLinear,
	kEJCanvasGradientTypeRadial
} EJCanvasGradientType;

typedef struct EJCanvasGradientColorStop {
	float pos;
	int order;
	EJColorRGBA color;
        static int compare(const void *first_arg, const void *second_arg) {
                EJCanvasGradientColorStop first = *(EJCanvasGradientColorStop*)first_arg;
                EJCanvasGradientColorStop second = *(EJCanvasGradientColorStop*)second_arg;

                return (first.pos == second.pos) ? (first.order - second.order) : (first.pos - second.pos);
        }
} EJCanvasGradientColorStop;

class EJCanvasGradient /*: public EJFillable*/ {

private:
        bool initLinearGradientWithP1(EJVector2 p1, EJVector2 p2);
        bool initRadialGradientWithP1(EJVector2 p1, float r1, EJVector2 p2, float r2);
        
        void addStopWithColor(EJColorRGBA color, float pos);
        void rebuild();
        
        ~EJCanvasGradient();
            
        //NSData * getPixelsWithWidth(int width, NSArray stops);
                    
        EJCanvasGradientType type;
        EJTexture *texture;
        EJVector2 p1;
        EJVector2 p2;
        float r1;
        float r2;
	NSArray *colorStops;
};
