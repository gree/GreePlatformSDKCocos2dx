package org.cocos2dx.lib.gree;

import org.apache.http.HeaderIterator;
//import android.util.Log;
import net.gree.asdk.api.Leaderboard.Score;
import net.gree.asdk.api.Leaderboard.ScoreListener;

public class NativeScoreListener implements ScoreListener {
	private static final String TAG = NativeScoreListener.class.getSimpleName();
	private final long mDelegate;

	public NativeScoreListener(long delegate){
		this.mDelegate = delegate;
	}

	private native void nativeScoreOnSuccess(long delegate, int totalSize, Score[] entries);
	private native void nativeScoreOnFailure(long delegate, int responseCode, String response);

	@Override
	public void onSuccess(Score[] entries){
		//Log.d(TAG, "onSuccess" + entries.length);
		nativeScoreOnSuccess(this.mDelegate, entries.length, entries);
	}

	@Override
	public void onFailure(int responseCode, HeaderIterator headers, String response){
		//Log.d(TAG, "onFAilure");
		if(response == null){
			response = new String("");
		}
		nativeScoreOnFailure(this.mDelegate, responseCode, response);
	}
}

