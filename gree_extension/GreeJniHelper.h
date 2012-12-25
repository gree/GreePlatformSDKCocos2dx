#ifndef __CGREEJNIHELPER_H__
#define __CGREEJNIHELPER_H__

#include "jni/JniHelper.h"
#include "GreeExtensionMacros.h"

NS_CC_GREE_EXT_BEGIN

//bool getEnv(JNIEnv **env);

typedef struct JniFieldInfo_
{
	JNIEnv *env;
	jclass classID;
	jfieldID fieldID;
} JniFieldInfo;

class GreeJniHelper
{
	public:
		static bool getInstanceMethodInfo(JniMethodInfo &methodinfo, jobject &obj, const char *methodName, const char *paramCode);
		static bool getStaticFieldInfo(JniFieldInfo &fieldinfo, const char *className, const char *fieldName, const char *paramCode);

};

NS_CC_GREE_EXT_END



#endif
