package org.cocos2dx.lib.gree;

import net.gree.asdk.api.auth.Authorizer;
import net.gree.asdk.api.auth.Authorizer.AuthorizeListener;
import net.gree.asdk.api.auth.Authorizer.UpdatedLocalUserListener;
import android.app.Activity;

public class NativeAuthorizerWrapper {
	public static void authorizeWithUserGrade(final Activity activity, final AuthorizeListener listener, final UpdatedLocalUserListener localUserListener, final int user_grade){
		new Thread(new Runnable(){
			public void run(){
				Cocos2dxGreePlatform.getPlatformUIHandler().post(new Runnable(){
					public void run(){
						Authorizer.authorize(activity, listener, localUserListener, user_grade);
					}
				});
			}
		}).start();
	}
}

