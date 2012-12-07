package org.cocos2dx.lib.gree;

import android.graphics.Bitmap;

public class NativeBitmapParser {
	static public int[] getBitmapData(Object obj){
		Bitmap bmp = (Bitmap)obj;
		int width = bmp.getWidth();
		int height = bmp.getHeight();
		int pixels[] = new int[width * height];
		bmp.getPixels(pixels, 0, width, 0, 0, width, height);
		return pixels;
	}

	static public int getBitmapWidth(Object obj){
		Bitmap bmp = (Bitmap)obj;
		return bmp.getWidth();
	}

	static public int getBitmapHeight(Object obj){
		Bitmap bmp = (Bitmap)obj;
		return bmp.getHeight();
	}
}

