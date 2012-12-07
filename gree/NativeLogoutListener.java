package org.cocos2dx.lib.gree;

import net.gree.asdk.api.auth.Authorizer.LogoutListener;
//import android.util.Log;

public class NativeLogoutListener implements LogoutListener {
	private static final String TAG = NativeLogoutListener.class.getSimpleName();
	private final int mFuncType;

	public NativeLogoutListener(int funcType){
		this.mFuncType = funcType;
	}

	private native void nativeOnLogouted(int funcType);
	private native void nativeOnLogoutError(int funcType);
	private native void nativeOnLogoutCancel(int funcType);

	@Override
    public void onLogout(){
    	//Log.d(TAG, "onLogout");
    	nativeOnLogouted(this.mFuncType);
    }

	@Override
    public void onError(){
    	//Log.d(TAG, "onError");
    	nativeOnLogoutError(this.mFuncType);
    }

	@Override
    public void onCancel(){
    	//Log.d(TAG, "onCancel");
    	nativeOnLogoutCancel(this.mFuncType);
    	
    }
}
