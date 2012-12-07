package org.cocos2dx.lib.gree;

import org.apache.http.HeaderIterator;
import net.gree.asdk.api.GreeUser.GreeIgnoredUserListener;
//import android.util.Log;

public class NativeGreeIgnoredUserListener implements GreeIgnoredUserListener {
	private static final String TAG = NativeGreeIgnoredUserListener.class.getSimpleName();
	private final long mDelegate;
	private final int mFuncType;	
	
	public NativeGreeIgnoredUserListener(long delegate, int funcType){
		this.mDelegate = delegate;
		this.mFuncType = funcType;
	}

	private static native void nativeGreeIgnoredUserOnSuccess(long delegate, int funcType, int index, int count, String[] ignoredUsers);
	private static native void nativeGreeIgnoredUserOnFailure(long delegate, int funcType, int responseCode, String response);
	
	@Override
	public void onSuccess(int index, int count, String[] ignoredUsers){
		//Log.d(TAG, "onSuccess : " + index + " : " + count);
		nativeGreeIgnoredUserOnSuccess(this.mDelegate, this.mFuncType, index, count, ignoredUsers);
	}

	@Override
	public void onFailure(int responseCode, HeaderIterator headers, String response){
		//Log.d(TAG, "onFaulure");
		if(response == null){
			response = new String("");
		}
		nativeGreeIgnoredUserOnFailure(this.mDelegate, this.mFuncType, responseCode, response);
	}
}

