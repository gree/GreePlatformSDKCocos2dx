package org.cocos2dx.lib.gree;

import net.gree.asdk.api.wallet.Payment;
import net.gree.asdk.api.wallet.Payment.PaymentListener;
import android.content.Context;
import android.os.Handler;
//import android.util.Log;

public class Cocos2dxGreePlatform {
	private static final String TAG = Cocos2dxGreePlatform.class.getSimpleName();
	private static Context sContext = null;
	private static NativePaymentHandler sHandler = null;
	private static Handler sLocalUIHandler = null;

	public static native void nativeSetContext(Context pContext);

	public static void init(Context pContext){
		setContext(pContext);
		// Handler must be created on UI thread
		sHandler = new NativePaymentHandler(pContext);
		sLocalUIHandler = new Handler();
	}

	public static void setContext(Context pContext){
		//Log.d(TAG, "Cocos2dxGreePlatform is set");
		Cocos2dxGreePlatform.sContext = pContext;
		nativeSetContext(pContext);
	}

	public static void requestWithHandler(final Payment obj, final PaymentListener listener){
		//Log.d(TAG, "requestWithHandler is called");
		new Thread(new Runnable(){
			public void run(){
				sLocalUIHandler.post(new Runnable(){
				public void run(){
					//Log.d(TAG, "thread name:" + Thread.currentThread().getName());
					obj.request(sContext, listener);
				}
			});
			}
		}).start();
	}

	public static Handler getPlatformUIHandler(){
		return sLocalUIHandler;
	}
}
