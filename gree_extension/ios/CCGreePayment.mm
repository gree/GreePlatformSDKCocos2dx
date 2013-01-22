#import "GreePlatform.h"
#import "GreeWallet.h"

#import "CCGreePayment.h"
#import "CCGreePlatform.h"

#import "cocoa/CCDictionary.h"

using namespace cocos2d;
using namespace cocos2d::gree_extension;

@interface GreeWalletDispatcher : NSObject<GreeWalletDelegate>
{
    void* mDelegate;
}

-(id)initWithItems:(void *)delegate
                 items:(NSMutableArray*)items
               message:(NSString*)message
           callbackUrl:(NSString*)callbackUrl
          successBlock:(void(^)(NSString *paymentId, NSArray* items))successBlock
          failureBlock:(void(^)(NSString *paymentId, NSArray* items, NSError* error))failureBlock;
@end

@implementation GreeWalletDispatcher

-(id)initWithItems:(void*)delegate
             items:(NSMutableArray*)items
               message:(NSString*)message
           callbackUrl:(NSString*)callbackUrl
          successBlock:(void(^)(NSString *paymentId, NSArray* items))successBlock
          failureBlock:(void(^)(NSString *paymentId, NSArray* items, NSError* error))failureBlock
{
    if ((self=[super init]))
    {
        mDelegate = delegate;
        [GreeWallet setDelegate:self];
        
        [GreeWallet paymentWithItems:items
                             message:message
                         callbackUrl:callbackUrl
                        successBlock:successBlock
                        failureBlock:failureBlock];
    }
    return self;
}


#pragma mark - walletDelegate
- (void)walletPaymentDidLaunchPopup
{
    NSLog(@"%s paymentDidLaunchPopup",__FUNCTION__);
    CCGreePaymentDelegate *delegate = CCGreePlatform::getPaymentDelegate();
    if(delegate != NULL && mDelegate != NULL){
        delegate->paymentRequestOpened((CCGreePayment*) mDelegate);
    }
}
- (void)walletPaymentDidDismissPopup
{
    NSLog(@"%s paymentDidDismissPopup",__FUNCTION__);
    [self release];
    CCGreePaymentDelegate *delegate = CCGreePlatform::getPaymentDelegate();
    if(delegate != NULL && mDelegate != NULL){
        delegate->paymentRequestClosed((CCGreePayment *) mDelegate);
    }
}

-(void)dealloc
{
    [super dealloc];
}

@end


NS_CC_GREE_EXT_BEGIN

//PaymentItem

CCGreePaymentItem::CCGreePaymentItem(void *obj){
    mPaymentItemObj = obj;
}

CCGreePaymentItem::~CCGreePaymentItem(){

}

CCGreePaymentItem* CCGreePaymentItem::create(const char *itemId, const char *itemName, double unitPrice, int quantity){
    CCGreePaymentItem *item = NULL;
    if(itemId == NULL || itemName == NULL || unitPrice < 0 || quantity < 0){
        return item;
    }
    NSString *itemIdStr = NSLocalizedString([[NSString alloc] initWithUTF8String:itemId], @"itemId");
    NSString *itemNameStr = NSLocalizedString([[NSString alloc]initWithUTF8String:itemName], @"itemName");
    NSInteger unitPriceInt = unitPrice;
    NSInteger quantityInt = quantity;
    
    GreeWalletPaymentItem *pItem = [GreeWalletPaymentItem paymentItemWithItemId:itemIdStr
                                                                       itemName:itemNameStr
                                                                      unitPrice:unitPriceInt
                                                                       quantity:quantityInt
                                                                       imageUrl:nil
                                                                    description:nil];
    if(pItem == nil){
        return item;
    }

    item = new CCGreePaymentItem((void*)pItem);
    return item;
}

void CCGreePaymentItem::setImageUrl(const char *url){
    if(url == NULL || mPaymentItemObj == NULL){
        return;
    }
    NSString *urlStr = NSLocalizedString([[NSString alloc] initWithUTF8String:url], @"url");

    GreeWalletPaymentItem *pItem = (GreeWalletPaymentItem *)mPaymentItemObj;
    
    pItem.imageUrl = urlStr;
}

