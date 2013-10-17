# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := ejecta

LOCAL_CFLAGS += -DENABLE_SINGLE_THREADED=1 -DUSE_FILE32API -D__LINUX__=1 -DCOMPATIBLE_GCC4=1 -D__LITTLE_ENDIAN__=1 -DGL_GLEXT_PROTOTYPES=1 -DEJECTA_DEBUG=1

LOCAL_C_INCLUDES := \
                    $(LOCAL_PATH) \
                    $(LOCAL_PATH)/../../../sources/ejecta \
                    $(LOCAL_PATH)/../../../sources/ejecta/EJCanvas \
                    $(LOCAL_PATH)/../../../sources/ejecta/Foundation \
                    $(LOCAL_PATH)/../../../sources/ejecta/Foundation/support \
                    $(LOCAL_PATH)/../../../sources/ejecta/EJUtils \
                    $(LOCAL_PATH)/../../../library/android/libfreetype/include \
                    $(LOCAL_PATH)/../../../library/android/libpng/include \
                    $(LOCAL_PATH)/../../../library/android/libjpeg/include \
                    $(LOCAL_PATH)/../../../library/android/libcurl/include \
                    $(LOCAL_PATH)/../../../library/android/JavaScriptCore/include 

LOCAL_SRC_FILES := \
                    ../../../sources/ejecta/lodefreetype/lodefreetype.cpp \
                    ../../../sources/ejecta/lodepng/lodepng.cpp \
                    ../../../sources/ejecta/lodejpeg/lodejpeg.cpp \
                    ../../../sources/ejecta/Foundation/support/nsCArray.cpp \
                    ../../../sources/ejecta/Foundation/NSObject.cpp \
                    ../../../sources/ejecta/Foundation/NSObjectFactory.cpp \
                    ../../../sources/ejecta/Foundation/NSGeometry.cpp \
                    ../../../sources/ejecta/Foundation/NSAutoreleasePool.cpp \
                    ../../../sources/ejecta/Foundation/NSArray.cpp \
                    ../../../sources/ejecta/Foundation/CGAffineTransform.cpp \
                    ../../../sources/ejecta/Foundation/NSDictionary.cpp \
                    ../../../sources/ejecta/Foundation/NSNS.cpp \
                    ../../../sources/ejecta/Foundation/NSSet.cpp \
                    ../../../sources/ejecta/Foundation/NSString.cpp \
                    ../../../sources/ejecta/Foundation/NSValue.cpp \
                    ../../../sources/ejecta/Foundation/NSZone.cpp \
                    ../../../sources/ejecta/Foundation/NSCache.cpp \
                    ../../../sources/ejecta/EJApp.cpp \
                    ../../../sources/ejecta/EJConvert.cpp \
                    ../../../sources/ejecta/EJBindingBase.cpp \
                    ../../../sources/ejecta/EJBindingEjectaCore.cpp \
                    ../../../sources/ejecta/EJBindingEventedBase.cpp \
                    ../../../sources/ejecta/EJTimer.cpp \
                    ../../../sources/ejecta/EJAudio/EJBindingAudio.cpp \
                    ../../../sources/ejecta/EJCanvas/EJBindingImage.cpp \
                    ../../../sources/ejecta/EJCanvas/EJBindingImageData.cpp \
                    ../../../sources/ejecta/EJCanvas/EJBindingCanvas.cpp \
                    ../../../sources/ejecta/EJCanvas/EJCanvasContext.cpp \
                    ../../../sources/ejecta/EJCanvas/EJCanvasContextScreen.cpp \
                    ../../../sources/ejecta/EJCanvas/EJCanvasContextTexture.cpp \
                    ../../../sources/ejecta/EJCanvas/EJPath.cpp \
                    ../../../sources/ejecta/EJCanvas/EJTexture.cpp \
                    ../../../sources/ejecta/EJCanvas/EJFont.cpp \
                    ../../../sources/ejecta/EJCanvas/EJImageData.cpp \
                    ../../../sources/ejecta/EJUtils/EJBindingHttpRequest.cpp \
                    ../../../sources/ejecta/EJUtils/EJBindingLocalStorage.cpp \
                    ../../../sources/ejecta/EJUtils/EJBindingTouchInput.cpp \
                    ejecta.cpp \

LOCAL_LDLIBS :=  -lz -llog -lGLESv1_CM \
                    -L$(LOCAL_PATH)/../../../library/android/libfreetype/libs/$(TARGET_ARCH_ABI) -lfreetype \
                    -L$(LOCAL_PATH)/../../../library/android/libpng/libs/$(TARGET_ARCH_ABI) -lpng \
                    -L$(LOCAL_PATH)/../../../library/android/libjpeg/libs/$(TARGET_ARCH_ABI) -ljpeg \
                    -L$(LOCAL_PATH)/../../../library/android/libcurl/libs/$(TARGET_ARCH_ABI) -lcurl \

LOCAL_SHARED_LIBRARIES := libJavaScriptCore

include $(BUILD_SHARED_LIBRARY)