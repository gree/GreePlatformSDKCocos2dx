#import "GreePlatform.h"
#import "GreeUser.h"
#import "CCGreePlatform.h"

using namespace cocos2d;

NS_CC_GREE_EXT_BEGIN

CCGreeUser::CCGreeUser(void *user){
	mGreeUser = user;
}

CCGreeUser::~CCGreeUser(){
	mGreeUser = NULL;
}



CCString *CCGreeUser::getNickname(){
    CCString* ccStr = NULL;
    if(mGreeUser != NULL){
        GreeUser *user = (GreeUser *)mGreeUser;
        NSString* nsStr = [user nickname];
        ccStr = new CCString([nsStr UTF8String]);
        ccStr->autorelease();
    }
    return ccStr;
}


CCString *CCGreeUser::getDisplayName(){
    CCString* ccStr = NULL;
    if(mGreeUser != NULL){
        GreeUser *user = (GreeUser *)mGreeUser;
        NSString* nsStr = [user displayName];
        ccStr = new CCString([nsStr UTF8String]);
        ccStr->autorelease();
    }
    return ccStr;
}
CCString *CCGreeUser::getId(){
    CCString* ccStr = NULL;
    if(mGreeUser != NULL){
        GreeUser *user = (GreeUser *)mGreeUser;
        NSString* nsStr = [user userId];
        ccStr = new CCString([nsStr UTF8String]);
        ccStr->autorelease();
    }
    return ccStr;
}

CCString *CCGreeUser::getRegion(){
    CCString* ccStr = NULL;
    if(mGreeUser != NULL){
        GreeUser *user = (GreeUser *)mGreeUser;
        NSString* nsStr = [user region];
        ccStr = new CCString([nsStr UTF8String]);
        ccStr->autorelease();
    }
    return ccStr;
}
CCString *CCGreeUser::getSubregion(){
    CCString* ccStr = NULL;
    if(mGreeUser != NULL){
        GreeUser *user = (GreeUser *)mGreeUser;
        NSString* nsStr = [user subRegion];
        ccStr = new CCString([nsStr UTF8String]);
        ccStr->autorelease();
    }
    return ccStr;
}
CCString *CCGreeUser::getLanguage(){
    CCString* ccStr = NULL;
    if(mGreeUser != NULL){
        GreeUser *user = (GreeUser *)mGreeUser;
        NSString* nsStr = [user language];
        ccStr = new CCString([nsStr UTF8String]);
        ccStr->autorelease();
    }
    return ccStr;
}
CCString *CCGreeUser::getTimezone(){
    CCString* ccStr = NULL;
    if(mGreeUser != NULL){
        GreeUser *user = (GreeUser *)mGreeUser;
        NSString* nsStr = [user timeZone];
        ccStr = new CCString([nsStr UTF8String]);
        ccStr->autorelease();
    }
    return ccStr;
}
CCString *CCGreeUser::getAboutMe(){
    CCString* ccStr = NULL;
    if(mGreeUser != NULL){
        GreeUser *user = (GreeUser *)mGreeUser;
        NSString* nsStr = [user aboutMe];
        ccStr = new CCString([nsStr UTF8String]);
        ccStr->autorelease();
    }
    return ccStr;
}
CCString *CCGreeUser::getBirthday(){
    CCString* ccStr = NULL;
    if(mGreeUser != NULL){
        GreeUser *user = (GreeUser *)mGreeUser;
        NSString* nsStr = [user birthday];
        ccStr = new CCString([nsStr UTF8String]);
        ccStr->autorelease();
    }
    return ccStr;
}
CCString *CCGreeUser::getGender(){
    CCString* ccStr = NULL;
    if(mGreeUser != NULL){
        GreeUser *user = (GreeUser *)mGreeUser;
        NSString* nsStr = [user gender];
        ccStr = new CCString([nsStr UTF8String]);
        ccStr->autorelease();
    }
    return ccStr;
}
CCString *CCGreeUser::getAge(){
    CCString* ccStr = NULL;
    if(mGreeUser != NULL){
        GreeUser *user = (GreeUser *)mGreeUser;
        NSString* nsStr = [user age];
        ccStr = new CCString([nsStr UTF8String]);
        ccStr->autorelease();
    }
    return ccStr;
}
CCString *CCGreeUser::getBloodType(){
    CCString* ccStr = NULL;
    if(mGreeUser != NULL){
        GreeUser *user = (GreeUser *)mGreeUser;
        NSString* nsStr = [user bloodType];
        ccStr = new CCString([nsStr UTF8String]);
        ccStr->autorelease();
    }
    return ccStr;
}
bool CCGreeUser::getHasApp(){
    GreeUser *user = (GreeUser *)mGreeUser;
    return [user hasThisApplication];
}

