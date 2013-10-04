package com.impactjs.ejecta.sample;

import android.util.Log;
import com.impactjs.ejecta.EjectaGLSurfaceView;
import android.app.Activity;
import android.content.res.Configuration;
import android.opengl.GLSurfaceView;
import android.os.Bundle;

import java.math.RoundingMode;
import java.text.DecimalFormat;
import java.text.NumberFormat;

public class DemoActivity extends Activity{
	private GLSurfaceView mGLView;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		int width = getWindowManager().getDefaultDisplay().getWidth();
		int height = getWindowManager().getDefaultDisplay().getHeight();

        /*****************
         * Ratio Control
         *****************/
        int gameWidth = width;
        int gameHeight = height;
        float scaleToFitX = (float)gameWidth / 480;
        float scaleToFitY = (float)gameHeight / 800;
        Log.d("ejecta", "=========================== ");
        Log.d("ejecta", "gameWidth          : " + gameWidth);
        Log.d("ejecta", "gameHeight         : " + gameHeight);
        Log.d("ejecta", "scaleToFitX        : " + Float.toString(scaleToFitX));
        Log.d("ejecta", "scaleToFitY        : " + Float.toString(scaleToFitY));

        float currentScreenRatio = (float)gameHeight / (float)gameWidth;
        float optimalRatio = Math.min(scaleToFitX, scaleToFitY);
        Log.d("ejecta", "optimalRatio       : " + optimalRatio);


        if (currentScreenRatio >= 1.77 && currentScreenRatio <= 1.79) {
            width = gameWidth;
            height = gameHeight;
        } else {
            Log.d("ejecta", "modified ratio?    : yes");
            width = Math.round(480 * optimalRatio);
            height = Math.round(800 * optimalRatio);
        }
        Log.d("ejecta", "width              : " + width);
        Log.d("ejecta", "height             : " + height);
        NumberFormat df = DecimalFormat.getInstance();
        df.setMinimumFractionDigits(2);
        df.setMaximumFractionDigits(2);
        df.setRoundingMode(RoundingMode.UP);
        Log.d("ejecta", "currentScreenRatio : " + df.format(currentScreenRatio));
        Log.d("ejecta", "=========================== ");

	    mGLView = new EjectaGLSurfaceView(this, width, height);
        setContentView(mGLView);
	}
	
	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		((EjectaGLSurfaceView)mGLView).onDestroy();
		super.onDestroy();
	}
	
	@Override
	public void onConfigurationChanged(Configuration newConfig) {
		// TODO Auto-generated method stub
		super.onConfigurationChanged(newConfig);
	}
	
	static {
    	//System.loadLibrary("corefoundation");
    	System.loadLibrary("JavaScriptCore");
        System.loadLibrary("ejecta");
    }
	   
}