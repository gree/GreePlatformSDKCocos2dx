package org.cocos2dx.lib.gree;

import org.json.JSONArray;
import org.json.JSONException;

import net.gree.asdk.api.ui.CloseMessage;
import net.gree.asdk.api.ui.RequestDialog;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
//import android.widget.Toast;

public class NativeRequestDialogHandler extends Handler {
	private Object mContext = null;
	private final long mDelegate;

	public NativeRequestDialogHandler(Object context, long delegate){
		this.mContext = context;
		this.mDelegate = delegate;
	}
	private native void nativeRequestDialogOpened(long delegate);
	private native void nativeRequestDialogCompleted(long delegate, int length, String[] array);
	private native void nativeRequestDialogClosed(long delegate);

	public void handleMessage(Message message) {
		switch (message.what) {
			case RequestDialog.OPENED:
				//Toast.makeText((Context)mContext, "DialogOpened", Toast.LENGTH_SHORT).show();
				nativeRequestDialogOpened(this.mDelegate);
				break;
			case RequestDialog.CLOSED:
				if(message.obj != null){
					//Toast.makeText((Context)mContext, "DialogClosed " + message.obj.toString(), Toast.LENGTH_LONG).show();
					JSONArray array = CloseMessage.getRecipientUserIds(message.obj.toString());
					String[] strArray = new String[array.length()];
					for(int i = 0; i < array.length(); i++){
						try {
							strArray[i] = (String)array.getString(i);
						} catch (JSONException e) {
							Log.e("Error", "Cannot get recipient_user_ids field");
							e.printStackTrace();
						}
					}
					nativeRequestDialogCompleted(this.mDelegate, array.length(), strArray);
				}else{
					//Toast.makeText((Context)mContext, "DialogClosed ", Toast.LENGTH_SHORT).show();
					nativeRequestDialogClosed(this.mDelegate);
				}
				break;
			default:
				break;
		}
	}
}

