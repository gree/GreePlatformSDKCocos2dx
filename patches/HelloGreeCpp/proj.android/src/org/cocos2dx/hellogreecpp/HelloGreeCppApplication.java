package org.cocos2dx.hellogreecpp;

import net.gree.asdk.api.GreePlatform;
import android.app.Application;

public class HelloGreeCppApplication extends Application {
		@Override
		public void onCreate(){
			super.onCreate();
			GreePlatform.initialize(getApplicationContext(), R.xml.gree_platform_configuration, null);
		}
}
