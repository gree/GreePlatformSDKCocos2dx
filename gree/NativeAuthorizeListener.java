package org.cocos2dx.lib.gree;

import net.gree.asdk.api.auth.Authorizer.AuthorizeListener;
//import android.util.Log;

public class NativeAuthorizeListener implements AuthorizeListener {
	private static final String TAG = NativeAuthorizeListener.class.getSimpleName();

	private native void nativeOnAuthorized(int funcType);
	private native void nativeOnAuthorizeCancel(int funcType);
	private native void nativeOnAuthorizeError(int funcType);

	private final int mFuncType;

	NativeAuthorizeListener(int funcType){
		this.mFuncType = funcType;
	}

	@Override
	public void onAuthorized() { 
		//Log.d(TAG, "onAuthorized");
		nativeOnAuthorized(this.mFuncType); 
	}

	@Override
	public void onCancel() {
		//Log.d(TAG, "onCancel");
		nativeOnAuthorizeCancel(this.mFuncType); 
	}

	@Override
	public void onError() { 
		//Log.d(TAG, "onError");
		nativeOnAuthorizeError(this.mFuncType);
	}
}

