#ifndef __Java_org_cocos2dx_lib_Cocos2dxGreePayment_H__
#define __Java_org_cocos2dx_lib_Cocos2dxGreePayment_H__


#include <string.h>

#include "cocos2d.h"

extern "C"
{
// PaymentItem
	jobject createPaymentItemJni(const char *itemId, const char* itemName,     double unitPrice, int quantity);

	void setImageUrlJni(jobject obj, const char *url);
	void setDescriptionJni(jobject obj, const char *desc);
	std::string getItemIdJni(jobject obj);
	std::string getItemNameJni(jobject obj);
	double getUnitPriceJni(jobject obj);
	int getQuantityJni(jobject obj);
	std::string getImageUrlJni(jobject obj);
	std::string getDescription(jobject obj);


// Payment
	jobject createPaymentJni(const char *message, cocos2d::CCArray *items);

	void setPaymentHandlerJni(jobject obj, void *delegate);
	void requestJni(jobject obj, void *delegate);
	void requestWithHandlerJni(jobject obj, void *delegate);

	void setCallbackUrlJni(jobject obj, const char *url);
	void verifyJni(const char *paymentId);
}

#endif
