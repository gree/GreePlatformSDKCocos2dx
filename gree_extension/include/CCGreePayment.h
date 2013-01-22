#ifndef __CCGREEPAYMENT_H__
#define __CCGREEPAYMENT_H__

#include <string.h>

#include "GreeExtensionMacros.h"

#include "cocoa/CCString.h"


NS_CC_GREE_EXT_BEGIN 


class CCGreePayment;

class CCGreePaymentDelegate {
	public:
		virtual void paymentRequestSuccess(CCGreePayment *payment, int responseCode, CCString* paymentId){};
		virtual void paymentRequestCancel(CCGreePayment *payment, int responseCode, CCString* paymentId){};
		virtual void paymentRequestFailure(CCGreePayment *payment, int responseCode, CCString *paymentId, CCString *response){};
		virtual void paymentRequestOpened(CCGreePayment *payment){};
		virtual void paymentVerifySuccess(int responseCode, CCString* paymentId){};
		virtual void paymentVerifyCancel(int responseCode, CCString* paymentId){};
		virtual void paymentVerifyFailure(int responseCode, CCString *paymentId, CCString *response){};
};

class CCGreePaymentItem : public CCObject
{
	public:
		CCGreePaymentItem(void* obj);
		static CCGreePaymentItem *create(const char *itemId, const char* itemName, double unitPrice, int quantity);
		void setImageUrl(const char *url);
		void setDescription(const char *desc);
		CCString *getItemId();
		CCString *getItemName();
		double getUnitPrice();
		int getQuantity();
		CCString *getImageUrl(); 
		CCString *getDescription();

		void* getPaymentItemObject();
	private:
		
		void* mPaymentItemObj;
};
			


class CCGreePayment : public CCObject
{
	public:
		CCGreePayment(void* obj);
		static CCGreePayment* create(const char *message, CCArray *items);
		static void verify(const char *paymentId);
		
		void request();
		void setCallbackUrl(const char *url);

		//	Callback
		void handlePaymentRequestOnSuccess(int responseCode, const char* paymentId);
		void handlePaymentRequestOnCancel(int responseCode, const char* paymentId);
		void handlePaymentRequestOnFailure(int responseCode, const char* paymentId, const char* response);
		void handleDialogOpened(void);
		static void handlePaymentVerifyOnSuccess(int responseCode, const char* paymentId);
		static void handlePaymentVerifyOnCancel(int responseCode, const char* paymentId);
		static void handlePaymentVerifyOnFailure(int responseCode, const char* paymentId, const char* response);
	private:
		void* mPaymentObj;
};

NS_CC_GREE_EXT_END

#endif
