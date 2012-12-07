package org.cocos2dx.lib.gree;

import net.gree.asdk.api.Achievement.AchievementChangeListener;
import org.apache.http.HeaderIterator;
//import android.util.Log;

public class NativeAchievementChangeListener implements AchievementChangeListener {
	private static final String TAG = NativeAchievementChangeListener.class.getSimpleName();
	private final long mDelegate;
	private final int mFuncType;

	public NativeAchievementChangeListener(long delegate, int funcType){
		this.mDelegate = delegate;
		this.mFuncType = funcType;
	}
	public native void nativeAchievementChangeOnSuccess(long delegate, int funcType);
	public native void nativeAchievementChangeOnFailure(long delegate, int funcType, int responseCode, String response);

	@Override
	public void onSuccess(){
		//Log.d(TAG, "onSuccess : ");
		nativeAchievementChangeOnSuccess(this.mDelegate, this.mFuncType);
	}

	@Override
	public void onFailure(int responseCode, HeaderIterator headers, String response){
		//Log.d(TAG, "onFailure" + response);
		if(response == null){
			response = new String("");
		}
		nativeAchievementChangeOnFailure(this.mDelegate, this.mFuncType, responseCode, response);
	}
}
