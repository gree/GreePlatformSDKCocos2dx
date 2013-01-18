#import "GreePlatformDispatcher.h"
#import "GreePlatform.h"
#import "GreePopup.h"

#import "UIViewController+GreeAdditions.h"
#import "UIViewController+GreePlatform.h"

#import "CCGreeInviteDialog.h"
#import "CCGreePlatform.h"

NS_CC_GREE_EXT_BEGIN

CCGreeInviteDialog::CCGreeInviteDialog(void *obj){
    mInviteDialog = obj;
}


CCGreeInviteDialog* CCGreeInviteDialog::create(){
    GreeInvitePopup* invitePopup = [GreeInvitePopup popup];
    CCGreeInviteDialog *dialog = NULL;
    if(invitePopup != nil){
        dialog = new CCGreeInviteDialog((void*)invitePopup);
    }
    return dialog;
}

void CCGreeInviteDialog::setParams(CCDictionary *params){
    if(params != NULL && mInviteDialog != NULL){
        CCDictElement* pElement = NULL;
        CCDICT_FOREACH(params, pElement){
            const std::string str = pElement->getStrKey();
            const char *pStr = str.c_str();
            GreeInvitePopup *invitePopup = (GreeInvitePopup *)mInviteDialog;
            if(!strncmp(GD_INVITE_DIALOG_PARAM_KEY_BODY, pStr, sizeof(GD_INVITE_DIALOG_PARAM_KEY_BODY))){
                //bode
                const char *pVal = ((CCString *)(pElement->getObject()))->getCString();
                invitePopup.message = NSLocalizedString([[NSString alloc] initWithUTF8String:pVal], @"message");
            }else if(!strncmp(GD_INVITE_DIALOG_PARAM_KEY_TOUSERID, pStr, sizeof(GD_INVITE_DIALOG_PARAM_KEY_TOUSERID))){
                //touser
                CCArray *arry = (CCArray *)(pElement->getObject());
                if(arry == NULL){
                    return;
                }
                NSMutableArray *userIdList = [[NSMutableArray alloc] initWithCapacity:arry->count()];
                CCObject *it;
                CCARRAY_FOREACH(arry, it){
                    CCString *val = dynamic_cast<CCString *>(it);
                    NSString *nsVal = NSLocalizedString([[NSString alloc] initWithUTF8String:val->getCString()], @"touser");
                    [userIdList addObject:nsVal];
                }
                invitePopup.toUserIds = userIdList;
            }
        }
    }
}

void CCGreeInviteDialog::show(){
    if(mInviteDialog != NULL){
        GreeInvitePopup *invitePopup = (GreeInvitePopup *)mInviteDialog;
        invitePopup.willLaunchBlock =^(GreePopup* aSender) {
            NSLog(@"invite popup will launch.");
        };
        invitePopup.didLaunchBlock =^(GreePopup* aSender) {
            NSLog(@"invite popup did launch.");
        };
        invitePopup.willDismissBlock =^(GreePopup* aSender) {
            NSLog(@"invite popup will dismiss.");
        };
        invitePopup.didDismissBlock =^(GreePopup* aSender) {
            NSLog(@"invite popup did dismiss.");
        };
        invitePopup.cancelBlock =^(GreePopup* aSender) {
            NSLog(@"invite popup was cancelled.");
        };
        invitePopup.completeBlock =^(GreePopup* aSender) {
            NSLog(@"invite popup completed.");
        };

        [[UIViewController greeLastPresentedViewController] showGreePopup:invitePopup];
    }
}

NS_CC_GREE_EXT_END

