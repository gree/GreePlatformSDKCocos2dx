package org.cocos2dx.lib.gree;

import net.gree.asdk.api.wallet.Payment.PaymentListener;
import org.apache.http.HeaderIterator;
//import android.util.Log;

public class NativePaymentListener implements PaymentListener {
	private static final String TAG = NativePaymentListener.class.getSimpleName();
	private long mDelegate;

	public NativePaymentListener(long delegate){
		this.mDelegate = delegate;
	}

	private native void nativePaymentOnSuccess(long delegate, int responseCode, String paymentId);
	private native void nativePaymentOnCancel(long delegate, int responseCode, String paymentId);
	private native void nativePaymentOnFailure(long delegate, int responseCode, String paymentId, String response);

	@Override
	public void onSuccess(int responseCode, HeaderIterator headers, String paymentId){
		//Log.d(TAG, "onSuccess : " + paymentId);
		if(paymentId == null){
			paymentId = new String("");
		}
		nativePaymentOnSuccess(this.mDelegate, responseCode, paymentId);
	}

	@Override
	public void onCancel(int responseCode, HeaderIterator headers, String paymentId){
		//Log.d(TAG, "onCancel : " + paymentId);
		if(paymentId == null){
			paymentId = new String("");
		}
		nativePaymentOnCancel(this.mDelegate, responseCode, paymentId);
	}

	@Override
	public void onFailure(int responseCode, HeaderIterator headers, String paymentId, String response){
		//Log.d(TAG, "onFailure : " + paymentId);
		if(paymentId == null){
			paymentId = new String("");
		}
		if(response == null){
			response = new String("");
		}
		nativePaymentOnFailure(this.mDelegate, responseCode, paymentId, response);
	}
}

