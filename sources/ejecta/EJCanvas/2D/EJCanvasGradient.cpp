#include "EJCanvasGradient.h"
// #include "EJAppViewController.h"


bool EJCanvasGradient::initLinearGradientWithP1(p1p, p2p) {
	if( self = [super init] ) {
		type = kEJCanvasGradientTypeLinear;
		p1 = p1p;
		p2 = p2p;
		
		// colorStops = [[NSMutableArray alloc] initWithCapacity:4];
                colorStops = (NSMutableArray *)->initWithCapacity(4);
	}
	return self;
}

bool EJCanvasGradient::initRadialGradientWithP1(p1p, r1p, p2p, r2p) {
	if( self = [super init] ) {
		type = kEJCanvasGradientTypeRadial;
		p1 = p1p;
		r1 = r1p;
		p2 = p2p;
		r2 = r2p;
		
		colorStops = (NSMutableArray *)->initWithCapacity(4);
	}
	return self;
}

EJCanvasGradient::~EJCanvasGradient() {
	delete texture;
	delete colorStops;
	// [super dealloc];
}

void EJCanvasGradient::addStopWithColor(color, pos) {
	float alpha = (float)color.rgba.a/255.0;
	EJColorRGBA premultiplied = { .rgba = {
		.r = (float)color.rgba.r * alpha,
		.g = (float)color.rgba.g * alpha,
		.b = (float)color.rgba.b * alpha,
		.a = color.rgba.a
	}};
	
	EJCanvasGradientColorStop stop = { .pos = pos, .color = premultiplied, .order = colorStops.count };
	[colorStops addObject:[NSValue value:&stop withObjCType:@encode(EJCanvasGradientColorStop)]];
	
	// Release current texture; it's invalid now
	delete texture;
	texture = NULL;
}

EJTexture * EJCanvasGradient::texture() {
	if( !texture ) {
		rebuild();
	}
	
	return texture;
}

EJCanvasGradient::rebuild() {
	// Sort color stops by positions. If two ore more stops are at the same
	// position, ensure that the one added last (.order) will be on top
        
        NSArray *sortedStops = colorStops->sortedArrayUsingComparator(EJCanvasGradientColorStop::compare);
	/*TODO: Remove this. Kept for reference.
        NSArray *sortedStops = [colorStops sortedArrayUsingComparator:^NSComparisonResult(id a, id b) {
		EJCanvasGradientColorStop s1, s2;
		[a getValue:&s1];
		[b getValue:&s2];
		
		return (s1.pos == s2.pos) ? (s1.order - s2.order) : (s1.pos - s2.pos);
	}];*/
	
	NSData *pixels = [self getPixelsWithWidth:EJ_CANVAS_GRADIENT_WIDTH forSortedStops:sortedStops];
	
	// Create or update Texture
	if( !texture ) {
		texture = [[EJTexture alloc] initWithWidth:EJ_CANVAS_GRADIENT_WIDTH height:1 pixels:pixels];
	}
	else {
		[texture updateWithPixels:pixels atX:0 y:0 width:EJ_CANVAS_GRADIENT_WIDTH height:1];
	}
}

NSData * EJCanvasGradient::getPixelsWithWidth(width, stops) {
	
	int byteSize = width * 4;
	NSMutableData *pixels = [NSMutableData dataWithLength:byteSize];
	
	if( !stops || !stops.count ) {
		// No stops? return empty pixel data
		return pixels;
	}
	
	EJCanvasGradientColorStop firstStop, currentStop, nextStop;
	[stops[0] getValue:&firstStop];
	currentStop = firstStop;
	
	GLubyte *bytes = pixels.mutableBytes;
	int index = 0;
	
	for( NSValue *v in stops ) {
		[v getValue:&nextStop];
		
		int stopIndex = MIN(nextStop.pos * (float)byteSize, byteSize);
		float length = (stopIndex - index)/4;
		
		// Keep the currentColor around as float values, so we can use
		// a float increment for each step.
		float currentColor[4] = {
			currentStop.color.rgba.r,
			currentStop.color.rgba.g,
			currentStop.color.rgba.b,
			currentStop.color.rgba.a,
		};

		float colorIncrement[4] = {
			(float)(nextStop.color.rgba.r - currentStop.color.rgba.r)/length,
			(float)(nextStop.color.rgba.g - currentStop.color.rgba.g)/length,
			(float)(nextStop.color.rgba.b - currentStop.color.rgba.b)/length,
			(float)(nextStop.color.rgba.a - currentStop.color.rgba.a)/length
		};
		
		for( ; index < stopIndex; index += 4 ) {
			bytes[index] = currentColor[0];
			bytes[index+1] = currentColor[1];
			bytes[index+2] = currentColor[2];
			bytes[index+3] = currentColor[3];
			
			currentColor[0] += colorIncrement[0];
			currentColor[1] += colorIncrement[1];
			currentColor[2] += colorIncrement[2];
			currentColor[3] += colorIncrement[3];
		}
		
		// Exit if we are at the end already, but set the color at the stopIndex to the
		// actual stop color; this avoids rounding errors with the colorIncrement
		if( index == byteSize ) {
			*(EJColorRGBA*)&bytes[byteSize-4] = nextStop.color;
			break;
		}
		
		currentStop = nextStop;
	}
	
	// Fill the remaining pixels if the last stop was not at 1.0
	for( ; index < byteSize; index += 4 ) {
		*(EJColorRGBA*)&bytes[index] = nextStop.color;
	}
	
	return pixels;
}

@end
