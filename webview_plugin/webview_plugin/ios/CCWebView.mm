#import "CCWebView.h"

#import "EAGLView.h"
#import "CCFileUtils.h"

@interface UIWebViewWithCloseHandler : UIWebView
{
    void *_ccWebView;
}
- (void)setCCWebView:(void*) ccWebView;
- (void)closeWebView;
@end

@implementation UIWebViewWithCloseHandler

- (void)setCCWebView:(void *)webView
{
    _ccWebView = webView;
}

- (void)closeWebView
{
    if (_ccWebView) {
        ((cocos2d::webview_plugin::CCWebView*)_ccWebView)->destroy();
    }
}

@end

@interface WebViewDelegate : NSObject<UIWebViewDelegate>
{
    // store c++ instance information related to this delegate
    void *object;
}

@property (nonatomic, readwrite) BOOL bannerModeEnable;

@end

@implementation WebViewDelegate
-(id)initWithDelegate:(void *)delegate
{
    self = [super init];
    object = delegate;
    _bannerModeEnable = NO;
    return self;
}

-(BOOL)webView:(UIWebView*)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType
{
    NSString *url = [[request URL] absoluteString];
    cocos2d::webview_plugin::CCWebView *pDelegate = (cocos2d::webview_plugin::CCWebView *)object;
    if([url hasPrefix:@"cocos2dx:"]){
        if(pDelegate != NULL){
            pDelegate->handleCalledFromJS([url UTF8String]);
        }
        return NO;
    }else{
        if (pDelegate != NULL) {
            return !pDelegate->handleShouldOverrideUrlLoading([url UTF8String]);
        }
        if (_bannerModeEnable) {
            [[UIApplication sharedApplication] openURL:[request URL]];
            return NO;
        }
        return YES;
    }
}

-(void)webViewDidFinishLoad:(UIWebView *)webView
{
    cocos2d::webview_plugin::CCWebView *pDelegate = (cocos2d::webview_plugin::CCWebView *)object;
    if (pDelegate != NULL) {
        NSString* url = [[[webView request] URL] absoluteString];
        pDelegate->handleOnPageFinished([url UTF8String]);
    }
}

-(void)webView:(UIWebView *)webView didFailLoadWithError:(NSError *)error
{
    cocos2d::webview_plugin::CCWebView *pDelegate = (cocos2d::webview_plugin::CCWebView *)object;
    if (pDelegate != NULL) {
        NSString* url = [[[webView request] URL] absoluteString];
        pDelegate->handleOnLoadError([url UTF8String]);
    }
}

@end

