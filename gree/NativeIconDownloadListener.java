package org.cocos2dx.lib.gree;

import net.gree.asdk.api.IconDownloadListener;
import org.apache.http.HeaderIterator;
import android.graphics.Bitmap;
//import android.util.Log;

public class NativeIconDownloadListener implements IconDownloadListener {
	private final String TAG = NativeIconDownloadListener.class.getSimpleName();

	private final long mDelegate;
	private final int mFuncType;

	public NativeIconDownloadListener(long delegate, int funcType){
		this.mDelegate = delegate;
		this.mFuncType = funcType;
	}

	private native void nativeIconDownloadOnSuccess(long delegate, int funcType, int[] src, int width, int height);
	private native void nativeIconDownloadOnFailure(long delegate, int funcType, int responseCode, String response);

	@Override
	public void onSuccess(Bitmap image){
		//Log.d(TAG, "onSuccess");
		int width = image.getWidth();
		int height = image.getHeight();
		int pixels[] = new int[width * height];
		//Log.d(TAG, "Width" + width + "Height" + height);
		image.getPixels(pixels, 0, width, 0, 0, width, height); // buffer, offset, stride, x, y, width, height
		nativeIconDownloadOnSuccess(this.mDelegate, this.mFuncType, pixels, width, height);
	}

	@Override
	public void onFailure(int responseCode, HeaderIterator header, String response){
		//Log.d(TAG, "onFailure" + response);
		if(response == null){
			response = new String("");
		}
		nativeIconDownloadOnFailure(this.mDelegate, this.mFuncType, responseCode, response);
	}
}
