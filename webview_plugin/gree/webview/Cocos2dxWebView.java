package org.cocos2dx.lib.gree.webview;

import java.util.concurrent.CountDownLatch;

import android.app.Activity;
import android.content.Context;
import android.util.Log;
import android.view.Display;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.view.ViewGroup.LayoutParams;
import android.view.WindowManager;
import android.webkit.WebChromeClient;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.FrameLayout;

public class Cocos2dxWebView {
	class WebViewPluginInterface
	{
	    private final long mDelegate;

	    public WebViewPluginInterface(final long delegate)
	    {   
	        mDelegate = delegate;
	    }   

	    public void call(String message)
	    {   
	    	if(message == null){
	    		message = new String("");
	    	}
	    	nativeCalledFromJS(this.mDelegate, message);
	    }   
	}
	private native void nativeCalledFromJS(long delegate, String message);
	
	private WebView mWebView;
	private static Context sContext;
	private static FrameLayout sLayout = null;
	public static void setContext(Context context){
		sContext = context;
	}
	//public WebViewWrapper(final Context context){
	public Cocos2dxWebView(){
		if(sContext != null){
			final CountDownLatch Signal = new CountDownLatch(1);
			((Activity)sContext).runOnUiThread(new Runnable(){
				@Override
				public void run(){
					mWebView = new WebView((Activity)sContext);
					mWebView.setVisibility(View.GONE);
					mWebView.setFocusable(true);
					mWebView.setFocusableInTouchMode(true);

					if(sLayout == null){
						sLayout = new FrameLayout(sContext);
						((Activity)sContext).addContentView(sLayout, new ViewGroup.LayoutParams(LayoutParams.FILL_PARENT, LayoutParams.FILL_PARENT));
						sLayout.setFocusable(true);
						sLayout.setFocusableInTouchMode(true);
					}
					sLayout.addView(mWebView, new FrameLayout.LayoutParams(LayoutParams.FILL_PARENT, LayoutParams.FILL_PARENT, Gravity.NO_GRAVITY));
					
					mWebView.setWebChromeClient(new WebChromeClient());
					mWebView.setWebViewClient(new WebViewClient());
					//mWebView.addJavascriptInterface(new WebViewPluginInterface(delegate), "Cocos2dx");
					WebSettings webSettings = mWebView.getSettings();
					webSettings.setSupportZoom(false);
					//webSettings.setJavaScriptEnabled(true);
					webSettings.setPluginsEnabled(true);
					Signal.countDown();
				}
			});
			try {
				Signal.await();
			} catch (InterruptedException e) {
				mWebView = null;
			}
			
		}else{
			mWebView = null;
		}
	}

	public void setJavascriptIf(final long delegate){
		if(sContext != null && mWebView != null){
			Activity a = (Activity)sContext;
			a.runOnUiThread(new Runnable() {public void run() {
				mWebView.addJavascriptInterface(new WebViewPluginInterface(delegate), "Cocos2dx");
				WebSettings webSettings = mWebView.getSettings();
				webSettings.setJavaScriptEnabled(true);		
			}});
		}
	}

    public void destroy()
    {
    	if(sContext != null && mWebView != null){
    		Activity a = (Activity)sContext;
    		a.runOnUiThread(new Runnable() {public void run() {
    			if (mWebView != null) {
    				sLayout.removeView(mWebView);
    				mWebView = null;
    			}
    		}});
    	}
    }
    public void loadURL(final String url)
    {
    	if(sContext != null && mWebView != null){
    		final Activity a = (Activity)sContext;
    		a.runOnUiThread(new Runnable() {public void run() {
    			mWebView.loadUrl(url);
    		}});
    	}
    }
    public void evaluateJS(final String js)
    {
    	if(sContext != null && mWebView != null){
    		final Activity a = (Activity)sContext;
    		a.runOnUiThread(new Runnable() {public void run() {
    			mWebView.loadUrl("javascript:" + js);
    		}});
    	}
    }
    //public void setMargins(int left, int top, int right, int bottom)
    public void setMargins(int x, int y, int width, int height)
    {
    	if(sContext != null && mWebView != null){
    	// convert coordination from Cocos2dx to Android UI
    		Activity a = (Activity)sContext;
    		WindowManager wm = (WindowManager)a.getSystemService(Context.WINDOW_SERVICE);
    		Display disp = wm.getDefaultDisplay();
    		int left = x;
    		int right = disp.getWidth() - (left + width);
    		int top = disp.getHeight() - (y + height);
    		int bottom = y;
        
    		final FrameLayout.LayoutParams params = new FrameLayout.LayoutParams(
    				LayoutParams.FILL_PARENT, LayoutParams.FILL_PARENT,
    				Gravity.NO_GRAVITY);
    		params.setMargins(left, top, right, bottom);

    		a.runOnUiThread(new Runnable() {public void run() {
    			mWebView.setLayoutParams(params);
    		}});
    	}
    }

    public void setVisibility(final boolean visibility)
    {
    	if(sContext != null && mWebView != null){
    		Activity a = (Activity)sContext;
    		a.runOnUiThread(new Runnable() {public void run() {

    			if (visibility) {
    				mWebView.setVisibility(View.VISIBLE);
    				sLayout.requestFocus();
    				mWebView.requestFocus();
    			} else {
    				mWebView.setVisibility(View.GONE);
    			}
    		}});
    	}
    }
}
