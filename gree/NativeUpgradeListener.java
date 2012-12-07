package org.cocos2dx.lib.gree;

//import android.util.Log;
import net.gree.asdk.api.auth.Authorizer.UpgradeListener;

public class NativeUpgradeListener implements UpgradeListener {
	private static final String TAG = NativeUpgradeListener.class.getSimpleName();

	private native void nativeOnUpgraded();
	private native void nativeOnUpgradeError();
	private native void nativeOnUpgradeCancel();

	@Override
	public void onUpgrade(){
		//Log.d(TAG, "onUpgrade");
		nativeOnUpgraded();
	}

	@Override
	public void onError(){
		//Log.d(TAG, "onError");
		nativeOnUpgradeError();
	}

	@Override
	public void onCancel(){
		//Log.d(TAG, "onCancel");
		nativeOnUpgradeCancel();
	}
}

