package org.cocos2dx.lib.gree;

import net.gree.asdk.api.ui.ShareDialog;
import android.os.Handler;
import android.os.Message;
//import android.util.Log;
//import android.widget.Toast;

public class NativeShareDialogHandler extends Handler {
	private Object mContext = null;
	private final long mDelegate;

	public NativeShareDialogHandler(Object context, long delegate){
		this.mContext = context;
		this.mDelegate = delegate;
	}
	private native void nativeShareDialogOpened(long delegate);
	private native void nativeShareDialogCompleted(long delegate);
	private native void nativeShareDialogCanceled(long delegate);

	public void handleMessage(Message message) {
		switch (message.what) {
			case ShareDialog.OPENED:
				//Toast.makeText((Context)mContext, "DialogOpened", Toast.LENGTH_SHORT).show();
				nativeShareDialogOpened(this.mDelegate);
				break;
			case ShareDialog.CLOSED:
				if(message.obj != null){
					//Toast.makeText((Context)mContext, "DialogClosed " + message.obj.toString(), Toast.LENGTH_LONG).show();
					nativeShareDialogCompleted(this.mDelegate);
				}else{
					//Toast.makeText((Context)mContext, "DialogClosed ", Toast.LENGTH_SHORT).show();
					nativeShareDialogCanceled(this.mDelegate);
				}
				break;
			default:
				break;
		}
	}
}