CCString *CCGreeUser::getUserHash(){
    CCString* ccStr = NULL;
    if(mGreeUser != NULL){
        GreeUser *user = (GreeUser *)mGreeUser;
        NSString* nsStr = [user userHash];
        ccStr = new CCString([nsStr UTF8String]);
        ccStr->autorelease();
    }
    return ccStr;
}
CCString *CCGreeUser::getUserType(){
    CCString* ccStr = NULL;
    if(mGreeUser != NULL){
        GreeUser *user = (GreeUser *)mGreeUser;
        NSString* nsStr = [user userType];
        ccStr = new CCString([nsStr UTF8String]);
        ccStr->autorelease();
    }
    return ccStr;

}
int  CCGreeUser::getUserGrade(){
    int ret = -1;
    if(mGreeUser != NULL){
        GreeUser *user = (GreeUser *)mGreeUser;
        GreeUserGrade grade = [user userGrade];
        ret = static_cast<int>(grade);
    }
    return ret;
}



bool CCGreeUser::loadThumbnail(int size){
    bool ret = false;
    if(mGreeUser){
        [(GreeUser *)mGreeUser loadThumbnailWithSize:GreeUserThumbnailSizeLarge block:^(UIImage *icon, NSError *error){
            if(error != nil){
                CCGreeUserDelegate *delegate = CCGreePlatform::getUserDelegate();
                if(delegate != NULL){
                    delegate->loadThumbnailFailure(this, [error code], new CCString([[error description] UTF8String]));
                }
                return;
            }
            CGImageRef imageRef = icon.CGImage;
            NSUInteger width = CGImageGetWidth(imageRef);
            NSUInteger height = CGImageGetHeight(imageRef);
            CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
            int* rawData = (int *)malloc(height * width * 4);
            NSUInteger bytesPerPixel = 4;
            NSUInteger bytesPerRow = bytesPerPixel * width;
            NSUInteger bitsPerComponent = 8;
            CGContextRef context = CGBitmapContextCreate(rawData, width, height,
                                                         bitsPerComponent, bytesPerRow, colorSpace,
                                                         kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
            CGColorSpaceRelease(colorSpace);
            CGContextDrawImage(context, CGRectMake(0, 0, width, height), imageRef);
            CGContextRelease(context);
            
            CCImage* img = new CCImage();
            img->initWithImageData((void *)rawData, width * height * 4, CCImage::kFmtRawData, width, height);
            CCGreeUserDelegate *delegate = CCGreePlatform::getUserDelegate();
            if(delegate != NULL){
                delegate->loadThumbnailSuccess(this, img);
            }
            free(rawData);
        }];
        ret = true;
    }
    return ret;
}

void CCGreeUser::loadFriends(int offset, int count){
    if(mGreeUser){
        GreeUser* user = reinterpret_cast<GreeUser*>(mGreeUser);
        id<GreeCountableEnumerator> enumerator = [user loadFriendsWithBlock : nil];
        [enumerator setStartIndex : offset];
        [enumerator loadNext : ^(NSArray* items, NSError* error){
            if(error != nil){
                CCGreeUserDelegate *delegate = CCGreePlatform::getUserDelegate();
                if(delegate != NULL){
                    delegate->loadFriendsFailure(this, [error code], new CCString([[error description] UTF8String]));
                }
                return;
            }
            int loadCount = [items count];
            CCArray *userArray = new CCArray();
            for(int i = 0; i < ((loadCount >= count) ? count : loadCount); i++){
                //without retain, GreeUser object seems to be released on cocos2dx main thread.
                userArray->addObject(new CCGreeUser((void*)([[items objectAtIndex : i] retain])));
            }
            if(count > loadCount && [enumerator canLoadNext]){
                //TODO : Load more cells
            }
            CCGreeUserDelegate *delegate = CCGreePlatform::getUserDelegate();
            if(delegate != NULL){
                delegate->loadFriendsSuccess(this, offset, loadCount, userArray);
            }
        }];
    }
}

NS_CC_GREE_EXT_END

