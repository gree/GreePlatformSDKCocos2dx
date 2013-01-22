#import "GreePlatformDispatcher.h"
#import "GreePlatform.h"
#import "GreePopup.h"

#import "UIViewController+GreeAdditions.h"
#import "UIViewController+GreePlatform.h"

#import "CCGreeShareDialog.h"
#import "CCGreePlatform.h"

NS_CC_GREE_EXT_BEGIN

CCGreeShareDialog::CCGreeShareDialog(void *obj){
    mShareDialog = obj;
}


CCGreeShareDialog* CCGreeShareDialog::create(){
    GreeSharePopup* sharePopup = [GreeSharePopup popup];
    CCGreeShareDialog *dialog = NULL;
    if(sharePopup != nil){
        dialog = new CCGreeShareDialog((void*)sharePopup);
    }
    return dialog;
}

void CCGreeShareDialog::setParams(CCDictionary *params){
    if(params != NULL && mShareDialog != NULL){
        CCDictElement* pElement = NULL;
        CCDICT_FOREACH(params, pElement){
            const std::string str = pElement->getStrKey();
            const char *pStr = str.c_str();
            GreeSharePopup *sharePopup = (GreeSharePopup *)mShareDialog;
            if(!strncmp(GD_SHARE_DIALOG_PARAM_KEY_IMG, pStr, sizeof(GD_SHARE_DIALOG_PARAM_KEY_IMG))){
                //CCImage
                CCImage *img = ((CCImage *)(pElement->getObject()));
                
                // generate UIImage
                unsigned char* pBuf = img->getData();
                unsigned short width = img->getWidth();
                unsigned short height = img->getHeight();
                
                CGDataProviderRef provider = CGDataProviderCreateWithData(NULL, pBuf, width * height * 4, NULL);
                CGColorSpaceRef colorSpaceRef = CGColorSpaceCreateDeviceRGB();
                CGBitmapInfo bmpInfo = kCGBitmapByteOrderDefault;
                CGColorRenderingIntent intent = kCGRenderingIntentDefault;
                CGImageRef imgRef = CGImageCreate(width, height, 8, 32, 4 * width,
                                                  colorSpaceRef, bmpInfo, provider, NULL, NO, intent);
                
                UIImage *newImg = [UIImage imageWithCGImage:imgRef];
                
                sharePopup.attachingImage = newImg;
            }else if(!strncmp(GD_SHARE_DIALOG_PARAM_KEY_MESSAGE, pStr, sizeof(GD_SHARE_DIALOG_PARAM_KEY_MESSAGE))){
                //message
                const char *pVal = ((CCString *)(pElement->getObject()))->getCString();
                sharePopup.text = NSLocalizedString([[NSString alloc] initWithUTF8String:pVal], @"message");
            }
        }
    }
}

void CCGreeShareDialog::show(){
    if(mShareDialog != NULL){
        GreeSharePopup *sharePopup = (GreeSharePopup *)mShareDialog;
        sharePopup.willLaunchBlock =^(GreePopup* aSender) {
            NSLog(@"share popup will launch.");
        };
        sharePopup.didLaunchBlock =^(GreePopup* aSender) {
            NSLog(@"share popup did launch.");
            CCGreeShareDialogDelegate *delegate = CCGreePlatform::getShareDialogDelegate();
            if(delegate != NULL){
                delegate->shareDialogOpened(this);
            }
        };
        sharePopup.willDismissBlock =^(GreePopup* aSender) {
            NSLog(@"share popup will dismiss.");
        };
        sharePopup.didDismissBlock =^(GreePopup* aSender) {
            NSLog(@"share popup did dismiss.");
            CCGreeShareDialogDelegate *delegate = CCGreePlatform::getShareDialogDelegate();
            if(delegate != NULL){
                delegate->shareDialogClosed(this);
            }
        };
        sharePopup.cancelBlock =^(GreePopup* aSender) {
            NSLog(@"share popup was cancelled.");
        };
        sharePopup.completeBlock =^(GreePopup* aSender) {
            NSLog(@"share popup completed.");
            CCGreeShareDialogDelegate *delegate = CCGreePlatform::getShareDialogDelegate();
            if(delegate != NULL){
                CCArray *arry = new CCArray();
                delegate->shareDialogCompleted(this, arry);
            }
        };

        //Show popup
        //UIViewController *controller = [UIApplication sharedApplication].keyWindow.rootViewController;
        //[controller showGreePopup:sharePopup];
        [[UIViewController greeLastPresentedViewController] showGreePopup:sharePopup];
    }
}


NS_CC_GREE_EXT_END

