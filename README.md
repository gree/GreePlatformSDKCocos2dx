GREE Platform SDK for Cocos2d-x
==========================================================

Developers can call GREE Platform SDK from cocos2d-x context

# setup:
To prepare your environment, please execute

    $./setup.sh
And proper cocos2dx.xxx.zip will be downloaded and be extracted.

To develop cocos2dx android app, also you have to download
AndroidNDK and AndroidSDK.

To get each of them from the urls below.

AndroidNDK : [http://developer.android.com/tools/sdk/ndk/index.html](http://developer.android.com/tools/sdk/ndk/index.html)

AndroidSDK : [http://developer.android.com/sdk/index.html](http://developer.android.com/sdk/index.html)

# create project(for Android):
Under cocos2dx top directory, please execute create-android-gree-project.sh

    $cd ./cocos2d-2.0-x-2.0.4
	$./create-android-gree-project.sh

To execute create-android-gree-project.sh, you have to specify both of AndroidNDK path and Android SDK path.
You can modify create-android-gree-project.sh or you can specify with Environmental valiables.
	
	$export NDK_ROOT="/home/hoge/android-ndk-r8b/";
	$export ANDROID_SDK_ROOT="/home/hoge/android-sdk-linux/";
	$./create-android-gree-project.sh

# install Xcode template(for iOS):
Under cocos2dx top directory, please execute install-gree-templates-xcode.sh with root permission,
and you can select cocos2dx gree_extension template from Xcode.

	$cd ./cocos2d-2.0-x-2.0.4
	$sudo ./install-gree-templates-xcode.sh


WebViewPlugin for Cocos2d-x:
==========================================================
Add webview_plugin module enables developers to use platform independent WebView function from Cocos2dx context.
It works on Android and iOS.
This is derived from the work done by keijiro-san on https://github.com/keijiro/unity-webview-integration.

You can select whether you use one of GreePlatformSDK and WebViewPlugin, or both of them with setup.sh script.

	$./setup.sh -m all  # prepare both of GreePlatformSDK and WebViewPlugin
	$./setup.sh -m webview # only setup WebViewPlugin