void CCGreePaymentItem::setDescription(const char *desc){
    if(desc == NULL || mPaymentItemObj == NULL){
        return;
    }
    NSString *descStr = NSLocalizedString([[NSString alloc] initWithUTF8String:desc], "@description");
    
    GreeWalletPaymentItem *pItem = (GreeWalletPaymentItem *)mPaymentItemObj;
    
    pItem.description = descStr;
}

CCString *CCGreePaymentItem::getItemId(){
    CCString* ccStr = NULL;
    if(mPaymentItemObj != NULL){
        GreeWalletPaymentItem *pItem = (GreeWalletPaymentItem *)mPaymentItemObj;
        NSString *itemIdStr = [pItem itemId];
        ccStr = new CCString([itemIdStr UTF8String]);
        ccStr->autorelease();
    }
    return ccStr;
}


CCString *CCGreePaymentItem::getItemName(){
    CCString* ccStr = NULL;
    if(mPaymentItemObj != NULL){
        GreeWalletPaymentItem *pItem = (GreeWalletPaymentItem *)mPaymentItemObj;
        NSString *itemNameStr = [pItem itemName];
        ccStr = new CCString([itemNameStr UTF8String]);
        ccStr->autorelease();
    }
    return ccStr;
}

double CCGreePaymentItem::getUnitPrice(){
    double price  = -1.0F;
    if(mPaymentItemObj != NULL){
        GreeWalletPaymentItem *pItem = (GreeWalletPaymentItem *)mPaymentItemObj;
        NSInteger priceInt = [pItem unitPrice];
        price = priceInt;
    }
    return price;
}

int CCGreePaymentItem::getQuantity(){
    int quantity = -1;
    if(mPaymentItemObj != NULL){
        GreeWalletPaymentItem *pItem = (GreeWalletPaymentItem *)mPaymentItemObj;
        NSInteger quantityInt = [pItem quantity];
        quantity = quantityInt;
    }
    return quantity;
}

CCString *CCGreePaymentItem::getImageUrl(){
    CCString* ccStr = NULL;
    if(mPaymentItemObj != NULL){
        GreeWalletPaymentItem *pItem = (GreeWalletPaymentItem *)mPaymentItemObj;
        NSString *imageUrlStr = [pItem imageUrl];
        ccStr = new CCString([imageUrlStr UTF8String]);
        ccStr->autorelease();
    }
    return ccStr;
}

CCString *CCGreePaymentItem::getDescription(){
    CCString* ccStr = NULL;
    if(mPaymentItemObj != NULL){
        GreeWalletPaymentItem *pItem = (GreeWalletPaymentItem *)mPaymentItemObj;
        NSString *dscStr = [pItem description];
        ccStr = new CCString([dscStr UTF8String]);
        ccStr->autorelease();
    }
    return ccStr;
}


void *CCGreePaymentItem::getPaymentItemObject(){
    return mPaymentItemObj;
}

//Payment
//CCGreePayment::CCGreePayment(void *obj){
CCGreePayment::CCGreePayment(void *obj, CCString* message, CCArray* items){
    // in iOS mMessage and mItems are not used.
    mPaymentObj = obj;
    ((CCObject*)mPaymentObj)->retain();
}

CCGreePayment::~CCGreePayment(){
    ((CCObject*)mPaymentObj)->release();
}

CCGreePayment* CCGreePayment::create(const char *message, CCArray *items){
    CCGreePayment* payment = NULL;
    if(items == NULL){
        return payment;
    }
    CCString *pMessage = new CCString(message);
    CCDictionary *params = CCDictionary::create();
    params->setObject(pMessage, "message");
    params->setObject(items, "items");

    //payment = new CCGreePayment((void*)params);
    payment = new CCGreePayment((void*)params, NULL, NULL);

    return payment;
}

CCString* CCGreePayment::getPaymentMessage(){
    CCString *message = NULL;
    if(mPaymentObj != NULL){
        CCDictionary *dict = (CCDictionary*)mPaymentObj;
        message = (CCString*)dict->objectForKey("message");
    }
    return message;
}
CCArray* CCGreePayment::getPaymentItems(){
    CCArray *items = NULL;
    if(mPaymentObj != NULL){
        CCDictionary *dict = (CCDictionary*)mPaymentObj;
        items = (CCArray*)dict->objectForKey("items");
    }
    return items;
}


