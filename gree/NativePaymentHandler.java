package org.cocos2dx.lib.gree;

import net.gree.asdk.api.wallet.Payment;
import android.widget.Toast;
import android.content.Context;
import android.os.Handler;
import android.os.Message;

public class NativePaymentHandler extends Handler {
	//private Object mObject = null;
	private Object mContext = null;
	public NativePaymentHandler(Object context){
		//this.mObject = obj;
		this.mContext = context;
	}
/*
	public void handleMessage(Message message) {
		switch (message.what) {
			case Payment.OPENED:
				Toast.makeText((Context)mContext, "Dialog opened", Toast.LENGTH_SHORT).show();
				break;
			case Payment.CANCELLED:
			case Payment.ABORTED:
				Toast.makeText((Context)mContext, "Dialog closed", Toast.LENGTH_SHORT).show();
				break;
			default:
				break;
		}
	}*/
}

