package org.cocos2dx.lib.gree;

import org.apache.http.HeaderIterator;
import net.gree.asdk.api.GreeUser;
import net.gree.asdk.api.GreeUser.GreeUserListener;
//import android.util.Log;

public class NativeGreeUserListener implements GreeUserListener {
	private static final String TAG = NativeGreeUserListener.class.getSimpleName();
	
	private final long mDelegate;
	private final int mFuncType;

	public NativeGreeUserListener(long delegate, int funcType){
		this.mDelegate = delegate;
		this.mFuncType = funcType;
	}

	private native void nativeGreeUserOnSuccess(long delegate, int funcType, int index, int count, GreeUser[] users);
	private native void nativeGreeUserOnFailure(long delegate, int funcType, int responseCode, String response);

	@Override
	public void onSuccess(int index, int count, GreeUser[] users){
		//Log.d(TAG, "onSuccess : " + index + " : " + count);
		nativeGreeUserOnSuccess(this.mDelegate, this.mFuncType, index, count, users);
	}

	@Override
	public void onFailure(int responseCode, HeaderIterator headers, String response){
		//Log.d(TAG, "onFaulure");
		if(response == null){
			response = new String("");
		}
		nativeGreeUserOnFailure(this.mDelegate, this.mFuncType, responseCode, response);
	}
}