namespace cocos2d { namespace webview_plugin {

CCWebViewDelegate *CCWebView::s_pWebViewDelegate = NULL;

CCWebView::CCWebView(void *obj){
    mWebView = obj;
    mCloseButton = NULL;
}

CCWebView* CCWebView::create(){
    CCWebView *webview = NULL;
    UIView *view = [EAGLView sharedEGLView];
    UIWebViewWithCloseHandler *uiView = [[UIWebViewWithCloseHandler alloc] init];
    UIInterfaceOrientation orientation = [[UIApplication sharedApplication] statusBarOrientation];
    if(UIInterfaceOrientationIsPortrait(orientation)){
        uiView.frame = CGRectMake(0, 0, view.frame.size.width, view.frame.size.height);
    }else{
        uiView.frame = CGRectMake(0, 0, view.frame.size.height, view.frame.size.width);
    }
    uiView.hidden = YES;
    uiView.dataDetectorTypes = UIDataDetectorTypeNone;
    [view addSubview:uiView];
    webview = new CCWebView((void*)uiView);
    webview->autorelease();
    [uiView setCCWebView:webview];
    
    uiView.delegate = (id<UIWebViewDelegate>)[[WebViewDelegate alloc] initWithDelegate:(void *)webview];
    return webview;
}

void CCWebView::setRect(int x, int y, int w, int h){
    UIView *view = [EAGLView sharedEGLView];
    CGRect frame = view.frame;
    CGFloat frameHeight = frame.size.height;
    UIWebView *uiView = (UIWebView*)mWebView;
    uiView.frame = CGRectMake(x, frameHeight - y - h, w, h);
}

void CCWebView::loadUrl(const char *url){
    NSString *nsStr = NSLocalizedString([[NSString alloc] initWithUTF8String:url], @"Url");
    NSURL *nsUrl = [NSURL URLWithString:nsStr];
    NSURLRequest *request = [NSURLRequest requestWithURL:nsUrl];
    UIWebView *uiView = (UIWebView*)mWebView;
    [uiView loadRequest:request];
}

void CCWebView::setVisibility(bool enable){
    UIWebView *uiView = (UIWebView*)mWebView;
    uiView.hidden = enable ? NO : YES;
    if (mCloseButton) {
        UIView* button = (UIView*)mCloseButton;
        button.hidden = uiView.hidden;
    }
}

CCString* CCWebView::evaluateJS(const char* js){
    UIWebView *uiView = (UIWebView*)mWebView;
    NSString *jsStr = NSLocalizedString([[NSString alloc] initWithUTF8String:js], @"JS");
    NSString* result = [uiView stringByEvaluatingJavaScriptFromString:jsStr];
    return CCString::create([result UTF8String]);
}

void CCWebView::destroy(){
    if (mWebView) {
        UIWebView *uiView = (UIWebView*)mWebView;
        WebViewDelegate *delegate = uiView.delegate;
        [delegate release];
        [uiView removeFromSuperview];
        [uiView release];
        mWebView = NULL;
    }
    if (mCloseButton) {
        UIView* button = (UIView*)mCloseButton;
        [button removeFromSuperview];
        [button release];
        mCloseButton = NULL;
    }
}

void CCWebView::handleCalledFromJS(const char *message){
    CCWebViewDelegate *delegate = CCWebView::getWebViewDelegate();
    if(delegate != NULL){
        CCString *str = new CCString(message);
        str->autorelease();
        delegate->callbackFromJS(this, str);
    }
}
    
bool CCWebView::handleShouldOverrideUrlLoading(const char* url) {
    CCWebViewDelegate *delegate = CCWebView::getWebViewDelegate();
    if (delegate) {
        CCString *str = CCString::create(url);
        return delegate->shouldOverrideUrlLoading(this, str);
    }
    return false;
}
    
void CCWebView::handleOnPageFinished(const char* url) {
    CCWebViewDelegate *delegate = CCWebView::getWebViewDelegate();
    if (delegate) {
        CCString *str = CCString::create(url);
        return delegate->onPageFinished(this, str);
    }
}

void CCWebView::handleOnLoadError(const char* url) {
    CCWebViewDelegate *delegate = CCWebView::getWebViewDelegate();
    if (delegate) {
        CCString *str = CCString::create(url);
        return delegate->onLoadError(this, str);
    }
}

    
void CCWebView::setBannerModeEnable(bool enable)
{
    UIWebView* webview = (UIWebView *)mWebView;
    WebViewDelegate* delegate = webview.delegate;
    delegate.bannerModeEnable = enable;
}
    
    
    
    void CCWebView::setCloseButton(const char * imageName, int x, int y, int w, int h)
    {
        UIView* uiView = [EAGLView sharedEGLView];
        UIWebViewWithCloseHandler *webView = (UIWebViewWithCloseHandler*)mWebView;
        CGFloat frameHeight = uiView.frame.size.height;
        
        std::string imagePath = CCFileUtils::sharedFileUtils()->fullPathForFilename(imageName);
        
        UIButton* button = [UIButton buttonWithType:UIButtonTypeCustom];
        UIImage* image = [[UIImage alloc] initWithContentsOfFile:[NSString stringWithUTF8String:imagePath.c_str()]];
        [button setImage:image forState:UIControlStateNormal];
        [image release];
        [button addTarget:webView action:@selector(closeWebView) forControlEvents:UIControlEventTouchUpInside];
        
        button.frame = CGRectMake(x, frameHeight - y - h, w, h);
        if (mCloseButton) {
            UIView* view = (UIView*)mCloseButton;
            [view removeFromSuperview];
            [view release];
        }
        [button retain];
        button.hidden = webView.hidden;
        mCloseButton = button;
        
        [uiView addSubview:button];
    }

}}

