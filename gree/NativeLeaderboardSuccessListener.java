package org.cocos2dx.lib.gree;

import net.gree.asdk.api.Leaderboard.SuccessListener;
import org.apache.http.HeaderIterator;
//import android.util.Log;

public class NativeLeaderboardSuccessListener implements SuccessListener {
	private static final String TAG = NativeLeaderboardSuccessListener.class.getSimpleName();
	private final long mDelegate;
	private final int mFuncType;

	public NativeLeaderboardSuccessListener(long delegate, int funcType){
		this.mDelegate = delegate;
		this.mFuncType = funcType;
	}

	private native void nativeLeaderboardSuccessListenerOnSuccess(long delegate, int funcType);
	private native void nativeLeaderboardSuccessListenerOnFailure(long delegate, int funcType, int responseCode, String response);

	@Override
	public void onSuccess(){
		//Log.d(TAG, "onSuccess");
		nativeLeaderboardSuccessListenerOnSuccess(this.mDelegate, this.mFuncType);
	}

	@Override
	public void onFailure(int responseCode, HeaderIterator headers, String response){
		//Log.d(TAG, "onFAilure");
		if(response == null){
			response = new String("");
		}
		nativeLeaderboardSuccessListenerOnFailure(this.mDelegate, this.mFuncType, responseCode, response);
	}
}

