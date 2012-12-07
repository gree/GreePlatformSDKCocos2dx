package org.cocos2dx.lib.gree;

import org.apache.http.HeaderIterator;
//import android.util.Log;
import net.gree.asdk.api.wallet.Payment.VerifyListener;

public class NativeVerifyListener implements VerifyListener {
	private static final String TAG = NativeVerifyListener.class.getSimpleName();

	private native void nativeVerifyOnSuccess(int responseCode, String paymentId);
	private native void nativeVerifyOnCancel(int responseCode, String paymentId);
	private native void nativeVerifyOnFailure(int responseCode, String paymentId, String response);

	@Override
	public void onSuccess(int responseCode, HeaderIterator headers, String paymentId){
		//Log.d(TAG, "onSuccess");
		if(paymentId == null){
			paymentId = new String("");
		}
		nativeVerifyOnSuccess(responseCode, paymentId);
	}

	@Override
	public void onCancel(int responseCode, HeaderIterator headers, String paymentId){
		//Log.d(TAG, "onCancel");
		if(paymentId == null){
			paymentId = new String("");
		}
		nativeVerifyOnCancel(responseCode, paymentId);
	}

	@Override
	public void onFailure(int responseCode, HeaderIterator headers, String paymentId, String response){
		//Log.d(TAG, "onFailure");
		if(paymentId == null){
			paymentId = new String("");
		}
		if(response == null){
			response = new String("");
		}
		nativeVerifyOnFailure(responseCode, paymentId, response);
	}
}

