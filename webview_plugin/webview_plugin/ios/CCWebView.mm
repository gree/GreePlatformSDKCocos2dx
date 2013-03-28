#import "CCWebView.h"

#import "EAGLView.h"

@interface WebViewDelegate : NSObject<UIWebViewDelegate>
{
    // store c++ instance information related to this delegate
    void *object;
}
@end

@implementation WebViewDelegate
-(id)initWithDelegate:(void *)delegate
{
    self = [super init];
    object = delegate;
    return self;
}

-(BOOL)webView:(UIWebView*)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType
{
    NSString *url = [[request URL] absoluteString];
    if([url hasPrefix:@"cocos2dx:"]){
        cocos2d::webview_plugin::CCWebView *pDelegate = (cocos2d::webview_plugin::CCWebView *)object;
        if(pDelegate != NULL){
            pDelegate->handleCalledFromJS([url UTF8String]);
        }
        return NO;
    }else{
        return YES;
    }
}
@end

namespace cocos2d { namespace webview_plugin {

CCWebViewDelegate *CCWebView::s_pWebViewDelegate = NULL;

CCWebView::CCWebView(void *obj){
    mWebView = obj;
}

CCWebView* CCWebView::create(){
    CCWebView *webview = NULL;
    UIView *view = [EAGLView sharedEGLView];
    UIWebView *uiView = [[UIWebView alloc] init];
    UIInterfaceOrientation orientation = [[UIApplication sharedApplication] statusBarOrientation];
    if(UIInterfaceOrientationIsPortrait(orientation)){
        uiView.frame = CGRectMake(0, 0, view.frame.size.width, view.frame.size.height);
    }else{
        uiView.frame = CGRectMake(0, 0, view.frame.size.height, view.frame.size.width);
    }
    uiView.hidden = YES;
    [view addSubview:uiView];
    webview = new CCWebView((void*)uiView);
    uiView.delegate = (id<UIWebViewDelegate>)[[WebViewDelegate alloc] initWithDelegate:(void *)webview];
    return webview;
}

void CCWebView::setRect(int x, int y, int w, int h){
    UIView *view = [EAGLView sharedEGLView];
    CGRect frame = view.frame;
    CGFloat scale = view.contentScaleFactor;
    frame.size.width = w / scale;
    frame.size.height = h / scale;
    UIWebView *uiView = (UIWebView*)mWebView;
    uiView.frame = frame;
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
}

void CCWebView::evaluateJS(const char* js){
    UIWebView *uiView = (UIWebView*)mWebView;
    NSString *jsStr = NSLocalizedString([[NSString alloc] initWithUTF8String:js], @"JS");
    [uiView stringByEvaluatingJavaScriptFromString:jsStr];
}

void CCWebView::destroy(){
    UIWebView *uiView = (UIWebView*)mWebView;
    WebViewDelegate *delegate = uiView.delegate;
    [delegate release];
    [uiView removeFromSuperview];
    [uiView release];
}

void CCWebView::handleCalledFromJS(const char *message){
    CCWebViewDelegate *delegate = CCWebView::getWebViewDelegate();
    if(delegate != NULL){
        CCString *str = new CCString(message);
        str->autorelease();
        delegate->callbackFromJS(this, str);
    }
}

}}

