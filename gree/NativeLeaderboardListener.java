package org.cocos2dx.lib.gree;

import org.apache.http.HeaderIterator;
//import android.util.Log;
import net.gree.asdk.api.Leaderboard;
import net.gree.asdk.api.Leaderboard.LeaderboardListener;

public class NativeLeaderboardListener implements LeaderboardListener {
	private final String TAG = NativeLeaderboardListener.class.getSimpleName(); 

	private native void nativeLeaderboardOnSuccess(int index, int totalListSize, Leaderboard[] leaderboards);
	private native void nativeLeaderboardOnFailure(int responseCode, String response);

	@Override
	public void onSuccess(int index, int totalListSize, Leaderboard[] leaderboards){
		//Log.d(TAG, "onSuccess");
		nativeLeaderboardOnSuccess(index, totalListSize, leaderboards);
	}

	@Override
	public void onFailure(int responseCode, HeaderIterator headers, String response){
		//Log.d(TAG, "OnFailure");
		if(response == null){
			response = new String("");
		}
		nativeLeaderboardOnFailure(responseCode, response);
	}
}

