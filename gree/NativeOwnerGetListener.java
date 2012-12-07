package org.cocos2dx.lib.gree;

import org.apache.http.HeaderIterator;
//import android.util.Log;
import net.gree.asdk.api.FriendCode.Data;
import net.gree.asdk.api.FriendCode.OwnerGetListener;

public class NativeOwnerGetListener implements OwnerGetListener {
	private static final String TAG = NativeOwnerGetListener.class.getSimpleName();

	private native void nativeOwnerGetListenerOnSuccess(Data owner);
	private native void nativeOwnerGetListenerOnFailure(int responseCode, String response);

	@Override
	public void onSuccess(Data owner){
		//Log.d(TAG, "onSuccess");
		nativeOwnerGetListenerOnSuccess(owner);
	}

	@Override
	public void onFailure(int responseCode, HeaderIterator headers, String response){
		//Log.d(TAG, "onFailure");
		if(response == null){
			response = new String("");
		}
		nativeOwnerGetListenerOnFailure(responseCode, response);
	}
}

