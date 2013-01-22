package org.cocos2dx.lib.gree;

import java.util.concurrent.CountDownLatch;
import net.gree.asdk.api.ui.InviteDialog;
import net.gree.asdk.api.ui.RequestDialog;
import net.gree.asdk.api.ui.ShareDialog;
import net.gree.asdk.api.wallet.Payment;
import android.content.Context;
import android.util.Log;

public class NativeThreadHelper {
	private static final String TAG = NativeThreadHelper.class.getSimpleName();
	private static final String INVITE_DIALOG  = "InviteDialog";
	private static final String REQUEST_DIALOG = "RequestDialog";
	private static final String SHARE_DIALOG   = "ShareDialog";
	private static final String PAYMENT_DIALOG = "PaymentDialog";

	private Object mObject = null;

	public Object createDialog(final Context context, final String dialogType){
		final CountDownLatch Signal = new CountDownLatch(1);
		new Thread(new Runnable(){
			public void run(){
				Cocos2dxGreePlatform.getPlatformUIHandler().post(new Runnable(){
					public void run(){
						//Log.d(TAG, "Thread name : " + Thread.currentThread().getName());
						if(dialogType.equals(INVITE_DIALOG)){
							mObject = (InviteDialog)new InviteDialog(context);
						}else if(dialogType.equals(REQUEST_DIALOG)){
							mObject = (RequestDialog)new RequestDialog(context);
						}else if(dialogType.equals(SHARE_DIALOG)){
							mObject = (ShareDialog)new ShareDialog(context);
						}else{
							Log.e(TAG, "Unsupported dialog type for showDialog");
							mObject = null;
						}
						Signal.countDown();
					}
				});
			}
		}).start();

		try {
			Signal.await();
		} catch (InterruptedException e) {
			//Log.e(TAG, "createDialog is interrupted");
			mObject = null;
		}
		return mObject;
	}

	public static void setHandler(final Context context, final Object obj, final String dialogType, final long delegate){
		new Thread(new Runnable(){
			public void run(){
				Cocos2dxGreePlatform.getPlatformUIHandler().post(new Runnable(){
					public void run(){
						if(dialogType.equals(INVITE_DIALOG)){
							NativeInviteDialogHandler handler = new NativeInviteDialogHandler(context, delegate);
							final InviteDialog dialog = (InviteDialog)obj;
							dialog.setHandler(handler);
						}else if(dialogType.equals(REQUEST_DIALOG)){
							NativeRequestDialogHandler handler = new NativeRequestDialogHandler(context, delegate);
							final RequestDialog dialog = (RequestDialog)obj;
							dialog.setHandler(handler);
						}else if(dialogType.equals(SHARE_DIALOG)){
							NativeShareDialogHandler handler = new NativeShareDialogHandler(context, delegate);
							final ShareDialog dialog = (ShareDialog)obj;
							dialog.setHandler(handler);
						}else if(dialogType.equals(PAYMENT_DIALOG)){
							NativePaymentHandler handler = new NativePaymentHandler(context, delegate);
							final Payment payment = (Payment)obj;
							payment.setHandler(handler);
						}else{
							Log.e(TAG, "Unsupported dialog type for setHandler");
						}
					}
				});
			}
		}).start();
	}

	public static void showDialog(final Object obj, final String dialogType){
		new Thread(new Runnable(){
			public void run(){
				Cocos2dxGreePlatform.getPlatformUIHandler().post(new Runnable(){
					public void run(){
						if(dialogType.equals(INVITE_DIALOG)){
							final InviteDialog dialog = (InviteDialog)obj;
							dialog.show();
						}else if(dialogType.equals(REQUEST_DIALOG)){
							final RequestDialog dialog = (RequestDialog)obj;
							dialog.show();
						}else if(dialogType.equals(SHARE_DIALOG)){
							final ShareDialog dialog = (ShareDialog)obj;
							dialog.show();
						}else{
							Log.e(TAG, "Unsupported dialog type for showDialog");
						}
					}
				});
			}
		}).start();
	}
}

