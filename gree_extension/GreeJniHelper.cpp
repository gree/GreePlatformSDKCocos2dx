#include "GreeJniHelper.h"
#include <android/log.h>

using namespace std;


#define LOG_TAG "GreeJniHelper"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define JAVAVM    cocos2d::JniHelper::getJavaVM()


extern "C"
{
    bool getEnv(JNIEnv **env)
    {
        bool bRet = false;

        do 
        {
            if (JAVAVM->GetEnv((void**)env, JNI_VERSION_1_4) != JNI_OK)
            {
                LOGD("Failed to get the environment using GetEnv()");
                break;
            }

            if (JAVAVM->AttachCurrentThread(env, 0) < 0)
            {
                LOGD("Failed to get the environment using AttachCurrentThread()");
                break;
            }

            bRet = true;
        } while (0);        

        return bRet;
    }
}


NS_CC_GREE_EXT_BEGIN
//bool GreeJniHelper::getInstanceMethodInfo(cocos2d::JniMethodInfo &methodinfo, jobject &obj, const char *methodName, const char *paramCode){
bool GreeJniHelper::getInstanceMethodInfo(JniMethodInfo &methodinfo, jobject &obj, const char *methodName, const char *paramCode){
	jmethodID methodID = 0;
	JNIEnv *pEnv = 0;
	bool bRet = false;
	do{
		if(!getEnv(&pEnv)){
			break;
		}
		jclass classID = pEnv->GetObjectClass(obj);
		methodID = pEnv->GetMethodID(classID, methodName, paramCode);
		if(methodID == NULL){
			CCLog("Failed to get method id of %s", methodName);
			break;
		}
		methodinfo.classID = classID;
		methodinfo.env = pEnv;
		methodinfo.methodID = methodID;

		bRet = true;
	}while(0);
	return bRet;
}

bool GreeJniHelper::getStaticFieldInfo(JniFieldInfo &fieldinfo, const char *className, const char *fieldName, const char *paramCode){
	jfieldID fieldIF = 0;
	JNIEnv *pEnv = 0;
	bool bRet = false;
	do{
		if(!getEnv(&pEnv)){
			break;
		}
		jclass classID = pEnv->FindClass(className);
		if(classID == NULL){
			CCLog("Failed to get class id of %s", className);
			break;
		}
		jfieldID fieldID = pEnv->GetStaticFieldID(classID, fieldName, paramCode);
		if(fieldID == NULL){
			CCLog("Faild to get field id of %s:%s", fieldName, paramCode);
			break;
		}
		fieldinfo.classID = classID;
		fieldinfo.fieldID = fieldID;
		fieldinfo.env = pEnv;
		bRet = true;
	}while(0);
	return bRet;
}

NS_CC_GREE_EXT_END



