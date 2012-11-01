/*
 * Copyright (C) 2011 Google Inc.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy of
 * the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */

package de.europa4.android;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.Window;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import org.ros.address.InetAddressFactory;
import org.ros.android.bluecam.R;
import org.ros.android.bluecam.RosActivity;
import org.ros.node.NodeConfiguration;
import org.ros.node.NodeMainExecutor;

import android.view.View;

/**
 * @author ethan.rublee@gmail.com (Ethan Rublee)
 * @author damonkohler@google.com (Damon Kohler)
 */
public class MainActivity extends RosActivity {

	// Message types sent from the BluetoothChatService Handler
	public static final int MESSAGE_STATE_CHANGE = 1;
	public static final int MESSAGE_READ = 2;
	public static final int MESSAGE_WRITE = 3;
	public static final int MESSAGE_DEVICE_NAME = 4;
	public static final int MESSAGE_TOAST = 5;

	// IDs for Buttons
	public static final int BUTTON_ID_BLUECAM = 1;
	public static final int BUTTON_ID_TOUCHRAUPE = 2;
	public static final int BUTTON_ID_EXIT = 3;
	
	// Key names received from the BluetoothChatService Handler
	public static final String DEVICE_NAME = "device_name";
	public static final String TOAST = "toast";

	private static final int REQUEST_ENABLE_BT = 3;

	// Layout Views
	private TextView mTitle;
	// Local Bluetooth adapter
	private BluetoothAdapter mBluetoothAdapter = null;

	private static final String TAG = "BlueCam";
	private static final boolean D = true;

	public MainActivity() {
		super("BlueCam", "BlueCam");
	}

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_CUSTOM_TITLE);
		setContentView(R.layout.main);
		//    getWindow().addFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN);
		getWindow().setFeatureInt(Window.FEATURE_CUSTOM_TITLE, R.layout.custom_title);
		
		Button bluecamButton = (Button) findViewById(R.id.bluecamButton);
		bluecamButton.setId(BUTTON_ID_BLUECAM);
    	// activating the button
		bluecamButton.setOnClickListener(new ButtonHandler());

		Button touchButton = (Button) findViewById(R.id.touchButton);
		touchButton.setId(BUTTON_ID_TOUCHRAUPE);
    	// activating the button
		touchButton.setOnClickListener(new ButtonHandler());

		Button exitButton = (Button) findViewById(R.id.exitButton);
		exitButton.setId(BUTTON_ID_EXIT);
    	// activating the button
		exitButton.setOnClickListener(new ButtonHandler());

		// Set up the custom title
		mTitle = (TextView) findViewById(R.id.title_left_text);
		mTitle.setText(R.string.app_name);
		mTitle = (TextView) findViewById(R.id.title_right_text);

		// Get local Bluetooth adapter
		mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();

		// If the adapter is null, then Bluetooth is not supported
		if (mBluetoothAdapter == null) {
			Toast.makeText(this, "Bluetooth is not available", Toast.LENGTH_LONG).show();
			finish();
			return;
		}
	}

	@Override
	public void onStart() {
		super.onStart();
		if(D) Log.e(TAG, "++ ON START ++");

		// If BT is not on, request that it be enabled.
		// setupChat() will then be called during onActivityResult
		if (!mBluetoothAdapter.isEnabled()) {
			Intent enableIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
			startActivityForResult(enableIntent, REQUEST_ENABLE_BT);
		}

	}

	@Override
	protected void init(NodeMainExecutor nodeMainExecutor) {
		NodeConfiguration nodeConfiguration =
				NodeConfiguration.newPublic(InetAddressFactory.newNonLoopback().getHostAddress());
		nodeConfiguration.setMasterUri(getMasterUri());
	}

	public void onActivityResult(int requestCode, int resultCode, Intent data) {
		if(D) Log.d(TAG, "onActivityResult " + resultCode);
		super.onActivityResult(requestCode, resultCode, data);

		switch (requestCode) {
		case REQUEST_ENABLE_BT:
			// When the request to enable Bluetooth returns
			if (resultCode != Activity.RESULT_OK) {
				// User did not enable Bluetooth or an error occured
				Log.d(TAG, "BT not enabled");
				Toast.makeText(this, R.string.bt_not_enabled_leaving, Toast.LENGTH_SHORT).show();
				finish();
			}
		}
	}
	
	private class ButtonHandler implements View.OnClickListener {
		public void onClick(View v)	{
			handleButtonClick(v);
		}	
    }

	private void handleButtonClick(View v) {
		switch (v.getId()) {
		case BUTTON_ID_BLUECAM:
	    	startActivity(new Intent(this, BlueCamActivity.class));
			break;
		case BUTTON_ID_TOUCHRAUPE:
	    	startActivity(new Intent(this, TouchRaupeActivity.class));
			break;
		case BUTTON_ID_EXIT:
			finish();
			break;
		}
    }

}
