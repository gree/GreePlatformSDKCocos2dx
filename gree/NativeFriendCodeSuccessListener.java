package org.cocos2dx.lib.gree;

import org.apache.http.HeaderIterator;
//import android.util.Log;
import net.gree.asdk.api.FriendCode.SuccessListener;

public class NativeFriendCodeSuccessListener implements SuccessListener {
	private static final String TAG = NativeFriendCodeSuccessListener.class.getSimpleName();
	private final long mDelegate;
	private final int mFuncType;
	
	public NativeFriendCodeSuccessListener(long delegate, int funcType){
		this.mDelegate = delegate;
		this.mFuncType = funcType;
	}
	
	private native void nativeFriendCodeSuccessListenerOnSuccess(long delegate, int funcType);
	private native void nativeFriendCodeSuccessListenerOnFailure(long delegate, int funcType, int responseCode, String response);

	@Override
	public void onSuccess(){
		//Log.d(TAG, "onSuccess");
		nativeFriendCodeSuccessListenerOnSuccess(this.mDelegate, this.mFuncType);
	}

	@Override
	public void onFailure(int responseCode, HeaderIterator headers, String response){
		//Log.d(TAG, "onFAilure");
		if(response == null){
			response = new String("");
		}
		nativeFriendCodeSuccessListenerOnFailure(this.mDelegate, this.mFuncType, responseCode, response);
	}
}

