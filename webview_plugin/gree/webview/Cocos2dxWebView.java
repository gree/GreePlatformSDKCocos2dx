package org.cocos2dx.lib.gree.webview;

import java.io.IOException;
import java.io.InputStream;
import java.util.concurrent.CountDownLatch;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.net.Uri;
import android.util.Log;
import android.view.Display;
import android.view.Gravity;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.view.ViewGroup.LayoutParams;
import android.view.WindowManager;
import android.webkit.WebChromeClient;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebView.HitTestResult;
import android.webkit.WebViewClient;
import android.widget.FrameLayout;
import android.widget.ImageButton;
import android.widget.ImageView.ScaleType;
import android.os.Build;

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

	class CCWebViewClient extends WebViewClient {
		private final long mDelegate;

		public CCWebViewClient(final long delegate) {
			mDelegate = delegate;
		}

		@Override
		public boolean shouldOverrideUrlLoading(WebView view, String url) {
			// open browser when banner mode
			if(mBannerModeEnable && view != null && view.getHitTestResult() != null) {
				int resultType = view.getHitTestResult().getType();
				if (resultType == HitTestResult.UNKNOWN_TYPE || resultType == HitTestResult.SRC_ANCHOR_TYPE) {
					Uri uri = Uri.parse(url);
					Intent intent = new Intent(Intent.ACTION_VIEW, uri);
					sContext.startActivity(intent);
				}
				return true;
			}
			return nativeShouldOverrideUrlLoading(mDelegate, url);
		}

		@Override
		public void onPageFinished(WebView view, final String url) {
			Cocos2dxActivity a = (Cocos2dxActivity)sContext;
			a.runOnGLThread(new Runnable() {
				@Override
				public void run() {
					nativeOnPageFinished(mDelegate, url);
				}
			});
		}

		@Override
		public void onReceivedError(WebView view, int errorCode,
				String description, final String failingUrl) {
			Cocos2dxActivity a = (Cocos2dxActivity)sContext;
			a.runOnGLThread(new Runnable() {
				@Override
				public void run() {
					nativeOnLoadError(mDelegate, failingUrl);
				}
			});
		}
	}

	private native boolean nativeShouldOverrideUrlLoading(long delegate, String url);
	private native void nativeOnPageFinished(long delegate, String url);
	private native void nativeOnLoadError(long delegate, String url);

	private WebView mWebView;
	private ImageButton mCloseButton = null;
	private boolean mBannerModeEnable = false;
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

	public void setWebViewClient(final long delegate) {
		if (sContext != null && mWebView != null) {
			Activity a = (Activity)sContext;
			a.runOnUiThread(new Runnable() {
				public void run() {
					mWebView.setWebViewClient(new CCWebViewClient(delegate));
				}
			});
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
    			if (mCloseButton != null) {
    				sLayout.removeView(mCloseButton);
    				mCloseButton = null;
    			}
    		}});
    	}
    }
    public void loadURL(final String url, final boolean transparent)
    {
    	if(sContext != null && mWebView != null){
    		final Activity a = (Activity)sContext;
    		a.runOnUiThread(new Runnable() {public void run() {
                WebSettings settings = mWebView.getSettings();
                settings.setCacheMode(WebSettings.LOAD_DEFAULT);
				if(transparent) {
				    settings.setDefaultTextEncodingName("utf-8");
				    mWebView.setBackgroundColor(Color.argb(1, 255, 255, 255));
					mWebView.setBackgroundDrawable(null);
//					if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB){  // Android v3.0+
//						try {
//							mWebView.setLayerType(View.LAYER_TYPE_SOFTWARE, null);
//				        } catch (Exception e) {
//				        }
//					}
				}
    			mWebView.loadUrl(url);
    		}});
    	}
    }
    public void clearCache()
    {
    	if(sContext != null && mWebView != null){
    		final Activity a = (Activity)sContext;
    		a.runOnUiThread(new Runnable() {public void run() {
                mWebView.clearCache(true);
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
    		final FrameLayout.LayoutParams params = getLayoutParams(x, y, width, height);

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
    			updateCloseButtonVisibility();
    		}});
    	}
    }

    public void setBannerModeEnable(final boolean enable)
    {
    	if(sContext != null && mWebView != null){
    		Activity a = (Activity)sContext;
    		a.runOnUiThread(new Runnable() {public void run() {
    			mBannerModeEnable = enable;
    		}});
    	}
    }

    public void setCloseButton(final String imageName,
    		final int x, final int y, final int width, final int height)
    {
    	this.runOnUIThread(new Runnable() {

			@Override
			public void run() {

				if (mCloseButton != null) {
					sLayout.removeView(mCloseButton);
					mCloseButton = null;
				}

				Resources r = sContext.getResources();
				try {
					InputStream is = r.getAssets().open(imageName.replaceFirst("assets/", ""));
					Bitmap bm = BitmapFactory.decodeStream(is);
					mCloseButton = new ImageButton(sContext);
					mCloseButton.setImageBitmap(bm);
					mCloseButton.setBackgroundDrawable(null);
					mCloseButton.setAdjustViewBounds(true);
					mCloseButton.setScaleType(ScaleType.FIT_XY);
					mCloseButton.setPadding(0, 0, 0, 0);
					mCloseButton.setOnClickListener(new OnClickListener() {
						@Override
						public void onClick(View v) {
							destroy();
						}
					});
					updateCloseButtonVisibility();

		    		sLayout.addView(mCloseButton, getLayoutParams(x, y, width, height));

				} catch (IOException e) {
					Log.w("Cocos2dxWebView", e.getMessage());
				}
			}
		});
    }

    private void updateCloseButtonVisibility() {
    	if (mCloseButton != null && mWebView != null) {
    		mCloseButton.setVisibility(mWebView.getVisibility());
    	}
    }

    private void runOnUIThread(Runnable runnable) {
    	if(sContext != null && mWebView != null){
    		Activity a = (Activity)sContext;
    		a.runOnUiThread(runnable);
    	}
    }

    private FrameLayout.LayoutParams getLayoutParams(int x, int y, int width, int height) {
		Activity a = (Activity)sContext;
		WindowManager wm = (WindowManager)a.getSystemService(Context.WINDOW_SERVICE);
		Display disp = wm.getDefaultDisplay();
		int right = disp.getWidth() - (x + width);
		int top = disp.getHeight() - (y + height);

		final FrameLayout.LayoutParams params = new FrameLayout.LayoutParams(
				LayoutParams.FILL_PARENT, LayoutParams.FILL_PARENT,
				Gravity.NO_GRAVITY);
		params.setMargins(x, top, right, y);
		return params;
    }
}
