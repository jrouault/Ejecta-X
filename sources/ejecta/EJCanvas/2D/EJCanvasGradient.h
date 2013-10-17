#include "EJCanvas2DTypes.h"
#include "../EJCanvasContext.h"
#include "../EJTexture.h"
#include "../../Foundation/NSMutableArray.h"
#include "../../Foundation/NSData.h"

#define EJ_CANVAS_GRADIENT_WIDTH 1024

typedef enum {
	kEJCanvasGradientTypeLinear,
	kEJCanvasGradientTypeRadial
} EJCanvasGradientType;

typedef struct {
	float pos;
	int order;
	EJColorRGBA color;
} EJCanvasGradientColorStop;

class EJCanvasGradient : public EJFillable {
public:
	EJCanvasGradientType type;
	EJVector2 p1, p2;
	float r1, r2;
	
	NSMutableArray *colorStops;
	EJTexture *texture;

private:
        bool initLinearGradientWithP1(EJVector2 p1, EJVector2 p2);
        bool initRadialGradientWithP1(EJVector2 p1, float r1, EJVector2 p2, float r2);
        
        void addStopWithColor(EJColorRGBA color, float pos);
        void rebuild();
        
        ~EJCanvasGradient();
            
        NSData * getPixelsWithWidth(int width, NSArray stops);
                    
        EJCanvasGradientType type;
        EJTexture *texture;
        EJVector2 p1;
        EJVector2 p2;
        float r1;
        float r2;
};
