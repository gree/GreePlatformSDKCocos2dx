package org.cocos2dx.lib.gree;

//import android.util.Log;
import net.gree.asdk.api.auth.Authorizer.UpdatedLocalUserListener;

public class NativeUpdatedLocalUserListener implements UpdatedLocalUserListener {
	private static final String TAG = NativeUpdatedLocalUserListener.class.getSimpleName();
	private final int mFuncType;

	NativeUpdatedLocalUserListener(int funcType){
		this.mFuncType = funcType;
	}

	private native void nativeOnUpdateLocalUser(int funcType);

	@Override
	public void onUpdateLocalUser() { 
		/*Cocos2dxGreeAuthorizer.nativeOnUpdateLocalUser();*/ 
		//Log.d(TAG, "onUpdateLocalUser");
		nativeOnUpdateLocalUser(this.mFuncType);
	}
}

