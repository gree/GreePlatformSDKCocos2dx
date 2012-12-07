package org.cocos2dx.lib.gree;

import org.apache.http.HeaderIterator;
//import android.util.Log;
import net.gree.asdk.api.FriendCode.Data;
import net.gree.asdk.api.FriendCode.EntryListGetListener;

public class NativeEntryListGetListener implements EntryListGetListener {
	private static final String TAG = NativeEntryListGetListener.class.getSimpleName();

	private native void nativeEntryListGetListenerOnSuccess(int startIndex, int itemsPerPage, int totalResults, Data[] entries);
	private native void nativeEntryListGetListenerOnFailure(int responseCode, String response);

	@Override
	public void onSuccess(int startIndex, int itemsPerPage, int totalResults, Data[] entries){
		//Log.d(TAG, "onSuccess");
		nativeEntryListGetListenerOnSuccess(startIndex, itemsPerPage, totalResults, entries);
	}

	@Override
	public void onFailure(int responseCode, HeaderIterator headers, String response){
		//Log.d(TAG, "onFailure");
		if(response == null){
			response = new String("");
		}
		nativeEntryListGetListenerOnFailure(responseCode, response);
	}
}