void CCGreePayment::setCallbackUrl(const char *url){
    if(url != NULL && mPaymentObj != NULL){
        CCString *pUrl = new CCString(url);
        CCDictionary *params = (CCDictionary *)mPaymentObj;
        params->setObject(pUrl, "url");
    }
}

void CCGreePayment::request(){
    if(mPaymentObj != NULL){
        CCDictionary *params = (CCDictionary *)mPaymentObj;
        CCDictElement *pElement = NULL;
        NSString *messageStr = nil;
        NSString *urlStr = nil;
        NSMutableArray *itemsList = nil;
        CCDICT_FOREACH(params, pElement){
            const std::string str = pElement->getStrKey();
            const char *pStr = str.c_str();
            if(!strncmp("message", pStr, sizeof("message"))){
                CCString *pMessage = ((CCString*)(pElement->getObject()));
                messageStr = NSLocalizedString([[NSString alloc] initWithUTF8String:pMessage->getCString()], @"message");
            }else if(!strncmp("items", pStr, sizeof("items"))){
                CCArray *items = ((CCArray*)(pElement->getObject()));
                itemsList = [[NSMutableArray alloc] initWithCapacity:items->count()];
                CCObject *it;
                CCARRAY_FOREACH(items, it){
                    CCGreePaymentItem *item = dynamic_cast<CCGreePaymentItem *>(it);
                    GreeWalletPaymentItem *pItem = (GreeWalletPaymentItem *)(item->getPaymentItemObject());
                    [itemsList addObject:pItem];
                }
                if(itemsList == nil){
                    return;
                }
            }else if(!strncmp("url", pStr, sizeof("url"))){
                CCString *pUrl = ((CCString*)(pElement->getObject()));
                urlStr = NSLocalizedString([[NSString alloc] initWithUTF8String:pUrl->getCString()], @"url");
            }
        }
        
        [[GreeWalletDispatcher alloc] initWithItems:(void*)this
                                              items:itemsList
                                            message:messageStr
                                        callbackUrl:urlStr
                                       successBlock:^(NSString* paymentId, NSArray* items){
                                           NSLog(@"Payment Request Success");
                                           this->handlePaymentRequestOnSuccess((int)0, [paymentId UTF8String]);
                                       }
                                       failureBlock:^(NSString* paymentId, NSArray* items, NSError* error){
                                           NSLog(@"Payment Request Failure");
                                           this->handlePaymentRequestOnFailure([error code], [paymentId UTF8String], [[error description] UTF8String]);
                                       }
         ];
        /* To catch dialog open/close callback, wrap apicall with GreeWalletDispatcher
        [GreeWallet paymentWithItems:itemsList
                         message:messageStr
                         callbackUrl:urlStr
                    successBlock:^(NSString* paymentId, NSArray* items){
                        NSLog(@"Payment Request Success");
                        this->handlePaymentRequestOnSuccess((int)0, [paymentId UTF8String]);
                    }
                    failureBlock:^(NSString* paymentId, NSArray* items, NSError* error){
                        NSLog(@"Payment Request Failure");
                        this->handlePaymentRequestOnFailure([error code], [paymentId UTF8String], [[error description] UTF8String]);
                    }
         ];*/
    }
}

void CCGreePayment::handlePaymentRequestOnSuccess(int responseCode, const char* paymentId){
    CCGreePaymentDelegate *delegate = CCGreePlatform::getPaymentDelegate();
    if(delegate != NULL){
        CCString *str = new CCString(paymentId);
        str->autorelease();
        delegate->paymentRequestSuccess(this, responseCode, str);
    }
}

void CCGreePayment::handlePaymentRequestOnFailure(int responseCode, const char *paymentId, const char* response){
    CCGreePaymentDelegate *delegate = CCGreePlatform::getPaymentDelegate();
    if(delegate != NULL){
        CCString *str1 = new CCString(paymentId);
        CCString *str2 = new CCString(response);
        str1->autorelease();
        str2->autorelease();
        delegate->paymentRequestFailure(this, responseCode, str1, str2);
    }
}

NS_CC_GREE_EXT_END

