package org.cocos2dx.lib.gree;

import net.gree.asdk.api.wallet.Payment;
//import android.widget.Toast;
//import android.content.Context;
import android.os.Handler;
import android.os.Message;

public class NativePaymentHandler extends Handler {
	private Object mContext = null;
	private final long mDelegate;
	public NativePaymentHandler(Object context, long delegate){
		this.mContext = context;
		this.mDelegate = delegate;
	}
	private native void nativePaymentDialogOpened(long delegate);
	//private native void nativePaymentDialogClosed(long delegate);
	//private native void nativePaymentDialogCanceled(long delegate);
	public void handleMessage(Message message) {
		switch (message.what) {
			case Payment.OPENED:
				//Toast.makeText((Context)mContext, "Payment Dialog opened", Toast.LENGTH_SHORT).show();
				nativePaymentDialogOpened(this.mDelegate);
				break;
			case Payment.DONE:
				//Toast.makeText((Context)mContext, "Payment Dialog done", Toast.LENGTH_SHORT).show();
				//nativePaymentDialogClosed();
				//break;
			case Payment.CANCELLED:
			case Payment.ABORTED:
				//nativePaymentDialogCanceled();
				//Toast.makeText((Context)mContext, "Payment Dialog closed", Toast.LENGTH_SHORT).show();
				break;
			default:
				break;
		}
	}
}
