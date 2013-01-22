package org.cocos2dx.lib.gree;

import org.json.JSONArray;
import org.json.JSONException;
import net.gree.asdk.api.ui.CloseMessage;
import net.gree.asdk.api.ui.InviteDialog;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
//import android.widget.Toast;

public class NativeInviteDialogHandler extends Handler {
	private Object mContext = null;
	private final long mDelegate;

	public NativeInviteDialogHandler(Object context, long delegate){
		this.mContext = context;
		this.mDelegate = delegate;
	}
	private native void nativeInviteDialogOpened(long delegate);
	private native void nativeInviteDialogCompleted(long delegate, int length, String[] array);
	private native void nativeInviteDialogCanceled(long delegate);

	public void handleMessage(Message message) {
		switch (message.what) {
			case InviteDialog.OPENED:
				//Toast.makeText((Context)mContext, "DialogOpened", Toast.LENGTH_SHORT).show();
				nativeInviteDialogOpened(this.mDelegate);
				break;
			case InviteDialog.CLOSED:
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
					nativeInviteDialogCompleted(this.mDelegate, array.length(), strArray);
				}else{
					//Toast.makeText((Context)mContext, "DialogClosed ", Toast.LENGTH_SHORT).show();
					nativeInviteDialogCanceled(this.mDelegate);
				}
				break;
			default:
				break;
		}
	}
}

