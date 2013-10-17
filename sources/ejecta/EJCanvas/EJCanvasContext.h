/****************************************************************************

****************************************************************************/

#ifndef __EJ_CANVAS_CONTEXT_H__
#define __EJ_CANVAS_CONTEXT_H__

#ifdef _WINDOWS
#include <windows.h>
#include <GL/glew.h>
#include <GL/gl.h>
#else
#include <GLES/gl.h>
#endif

#include "../EJCocoa/support/nsMacros.h"
#include "EJTexture.h"
#include "EJImageData.h"
#include "EJPath.h"
#include "2D/EJCanvas2DTypes.h"
#include "EJFont.h"
#include "../EJCocoa/NSDictionary.h"
#include "../EJCocoa/NSCache.h"
#include "../EJCocoa/UIFont.h"

#define EJ_CANVAS_STATE_STACK_SIZE 16
#define EJ_CANVAS_VERTEX_BUFFER_SIZE 2048

extern EJVertex CanvasVertexBuffer[EJ_CANVAS_VERTEX_BUFFER_SIZE];

class EJPath;

typedef enum {
	kEJLineCapButt,
	kEJLineCapRound,
	kEJLineCapSquare
} EJLineCap;

typedef enum {
	kEJLineJoinMiter,
	kEJLineJoinBevel,
	kEJLineJoinRound
} EJLineJoin;

typedef enum {
	kEJTextBaselineAlphabetic,
	kEJTextBaselineMiddle,
	kEJTextBaselineTop,
	kEJTextBaselineHanging,
	kEJTextBaselineBottom,
	kEJTextBaselineIdeographic
} EJTextBaseline;

typedef enum {
	kEJTextAlignStart,
	kEJTextAlignEnd,
	kEJTextAlignLeft,
	kEJTextAlignCenter,
	kEJTextAlignRight
} EJTextAlign;

typedef enum {
	kEJCompositeOperationSourceOver,
	kEJCompositeOperationLighter,
	kEJCompositeOperationDarker,
	kEJCompositeOperationDestinationOut,
	kEJCompositeOperationDestinationOver,
	kEJCompositeOperationSourceAtop,
	kEJCompositeOperationXOR
} EJCompositeOperation;

static const struct { GLenum source; GLenum destination; } EJCompositeOperationFuncs[] = {
	{GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA},
	{GL_SRC_ALPHA, GL_ONE},
	{GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA},
	{GL_ZERO, GL_ONE_MINUS_SRC_ALPHA},
	{GL_ONE_MINUS_DST_ALPHA, GL_ONE},
	{GL_DST_ALPHA, GL_ONE_MINUS_SRC_ALPHA},
	{GL_ONE_MINUS_DST_ALPHA, GL_ONE_MINUS_SRC_ALPHA}
};


typedef struct {
	CGAffineTransform transform;
	
	EJCompositeOperation globalCompositeOperation;
	EJColorRGBA fillColor;
	EJColorRGBA strokeColor;
	float globalAlpha;
	
	float lineWidth;
	EJLineCap lineCap;
	EJLineJoin lineJoin;
	float miterLimit;
	
	EJTextAlign textAlign;
	EJTextBaseline textBaseline;
	UIFont* font;
	
	EJPath * clipPath;
} EJCanvasState;

class EJCanvasContext : public NSObject {
protected:
	GLuint viewFrameBuffer, viewRenderBuffer;
	GLuint msaaFrameBuffer, msaaRenderBuffer;
	GLuint stencilBuffer;
	
	short width, height;
	short viewportWidth, viewportHeight;
	short bufferWidth, bufferHeight;
	
	EJTexture * currentTexture;
	
	EJPath * path;
	
	int vertexBufferIndex;
	
	int stateIndex;
	EJCanvasState stateStack[EJ_CANVAS_STATE_STACK_SIZE];
		
public:
	NSCache * fontCache;

	EJCanvasState * state;
	EJCompositeOperation globalCompositeOperation;
	UIFont * font;
	float backingStoreRatio;
	bool msaaEnabled;
	int msaaSamples;
	bool imageSmoothingEnabled;

	EJCanvasContext();
	EJCanvasContext(short widthp, short heightp);
	~EJCanvasContext();
	virtual void create();
	void setScreenSize(int widthp, int heightp);
	void createStencilBufferOnce();
	void bindVertexBuffer();
	virtual void prepare();
	void setTexture(EJTexture * newTexture);
	void pushTri(float x1, float y1, float x2, float y2, float x3, float y3, EJColorRGBA color, CGAffineTransform transform);
	void pushQuad(EJVector2 v1, EJVector2 v2, EJVector2 v3, EJVector2 v4, EJVector2 t1, EJVector2 t2, EJVector2 t3, EJVector2 t4, EJColorRGBA color, CGAffineTransform transform);
	void pushRect(float x, float y, float w, float h, float tx, float ty, float tw, float th, EJColorRGBA color, CGAffineTransform transform);
	void flushBuffers();
	
	void save();
	void restore();
	void rotate(float angle);
	void translate(float x, float y);
	void scale(float x, float y);
	void transform(float m11, float m12, float m21, float m22, float dx, float dy);
	void setTransform(float m11, float m12, float m21, float m22, float dx, float dy);
	void drawImage(EJTexture * texture, float sx, float sy, float sw, float sh, float dx, float dy, float dw, float dh);
	void fillRect(float x, float y, float w, float h);
	void strokeRect(float x, float y, float w, float h);
	void clearRect(float x, float y, float w, float h);
	virtual EJImageData* getImageData(float sx, float sy, float sw, float sh);
	void putImageData(EJImageData* imageData, float dx, float dy);
	void beginPath();
	void closePath();
	void fill();
	void stroke();
	void moveTo(float x, float y);
	void lineTo(float x, float y);
	void rect(float x, float y, float w, float h);
	void bezierCurveTo(float cpx, float cpy, float cpx2, float cpy2, float x, float y);
	void quadraticCurveTo(float cpx, float cpy, float x, float y);
	void arcTo(float x1, float y1, float x2, float y2, float radius);
	void arc(float x, float y, float radius, float startAngle, float endAngle, BOOL antiClockwise);
	EJFont* acquireFont(NSString* fontName , float pointSize ,BOOL fill ,float contentScale);
	void fillText(NSString * text, float x, float y);
	void strokeText(NSString * text, float x, float y);
	float measureText(NSString * text);

	void clip();
	void resetClip();

	//返回类名
	virtual const char* getClassName();
};

#endif // __EJ_CANVAS_CONTEXT_H__