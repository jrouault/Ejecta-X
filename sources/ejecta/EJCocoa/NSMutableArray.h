/****************************************************************************

****************************************************************************/
#ifndef __NSMUTABLEARRAY_H__
#define __NSMUTABLEARRAY_H__

#include <stdarg.h>
#include "NSArray.h"

NS_NS_BEGIN

class NS_DLL NSMutableArray : public NSArray
{
public:
    ~NSMutableArray();

    /* static functions */
    /** Create an array 
    @deprecated: Please use create() instead. This interface will be deprecated sooner or later.
    */
    NS_DEPRECATED_ATTRIBUTE static NSMutableArray* array();
    /** Create an array with one object 
    @deprecated: Please use createWithObject(NSObject*) instead. This interface will be deprecated sooner or later.
    */
    NS_DEPRECATED_ATTRIBUTE static NSMutableArray* arrayWithObject(NSObject* pObject);
    /** Create an array with some objects 
    @deprecated: Please use create(NSObject*, ...) instead. This interface will be deprecated sooner or later.
    */
    NS_DEPRECATED_ATTRIBUTE static NSMutableArray* arrayWithObjects(NSObject* pObject, ...);
    /** Create an array with capacity 
    @deprecated: Please use createWithCapacity(unsigned int) instead. This interface will be deprecated sooner or later.
    */
    NS_DEPRECATED_ATTRIBUTE static NSMutableArray* arrayWithCapacity(unsigned int capacity);
    /** Create an array with an existing array
    @deprecated: Please use createWithArray(NSMutableArray*) instead. This interface will be deprecated sooner or later.
    */
    NS_DEPRECATED_ATTRIBUTE static NSMutableArray* arrayWithArray(NSMutableArray* otherArray);
    /**
     @brief   Generate a NSMutableArray pointer by file
     @param   pFileName  The file name of *.plist file
     @return  The NSMutableArray pointer generated from the file
     @deprecated: Please use createWithContentsOfFile(const char*) instead. This interface will be deprecated sooner or later.
     */
     NS_DEPRECATED_ATTRIBUTE static NSMutableArray* arrayWithContentsOfFile(const char* pFileName);
    
    /*
     @brief The same meaning as arrayWithContentsOfFile(), but it doesn't call autorelease, so the
     invoker should call release().
     @deprecated: Please use createWithContentsOfFileThreadSafe(const char*) instead. This interface will be deprecated sooner or later.
     */
    NS_DEPRECATED_ATTRIBUTE static NSMutableArray* arrayWithContentsOfFileThreadSafe(const char* pFileName);

    /** Create an array */
    static NSMutableArray* create();
    /** Create an array with some objects */
    static NSMutableArray* create(NSObject* pObject, ...);
    /** Create an array with one object */
    static NSMutableArray* createWithObject(NSObject* pObject);
    /** Create an array with capacity */
    static NSMutableArray* createWithCapacity(unsigned int capacity);
    /** Create an array with an existing array */
    static NSMutableArray* createWithArray(NSMutableArray* otherArray);
    /**
     @brief   Generate a NSMutableArray pointer by file
     @param   pFileName  The file name of *.plist file
     @return  The NSMutableArray pointer generated from the file
     */
    static NSMutableArray* createWithContentsOfFile(const char* pFileName);
    
    /*
     @brief The same meaning as arrayWithContentsOfFile(), but it doesn't call autorelease, so the
     invoker should call release().
     */
    static NSMutableArray* createWithContentsOfFileThreadSafe(const char* pFileName);

    /** Initializes an array */
    bool init();
    /** Initializes an array with one object */
    bool initWithObject(NSObject* pObject);
    /** Initializes an array with some objects */
    bool initWithObjects(NSObject* pObject, ...);
    /** Initializes an array with capacity */
    bool initWithCapacity(unsigned int capacity);
    /** Initializes an array with an existing array */
    bool initWithArray(NSMutableArray* otherArray);

    // Querying an Array

    /** Returns element count of the array */
    unsigned int count();
    /** Returns capacity of the array */
    unsigned int capacity();
    /** Returns index of a certain object, return UINT_MAX if doesn't contain the object */
    unsigned int indexOfObject(NSObject* object);
    /** Returns an element with a certain index */
    NSObject* objectAtIndex(unsigned int index);
    /** Returns last element */
    NSObject* lastObject();
    /** Returns a random element */
    NSObject* randomObject();
    /** Returns a Boolean value that indicates whether object is present in array. */
    bool containsObject(NSObject* object);
    /** @since 1.1 */
    bool isEqualToArray(NSMutableArray* pOtherArray);
    // Adding Objects

    /** Add a certain object */
    void addObject(NSObject* object);
    /** Add all elements of an existing array */
    void addObjectsFromArray(NSMutableArray* otherArray);
    /** Insert a certain object at a certain index */
    void insertObject(NSObject* object, unsigned int index);

    // Removing Objects

    /** Remove last object */
    void removeLastObject(bool bReleaseObj = true);
    /** Remove a certain object */
    void removeObject(NSObject* object, bool bReleaseObj = true);
    /** Remove an element with a certain index */
    void removeObjectAtIndex(unsigned int index, bool bReleaseObj = true);
    /** Remove all elements */
    void removeObjectsInArray(NSMutableArray* otherArray);
    /** Remove all objects */
    void removeAllObjects();
    /** Fast way to remove a certain object */
    void fastRemoveObject(NSObject* object);
    /** Fast way to remove an element with a certain index */
    void fastRemoveObjectAtIndex(unsigned int index);

    // Rearranging Content

    /** Swap two elements */
    void exchangeObject(NSObject* object1, NSObject* object2);
    /** Swap two elements with certain indexes */
    void exchangeObjectAtIndex(unsigned int index1, unsigned int index2);

    /** Replace object at index with another object. */
    void replaceObjectAtIndex(unsigned int uIndex, NSObject* pObject, bool bReleaseObject = true);

    /** Revers the array */
    void reverseObjects();
    /* Shrinks the array so the memory footprint corresponds with the number of items */
    void reduceMemoryFootprint();
  
    /* override functions */
    virtual NSObject* copyWithZone(NSZone* pZone);

public:
    nsArray* data;
    NSMutableArray();
    NSMutableArray(unsigned int capacity);
};

// end of data_structure group
/// @}

NS_NS_END

#endif // __NSMUTABLEARRAY_H__
