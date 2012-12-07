package org.cocos2dx.lib.gree;

import org.apache.http.HeaderIterator;
//import android.util.Log;
import net.gree.asdk.api.FriendCode.Code;
import net.gree.asdk.api.FriendCode.CodeListener;

public class NativeCodeListener implements CodeListener {
	private static final String TAG = NativeCodeListener.class.getSimpleName();
	private final int mFuncType;

	public NativeCodeListener(int funcType){
		this.mFuncType = funcType;
	}

	private native void nativeCodeListenerOnSuccess(int funcType, Code code);
	private native void nativeCodeListenerOnFailure(int funcType, int responseCode, String response);

	@Override
	public void onSuccess(Code code){
		//Log.d(TAG, "onSuccess");
		nativeCodeListenerOnSuccess(this.mFuncType, code);
	}

	@Override
	public void onFailure(int responseCode, HeaderIterator headers, String response){
		//Log.d(TAG, "onFailure");
		if(response == null){
			response = new String("");
		}
		nativeCodeListenerOnFailure(this.mFuncType, responseCode, response);
	}
}

