#import "GreePlatformDispatcher.h"


@implementation GreePlatformDispatcher

static GreePlatformDispatcher* s_pGreePlatformDispatcher;

+(id) sharedGreePlatformDispatcher
{
    if(s_pGreePlatformDispatcher == nil){
        s_pGreePlatformDispatcher = [[self alloc] init];
    }
    return s_pGreePlatformDispatcher;
}


-(id)init
{
    // Initialize GreePlatformSDK
    NSDictionary* settings = [NSDictionary dictionaryWithObjectsAndKeys : GreeDevelopmentModeSandbox, GreeSettingDevelopmentMode, nil];
    
    [GreePlatform initializeWithApplicationId : @"xxxxx" consumerKey : @"xxxxxxxxxx" consumerSecret : @"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"  settings : settings delegate : self ];
    
    return self;
}

-(void)dealloc
{
    s_pGreePlatformDispatcher = 0;
    [super dealloc];
}


-(void)greePlatformWillShowModalView:(GreePlatform*)platform
{
    NSLog(@"%s", __FUNCTION__);
}

-(void)greePlatformDidDismissModalView:(GreePlatform*)platform
{
    NSLog(@"%s", __FUNCTION__);
}

-(void)greePlatform:(GreePlatform*)platform didLoginUser:(GreeUser*)localUser
{
    NSLog(@"%s", __FUNCTION__);
    NSLog(@"Local User: %@", localUser);
    cocos2d::gree_extension::CCGreeAuthorizer::handleOnAuthorized();
}

-(void)greePlatform:(GreePlatform *)platform didLogoutUser:(GreeUser *)localUser
{
    NSLog(@"%s", __FUNCTION__);
    cocos2d::gree_extension::CCGreeAuthorizer::handleOnLogouted();
}

-(void)greePlatformParamsReceived:(NSDictionary*)params
{
    NSLog(@"%s", __FUNCTION__);
    NSLog(@"params: %@", params.description);
}

@end

