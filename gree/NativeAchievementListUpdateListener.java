package org.cocos2dx.lib.gree;

import net.gree.asdk.api.Achievement;
import net.gree.asdk.api.Achievement.AchievementListUpdateListener;
import org.apache.http.HeaderIterator;
//import android.util.Log;

public class NativeAchievementListUpdateListener implements AchievementListUpdateListener {
	private static final String TAG = NativeAchievementListUpdateListener.class.getSimpleName();
	private native void nativeAchievementListUpdateOnSuccess(int index, int totalListSize, Achievement[] requestedElements);
	private native void nativeAchievementListUpdateOnFailure(int responseCode, String response);

	@Override
	public void onSuccess(int index, int totalListSize, Achievement[] requestedElements){
		//Log.d(TAG, "onSuccess " + index + " : " + totalListSize);
		nativeAchievementListUpdateOnSuccess(index, totalListSize, requestedElements);
	}

	@Override
	public void onFailure(int responseCode, HeaderIterator headers, String response){
		//Log.d(TAG, "onFailure");
		if(response == null){
			response = new String("");
		}
		nativeAchievementListUpdateOnFailure(responseCode, response);
	}
}

